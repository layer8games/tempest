#pragma once

//=====Engine Includes=====
#include "stdafx.h"
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

    constexpr auto RIFF_ID = 0x46464952;
    constexpr auto FMT_ID = 0x20746D66;
    constexpr auto DATA_ID = 0x61746164;

    class AudioClip
    {
    public:
        TEMPEST_API AudioClip(void);

        TEMPEST_API ~AudioClip(void);

        TEMPEST_API void LoadWAV2(string filename);

        inline const U32 GetBufferID(void) const
        {
            return _bufferID;
        }

    private:
        inline bool _IsBigEndian(void)
        {
            int a = 1;
            return !((char*)&a)[0];
        }

        U32 _ConvertToInt(char* buffer, int len);

        void _GetIndexRange(char* source, char* dest, int offset, int len);

        char* _FindChunk(char* fileBegin, char* fileEnd, S32 desiredID, S32 swapped);

        char* _ChunkEnd(char* chunkStart, S32 swapped);

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

        U32   _bufferID;		
        char* _data;			
        
    };//end Class
    typedef shared_ptr<AudioClip> p_AudioClip;
}//end Namespace
