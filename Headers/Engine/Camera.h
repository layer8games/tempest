/*==========================================================================
This class will control the view port in OpenGL, and will allow for the use
of the camera. It will controll the background color of a leve, and it will
have the ability to move, and will set the projection type. 

For now, I will build it out to be a singleton. I can see that there are 
issues with this design that will need to be looked into, but it will make
things easier to program for now. This will be awesome

This is not free to use, and cannot be used without the express permission
of KillerWave. 

Written by Maxwell Miller
==========================================================================*/
#ifndef CAMERA_H
#define CAMERA_H

//=====Killer includes=====
#include <Engine/Atom.h>
#include <Engine/WinProgram.h>
#include <Engine/Matrix.h>
#include <Engine/Vector2.h> 

namespace KM = KillerMath;

//=====OGL includes=====
//=====OGL includes=====
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/wglext.h>

namespace KillerEngine
{
	class Camera
	{
	public:
//==========================================================================================================================
//
//Camera Functions
//
//==========================================================================================================================		
		static Camera* Instance(void);

		void SetProjectionOrthographic(void);

		void SetPosition(KM::Vector2& pos, F32 scale) 
		{ 
			_pos.AddScaledVector(pos, scale);
			_translation.Translate(pos); 
		}

		void SetPosition(F32 x, F32 y, F32 scale) 
		{ 
			_pos.AddScaledVector(KM::Vector2(x, y), scale);
			_translation.Translate(_pos); 
		}

		void SetColor(Col& col) { _background = col; }

		void SetUp(GLuint shader);

		//Will be implemented later
		//void SetProjectionPerspective(void) { }
	
	private:
//==========================================================================================================================
//
//Private members
//
//==========================================================================================================================		
		static Camera* 	_instance;
		Col    			_background;
		KM::Vector2  	_pos;
		KM::Matrix 		_projection;
		KM::Matrix 		_translation;

	protected:
//==========================================================================================================================
//
//Constructor
//
//==========================================================================================================================
		Camera(void);
	};
}//end namespace
#endif