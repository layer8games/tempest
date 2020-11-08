#include "stdafx.h"
#include "Engine/OrbitCamera.h"
using namespace Tempest;

OrbitCamera::OrbitCamera(void)
:
_radius(10.0f),
_minRadius(2.0f),
_maxRadius(80.0f)
{  }

OrbitCamera::~OrbitCamera(void)
{  }

void OrbitCamera::v_Rotate(void)
{
    Camera::_yaw = RADIAN(Camera::_deltaYaw);
    Camera::_pitch = RADIAN(Camera::_deltaPitch);

    Camera::_pitch = REAL_CLAMP(Camera::_pitch, -R_PI / 2.0f + 0.1f, R_PI / 2.0f - 0.1f);

    _v_UpdateCameraVectors();
}

void OrbitCamera::v_Update(void)
{
    Camera::_lastMouseCoords = Camera::_currentMouseCoords;
    
    // TODO: DO NOT call controller here. Update should be sent the coords it needs, or another accessor should be created
    Camera::_currentMouseCoords = Input::Instance()->GetMouseCoord();
    
    v_Rotate();
}

void OrbitCamera::Orbit(void)
{
    Camera::_deltaYaw -= (Camera::_currentMouseCoords.GetX() - Camera::_lastMouseCoords.GetX()) * Camera::_mouseSensitivity;
    Camera::_deltaPitch += (Camera::_currentMouseCoords.GetY() - Camera::_lastMouseCoords.GetY()) * Camera::_mouseSensitivity;
}

void OrbitCamera::Zoom(void)
{
    F32 dx = 0.01f * (Camera::_currentMouseCoords.GetX() - Camera::_lastMouseCoords.GetX());
    F32 dy = 0.01f * (Camera::_currentMouseCoords.GetY() - Camera::_lastMouseCoords.GetY());
    _radius += dx - dy;
}

void OrbitCamera::_v_UpdateCameraVectors(void)
{
    _position.SetX(_target.GetX() + _radius * cos(_pitch) * sin(_yaw));
    _position.SetY(_target.GetY() + _radius * sin(_pitch));
    _position.SetZ(_target.GetZ() + _radius * cos(_pitch) * cos(_yaw));
    _UpdateLookMatrix();
}
