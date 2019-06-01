#include <Engine/AudioClip.h>
#include <iostream>

using namespace KillerEngine;
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
AudioClip::AudioClip(void)
:
_bufferID(0),
_channels(0),
_sampleRate(0),
_bps(0),
_size(0),
_alFormat(0),
_data(nullptr)
{  }

AudioClip::~AudioClip(void)
{
	if(_data != nullptr)
    {
        delete[] _data;
    }

    alDeleteBuffers(1, &_bufferID);
}

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
void AudioClip::LoadWAV(string filename)
{
	AudioManager::Instance();

    std::ifstream in(filename.c_str());

	//Get the total size of the file
	in.seekg(0, in.end);

    int totalSize = (int)in.tellg();

    in.seekg(0, in.beg);

    //Save the whole file to a buffer using read
    _data = new char[totalSize];

    in.read(_data, totalSize);

    in.close();

    //Extract info about the audio file.
    char info[4];

    for(int i = 0; i < totalSize; ++i)
    {
    	//Get the current buffer data
    	_GetIndexRange(_data, info, i, 4);
    	
    	if(strncmp(info, "fmt ", 4) == 0)
    	{
    		//Move the position past the title
    		i += 4;

    		//Get the number of channels
    		_GetIndexRange(_data, info, i+NUM_CHANNELS_OFFSET, CHANNELS_SIZE);
    		_channels = _ConvertToInt(info, CHANNELS_SIZE);

    		//Get the sample rate
    		_GetIndexRange(_data, info, i+SAMPLE_RATE_OFFSET, SAMPLE_RATE_SIZE);
    		_sampleRate = _ConvertToInt(info, SAMPLE_RATE_SIZE);

    		//Get the byte rate
    		_GetIndexRange(_data, info, i+BPS_OFFSET, BPS_SIZE);
    		_bps = _ConvertToInt(info, BPS_SIZE);
    	}

    	if(strncmp(info, "LIST", 4) == 0)
		{
			//Move the position past the title
			i += 4;
			
			//Get the size of the list
			_GetIndexRange(_data, info, i, LIST_SIZE);

			//Skip past the list
			i = i + _ConvertToInt(info, LIST_SIZE);			
		}

    	if(strncmp(info, "data", 4) == 0)
    	{
    		//Move the position past the title
    		i += 4;

    		//Get the size of the data chunk
    		_GetIndexRange(_data, info, i, DATA_SIZE);
    		_size = _ConvertToInt(info, DATA_SIZE);
    		
            //end loop early
            i = totalSize;
    	}
    }	

    _SetALFormat();

    alGenBuffers(1, &_bufferID);

    ALCenum error = alGetError();

    if(error != AL_NO_ERROR)
    {
        ErrorManager::Instance()->SetError(AUDIO, "AudioClip: LoadWAV: Failed to generate buffer! " + AudioManager::Instance()->GetALCerror(error));
    }

    alBufferData(_bufferID, _alFormat, _data, _size, _sampleRate);

    error = alGetError();

    if(error != AL_NO_ERROR)
    {
        ErrorManager::Instance()->SetError(AUDIO, "AudioClip: LoadWAV: Failed to loaded data into buffer! " + AudioManager::Instance()->GetALCerror(error));
    }
}

//==========================================================================================================================
//
//Private Functions
//
//==========================================================================================================================
U32 AudioClip::_ConvertToInt(char* buffer, int len)
{
	int a = 0;

	if(!_IsBigEndian())
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

void AudioClip::_SetALFormat(void)
{
    if(_channels == 1)
    {
        if(_bps == 8)
        {
            _alFormat = AL_FORMAT_MONO8;
        }
        else if(_bps == 16)
        {
            _alFormat = AL_FORMAT_MONO16;
        }
        else
        {
            _alFormat = 0;
        }
    }
    else
    {
        if(_bps == 8)
        {
            _alFormat = AL_FORMAT_STEREO8;
        }
        else if(_bps == 16)
        {
            _alFormat = AL_FORMAT_STEREO16;
        }
        else
        {
            _alFormat = 0;
        }   
    }   
}