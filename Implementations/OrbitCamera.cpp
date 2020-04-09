#include <Engine/OrbitCamera.h>

using namespace Tempest;
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
OrbitCamera::OrbitCamera(void)
:
_radius(10.0f),
_minRadius(2.0f),
_maxRadius(80.0f)
{  }

OrbitCamera::~OrbitCamera(void)
{  }

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
void OrbitCamera::v_Rotate(void)
{
	Camera::_yaw = RADIAN(Camera::_deltaYaw);
	Camera::_pitch = RADIAN(Camera::_deltaPitch);

	Camera::_pitch = FLOAT_CLAMP(Camera::_pitch, -R_PI / 2.0f + 0.1f, R_PI / 2.0f - 0.1f);

	_v_UpdateCameraVectors();
}

void OrbitCamera::v_Update(void)
{
	Camera::_lastMouseCoords = Camera::_currentMouseCoords;
	Camera::_currentMouseCoords = Controller::Instance()->GetMouseCoord();
	
	v_Rotate();
}

void OrbitCamera::Orbit(void)
{
	Camera::_deltaYaw -= (Camera::_currentMouseCoords[0] - Camera::_lastMouseCoords[0]) * Camera::_mouseSensitivity;
	Camera::_deltaPitch += (Camera::_currentMouseCoords[1] - Camera::_lastMouseCoords[1]) * Camera::_mouseSensitivity;
}

void OrbitCamera::Zoom(void)
{
	F32 dx = 0.01f * (Camera::_currentMouseCoords[0] - Camera::_lastMouseCoords[0]);
	F32 dy = 0.01f * (Camera::_currentMouseCoords[1] - Camera::_lastMouseCoords[1]);
	_radius += dx - dy;
}

//==========================================================================================================================
//
//Private
//
//==========================================================================================================================
void OrbitCamera::_v_UpdateCameraVectors(void)
{
	_position.x = _target.x + _radius * cos(_pitch) * sin(_yaw);
	_position.y = _target.y + _radius * sin(_pitch);
	_position.z = _target.z + _radius * cos(_pitch) * cos(_yaw);
}
