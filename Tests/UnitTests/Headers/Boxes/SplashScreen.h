/*==========================================================================================================================
Opening Splash screen prototype

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
==========================================================================================================================*/
#pragma once

//Killer1 includes
#include <Engine/Atom.h>
#include <Engine/LevelManager.h>
#include <Engine/WinProgram.h>
#include <Engine/Level.h>
#include <Engine/Timer.h>
#include <Engine/TextureManager.h>
#include <Engine/FontManager.h>
#include <Engine/Text.h>
#include <Engine/Color.h>
#include <Engine/Point.h>
#include <Engine/Controller.h>
#include <Engine/Engine.h>

//===== OpenAL =====
#include <OpenAL/al.h>
#include <OpenAL/alc.h>

namespace KE = KillerEngine;
namespace KM = KillerMath;

//=====Box includes=====
#include <Boxes/Box.h>

//===== remove later =====
#include <fstream>
#include <iostream>
#include <cstring>

namespace Boxes 
{

	class SplashScreen: public KE::Level
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================		
		SplashScreen(void);
		
		~SplashScreen(void);

//==========================================================================================================================
//
//Virtual functions
//
//==========================================================================================================================		
		void v_InitLevel(U32 id, S32 w, S32 h, const KE::Color& c);
		
		void v_Update(void);
	
	private:
//==========================================================================================================================
//
//Members
//
//==========================================================================================================================		
		Box 	 _red;
		Box 	 _green;
		Box 	 _blue;
		KE::Text _mainTitle;

		ALCdevice* _device;
		ALCcontext* _context;
		U32 _sourceID;
		U32 _bufferID;
		char* _data;
	};

	//returns a list of audio devices. Part of OpenAL tests
	static void list_audio_devices(const ALCchar* devices)
	{
		const ALCchar* device = devices, *next = devices + 1;
		size_t len = 0;

		fprintf(stdout, "Devices list:\n");
		fprintf(stdout, "-----------\n");

		while(device && *device != '\0' && next && *next != '\0')
		{
			fprintf(stdout, "%s\n", device);
			len = strlen(device);
			device += (len + 1);
			next += (len + 2);
		}

		fprintf(stdout, "-----------\n");
	}

	//check big vs little endian machine
	static bool IsBigEndian(void)
	{
		int a = 1;
		return !((char*)&a)[0];
	}

	static int ConvertToInt(char* buffer, int len)
	{
		int a = 0;

		if(!IsBigEndian())
		{
			for(int i = 0; i < len; ++i)
			{
				((char*)&a)[i] = buffer[i];
			}
		}
		else
		{
			for(int i = 0; i < len; ++i)
			{
				((char*)&a)[3-i] = buffer[i];
			}
		}

		return a;
	}

	//Location and size of data is found here: http://www.topherlee.com/software/pcm-tut-wavformat.html
	static char* LoadWAV(string filename, int& channels, int& sampleRate, int& bps, int& size)
	{
		char buffer[4];

		std::ifstream in(filename.c_str());
		in.read(buffer, 4);

		if(strncmp(buffer, "RIFF", 4) != 0)
		{
			std::cout << "Error here, not a valid WAV file, RIFF not found in header\n This was found instead: "
					  << buffer[0] << buffer[1] << buffer[2] << buffer[3] << std::endl;
		}

		in.read(buffer, 4);//size of file. Not used. Read it to skip over it.  
		
		in.read(buffer, 4);//Format, should be WAVE

		if(strncmp(buffer, "WAVE", 4) != 0)
		{
			std::cout << "Error here, not a valid WAV file, WAVE not found in header.\n This was found instead: "
					  << buffer[0] << buffer[1] << buffer[2] << buffer[3] << std::endl;
		}

		in.read(buffer, 4);//Format Space Marker. should equal fmt (space)

		if(strncmp(buffer, "fmt ", 4) != 0)
		{
			std::cout << "Error here, not a valid WAV file, Format Marker not found in header.\n This was found instead: "
					  << buffer[0] << buffer[1] << buffer[2] << buffer[3] << std::endl;
		}

		in.read(buffer, 4);//Length of format data. Should be 16 for PCM, meaning uncompressed.

		if(ConvertToInt(buffer, 4) != 16)
		{
			std::cout << "Error here, not a valid WAV file, format length wrong in header.\n This was found instead: "
					  << ConvertToInt(buffer, 4) << std::endl;
		}

		in.read(buffer, 2);//Type of format, 1 = PCM

		if(ConvertToInt(buffer, 2) != 1)
		{
			std::cout << "Error here, not a valid WAV file, file not in PCM format.\n This was found instead: "
					  << ConvertToInt(buffer, 4) << std::endl;
		}

		in.read(buffer, 2);//Get number of channels. 

		//Assume at this point that we are dealing with a WAV file. This value is needed by OpenAL
		channels = ConvertToInt(buffer, 2);

		in.read(buffer, 4);//Get sampler rate. 

		sampleRate = ConvertToInt(buffer, 4);

		//Skip Byte Rate and Block Align. Maybe use later?
		in.read(buffer, 4);//Block Allign
		in.read(buffer, 2);//ByteRate

		in.read(buffer, 2);//Get Bits Per Sample

		bps = ConvertToInt(buffer, 2);

		//Skip character data, which marks the start of the data that we care about. 
		in.read(buffer, 4);//"data" chunk. 

		in.read(buffer, 4); //Get size of the data

		size = ConvertToInt(buffer, 4);

		if(size < 0)
		{
			std::cout << "Error here, not a valid WAV file, size of file reports 0.\n This was found instead: "
					  << size << std::endl;
		}

		char* data = new char[size];

		in.read(data, size);//Read audio data into buffer, return.

		//in.close();

		return data;	
	}

	static U32 GetALFormat(U32 channels, U32 bps)
	{
		if(channels == 1)
		{
			if(bps == 8)
			{
				std::cout << "mono8\n";
				return AL_FORMAT_MONO8;
			}
			else if(bps == 16)
			{
				std::cout << "mono16\n";
				return AL_FORMAT_MONO16;
			}
			else
			{
				std::cout << "0000\n";
				return 0;
			}
		}
		else
		{
			if(bps == 8)
			{
				std::cout << "stereo8\n";
				return AL_FORMAT_STEREO8;
			}
			else if(bps == 16)
			{
				std::cout << "stereo16\n";
				return AL_FORMAT_STEREO16;
			}
			else
			{
				std::cout << "000\n";
				return 0;
			}	
		}
	}

}//End namespace