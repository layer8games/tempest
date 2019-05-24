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

//Header values for WAV file. Values are in bytes. 
	const U32 WAV_CHANNELS_OFFSET = 22;
	const U32 WAV_CHANNELS_SIZE = 2;

	const U32 WAV_SAMPLE_RATE_OFFSET = 24;
	const U32 WAV_SAMPLE_RATE_SIZE = 4;

	const U32 WAV_BYTE_RATE_OFFSET = 34;
	const U32 WAV_BYTE_RATE_SIZE = 2;

	const U32 WAV_DATA_OFFSET = 36;
	const U32 WAV_DATA_HEADER_SIZE = 4;
	const U32 WAV_DATA_SIZE_INFO_SIZE = 2;

	static void GetIndexRange(char* source, char* dest, int offset, int len)
	{
		for(int i = 0; i < len; ++i)
		{
			dest[i] = source[offset + i];
		}
	}

	//Location and size of data is found here: http://www.topherlee.com/software/pcm-tut-wavformat.html
	static char* LoadWAV(string filename, int& channels, int& sampleRate, int& bps, int& size)
	{
		std::ifstream in(filename.c_str());

		//Get the total size of the file
		in.seekg(0, in.end);
 
        int totalSize = (int)in.tellg();
 
        in.seekg(0, in.beg);
 
        //Save the whole file to a buffer using read
        char* buffer = new char[totalSize];
 
        in.read(buffer, totalSize);

        //Extract info about the audio file.
        char info[4];

        GetIndexRange(buffer, info, WAV_CHANNELS_OFFSET, WAV_CHANNELS_SIZE);

        channels = ConvertToInt(info, WAV_CHANNELS_SIZE);

        GetIndexRange(buffer, info, WAV_SAMPLE_RATE_OFFSET, WAV_SAMPLE_RATE_SIZE);

        sampleRate = ConvertToInt(info, WAV_SAMPLE_RATE_SIZE);

        GetIndexRange(buffer, info, WAV_BYTE_RATE_OFFSET, WAV_BYTE_RATE_SIZE);

        bps = ConvertToInt(info, WAV_BYTE_RATE_SIZE);

        //Extract the data itself.
        GetIndexRange(buffer, info, WAV_DATA_OFFSET, WAV_DATA_HEADER_SIZE);

        U32 POSITION = WAV_DATA_OFFSET + WAV_DATA_HEADER_SIZE;
        U32 moveTo = 0;

        while(strncmp(info, "data", 4) != 0)
		{
			if(strncmp(info, "LIST", 4) == 0)
			{
				GetIndexRange(buffer, info, POSITION, WAV_DATA_SIZE_INFO_SIZE);

				moveTo = ConvertToInt(info, WAV_DATA_SIZE_INFO_SIZE);			
			}
			//Set new position, move foreward one for rough check
			GetIndexRange(buffer, info, moveTo, WAV_DATA_HEADER_SIZE);
			POSITION = moveTo;
			moveTo = ++POSITION;
		}

		U32 DATA_SIZE_POSITION = POSITION - 1 + WAV_DATA_HEADER_SIZE;

		GetIndexRange(buffer, info, DATA_SIZE_POSITION, 4);

		size = ConvertToInt(info, 4);

        return buffer;
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