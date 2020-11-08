#include "stdafx.h"
#include "Engine/AudioListener.h"

using namespace Tempest;

AudioListener::AudioListener(void)
:
_orientation{0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f},
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

const F32* AudioListener::GetOrientation(void) const
{
    return _orientation;
}

const TM::Vector3& AudioListener::GetPosition(void) const
{
    return _position;
}

void AudioListener::SetOrientation(F32* orientation)
{
    _orientation[0] = orientation[0];
    _orientation[1] = orientation[1];
    _orientation[2] = orientation[2];
    _orientation[3] = orientation[3];
    _orientation[4] = orientation[4];
    _orientation[5] = orientation[5];

    alListenerfv(AL_ORIENTATION, _orientation);

    ALCenum error = alGetError();
    if(error != AL_NO_ERROR)
    {
        ErrorManager::Instance()->SetError(AUDIO, "Oops! There was an error setting listener orientation\n");
    }
}

void AudioListener::SetPosition(const TM::Vector3& pos)
{
    _position = pos;

    alListener3f(AL_POSITION, _position.GetX(), _position.GetY(), _position.GetZ());
    
    ALCenum error = alGetError();
    if(error != AL_NO_ERROR)
    {
        ErrorManager::Instance()->SetError(AUDIO, "Oops! There was an error setting the listener pos\n");
    }
}

void AudioListener::SetPosition(F32 xVal, F32 yVal, F32 zVal)
{
    _position.Set(xVal, yVal, zVal);

    alListener3f(AL_POSITION, _position.GetX(), _position.GetY(), _position.GetZ());
    
    ALCenum error = alGetError();
    if(error != AL_NO_ERROR)
    {
        ErrorManager::Instance()->SetError(AUDIO, "Oops! There was an error setting the listener pos\n");
    }
}

const TM::Vector3& AudioListener::GetVelocity(void) const
{
    return _velocity;
}

void AudioListener::SetVelocity(const TM::Vector3 vel)
{
    _velocity = vel;

    alListener3f(AL_VELOCITY, _velocity.GetX(), _velocity.GetY(), _velocity.GetZ());

    ALCenum error = alGetError();
    if(error != AL_NO_ERROR)
    {
        ErrorManager::Instance()->SetError(AUDIO, "Oops! There was an error setting listener velocity\n");
    }
}

void AudioListener::SetVelocity(F32 xVal, F32 yVal, F32 zVal)
{
    _velocity.Set(xVal, yVal, zVal);

    alListener3f(AL_VELOCITY, _velocity.GetX(), _velocity.GetY(), _velocity.GetZ());

    ALCenum error = alGetError();
    if(error != AL_NO_ERROR)
    {
        ErrorManager::Instance()->SetError(AUDIO, "Oops! There was an error setting listener velocity\n");
    }
}