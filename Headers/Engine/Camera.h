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
#pragma once

//=====Killer includes=====
#include <Engine/Atom.h>
#include <Engine/WinProgram.h>
#include <Engine/Matrix.h>
#include <Engine/Vector2.h> 
#include <Engine/Vector3.h>
#include <Engine/Color.h>

namespace KM = KillerMath;

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
//Constructors
//
//==========================================================================================================================
		~Camera(void);

//==========================================================================================================================
//
//Camera Functions
//
//==========================================================================================================================		
/*! Singleton function. Returns global camera object
	\param none
*/		
		static shared_ptr<Camera> Instance(void);

/*! Sets private Matrix to use an orthogrphic projection. This calls the WinProgram to get the demensions for the Matrix. 
	\param none
*/
		void SetOrthographic(void);

/*! Sets the private Matrix to use a perspective projection. Values are hard coded for now. 
	\param none
*/
		void SetPerspective(void);

/*! Helper function to set the projection Matrix to be an identity Matrix. 
	\param none
*/
		void SetDefaultMatrix(void);

/*! 
*/
		void SetPosition(F32 x, F32 y);

		void SetPosition(const KM::Vector2& V);

		void SetPosition(F32 x, F32 y, F32 z);

		void SetPosition(const KM::Vector3& V);

		void ScalePosition(F32 x, F32 y, F32 scale);

		void ScalePosition(const KM::Vector2& v, F32 scale);

		void ScalePosition(F32 x, F32 y, F32 z, F32 scale);

		void ScalePosition(const KM::Vector3& V, F32 scale);

		void SetColor(const Color& col) 
		{ 
			_background = col; 
		}

		void SetUp(GLuint shader);

		//Will be implemented later
		//void SetProjectionPerspective(void) { }
	
	private:
//==========================================================================================================================
//
//Private members
//
//==========================================================================================================================		
		static shared_ptr<Camera> 	    _instance;		///< Singleton global instance.
		Color  							_background;	///< Background color of current level.
		KM::Vector3  					_pos;			///< Position of Camera in world space.
		KM::Matrix 						_projection;	///< Projection Matrix (Orthographic or Perspective). Not used
		KM::Matrix 						_translation;	///< Amount of Translation needed to reflect Position. Should be opposite of _pos
		GLuint							_currentShader;	///< Fully compiled OpenGL Shader Program. 

	protected:
//==========================================================================================================================
//
//Constructor
//
//==========================================================================================================================
		Camera(void);
	};
}//end namespace