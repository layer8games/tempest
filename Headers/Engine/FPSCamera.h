#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/Camera.h>
#include <Engine/Point3.h>
#include <Engine/Vector3.h>

namespace TM = TempestMath;

namespace Tempest
{
    class FPSCamera : public Camera
    {
    public:
        TEMPEST_API FPSCamera(void);

        TEMPEST_API FPSCamera(const TM::Point3& position, F32 yaw, F32 pitch);

        TEMPEST_API ~FPSCamera(void);

        TEMPEST_API void v_Update(void) final;

        TEMPEST_API void v_Rotate(void) final;

        TEMPEST_API void v_Move(const TM::Vector3& offset) final;

        TEMPEST_API void _v_UpdateCameraVectors(void) final;

        inline void SetWorldUp(const TM::Vector4 vec)
        {
            _worldUp = vec;
        }

        inline const TM::Vector3& GetWorldUp(void)
        {
            return _worldUp;
        }

        inline void SetZoom(F64 val)
        {
            _zoomSensitivity = val;
        }

        inline F64 GetZoom(void)
        {
            return _zoomSensitivity;
        }

        inline void SetMoveSpeed(F32 val)
        {
            _moveSpeed = val;
        }

        inline F32 GetMoveSpeed(void)
        {
            return _moveSpeed;
        }

        inline void SetDeadZone(F32 val)
        {
            _deadZone = val;
        }

    private:
        F64 _zoomSensitivity;	
        F32 _moveSpeed;			
        F32 _deadZone;			

    };//end FPSCamera
    typedef shared_ptr<FPSCamera> p_FPSCamera;
}//end Namespace
