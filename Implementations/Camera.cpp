#include <Engine/Camera.h>
#include <iostream>

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
_projection(1.0f),
_position(0.0f),
_target(0.0f),
_up(0.0f, 1.0f, 0.0f),
_look(0.0f),
_right(0.0f),
_lastMouseCoords(0.0f),
_mouseSensitivity(1.0f),
_yaw(0.0f), 
_pitch(0.0f),
_deltaYaw(0.0f),
_deltaPitch(0.0f),
_fov(45.0f)
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

	_v_UpdateCameraVectors();
}

void OrbitCamera::v_Update(void)
{
	KM::Vector coords = Controller::Instance()->GetMouseCoord();

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
void OrbitCamera::_v_UpdateCameraVectors(void)
{
	_position[0] = _target[0] + _radius * cos(_pitch) * sin(_yaw);
	_position[1] = _target[1] + _radius * sin(_pitch);
	_position[2] = _target[2] + _radius * cos(_pitch) * cos(_yaw);
}

//==========================================================================================================================
//FPS Camera
//==========================================================================================================================
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================		
FPSCamera::FPSCamera(void)
:
_worldUp(0.0f, 1.0f, 0.0f),
_zoomSensitivity(1.0f),
_moveSpeed(1.0f),
_deadZone(0.01f)
{
	_position = 0.0f;
	_yaw = R_PI;
	_pitch = 0.0f;
}

FPSCamera::FPSCamera(const KM::Vector position, F32 yaw, F32 pitch)
:
_worldUp(0.0f, 1.0f, 0.0f),
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

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
void FPSCamera::v_Update(void)
{
	KM::Vector mouseCoord = Controller::Instance()->GetMouseCoord();
	S32 width = WinProgram::Instance()->GetWidth();
	S32 height = WinProgram::Instance()->GetHeight();

	//Set yaw and pitch for rotate
	_deltaYaw = static_cast<F32>((width / 2.0f - mouseCoord[0])) * _mouseSensitivity;
	_deltaPitch = static_cast<F32>((height / 2.0f - mouseCoord[1])) * _mouseSensitivity;

	v_Rotate();

	//Clamp cursor to screen
	WinProgram::Instance()->ResetMouseCursor();

	if(Controller::Instance()->GetKeyHeld(W))
	{
		v_Move(_look); //forward
	}
	else if(Controller::Instance()->GetKeyHeld(S))
	{
		v_Move(_look * -1.0f); //back
	}
	
	if(Controller::Instance()->GetKeyHeld(D))
	{
		v_Move(_right); //right
	}
	else if(Controller::Instance()->GetKeyHeld(A))
	{
		v_Move(_right * -1.0f); //left
	}

	if(Controller::Instance()->GetKeyHeld(SPACE))
	{
		v_Move(_up); //up
	}
	else if(Controller::Instance()->GetKeyHeld(LSHIFT))
	{
		v_Move(_up * -1.0f); //down
	}
}

void FPSCamera::v_Rotate(void)
{
	_yaw += RADIAN(_deltaYaw);
	_pitch += RADIAN(_deltaPitch);

	_pitch = FLOAT_CLAMP(_pitch, -R_PI / 2.0f + 0.1f, R_PI / 2.0f - 0.1f);

	_v_UpdateCameraVectors();

	_deltaYaw = 0.0f;
	_deltaPitch = 0.0f;
}

void FPSCamera::v_Move(const KM::Vector offset)
{
	_position += offset * _moveSpeed * KM::Timer::Instance()->DeltaTime();
	_v_UpdateCameraVectors();
}

void FPSCamera::_v_UpdateCameraVectors(void)
{
	//Using spherical to cartesian
	//Calculate the view direction
	_look[0] = cos(_pitch) * sin(_yaw);
	_look[1] = sin(_pitch);
	_look[2] = cos(_pitch) * cos(_yaw);
	_look.Normalize();

	//Re-calculate the right and up vectors
	_right = _look.CrossProduct(_worldUp);
	_right.Normalize();

	_up = _right.CrossProduct(_look);
	_up.Normalize();

	_target = _position + _look;
}