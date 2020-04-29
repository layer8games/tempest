#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/Vector3.h>
#include <Engine/AudioManager.h>

namespace TM = TempestMath;

namespace Tempest
{
    class AudioListener
    {
    public:
        TEMPEST_API AudioListener(void);

        TEMPEST_API ~AudioListener(void);

        inline const F32* GetOrientation(void) const
        {
            return _orientation;
        }

        TEMPEST_API void SetOrientation(F32* orientation);

        inline const TM::Vector3& GetPosition(void) const
        {
            return _position;
        }

        TEMPEST_API void SetPosition(const TM::Vector3& pos);

        TEMPEST_API void SetPosition(F32 xVal, F32 yVal, F32 zVal);

        inline const TM::Vector3& GetVelocity(void) const
        {
            return _velocity;
        }

        TEMPEST_API void SetVelocity(const TM::Vector3 vel);

        TEMPEST_API void SetVelocity(F32 xVal, F32 yVal, F32 zVal);

    private:
        F32 		_orientation[6]; 
        TM::Vector3 _position;		 
        TM::Vector3 _velocity;		 

    };//end Class
    typedef shared_ptr<AudioListener> p_AudioListener;
}//end Namespace
