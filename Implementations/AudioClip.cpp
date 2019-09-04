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
{
    AudioManager::Instance();
}

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

	//AudioManager::Instance();
	

	std::ifstream in(filename.c_str(), std::ios::in);

	if(!in)
	{
		ErrorManager::Instance()->SetError(AUDIO, "AudioClip::LoadWAV: Unable to open file " + filename);
		return;
	}

	//Get the total size of the file
	in.seekg(0, in.end);

    int totalSize = (int)in.tellg();

	std::cout << "total size = " << totalSize << std::endl;

    in.seekg(0, in.beg);

    //Save the whole file to a buffer using read
    //char*  tmpData = new char[totalSize];
	_data = new char[totalSize];

    //in.read(tmpData, totalSize);
	in.read(_data, totalSize);

    //in.close();

	//print data for testing
	//for(int i = 0; i < totalSize; ++i)
	//{
	//	std::cout << tmpData[i];
	//}

	//std::cout << std::endl;

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

		in.close();
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

	std::cout << "error == " << error << std::endl;

    if(error != AL_NO_ERROR)
    {
        ErrorManager::Instance()->SetError(AUDIO, "AudioClip: LoadWAV: Failed to load data into buffer! " + AudioManager::Instance()->GetALCerror(error));
    }
}

void AudioClip::LoadWAV2(string filename)
{
	//first, open file
	FILE* fi;
	errno_t err;
		
	err = fopen_s(&fi, filename.c_str(), "rb");
	
	if(fi == NULL || err != 0)
	{
		ErrorManager::Instance()->SetError(AUDIO, "AudioClip::LoadWav2: failed to load file - could not open");
		return;
	}

	fseek(fi, 0, SEEK_END);
	S32 fileSize = ftell(fi);
	fseek(fi, 0, SEEK_SET);

	char* mem = (char*) malloc(fileSize);

	if(mem == NULL)
	{
		ErrorManager::Instance()->SetError(AUDIO, "AudioClip::LoadWav2: failed to load file - not enough memory");
		fclose(fi);
		return;
	}

	if(fread(mem, 1, fileSize, fi) != fileSize)
	{
		ErrorManager::Instance()->SetError(AUDIO, "AudioClip::LoadWav2: failed to load file - could not read file");
		free(mem);
		fclose(fi);
		return;
	}

	fclose(fi);
	
	char* memEnd = mem + fileSize;

	//second, find the RIFF chunk, read the header. 
	S32 swapped = 0;

	char* riff = _FindChunk(mem, memEnd, RIFF_ID, 0);
	if(riff == NULL)
	{
		riff = riff = _FindChunk(mem, memEnd, RIFF_ID, 1);
		if(riff)
		{
			swapped = 1;
		}
		else
		{
			ErrorManager::Instance()->SetError(AUDIO, "AudioClip::LoadWav2: Could not find riff chunk");
			return;
		}
	}

	if(riff[0] != 'W' ||
	   riff[1] != 'A' ||
	   riff[2] != 'V' ||
	   riff[3] != 'E')
	{
		ErrorManager::Instance()->SetError(AUDIO, "AudioClip::LoadWav2: Could not find WAVE signature in file");
		return;
	}

	char* format = _FindChunk(riff+4, _ChunkEnd(riff, swapped), FMT_ID, swapped);
	if(format == NULL)
	{
		ErrorManager::Instance()->SetError(AUDIO, "AudioClip::LoadWav2: Could not find FMT chunc in file");
		return;
	}

	FormatInfo* fmt = (FormatInfo*)format;

	if(swapped)
	{
		fmt->format = SWAP_16(fmt->format);
		fmt->numChannels = SWAP_16(fmt->numChannels);
		fmt->sampleRate = SWAP_16(fmt->sampleRate);
		fmt->byteRate = SWAP_16(fmt->byteRate);
		fmt->blockAllign = SWAP_16(fmt->blockAllign);
		fmt->bitsPerSample = SWAP_16(fmt->bitsPerSample);
	}

	if(fmt->format != 1)
	{
		ErrorManager::Instance()->SetError(AUDIO, "AudioClip::LoadWav2: file is not PCM format data");
		return;
	}

	if(fmt->numChannels != 1 && fmt->numChannels != 2)
	{
		ErrorManager::Instance()->SetError(AUDIO, "AudioClip::LoadWav2: Must have mono or stereo sound");
		return;
	}

	if(fmt->bitsPerSample != 8 && fmt->bitsPerSample != 16)
	{
		ErrorManager::Instance()->SetError(AUDIO, "AudioClip::LoadWav2: Must have 8 or 16 bit sound");
		return;
	}

	char* data = _FindChunk(riff+4, _ChunkEnd(riff, swapped), DATA_ID, swapped);
	if(data == NULL)
	{
		ErrorManager::Instance()->SetError(AUDIO, "AudioClip::LoadWav2: Could not find the DATA chunk");
		return;
	}

	S32 sampleSize = fmt->numChannels * fmt->bitsPerSample / 8;
	S32 dataBytes = _ChunkEnd(data, swapped) - data;
	S32 dataSamples = dataBytes / sampleSize;

	// endian swap if audio is 16 bit
	if(fmt->bitsPerSample == 16 && swapped)
	{
		S16* ptr = (S16*)data;
		S32 words = dataSamples * fmt->numChannels;

		while(words--)
		{
			*ptr = SWAP_16(*ptr);
			++ptr;
		}
	}

	// OpenAL Calls, we have the data now.
	// Consider more advanced error checking here, using the OpenAL GetError calls
	_bufferID = 0; 
	alGenBuffers(1, &_bufferID);
	if(_bufferID == 0)
	{
		ErrorManager::Instance()->SetError(AUDIO, "AudioClip::LoadWav2: Unable to create buffer in OpenAL");
		return;
	}

	alBufferData(_bufferID, fmt->bitsPerSample == 16 ? 
							(fmt->numChannels == 2 ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16) :
							(fmt->numChannels == 2 ? AL_FORMAT_STEREO8 : AL_FORMAT_MONO8),
				 data, dataBytes, fmt->sampleRate);

	free(mem);
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

char* AudioClip::_FindChunk(char* fileBegin, char* fileEnd, S32 desiredID, S32 swapped)
{
	while(fileBegin < fileEnd)
	{
		ChunkHeader* header = (ChunkHeader*)fileBegin;
		
		if(header->id == desiredID && !swapped)
		{
			return fileBegin + sizeof(ChunkHeader);
		}

		if(header->id == SWAP_32(desiredID) && swapped)
		{
			return fileBegin + sizeof(ChunkHeader);
		}

		S32 chunkSize = swapped ? SWAP_32(header->size) : header->size;
		char* next = fileBegin + chunkSize + sizeof(ChunkHeader);

		if(next > fileEnd || next <= fileBegin)
		{
			return NULL;
		}

		fileBegin = next;
	}
	return NULL;
}

char* AudioClip::_ChunkEnd(char* chunkStart, S32 swapped)
{
	ChunkHeader* header = (ChunkHeader*)(chunkStart - sizeof(ChunkHeader));
	return chunkStart + (swapped ? SWAP_32(header->size) : header->size);
}