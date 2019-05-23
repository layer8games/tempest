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

/*

here are the headers you need:

R I F F ~ 4 ü   W A V E f m t                D ¼      ▒          L I S T R      I N F O I A R T        K o m i k u     I C M T í       U R L :   h t t p : / / f r e e m u s i c a r c h i v e . o r g / m u s i c / K o m i k u / C a p t a i n _ G l o u g l o u s _ I n c r e d i b l e _ W e e k _ S o u n d t r a c k / S k a t e
 C o m m e n t s :   h t t p : / / f r e e m u s i c a r c h i v e . o r g /
 C u r a t o r :
 C o p y r i g h t :       I C R D        2 0 1 8 - 0 7 - 1 4 T 0 4 : 3 7 : 0 5   I G N R        E l e c t r o n i c     I N A M        S k a t e   I P R D .       C a p t a i n   G l o u g l o u ' s   I n c r e d i b l e   W e e k   S o u n d t r a c k   I P R T        4   I S F T        L a v f 5 8 . 2 7 . 1 0 3   d a t a 

If it does not say "data" then you need to move along until it does. 

*/

	//Location and size of data is found here: http://www.topherlee.com/software/pcm-tut-wavformat.html
	static char* LoadWAV(string filename, int& channels, int& sampleRate, int& bps, int& size)
	{
		std::ifstream in(filename.c_str());		

		char buffer[4];

		in.read(buffer, 4);//Chunk ID

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
		//Gotta check here for the right thing.  
		in.read(buffer, 4);//"data" chunk. 

		while(strncmp(buffer, "data", 4) != 0)
		{
			if(strncmp(buffer, "LIST", 4) != 0)
			{
				in.read(buffer, 2);
				int goTo = ConvertToInt(buffer, 2);
				//error here. need to find out how to skip goTo bytes
				in.seekg(in.tellg(), goTo);
			}

			in.read(buffer, 4);
			std::cout << buffer[0] << buffer[1] << buffer[2] << buffer[3] << std::endl;

		}

		if(strncmp(buffer, "data", 4) != 0)
		{
			std::cout << "Error here, may be extra data in your file\n" 
					  << buffer[0] << buffer[1] << buffer[2] << buffer[3] << std::endl;
		}

		in.read(buffer, 4); //Get size of the data

		size = ConvertToInt(buffer, 4);

		std::cout << "size: " << size << std::endl;

		if(size < 0)
		{
			std::cout << "Error here, not a valid WAV file, size of file reports 0.\n This was found instead: "
					  << size << std::endl;
		}


		char* data = new char[1];

		//in.read(data, size);//Read audio data into buffer, return.

		in.close();

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