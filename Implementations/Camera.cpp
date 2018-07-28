#include <Engine/Camera.h>
#include <iostream>

using namespace KillerEngine;

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Camera::Camera(void) 
: 
_background(1.0f), 
_projection(), 
_translation(), 
_currentShader(0)
{  }

Camera::~Camera(void)
{  }

//==========================================================================================================================
//
//Camera Functions
//
//==========================================================================================================================
shared_ptr<Camera> Camera::_instance{NULL};

shared_ptr<Camera> Camera::Instance(void)
{
	if(_instance == NULL) 
	{
	 	_instance = shared_ptr<Camera>{new Camera()}; 
	}
	return _instance;
}

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

void Camera::SetPosition(F32 x, F32 y)
{
	_pos = KM::Vector(x, y);
	_translation.Translate(_pos);
}

void Camera::SetPosition(F32 x, F32 y, F32 z)
{
	_pos = KM::Vector(x, y, z);
	_translation.Translate(_pos);
}

void Camera::SetPosition(const KM::Vector& V)
{
	_pos = V;
	_translation.Translate(_pos);
}

void Camera::ScalePosition(F32 x, F32 y, F32 scale)
{
	_pos.AddScaledVector(KM::Vector(x, y), scale);
	_translation.Translate(_pos);
}

void Camera::ScalePosition(F32 x, F32 y, F32 z, F32 scale)
{
	_pos.AddScaledVector(KM::Vector(x, y, z), scale);
	_translation.Translate(_pos);
}

void Camera::ScalePosition(const KM::Vector& V, F32 scale)
{
	_pos.AddScaledVector(V, scale);
	_translation.Translate(_pos);
}