#include <Engine/Camera.h>

using namespace Tempest;

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
_bgColor(1.0f), 
_projection(1.0f),
_position(0.0f),
_target(0.0f, 0.0f, -1.0f),
_worldUp(0.0f, 1.0f, 0.0f),
_up(0.0f, 1.0f, 0.0f),
_look(0.0f),
_right(0.0f),
_currentMouseCoords(0.0f),
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
void Camera::SetOrthographic(F32 left, F32 right, F32 bottom, F32 top, F32 nearPlane, F32 farPlane)
{
	_projection.MakeOrthographic(left, right, bottom, top, nearPlane, farPlane);
}

void Camera::SetPerspective(F32 fov, F32 aspect, F32 nearPlane, F32 farPlane)
{
	_projection.MakePerspective(fov, aspect, nearPlane, farPlane);
}

void Camera::SetDefaultMatrix4(void)
{
	_projection.MakeIdentity();
}

void Camera::DefaultUpdateCameraVectors(void)
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