#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/Camera.h>
#include <Engine/Vector4.h>
#include <Engine/Input.h>

namespace TM = TempestMath;

namespace Tempest
{
    class OrbitCamera : public Camera
    {
    public:
        TEMPEST_API OrbitCamera(void);

        TEMPEST_API ~OrbitCamera(void);

        TEMPEST_API virtual void v_Rotate(void) final;

        TEMPEST_API virtual void v_Update(void) final;

        TEMPEST_API void Orbit(void);

        TEMPEST_API void Zoom(void);

        inline void SetRadius(F32 val)
        {
            _radius = REAL_CLAMP(val, _minRadius, _maxRadius);
        }

        inline void SetMinRadius(F32 val)
        {
            _minRadius = val;
        }

        inline F32 GetMinRadius(void)
        {
            return _minRadius;
        }

        inline void SetMaxRaidus(F32 val)
        {
            _maxRadius = val;
        }

        inline F32 GetMaxRadius(void)
        {
            return _maxRadius;
        }

    private:
        virtual void _v_UpdateCameraVectors(void);

        F32 _radius;		
        F32 _minRadius;		
        F32 _maxRadius;		

    };//end OrbitCamera
    typedef shared_ptr<OrbitCamera> p_OrbitCamera;
}//end Namespace
