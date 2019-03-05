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
#include <Engine/Matrix4.h>
#include <Engine/Vector4.h>
#include <Engine/Point.h>
#include <Engine/Color.h>
#include <Engine/Controller.h>
#include <Engine/Timer.h>

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

		virtual void v_Move(const KM::Vector4& offset)
		{  }

//==========================================================================================================================
//
//Camera Functions
//
//==========================================================================================================================
/*! Sets private Matrix4 to use an orthogrphic projection. This calls the WinProgram to get the demensions for the Matrix4. 
	\param none
*/
		void SetOrthographic(void);

		void SetOrthographic(F32 left, F32 right, F32 bottom, F32 top, F32 nearPlane, F32 farPlane);

/*! Sets the private Matrix4 to use a perspective projection. Values are hard coded for now. 
	\param none
*/
		void SetPerspective(void);

		void SetPerspective(F32 fov, F32 aspect, F32 nearPlane, F32 farPlane);

/*! Helper function to set the projection Matrix4 to be an identity Matrix4. 
	\param none
*/
		void SetDefaultMatrix4(void);

		inline const virtual KM::Matrix4 GetViewMatrix4(void)
		{
			return KM::Matrix4::LookAt(_position, _target, _up);
		}

		inline const KM::Matrix4& GetProjectionMatrix4(void)
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

		inline void SetPosition(const KM::Point& point)
		{
			_position = point;
		}

		inline void ScalePosition(F32 x, F32 y, F32 scale)
		{
			_position.AddScaledPoint(KM::Point(x, y), scale);
		}

		inline void ScalePosition(F32 x, F32 y, F32 z, F32 scale)
		{
			_position.AddScaledPoint(KM::Point(x, y, z), scale);
		}

		inline void ScalePosition(const KM::Point& point, F32 scale)
		{
			_position.AddScaledPoint(point, scale);
		}

		inline const KM::Point& GetPosition(void) const
		{
			return _position;
		}

//==========================================================================================================================
//Target
//==========================================================================================================================
		inline void SetTarget(const KM::Point& target)
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

		inline const KM::Point& GetTarget(void)
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

		inline void SetUpVector(const KM::Vector4& vec)
		{
			_up	 = vec;
		}

		inline const KM::Vector4& GetUpVector(void) const
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

		inline void SetLookVector(const KM::Vector4& vec)
		{
			_look = vec;
		}

		inline const KM::Vector4& GetLookVector(void) const
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

		inline void SetRightVector(const KM::Vector4& vec)
		{
			_right = vec;
		}

		inline const KM::Vector4& GetRightVector(void) const
		{
			return _right;
		}
//==========================================================================================================================
//Mouse
//==========================================================================================================================
		inline void SetMouseSensitivity(F32 val)
		{
			_mouseSensitivity = val;
		}

		inline F32 GetMouseSensitivity(void)
		{
			return _mouseSensitivity;
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
		KM::Matrix4 					_projection;	///< Projection Matrix4 (Orthographic or Perspective). Not used 
		
	protected:
		KM::Point  						_position;		///< Position of Camera in world space.
		KM::Point 						_target;
		KM::Vector4 					_up;
		KM::Vector4 					_look;
		KM::Vector4 					_right;
		KM::Point 						_currentMouseCoords;
		KM::Point 						_lastMouseCoords;
		F32								_mouseSensitivity;
		F32 							_yaw;
		F32 							_pitch;
		F32								_deltaYaw;
		F32								_deltaPitch;
		F32 							_fov;
	};//end Camera
}//end namespace