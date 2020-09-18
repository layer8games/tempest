#include "stdafx.h"
#include "Engine/FPSCamera.h"
using namespace Tempest;
    
FPSCamera::FPSCamera(void)
:
_zoomSensitivity(1.0f),
_moveSpeed(1.0f),
_deadZone(0.01f)
{
    _position = 0.0f;
    _yaw = R_PI;
    _pitch = 0.0f;
}

FPSCamera::FPSCamera(const TM::Point3& position, F32 yaw, F32 pitch)
:
_zoomSensitivity(1.0f),
_moveSpeed(1.0f),
_deadZone(0.01f)
{
    _position = position;
    _yaw = yaw;
    _pitch = pitch;
}

FPSCamera::~FPSCamera(void)
{  }

void FPSCamera::v_Update(void)
{
    TM::Point2 mouseCoord = Input::Instance()->GetMouseCoord();
    S32 width = Driver::Instance()->GetScreenWidth();
    S32 height = Driver::Instance()->GetScreenHeight();

    ////Set yaw and pitch for rotate
    _deltaYaw = static_cast<F32>((width / 2.0f - mouseCoord.GetX())) * _mouseSensitivity;
    _deltaPitch = static_cast<F32>((height / 2.0f - mouseCoord.GetY())) * _mouseSensitivity;

    v_Rotate();

    Driver::Instance()->ResetMouseCursor();
}

void FPSCamera::v_Rotate(void)
{
    _yaw += RADIAN(_deltaYaw);
    _pitch += RADIAN(_deltaPitch);

    _pitch = REAL_CLAMP(_pitch, -R_PI / 2.0f + 0.1f, R_PI / 2.0f - 0.1f);

    _v_UpdateCameraVectors();

    _deltaYaw = 0.0f;
    _deltaPitch = 0.0f;
}

void FPSCamera::v_Move(const TM::Vector3& offset)
{
    _position += offset * _moveSpeed * TM::Timer::Instance()->DeltaTime();
    _v_UpdateCameraVectors();
}

void FPSCamera::_v_UpdateCameraVectors(void)
{
    //Using spherical to cartesian
    //Calculate the view direction
    _lookDirection.SetX(cos(_pitch) * sin(_yaw));
    _lookDirection.SetY(sin(_pitch));
    _lookDirection.SetZ(cos(_pitch) * cos(_yaw));
    _lookDirection.Normalize();

    //Re-calculate the right and up Vector4s
    _right = _lookDirection.CrossProduct(_worldUp);
    _right.Normalize();

    _up = _right.CrossProduct(_lookDirection);
    _up.Normalize();

    _target = _position + _lookDirection;
    _UpdateLookMatrix();
}

void FPSCamera::SetWorldUp(const TM::Vector4 vec)
{
    _worldUp = vec;
}

const TM::Vector3& FPSCamera::GetWorldUp(void) const
{
    return _worldUp;
}

void FPSCamera::SetZoom(F64 val)
{
    _zoomSensitivity = val;
}

F64 FPSCamera::GetZoom(void) const
{
    return _zoomSensitivity;
}

void FPSCamera::SetMoveSpeed(F32 val)
{
    _moveSpeed = val;
}

F32 FPSCamera::GetMoveSpeed(void) const
{
    return _moveSpeed;
}

void FPSCamera::SetDeadZone(F32 val)
{
    _deadZone = val;
}
