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
void Camera::SetUp(GLuint shader)
{		
/*
	KM::Matrix finalMatrix = _projection * _translation;

	const F32* data = finalMatrix.GetElems();

	GLint transform1 = glGetUniformLocation(shader, "projection_mat");

	glUniformMatrix4fv(transform1, 1, GL_FALSE, data);
*/
	//not working matrix multiplication. Will fix later
	//_translation = _projection * _translation;
	//_translation *= _projection;

	std::vector<F32> data = _projection.GetElems();

	GLint transform = glGetUniformLocation(shader, "projection_mat");

	glUniformMatrix4fv(transform, 1, GL_FALSE, &data[0]);
}

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
void OrbitCamera::v_Rotate(F32 yaw, F32 pitch)
{
	_yaw = DegreeToRadian(yaw);
	_pitch = DegreeToRadian(pitch);

	_pitch = _FloatClamp(pitch, -R_PI / 2.0f + 0.1f, R_PI / 2.0f - 0.1f);

	UpdateCameraVectors();
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