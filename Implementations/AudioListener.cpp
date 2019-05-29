#include <Engine/AudioListener.h>

using namespace KillerEngine;
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
AudioListener::AudioListener(void)
:
_orientation(new F32[6]),
_position(0.0f, 0.0f, 1.0f),
_velocity(0.0f, 0.0f, 0.0f)
{
	AudioManager::Instance();

	SetOrientation(_orientation);
	SetPosition(_position);
	SetVelocity(_velocity);
}

AudioListener::~AudioListener(void)
{  }

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================

void AudioListener::SetOrientation(F32* orientation)
{
	_orientation = orientation;

	alListenerfv(AL_ORIENTATION, _orientation);

	ALCenum error = alGetError();
	if(error != AL_NO_ERROR)
	{
		ErrorManager::Instance()->SetError(AUDIO, "Oops! There was an error setting listener orientation\n");
	}
}

void AudioListener::SetPosition(const KM::Vector3& pos)
{
	_position = pos;

	alListener3f(AL_POSITION, _position[x], _position[y], _position[z]);
	
	ALCenum error = alGetError();
	if(error != AL_NO_ERROR)
	{
		ErrorManager::Instance()->SetError(AUDIO, "Oops! There was an error setting the listener pos\n");
	}
}

void AudioListener::SetVelocity(const KM::Vector3 vel)
{
	_velocity = vel;

	alListener3f(AL_VELOCITY, _velocity[x], _velocity[y], _velocity[z]);

	ALCenum error = alGetError();
	if(error != AL_NO_ERROR)
	{
		ErrorManager::Instance()->SetError(AUDIO, "Oops! There was an error setting listener velocity\n");
	}
}