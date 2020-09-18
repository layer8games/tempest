#pragma once

#include "stdafx.h"
#include "Engine/Atom.h"
#include "Engine/Vector3.h"
#include "Engine/AudioManager.h"

namespace TM = TempestMath;

namespace Tempest
{
    class AudioListener
    {
    public:
        TEMPEST_API AudioListener(void);

        TEMPEST_API ~AudioListener(void);

        TEMPEST_API const F32* GetOrientation(void) const;

        TEMPEST_API void SetOrientation(F32* orientation);

        TEMPEST_API const TM::Vector3& GetPosition(void) const;

        TEMPEST_API void SetPosition(const TM::Vector3& pos);

        TEMPEST_API void SetPosition(F32 xVal, F32 yVal, F32 zVal);

        TEMPEST_API const TM::Vector3& GetVelocity(void) const;

        TEMPEST_API void SetVelocity(const TM::Vector3 vel);

        TEMPEST_API void SetVelocity(F32 xVal, F32 yVal, F32 zVal);

    private:
        F32 _orientation[6];
        TM::Vector3 _position;
        TM::Vector3 _velocity;

    };//end Class
    typedef shared_ptr<AudioListener> p_AudioListener;
}//end Namespace
