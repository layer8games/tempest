#include <Engine/FPSCamera.h>

using namespace KillerEngine;
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

FPSCamera::FPSCamera(const KM::Vector4 position, F32 yaw, F32 pitch)
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
	KM::Vector4 mouseCoord = Controller::Instance()->GetMouseCoord();
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

	_v_UpdateCameraVector4s();

	_deltaYaw = 0.0f;
	_deltaPitch = 0.0f;
}

void FPSCamera::v_Move(const KM::Vector4 offset)
{
	_position += offset * _moveSpeed * KM::Timer::Instance()->DeltaTime();
	_v_UpdateCameraVector4s();
}

void FPSCamera::_v_UpdateCameraVector4s(void)
{
	//Using spherical to cartesian
	//Calculate the view direction
	_look[0] = cos(_pitch) * sin(_yaw);
	_look[1] = sin(_pitch);
	_look[2] = cos(_pitch) * cos(_yaw);
	_look.Normalize();

	//Re-calculate the right and up Vector4s
	_right = _look.CrossProduct(_worldUp);
	_right.Normalize();

	_up = _right.CrossProduct(_look);
	_up.Normalize();

	_target = _position + _look;
}
