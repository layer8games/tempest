#pragma once

#include "stdafx.h"
#include "Engine/Atom.h"
#include "Engine/Camera.h"
#include "Engine/Vector3.h"

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

        TEMPEST_API void SetWorldUp(const TM::Vector4 vec);

        TEMPEST_API const TM::Vector3& GetWorldUp(void) const;

        TEMPEST_API void SetZoom(F64 val);

        TEMPEST_API F64 GetZoom(void) const;

        TEMPEST_API void SetMoveSpeed(F32 val);

        TEMPEST_API F32 GetMoveSpeed(void) const;

        TEMPEST_API void SetDeadZone(F32 val);

    private:
        F64 _zoomSensitivity;
        F32 _moveSpeed;
        F32 _deadZone;

    };//end FPSCamera
    typedef shared_ptr<FPSCamera> p_FPSCamera;
}//end Namespace
