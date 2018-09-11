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
#include <Engine/Controller.h>

#include <vector>

namespace KM = KillerMath;

namespace KillerEngine
{
//==========================================================================================================================
//
//Camera
//
//==========================================================================================================================	
	class Camera
	{
	public:
//==========================================================================================================================
//
//Constructor
//
//==========================================================================================================================
		Camera(void);

		~Camera(void);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
		virtual void v_Rotate(void)
		{  }

		virtual void v_Update(void)
		{  }

		virtual void v_Move(void)
		{  }

//==========================================================================================================================
//
//Camera Functions
//
//==========================================================================================================================
/*! Sets private Matrix to use an orthogrphic projection. This calls the WinProgram to get the demensions for the Matrix. 
	\param none
*/
		void SetOrthographic(void);

/*! Sets the private Matrix to use a perspective projection. Values are hard coded for now. 
	\param none
*/
		void SetPerspective(void);

		void SetPerspective(F32 fov, F32 aspect, F32 nearPlane, F32 farPlane);

/*! Helper function to set the projection Matrix to be an identity Matrix. 
	\param none
*/
		void SetDefaultMatrix(void);

		inline const KM::Matrix GetViewMatrix(void)
		{
			return KM::Matrix::LookAt(_position, _target, _up);
		}

		inline const KM::Matrix& GetProjectionMatrix(void)
		{
			return _projection;
		}

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
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
//Target
//==========================================================================================================================
		inline void SetTarget(const KM::Vector& target)
		{
			_target = target;
		}

		inline void SetTarget(F32 xVal, F32 yVal)
		{
			_target[0] = xVal;
			_target[1] = yVal;
			_target[2] = 0.0f;
		}

		inline void SetTarget(F32 xVal, F32 yVal, F32 zVal)
		{
			_target[0] = xVal;
			_target[1] = yVal;
			_target[2] = zVal;
		}

		inline const KM::Vector& GetTarget(void)
		{
			return _target;
		}		

 

//==========================================================================================================================
//Up
//==========================================================================================================================		
		inline void SetUpVector(F32 val)
		{
			_up[1] = val;
		}

		inline void SetUpVector(F32 xVal, F32 yVal, F32 zVal)
		{
			_up[0] = xVal;
			_up[1] = yVal;
			_up[2] = zVal;
		}

		inline void SetUpVector(const KM::Vector& vec)
		{
			_up	 = vec;
		}

		inline const KM::Vector& GetUpVector(void) const
		{
			return _up;
		}

//==========================================================================================================================
//Look
//==========================================================================================================================
		inline void SetLookVector(F32 val)
		{
			_look = val;
		}

		inline void SetLookVector(F32 xVal, F32 yVal)
		{
			_look[0] = xVal;
			_look[1] = yVal;
		}

		inline void SetLookVector(F32 xVal, F32 yVal, F32 zVal)
		{
			_look[0] = xVal;
			_look[1] = yVal;
			_look[2] = zVal;
		}

		inline void SetLookVector(const KM::Vector& vec)
		{
			_look = vec;
		}

		inline const KM::Vector& GetLookVector(void) const
		{
			return _look;
		}

//==========================================================================================================================
//Right
//==========================================================================================================================
		inline void SetRightVector(F32 val)
		{
			_right = val;
		}

		inline void SetRightVector(F32 xVal, F32 yVal)
		{
			_right[0] = xVal;
			_right[1] = yVal;
		}

		inline void SetRightVector(F32 xVal, F32 yVal, F32 zVal)
		{
			_right[0] = xVal;
			_right[1] = yVal;
			_right[2] = zVal;
		}

		inline void SetRightVector(const KM::Vector& vec)
		{
			_right = vec;
		}

		inline const KM::Vector& GetRightVector(void) const
		{
			return _right;
		}
//==========================================================================================================================
//Yaw
//==========================================================================================================================
		inline F32 GetYaw(void) const
		{
			return _yaw;
		}

//==========================================================================================================================
//Pitch
//==========================================================================================================================		
		inline F32 GetPitch(void) const
		{
			return _pitch;
		}

//==========================================================================================================================
//Field of View
//==========================================================================================================================
		inline void SetFOV(F32 val)
		{
			_fov = val;
		}

		inline F32 GetFOV(void) const
		{
			return _fov;
		}

	private:
		virtual void _v_UpdateCameraVectors(void)
		{  }

//==========================================================================================================================
//
//Data
//
//==========================================================================================================================		
		Color  							_background;	///< Background color of current level.
		KM::Matrix 						_projection;	///< Projection Matrix (Orthographic or Perspective). Not used 
		
	protected:
		KM::Vector  					_position;		///< Position of Camera in world space.
		KM::Vector 						_target;
		KM::Vector 						_up;
		KM::Vector 						_look;
		KM::Vector 						_right;
		F32 							_yaw;			///< Euler angle in Radians
		F32 							_pitch;			///< Euler angle in Radians
		F32 							_fov;
	};//end Camera

//==========================================================================================================================
//Orbit Camera
//==========================================================================================================================
	class OrbitCamera : public Camera
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		OrbitCamera(void);

		~OrbitCamera(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================		
		virtual void v_Rotate(void);

		virtual void v_Update(void);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================		
		//ToDO: Make the min and max member vairables
		//that can be changed per instance
		inline void SetRadius(F32 val)
		{
			_radius = _FloatClamp(val, 2.0f, 80.0f);
		}

		inline void SetMouseSensitivity(F32 val)
		{
			_mouseSensitivity = val;
		}

		inline F32 GetMouseSensitivity(void)
		{
			return _mouseSensitivity;
		}

	private:
		virtual void _v_UpdateCameraVectors(void);

		F32 _FloatClamp(F32 val, F32 min, F32 max);
//==========================================================================================================================
//
//Data
//
//==========================================================================================================================		
		F32 		_radius;
		F32			_mouseSensitivity;
		KM::Vector 	_lastMouseCoords;
		F32			_newYaw;
		F32			_newPitch;

	};//end OrbitCamera

//==========================================================================================================================
//FPSCamera
//==========================================================================================================================
	class FPSCamera : public Camera
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================		
		FPSCamera(void);

		FPSCamera(const KM::Vector position, F32 yaw, F32 pitch);

		~FPSCamera(void);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
		virtual void v_Rotate(void);

		virtual void v_Move(void);

	private:
		virtual void _v_UpdateCameraVectors(void);

	};//end FPSCamera

}//end namespace