#include <Engine/AudioManager.h>

using namespace KillerEngine;
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
AudioManager::AudioManager(void)
:
_device(nullptr),
_context(nullptr)
{
	ALCenum error;

	_device = alcOpenDevice(NULL);

	error = alGetError();

	if(!_device || error != AL_NO_ERROR)
	{
		ErrorManager::Instance()->SetError(AUDIO, "AudioManager::Constructor: Unable to open device! " + GetALCerror(error));
	}

	//Create a context and make it active
	_context = alcCreateContext(_device, NULL);

	error = alGetError();

	if(!_context || error != AL_NO_ERROR)
	{
		ErrorManager::Instance()->SetError(AUDIO, "AudioManager::Constructor: Unable to create context! " + GetALCerror(error));
	}

	//Make current
	if(!alcMakeContextCurrent(_context))
	{
		ErrorManager::Instance()->SetError(AUDIO, "AudioManager::Constructor: Unable to make context current! " + GetALCerror(error));
	}

//==========================================================================================================================
//Move to listener later
//==========================================================================================================================
	//Configure listener
	ALfloat listernOrientation[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };

	alListener3f(AL_POSITION, 0.0f, 0.0f, 1.0f);
	error = alGetError();

	if(error != AL_NO_ERROR)
	{
		ErrorManager::Instance()->SetError(AUDIO, "AudioManager::Constructor: There was an error setting the listener pos! " + GetALCerror(error));
	}

	alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f);

	error = alGetError();
	if(error != AL_NO_ERROR)
	{
		ErrorManager::Instance()->SetError(AUDIO, "AudioManager::Constructor: There was an error setting listener velocity! " + GetALCerror(error));
	}

	alListenerfv(AL_ORIENTATION, listernOrientation);
	
	error = alGetError();
	if(error != AL_NO_ERROR)
	{
		ErrorManager::Instance()->SetError(AUDIO, "AudioManager::Constructor: There was an error setting listener orientation! " + GetALCerror(error));
	}

/*
	TODO: not sure where this code should live. It could possible be put into WinProgram, but maybe it should stay here.
		  This check should happen around here though, or at least before here. This would allow for the user to select
		  which audio device they want the sound of the game to come through. Not a lot of games do this... maybe its
		  not something which should be included. This should be called after the device is created, but before the
		  context is made active

		  If you decide to get rid of this code, then it should at least be saved as a gem. 

	//Get device list
	ALboolean enumeration;
	enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");

	if(enumeration == AL_FALSE)
	{
		std::cout << "enumeration not supported\n";
	}
	else
	{
		//Could get a list for a tool here, letting the user select
		//which audio device they want to use. This is purely optional, 
		//passing NULL to alcOpenDevice will select the devault one,
		//or maybe create context is what selects that. Look it up. 
		//list_audio_devices(alcGetString(NULL, ALC_DEVICE_SPECIFIER));
	}

	error = alGetError();

	if(error != AL_NO_ERROR)
	{
		std::cout << "Oops! There was an error checking for devices\n";
	}

Function:

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

*/
}

AudioManager::~AudioManager(void)
{
	alcDestroyContext(_context);
	alcCloseDevice(_device);
}

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
//==========================================================================================================================
//Singleton
//==========================================================================================================================
shared_ptr<AudioManager> AudioManager::_instance = nullptr;

shared_ptr<AudioManager> AudioManager::Instance(void)
{
	if(_instance == nullptr)
	{
		_instance = shared_ptr<AudioManager>(new AudioManager());
	}

	return _instance;
}

string AudioManager::GetALCerror(ALCenum error)
{
	switch (error) 
	{
	  case AL_NO_ERROR: 
	  	return "AL_NO_ERROR";
	  case AL_INVALID_NAME: 
	  	return "AL_INVALID_NAME";
	  case AL_INVALID_ENUM: 
	  	return "AL_INVALID_ENUM";
	  case AL_INVALID_VALUE: 
	  	return "AL_INVALID_VALUE";
	  case AL_INVALID_OPERATION: 
	  	return "AL_INVALID_OPERATION";
	  case AL_OUT_OF_MEMORY: 
	  	return "AL_OUT_OF_MEMORY";
	  default:
	    return "Unknown error code";
	}
}