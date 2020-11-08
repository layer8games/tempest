#pragma once

#include "stdafx.h"
#include "Engine/Atom.h"
#include "Engine/AudioManager.h"
#include "Engine/Vector3.h"
#include "Engine/AudioClip.h"

namespace TM = TempestMath;

namespace Tempest
{
    class AudioClip;
    typedef shared_ptr<AudioClip> p_AudioClip;

    class AudioSource
    {
    public:
        TEMPEST_API AudioSource(void);

        TEMPEST_API ~AudioSource(void);

        TEMPEST_API void Play(void);

        TEMPEST_API void Stop(void);

        TEMPEST_API void Pause(void);

        TEMPEST_API void Restart(void);

        TEMPEST_API void AddClip(shared_ptr<AudioClip> clip);

        TEMPEST_API bool GetPlaying(void) const;

        TEMPEST_API void SetLooping(bool state);

        TEMPEST_API bool GetLooping(void) const;

        TEMPEST_API const U32 GetSourceID(void) const;

        TEMPEST_API void SetPitch(F32 pitch);

        TEMPEST_API F32 GetPitch(void) const;

        TEMPEST_API void SetGain(F32 gain);

        TEMPEST_API F32 GetGain(void) const;

        TEMPEST_API void SetPosition(const TM::Vector3& pos);

        TEMPEST_API void SetPosition(F32 xVal, F32 yVal, F32 zVal);

        TEMPEST_API const TM::Vector3& GetPosition(void) const;

        TEMPEST_API void SetVelocity(const TM::Vector3& vel);

        TEMPEST_API void SetVelocity(F32 xVal, F32 yVal, F32 zVal);

        TEMPEST_API const TM::Vector3& GetVelocity(void) const;

        TEMPEST_API const p_AudioClip GetClip(void) const;

    private:
        S32 _GetPlayState(void) const;

        bool _looping;
        U32 _sourceID;
        F32 _pitch;
        F32 _gain;
        TM::Vector3 _position;
        TM::Vector3 _velocity;
        p_AudioClip _clip;
    };//end Class
    typedef shared_ptr<AudioSource> p_AudioSource;
}//end Namespace
