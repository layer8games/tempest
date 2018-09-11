#include <Engine/Camera.h>

using namespace KillerEngine;

//==========================================================================================================================
//Camera
//==========================================================================================================================
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Camera::Camera(void) 
: 
_background(1.0f), 
_up(0.0f, 1.0f, 0.0f),
_projection(),
_currentShader(0),
_position(),
_target(),
_yaw(0.0f), 
_pitch(0.0f)
{  }

Camera::~Camera(void)
{  }

//==========================================================================================================================
//
//Camera Functions
//
//==========================================================================================================================
void Camera::SetOrthographic(void)
{
	_projection.MakeOrthographic((F32)WinProgram::Instance()->GetWidth(), (F32)WinProgram::Instance()->GetHeight(), 200.0f, false);
}

void Camera::SetPerspective(void)
{
	F32 w = static_cast<F32>(WinProgram::Instance()->GetWidth());
	F32 h = static_cast<F32>(WinProgram::Instance()->GetHeight());

	_projection.MakePerspective(90.0f,  //field of view
								w / h,  //aspect ratio
								0.1f, 	//near
								200.0f);//far
}

void Camera::SetPerspective(F32 fov, F32 aspect, F32 nearPlane, F32 farPlane)
{
	_projection.MakePerspective(fov, aspect, nearPlane, farPlane);
}

void Camera::SetDefaultMatrix(void)
{
	_projection.MakeIdentity();
}

//==========================================================================================================================
//OrbitCamera
//==========================================================================================================================
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
OrbitCamera::OrbitCamera(void)
:
_radius(10.0f),
_mouseSensitivity(1.0f),
_lastMouseCoords(0.0f),
_newYaw(0.0f),
_newPitch(0.0f)
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
	_yaw = DegreeToRadian(_newYaw);
	_pitch = DegreeToRadian(_newPitch);

	_pitch = _FloatClamp(_pitch, -R_PI / 2.0f + 0.1f, R_PI / 2.0f - 0.1f);

	UpdateCameraVectors();
}

void OrbitCamera::v_Update(void)
{
	KM::Vector coords = Controller::Instance()->GetMouseCoord();

	//Change oribt with left click
	if(Controller::Instance()->GetKeyHeld(LEFT_MOUSE))
	{	
		_newYaw -= (coords[0] - _lastMouseCoords[0]) * _mouseSensitivity;
		_newPitch += (coords[1] - _lastMouseCoords[1]) * _mouseSensitivity;
	}

	if(Controller::Instance()->GetKeyHeld(RIGHT_MOUSE))
	{
		F32 dx = 0.01f * (coords[0] - _lastMouseCoords[0]);
		F32 dy = 0.01f * (coords[1] - _lastMouseCoords[1]);
		_radius += dx - dy;
	}

	_lastMouseCoords = coords;
}

void OrbitCamera::UpdateCameraVectors(void)
{
	_position[0] = _target[0] + _radius * cos(_pitch) * sin(_yaw);
	_position[1] = _target[1] + _radius * sin(_pitch);
	_position[2] = _target[2] + _radius * cos(_pitch) * cos(_yaw);
}

//==========================================================================================================================
//
//Private
//
//==========================================================================================================================
F32 OrbitCamera::_FloatClamp(F32 val, F32 min, F32 max)
{
	if(val < min)
	{
		return min;
	}
	else if(val > max)
	{
		return max;
	}
	else
	{
		return val;
	}
}