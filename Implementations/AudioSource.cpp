#include "stdafx.h"
#include <Engine/AudioSource.h>

using namespace Tempest;
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
AudioSource::AudioSource(void)
:
_looping(false),
_sourceID(0),
_pitch(1.0f),
_gain(1.0f),
_position(0.0f, 0.0f, 0.0f),
_velocity(0.0f, 0.0f, 0.0f),
_clip(nullptr)
{
    AudioManager::Instance();

    ALCenum error = alGetError();

    //generate sources
    alGenSources(1, &_sourceID);

    error = alGetError();
    if(error != AL_NO_ERROR)
    {
        ErrorManager::Instance()->SetError(AUDIO, "AudioSource::Constructor: There was an error generating a source! " + AudioManager::Instance()->GetALCerror(error));
    }

    SetPitch(_pitch);

    SetGain(_gain);

    SetPosition(_position);

    SetVelocity(_velocity);

    SetLooping(_looping);
}

AudioSource::~AudioSource(void)
{
    _clip = nullptr;
    alDeleteSources(1, &_sourceID);
}

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
bool AudioSource::GetPlaying(void) const
{
    ALint state = _GetPlayState();

    if(state == AL_PLAYING)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void AudioSource::Play(void)
{
    ALint state = _GetPlayState();
    
    if(_clip != nullptr && state == AL_INITIAL || state == AL_STOPPED || state == AL_PAUSED)
    {
        alSourcePlay(_sourceID);

        ALCenum error = alGetError();
        if(error != AL_NO_ERROR)
        {
            ErrorManager::Instance()->SetError(AUDIO, "AudioSource::Play: Unable to play clip! " + AudioManager::Instance()->GetALCerror(error));
        }
    }
}

void AudioSource::Stop(void)
{
    ALint state = _GetPlayState();
    
    if(_clip != nullptr && state == AL_PLAYING)
    {
        alSourceStop(_sourceID);
        
        ALCenum error = alGetError();
        if(error != AL_NO_ERROR)
        {
            ErrorManager::Instance()->SetError(AUDIO, "AudioSource::Pause: Unable to stop clip! " + AudioManager::Instance()->GetALCerror(error));
        }
    }
}

void AudioSource::Pause(void)
{
    ALint state = _GetPlayState();
    
    if(_clip != nullptr && state == AL_PLAYING)
    {
        alSourcePause(_sourceID);
        
        ALCenum error = alGetError();
        if(error != AL_NO_ERROR)
        {
            ErrorManager::Instance()->SetError(AUDIO, "AudioSource::Pause: Unable to pause clip! " + AudioManager::Instance()->GetALCerror(error));
        }
    }
}

void AudioSource::Restart(void)
{
    alSourcePlay(_sourceID);

    ALCenum error = alGetError();
    if(error != AL_NO_ERROR)
    {
        ErrorManager::Instance()->SetError(AUDIO, "AudioSource::Play: Unable to play clip! " + AudioManager::Instance()->GetALCerror(error));
    }
}

void AudioSource::AddClip(shared_ptr<AudioClip> clip)
{
    _clip = clip;

    if(_clip->GetBufferID() <= 0)
    {
        ErrorManager::Instance()->SetError(AUDIO, "AudioSource::AddClip: Clip buffer has no data!");
        return;
    }

    alSourcei(_sourceID, AL_BUFFER, _clip->GetBufferID());

    ALCenum error = alGetError();
    if(error != AL_NO_ERROR)
    {
        ErrorManager::Instance()->SetError(AUDIO, "AudioSource::AddClip: Unable to add clip to source! alSourcei failed! " + AudioManager::Instance()->GetALCerror(error));
    }
}

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
void AudioSource::SetLooping(bool state)
{
    _looping = state;
    alSourcei(_sourceID, AL_LOOPING, _looping);

    ALCenum error = alGetError();
    if(error != AL_NO_ERROR)
    {
        ErrorManager::Instance()->SetError(AUDIO, "AudioManager::Constructor: There was an error setting source looping! " + AudioManager::Instance()->GetALCerror(error));
    }
}

void AudioSource::SetPitch(F32 pitch)
{
    _pitch = pitch;
    alSourcef(_sourceID, AL_PITCH, _pitch);

    ALCenum error = alGetError();
    if(error != AL_NO_ERROR)
    {
        ErrorManager::Instance()->SetError(AUDIO, "AudioManager::Constructor: There was an error setting source pitch! " + AudioManager::Instance()->GetALCerror(error));
    }
}

void AudioSource::SetGain(F32 gain)
{
    _gain = gain;
    alSourcef(_sourceID, AL_GAIN, _gain);

    ALCenum error = alGetError();
    if(error != AL_NO_ERROR)
    {
        ErrorManager::Instance()->SetError(AUDIO, "AudioManager::Constructor: There was an error setting source gain! " + AudioManager::Instance()->GetALCerror(error));
    }
}

void AudioSource::SetPosition(const TM::Vector3& pos)
{
    _position = pos;
    alSource3f(_sourceID, AL_POSITION, _position.x, _position.y, _position.z);

    ALCenum error = alGetError();
    if(error != AL_NO_ERROR)
    {
        ErrorManager::Instance()->SetError(AUDIO, "AudioManager::Constructor: There was an error setting source pos! " + AudioManager::Instance()->GetALCerror(error));
    }
}

void AudioSource::SetPosition(F32 xVal, F32 yVal, F32 zVal)
{
    _position.x = xVal;
    _position.y = yVal;
    _position.z = zVal;
    alSource3f(_sourceID, AL_POSITION, _position.x, _position.y, _position.z);

    ALCenum error = alGetError();
    if(error != AL_NO_ERROR)
    {
        ErrorManager::Instance()->SetError(AUDIO, "AudioManager::Constructor: There was an error setting source pos! " + AudioManager::Instance()->GetALCerror(error));
    }
}

void AudioSource::SetVelocity(const TM::Vector3& vel)
{
    _velocity = vel;
    alSource3f(_sourceID, AL_VELOCITY, _velocity.x, _velocity.y, _velocity.z);

    ALCenum error = alGetError();
    if(error != AL_NO_ERROR)
    {
        ErrorManager::Instance()->SetError(AUDIO, "AudioManager::Constructor: There was an error setting source velocity! " + AudioManager::Instance()->GetALCerror(error));
    }
}

void AudioSource::SetVelocity(F32 xVal, F32 yVal, F32 zVal)
{
    _velocity.x = xVal;
    _velocity.y = yVal;
    _velocity.z = zVal;
    alSource3f(_sourceID, AL_VELOCITY, _velocity.x, _velocity.y, _velocity.z);

    ALCenum error = alGetError();
    if(error != AL_NO_ERROR)
    {
        ErrorManager::Instance()->SetError(AUDIO, "AudioManager::Constructor: There was an error setting source velocity! " + AudioManager::Instance()->GetALCerror(error));
    }
}

ALint AudioSource::_GetPlayState(void) const
{
    ALint state;
    alGetSourcei(_sourceID, AL_SOURCE_STATE, &state);
    return state;
}