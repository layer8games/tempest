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

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

namespace Tempest
{
// Macro to swap endian values
#define SWAP_32(value)                 \
        (((((unsigned short)value)<<8) & 0xFF00)   | \
         ((((unsigned short)value)>>8) & 0x00FF))

#define SWAP_16(value)                     \
        (((((unsigned int)value)<<24) & 0xFF000000)  | \
         ((((unsigned int)value)<< 8) & 0x00FF0000)  | \
         ((((unsigned int)value)>> 8) & 0x0000FF00)  | \
         ((((unsigned int)value)>>24) & 0x000000FF))



#define FAIL(X) { XPLMDebugString(X); free(mem); return 0; }

constexpr auto RIFF_ID = 0x46464952;		// 'RIFF'
constexpr auto FMT_ID = 0x20746D66;			// 'FMT '
constexpr auto DATA_ID = 0x61746164;		// 'DATA'


///	A wrapper around an OpenAL audio buffer. This stores a clip of audio that, after added to an AudioSource, can be played.
	class AudioClip
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
///	Calls AudioManager::Instance to make sure that the context and device has been set up in OpenAL before use. 
		TEMPEST_API AudioClip(void);


///	Calls delete[] on the data array to free that resource. Deletes the buffer handle from OpenAL. 
		TEMPEST_API ~AudioClip(void);
//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
///	Reads a .wav file from the hard drive. Parses over the file extracting needed information from the headers, then saves
///	the audio file in a buffer that is registered with OpenAL. This is used later to actually play back the file. This is
///	where all the magic happens. 
///	\param filename is the path to the file to be read. Should live in ../Assets/Audio by convention.
		TEMPEST_API void LoadWAV2(string filename);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
///	Returns the buffer handle from OpenAL. 
		inline const U32 GetBufferID(void) const
		{
			return _bufferID;
		}

	private:
//==========================================================================================================================
//
//Private Functions
//
//==========================================================================================================================
///	 Used to test how the bits of an int are arranged in the internal format of the machine the code is running on. Returns 
///	 true if the machine is Big Endian, false if it is Little Endian. https://en.wikipedia.org/wiki/Endianness
		inline bool _IsBigEndian(void)
		{
			int a = 1;
			return !((char*)&a)[0];
		}

///	Converts a bit buffer of a set length into its integar equivalent.
///	\param buffer are the bits to convert. 
///	\param len is the size of the buffer. This must match what you are expecting! 
		U32 _ConvertToInt(char* buffer, int len);

///	An ad hoc solution to array slicing. It returns into the destination the elements of the source array from an offset by
///	a set amount. For example, if source is an array with 100 elements, and offset is 10, with len being 10, then dest will
///	be source elements 10 through 20. 
///	\param source is the original array we are slicing into.
///	\param dest is where the sub array from source will be stores. 
///	\param offset is how far into source to start slicing. 
///	\param len is how many elements past offset to slice into dest.
		void _GetIndexRange(char* source, char* dest, int offset, int len);

		char* _FindChunk(char* fileBegin, char* fileEnd, S32 desiredID, S32 swapped);

		char* _ChunkEnd(char* chunkStart, S32 swapped);

//==========================================================================================================================
//
//Data
//
//==========================================================================================================================

///	\enum Header values for WAV file. Values are in bytes. These values are pretty rigid and will only work on .wav files.
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

		struct ChunkHeader
		{
			S32 id;
			S32 size;
		};

		struct FormatInfo
		{
			S16 format;
			S16 numChannels;
			S32 sampleRate;
			S32 byteRate;
			S16 blockAllign;
			S16 bitsPerSample;
		};

		U32   _bufferID;		///< OpenAL buffer handle. This is the ID OpenAL uses, similar to OpenGL's handles. 
		char* _data;			///< Data buffer for the file. This is the full file, headers included.
		
	};//end Class
	typedef shared_ptr<AudioClip> p_AudioClip;
}//end Namespace
