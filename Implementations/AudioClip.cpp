#include <Engine/AudioClip.h>

using namespace KillerEngine;
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
AudioClip::AudioClip(void)
:
_bufferID(0),
_data(nullptr)
{  }

AudioClip::~AudioClip(void)
{
	delete[] _data;
}

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
char* AudioClip::LoadWAV(string filename, int& channels, int& sampleRate, int& bps, int& size)
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

    for(int i = 0; i < totalSize; ++i)
    {
    	//Get the current buffer data
    	GetIndexRange(buffer, info, i, 4);
    	
    	if(strncmp(info, "fmt ", 4) == 0)
    	{
    		//Move the position past the title
    		i += 4;

    		//Get the number of channels
    		GetIndexRange(buffer, info, i+NUM_CHANNELS_OFFSET, CHANNELS_SIZE);
    		channels = ConvertToInt(info, CHANNELS_SIZE);

    		//Get the sample rate
    		GetIndexRange(buffer, info, i+SAMPLE_RATE_OFFSET, SAMPLE_RATE_SIZE);
    		sampleRate = ConvertToInt(info, SAMPLE_RATE_SIZE);

    		//Get the byte rate
    		GetIndexRange(buffer, info, i+BPS_OFFSET, BPS_SIZE);
    		bps = ConvertToInt(info, BPS_SIZE);
    	}

    	if(strncmp(info, "LIST", 4) == 0)
		{
			//Move the position past the title
			i += 4;
			
			//Get the size of the list
			GetIndexRange(buffer, info, i, LIST_SIZE);

			//Skip past the list
			i = i + ConvertToInt(info, LIST_SIZE);			
		}

    	if(strncmp(info, "data", 4) == 0)
    	{
    		//Move the position past the title
    		i += 4;

    		//Get the size of the data chunk
    		GetIndexRange(buffer, info, i, DATA_SIZE);
    		size = ConvertToInt(info, DATA_SIZE);
    		i = totalSize;
    	}
    }	

    return buffer;
}

//==========================================================================================================================
//
//Private Functions
//
//==========================================================================================================================
U32 AudioClip::_ConvertToInt(char* buffer, int len)
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

void AudioClip::_GetIndexRange(char* source, char* dest, int offset, int len)
{
	for(int i = 0; i < len; ++i)
	{
		dest[i] = source[offset + i];
	}
}