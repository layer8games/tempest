#include "stdafx.h"
#include "Engine/Camera.h"

using namespace Tempest;

Camera::Camera(void) 
    :
    _projectionMatrix(1.0f),
    _lookAtMatrix(1.0f),
    _position(0.0f),
    _target(0.0f, 0.0f, -1.0f),
    _currentMouseCoords(0.0f),
    _lastMouseCoords(0.0f),
    _worldUp(0.0f, 1.0f, 0.0f),
    _up(0.0f, 1.0f, 0.0f),
    _lookDirection(0.0f),
    _right(0.0f),
    _bgColor(1.0f),
    _mouseSensitivity(1.0f),
    _yaw(0.0f), 
    _pitch(0.0f),
    _deltaYaw(0.0f),
    _deltaPitch(0.0f),
    _fov(45.0f)
{  }

Camera::~Camera(void)
{  }

void Camera::v_Rotate(void)
{  }

void Camera::v_Update(void)
{  }

void Camera::v_Move(const TM::Vector3& offset)
{  }

const TM::Matrix4& Camera::GetViewMatrix(void) const
{
    return _lookAtMatrix;
}

const TM::Matrix4& Camera::GetProjectionMatrix(void) const
{
    return _projectionMatrix;
}

void Camera::SetOrthographic(void)
{
    // TODO
    // Reversed right and left. This is a temporary fix. Review tutorial here to fix: 
    // https://learnopengl.com/Getting-started/Camera
    _projectionMatrix.MakeOrthographic(Driver::Instance()->GetScreenRight(),
                                       Driver::Instance()->GetScreenLeft(),
                                       Driver::Instance()->GetScreenBottom(),
                                       Driver::Instance()->GetScreenTop(),
                                       -100.0f,
                                       100.0f
    );
    _DefaultUpdateCameraVectors();
}

void Camera::SetOrthographic(F32 left, F32 right, F32 bottom, F32 top, F32 nearPlane, F32 farPlane)
{
    _projectionMatrix.MakeOrthographic(left, right, bottom, top, nearPlane, farPlane);
}

void Camera::SetPerspective(void)
{
    _projectionMatrix.MakePerspective(45.0f,
                                      static_cast<F32>(TE::Driver::Instance()->GetScreenWidth()) / static_cast<F32>(TE::Driver::Instance()->GetScreenHeight()), 
                                      0.1f, 
                                      100.0f
    );
}

void Camera::SetPerspective(F32 fov, F32 aspect, F32 nearPlane, F32 farPlane)
{
    _projectionMatrix.MakePerspective(fov, aspect, nearPlane, farPlane);
}

void Camera::SetPosition(F32 x, F32 y)
{
    _position.SetX(x);
    _position.SetY(y);

    _v_UpdateCameraVectors();
}

void Camera::SetPosition(F32 x, F32 y, F32 z)
{
    _position.Set(x, y, z);

    _v_UpdateCameraVectors();
}

void Camera::SetPosition(const TM::Point3& point)
{
    _position = point;

    _v_UpdateCameraVectors();
}

void Camera::ScalePosition(F32 x, F32 y, F32 z, F32 scale)
{
    _position.AddScaledVector(TM::Point3(x, y, z), scale);

    _v_UpdateCameraVectors();
}

void Camera::ScalePosition(const TM::Point3& point, F32 scale)
{
    _position.AddScaledVector(point, scale);

    _v_UpdateCameraVectors();
}

const TM::Point3& Camera::GetPosition(void) const
{
    return _position;
}

void Camera::SetTargetPosition(const TM::Point3& target)
{
    _target = target;
}

const TM::Point3& Camera::GetTarget(void) const
{
    return _target;
}

void Camera::SetUpDirection(const TM::Vector3& vec)
{
    _up	 = vec;
}

const TM::Vector3& Camera::GetUpDirection(void) const
{
    return _up;
}

void Camera::SetLookDirection(const TM::Vector3& vec)
{
    _lookDirection = vec;
}

const TM::Vector3& Camera::GetLookDirection(void) const
{
    return _lookDirection;
}

void Camera::SetRightDirection(const TM::Vector3& vec)
{
    _right = vec;
}

const TM::Vector3& Camera::GetRightVector(void) const
{
    return _right;
}

void Camera::SetMouseSensitivity(F32 val)
{
    _mouseSensitivity = val;
}

F32 Camera::GetYaw(void) const
{
    return _yaw;
}

F32 Camera::GetMouseSensitivity(void) const
{
    return _mouseSensitivity;
}

F32 Camera::GetPitch(void) const
{
    return _pitch;
}

void Camera::SetFOV(F32 val)
{
    _fov = val;
}

F32 Camera::GetFOV(void) const
{
    return _fov;
}

void Camera::_v_UpdateCameraVectors(void)
{
    _DefaultUpdateCameraVectors();
}

void Camera::_DefaultUpdateCameraVectors(void)
{
    //Using spherical to cartesian
    //Calculate the view direction
    _lookDirection.Set(real_cos(_pitch) * real_sin(_yaw),
                       real_sin(_pitch),
                       real_cos(_pitch) * real_cos(_yaw));

    _lookDirection.Normalize();


    //Re-calculate the right and up Vector4s
    _right = _lookDirection.CrossProduct(_worldUp);
    _right.Normalize();

    _up = _right.CrossProduct(_lookDirection);
    _up.Normalize();

    _target = _position + _lookDirection;
    
    _UpdateLookMatrix();
}

void Camera::_UpdateLookMatrix(void)
{
    _lookAtMatrix.SetLookAt(_position, _target, _up);
}