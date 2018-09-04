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
#include <Engine/Vector.h>
#include <Engine/Color.h>

#include <vector>

namespace KM = KillerMath;

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

		void SetUp(GLuint shader);

		inline const KM::Matrix& GetViewMatrix(void)
		{
			return KM::Matrix::Translate(_position);
		}

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
//==========================================================================================================================
//Position
//==========================================================================================================================
		inline void SetPosition(F32 x, F32 y)
		{
			_position[0] = x;
			_position[1] = y;
		}

		inline void SetPosition(F32 x, F32 y, F32 z)
		{
			_position[0] = x;
			_position[1] = y;
			_position[2] = z;
		}

		inline void SetPosition(const KM::Vector& vec)
		{
			_position = vec;
		}

		inline void ScalePosition(F32 x, F32 y, F32 scale)
		{
			_position.AddScaledVector(KM::Vector(x, y), scale);
		}

		inline void ScalePosition(F32 x, F32 y, F32 z, F32 scale)
		{
			_position.AddScaledVector(KM::Vector(x, y, z), scale);
		}

		inline void ScalePosition(const KM::Vector& vec, F32 scale)
		{
			_position.AddScaledVector(vec, scale);
		}

		inline const KM::Vector& GetPosition(void) const
		{
			return _position;
		}

//==========================================================================================================================
//Background Color
//==========================================================================================================================
		inline void SetColor(const Color& col) 
		{ 
			_background = col; 
		}

		inline const Color& GetBackgroundColor(void) const
		{
			return _background;
		} 

//==========================================================================================================================
//Up
//==========================================================================================================================		
		inline void SetUpVector(F32 val)
		{
			_up[1] = val;
		}

		inline void SetUpVector(const KM::Vector& vec)
		{
			_up	 = vec;
		}

//==========================================================================================================================
//Target
//==========================================================================================================================

	
	private:
//==========================================================================================================================
//
//Private members
//
//==========================================================================================================================		
		static shared_ptr<Camera> 	    _instance;		///< Singleton global instance.
		Color  							_background;	///< Background color of current level.
		KM::Vector  					_position;		///< Position of Camera in world space.
		KM::Vector 						_up;
		KM::Vector 						_target;
		KM::Matrix 						_projection;	///< Projection Matrix (Orthographic or Perspective). Not used
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