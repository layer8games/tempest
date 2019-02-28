#include <Engine/OrbitCamera.h>

using namespace KillerEngine;
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
OrbitCamera::OrbitCamera(void)
:
_radius(10.0f)
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
	_yaw = RADIAN(_deltaYaw);
	_pitch = RADIAN(_deltaPitch);

	_pitch = FLOAT_CLAMP(_pitch, -R_PI / 2.0f + 0.1f, R_PI / 2.0f - 0.1f);

	_v_UpdateCameraVector4s();
}

void OrbitCamera::v_Update(void)
{
	KM::Vector4 coords = Controller::Instance()->GetMouseCoord();

	//Change oribt with left click
	if(Controller::Instance()->GetKeyHeld(LEFT_MOUSE))
	{	
		_deltaYaw -= (coords[0] - _lastMouseCoords[0]) * _mouseSensitivity;
		_deltaPitch += (coords[1] - _lastMouseCoords[1]) * _mouseSensitivity;
	}

	if(Controller::Instance()->GetKeyHeld(RIGHT_MOUSE))
	{
		F32 dx = 0.01f * (coords[0] - _lastMouseCoords[0]);
		F32 dy = 0.01f * (coords[1] - _lastMouseCoords[1]);
		_radius += dx - dy;
	}

	_lastMouseCoords = coords;

	v_Rotate();
}

//==========================================================================================================================
//
//Private
//
//==========================================================================================================================
void OrbitCamera::_v_UpdateCameraVector4s(void)
{
	_position[0] = _target[0] + _radius * cos(_pitch) * sin(_yaw);
	_position[1] = _target[1] + _radius * sin(_pitch);
	_position[2] = _target[2] + _radius * cos(_pitch) * cos(_yaw);
}
