#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>

//===== OpenAL =====
#include <OpenAL/al.h>
#include <OpenAL/alc.h>

//===== STL Includes =====
#include <fstream>
#include <cstring>

namespace KillerEngine
{
	class AudioClip
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		AudioClip(void);

		~AudioClip(void);
//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
		const U32 GetBufferID(void)
		{
			return _bufferID;
		}

		//Header values for WAV file. Values are in bytes. 
	const U32 NUM_CHANNELS_OFFSET = 6;
	const U32 CHANNELS_SIZE = 2;
	
	const U32 SAMPLE_RATE_OFFSET = 8;
	const U32 SAMPLE_RATE_SIZE = 4;
	
	const U32 BPS_OFFSET = 18;
	const U32 BPS_SIZE = 2;

	const U32 LIST_SIZE = 2;
	const U32 DATA_SIZE = 4;

		char* LoadWAV(string filename, int& channels, int& sampleRate, int& bps, int& size);

	private:
//==========================================================================================================================
//
//Private Functions
//
//==========================================================================================================================
		inline bool IsBigEndian(void)
		{
			int a = 1;
			return !((char*)&a)[0];
		}

		U32 _ConvertToInt(char* buffer, int len);

		void _GetIndexRange(char* source, char* dest, int offset, int len);
//==========================================================================================================================
//
//Data
//
//==========================================================================================================================
		U32   _bufferID;
		char* _data;
		
	};//end Class
}//end Namespace
