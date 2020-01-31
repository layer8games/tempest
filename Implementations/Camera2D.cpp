#include <Engine/Camera2D.h>

using namespace Tempest;

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Camera2D::Camera2D(void)
	:
	_moveSpeed(1.0f)
{  }

Camera2D::~Camera2D(void)
{  }

void Camera2D::v_Move(const TM::Vector4& offset)
{
	_position += offset * _moveSpeed * TM::Timer::Instance()->DeltaTime();
}

void Camera2D::v_Move(F32 xVal, F32 yVal)
{
	F32 delta = TM::Timer::Instance()->DeltaTime();
	_position[x] += xVal * _moveSpeed * delta;
	_position[y] += yVal * _moveSpeed * delta;
}