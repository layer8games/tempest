#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/AudioManager.h>

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
		void LoadWAV(string filename);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		const U32 GetBufferID(void) const
		{
			return _bufferID;
		}

		const U32 GetChannels(void) const
		{
			return _channels;
		}	

		const U32 GetSampleRate(void) const
		{
			return _sampleRate;
		}

		const U32 GetBPS(void) const
		{
			return _bps;
		}

		const U32 GetSize(void) const
		{
			return _size;
		}

		const U32 GetALFormat(void) const
		{
			return _alFormat;
		}

	private:
//==========================================================================================================================
//
//Private Functions
//
//==========================================================================================================================
		inline bool _IsBigEndian(void)
		{
			int a = 1;
			return !((char*)&a)[0];
		}

		U32 _ConvertToInt(char* buffer, int len);

		void _GetIndexRange(char* source, char* dest, int offset, int len);

		void _SetALFormat(void);

//==========================================================================================================================
//
//Data
//
//==========================================================================================================================
		//Header values for WAV file. Values are in bytes.
		enum HeaderOffsets
		{
			NUM_CHANNELS_OFFSET = 6,
			CHANNELS_SIZE = 2,
			SAMPLE_RATE_OFFSET = 8,
			SAMPLE_RATE_SIZE = 4,
			BPS_OFFSET = 18,
			BPS_SIZE = 2,
			LIST_SIZE = 2,
			DATA_SIZE = 4
		};

		U32   _bufferID;
		U32   _channels;
		U32	  _sampleRate;
		U32   _bps;
		U32   _size;
		U32   _alFormat;
		char* _data;
		
	};//end Class
}//end Namespace
