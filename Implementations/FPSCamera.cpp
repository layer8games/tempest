#include <Engine/FPSCamera.h>

using namespace Tempest;
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================		
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

FPSCamera::FPSCamera(const TM::Point& position, F32 yaw, F32 pitch)
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

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
void FPSCamera::v_Update(void)
{
	//TM::Point mouseCoord = Controller::Instance()->GetMouseCoord();
	//S32 width = GameWindow::Instance()->GetWidth();
	//S32 height = GameWindow::Instance()->GetHeight();

	////Set yaw and pitch for rotate
	//_deltaYaw = static_cast<F32>((width / 2.0f - mouseCoord[0])) * _mouseSensitivity;
	//_deltaPitch = static_cast<F32>((height / 2.0f - mouseCoord[1])) * _mouseSensitivity;

	//v_Rotate();

	//GameWindow::Instance()->ResetMouseCursor();
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

void FPSCamera::v_Move(const TM::Vector4& offset)
{
	_position += offset * _moveSpeed * TM::Timer::Instance()->DeltaTime();
	_v_UpdateCameraVectors();
}

void FPSCamera::v_Move(F32 xVal, F32 yVal)
{
	F32 delta = TM::Timer::Instance()->DeltaTime();
	_position[x] += xVal * _moveSpeed * delta;
	_position[y] += yVal * _moveSpeed * delta;
	_v_UpdateCameraVectors();
}

//void FPSCamera::_v_UpdateCameraVector4s(void)
//{
//	//Using spherical to cartesian
//	//Calculate the view direction
//	_look[0] = cos(_pitch) * sin(_yaw);
//	_look[1] = sin(_pitch);
//	_look[2] = cos(_pitch) * cos(_yaw);
//	_look.Normalize();
//
//	//Re-calculate the right and up Vector4s
//	_right = _look.CrossProduct(_worldUp);
//	_right.Normalize();
//
//	_up = _right.CrossProduct(_look);
//	_up.Normalize();
//
//	_target = _position + _look;
//}
