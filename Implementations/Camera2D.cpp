#include "stdafx.h"
#include <Engine/Camera2D.h>
using namespace Tempest;

Camera2D::Camera2D(void)
    :
    _moveSpeed(1.0f)
{
    _position = 0.0f;
    _yaw = R_PI;
    _pitch = 0.0f;
}

Camera2D::~Camera2D(void)
{  }

void Camera2D::v_Move(const TM::Vector3& offset)
{
    _position += offset * _moveSpeed * TM::Timer::Instance()->DeltaTime();
    _v_UpdateCameraVectors();
}

void Camera2D::SetMoveSpeed(F32 val)
{
    _moveSpeed = val;
}

F32 Camera2D::GetMoveSpeed(void)
{
    return _moveSpeed;
}