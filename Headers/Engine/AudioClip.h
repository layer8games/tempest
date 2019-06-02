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
/*!
	A wrapper around an OpenAL audio buffer. This stores a clip of audio that, after added to an AudioSource, can be played.
*/
	class AudioClip
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
/*!
	Calls AudioManager::Instance to make sure that the context and device has been set up in OpenAL before use. 
*/
		AudioClip(void);

/*!
	Calls delete[] on the data array to free that resource. Deletes the buffer handle from OpenAL. 
*/
		~AudioClip(void);
//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
/*!
	Reads a .wav file from the hard drive. Parses over the file extracting needed information from the headers, then saves
	the audio file in a buffer that is registered with OpenAL. This is used later to actually play back the file. This is
	where all the magic happens. 
	\param filename is the path to the file to be read. Should live in ../Assets/Audio by convention.
*/
		void LoadWAV(string filename);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
/*!
	Returns the buffer handle from OpenAL. 
*/
		const U32 GetBufferID(void) const
		{
			return _bufferID;
		}

/*!
	Returns the number of channels the audio file has. 0 by default. Usually this will be 1 for mono and 2 for stereo. 
*/
		const U32 GetChannels(void) const
		{
			return _channels;
		}	

/*!
	Returns the sample rate the audio file has. 0 by default. This represents the frequency of the audio file, usually it 
	will be 44100 for most .wav files. 
*/
		const U32 GetSampleRate(void) const
		{
			return _sampleRate;
		}

/*!
	Returns the bit rate of the file. 0 by default. This will be either 8 or 16, usually.
*/
		const U32 GetBPS(void) const
		{
			return _bps;
		}

/*!
	Returns the size in bits of the audio part of the file (does not include headers). 0 by default. This number should be
	pretty big.
*/
		const U32 GetSize(void) const
		{
			return _size;
		}

/*!
	Returns the internal format that OpenAL uses to idenify the clip. Will be 0 by default. 
*/
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
/*!
	 Used to test how the bits of an int are arranged in the internal format of the machine the code is running on. Returns 
	 true if the machine is Big Endian, false if it is Little Endian. https://en.wikipedia.org/wiki/Endianness
*/
		inline bool _IsBigEndian(void)
		{
			int a = 1;
			return !((char*)&a)[0];
		}

/*!
	Converts a bit buffer of a set length into its integar equivalent.
	\param buffer are the bits to convert. 
	\param len is the size of the buffer. This must match what you are expecting! 
*/
		U32 _ConvertToInt(char* buffer, int len);

/*!
	An ad hoc solution to array slicing. It returns into the destination the elements of the source array from an offset by
	a set amount. For example, if source is an array with 100 elements, and offset is 10, with len being 10, then dest will
	be source elements 10 through 20. 
	\param source is the original array we are slicing into.
	\param dest is where the sub array from source will be stores. 
	\param offset is how far into source to start slicing. 
	\param len is how many elements past offset to slice into dest.
*/
		void _GetIndexRange(char* source, char* dest, int offset, int len);

/*!
	Reads the internal members to determine what the AL Format is. If no file has been loaded, then _alFormat will be set to 0;
*/
		void _SetALFormat(void);

//==========================================================================================================================
//
//Data
//
//==========================================================================================================================

/*!
	Header values for WAV file. Values are in bytes. These values are pretty rigid and will only work on .wav files.
*/
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

		U32   _bufferID;		///< OpenAL buffer handle. This is the ID OpenAL uses, similar to OpenGL's handles. 
		U32   _channels;		///< Number of channels the audio file has. 
		U32	  _sampleRate;		///< Sample play rate for the file. 
		U32   _bps;				///< Byte rate for the file. 
		U32   _size;			///< Size of the audio portion of the file. 
		U32   _alFormat;		///< Format marker OpenAL uses to determine how to play the file. 
		char* _data;			///< Data buffer for the file. This is the full file, headers included.
		
	};//end Class
}//end Namespace
