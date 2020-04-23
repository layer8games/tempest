#pragma once

//=====Killer includes=====
#include <Engine/Atom.h>
#include <Engine/Matrix4.h>
#include <Engine/Vector4.h>
#include <Engine/Point3.h>
#include <Engine/Color.h>
#include <Engine/Timer.h>

#include <vector>

namespace TM = TempestMath;

namespace Tempest
{
//==========================================================================================================================
//
//Camera
//
//==========================================================================================================================	
/// Default Camera for the Engine. This Camera is fully operational. It controls the offset of the view port from the origin.
/// When the position of the Camera is set, every other GameObject that is rendered is moved the negative of the position.
/// If this Camera doesn't do what you need it to do, it is meant to be extended, with functions that are virtual.
	class Camera
	{
	public:
//==========================================================================================================================
//
//Constructor
//
//==========================================================================================================================
/// No implementation.
		TEMPEST_API Camera(void);

/// No implementation		
		TEMPEST_API virtual ~Camera(void);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
/// No implemenations. This is meant to overloaded.		
		inline virtual void v_Rotate(void)
		{  }

/// No implemenations. This is meant to overloaded.		
		inline virtual void v_Update(void)
		{  }

/// No implemenations. This is meant to overloaded.				
		inline virtual void v_Move(const TM::Vector4& offset)
		{  }

		inline virtual void v_Move(F32 xVal, F32 yVal)
		{  }

		inline virtual void v_Move(F32 xVal, F32 yVal, F32 zVal)
		{  }

//==========================================================================================================================
//
//Camera Functions
//
//==========================================================================================================================
	/// Sets private Matrix4 to use an orthogrphic projection. The params should be sent in game units. For instance, the default 
	///	version of this function calls the OpenGLGameWindow dimensions to size the projection size. 
	/// \param left is the left border of the view port.
	/// \param right is the right border of the view port.
	/// \param bottom is the lower border of the view port
	/// \param top is the uppoer border of the view port.
	/// \param nearPlane is the close (next to the view) border of the view port.
	/// \param farPlane is the distance border of the view port, ie. the max view distance.
		TEMPEST_API void SetOrthographic(F32 left, F32 right, F32 bottom, F32 top, F32 nearPlane, F32 farPlane);

	/// Sets the private Matrix4 to use a perspective projection. 
	/// \param fov is the field of view for the view port. 70 to 90 is a good range for this.
	/// \param aspect is the aspect ratio of the view port. This can be found by dividing the width by the hieght of the window.
	/// \param farPlane is the distance border of the view port, ie. the max view distance.
		TEMPEST_API void SetPerspective(F32 fov, F32 aspect, F32 nearPlane, F32 farPlane);

	/// Helper function to set the projection Matrix4 to be an identity Matrix4. 
	/// \param none
		TEMPEST_API void SetDefaultMatrix4(void);

	/// Returns a Matrix4 that can be used to transform that can be used as a view matrix for the camera. For use in a Shader for instance.
		inline const virtual TM::Matrix4 GetViewMatrix4(void)
		{
			return TM::Matrix4::LookAt(_position, _target, _up);
		}

	/// This should not be used right now. In theory, it returns an internally cached projection matrix for rendering.
		inline const TM::Matrix4& GetProjectionMatrix4(void)
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
	///	Change the color OpenGL will use to color the background of the program window. This includes the call to actually change
	///	that color state in OpenGL.
	/// \param col is the new color to set.
		inline void SetColor(const Color& col)
		{ 
			_bgColor = col;
			glClearColor(_bgColor[0], _bgColor[1], _bgColor[2], _bgColor[3]);
		}

	///	Change the color OpenGL will use to color the background of the program window. This includes the call to actually change
	///	that color state in OpenGL.
	/// \param red should be between 0 and 1.
	/// \param green should be between 0 and 1.
	/// \param blue should be between 0 and 1.
		inline void SetColor(F32 red, F32 green, F32 blue)
		{
			_bgColor[0] = red;
			_bgColor[1] = green;
			_bgColor[2] = blue;
			glClearColor(_bgColor[0], _bgColor[1], _bgColor[2], _bgColor[3]);
		}

	/// Returns the current background color. Not currently in use.
		inline const Color& GetBackgroundColor(void) const
		{
			return _bgColor;
		}

//==========================================================================================================================
//Position
//==========================================================================================================================
	/// Set the position of the Camera along the x and y axis in the world space.
	/// \param x is the new position along the x axis.
	/// \param y is the new position along the y axis.
		inline void SetPosition(F32 x, F32 y)
		{
			_position.x = x;
			_position.y = y;

			_v_UpdateCameraVectors();
		}

	/// Set the position of the Camera along the x, y and z axis in world space.
	/// \param x is the new position along the x axis.
	/// \param y is the new position along the y axis.
	/// \param z is the new position along the z axis.
		inline void SetPosition(F32 x, F32 y, F32 z)
		{
			_position.x = x;
			_position.y = y;
			_position.z = z;

			_v_UpdateCameraVectors();
		}

	/// Set the position of the Camera to a Point in world space.
	/// \param point is the new position.
		inline void SetPosition(const TM::Point3& point)
		{
			_position = point;

			_v_UpdateCameraVectors();
		}

	/// Set the position of the Camera in world space scaled by a value.
	/// \param x is the new position along the x axis.
	/// \param y is the new position along the y axis.
	/// \param z is the new position along the z axis.
	/// \param scale is the value to scale the positions by		
		inline void ScalePosition(F32 x, F32 y, F32 z, F32 scale)
		{
			_position.AddScaledPoint(TM::Point3(x, y, z), scale);

			_v_UpdateCameraVectors();
		}

	/// Set the position of the Camera in world space scaled by a value.
	/// \param point is the new position.
	/// \param scale is the value to scale the positions by
		inline void ScalePosition(const TM::Point3& point, F32 scale)
		{
			_position.AddScaledPoint(point, scale);

			_v_UpdateCameraVectors();
		}

	/// Return the current position of the Camera in world space.
		inline const TM::Point3& GetPosition(void) const
		{
			return _position;
		}

//==========================================================================================================================
//Target
//==========================================================================================================================
	/// Set a pointer to a target Point in world space. This can be used for many different things. Point is set and stored by 
	/// value, not ref or pointer.
		inline void SetTarget(const TM::Point3& target)
		{
			_target = target;
		}

	/// Set the position in world space of the target manually. Z is set to 0.0f automatically.
	/// \param xVal is the new position along the x axis.
	/// \param yVal is the new position along the y axis.
		inline void SetTarget(F32 xVal, F32 yVal)
		{
			_target.x = xVal;
			_target.y = yVal;
			_target.z = 0.0f;
		}

	/// Set the position in world space of the target manually.
	/// \param xVal is the new position along the x axis.
	/// \param yVal is the new position along the y axis.
	/// \param zVal is the new position along the z axis.
		inline void SetTarget(F32 xVal, F32 yVal, F32 zVal)
		{
			_target.x = xVal;
			_target.y = yVal;
			_target.z = zVal;
		}

	/// Return the current target point in world space.
		inline const TM::Point3& GetTarget(void)
		{
			return _target;
		}

//==========================================================================================================================
//Up
//==========================================================================================================================		
	///	Set the direction of Up in world space for the Camera. This is not tested in a way that defines up other than 1.0f.
	/// \param val is the new direction of just y in the up vector. 
		inline void SetUpVector(F32 val)
		{
			_up.y = val;
		}

	///	Set the direction of Up in world space for the Camera. This is not tested in a way that defines up other than 1.0f.
	/// \param xVal is the x direction of Up.
	/// \param yVal is the y direction of Up.
	/// \param zVal is the z direction of Up.
		inline void SetUpVector(F32 xVal, F32 yVal, F32 zVal)
		{
			_up.x = xVal;
			_up.y = yVal;
			_up.z = zVal;
		}

	///	Set the direction of Up in world space for the Camera. This is not tested in a way that defines up other than 1.0f.
	/// \param vec is the full direction of Up in vector form.
		inline void SetUpVector(const TM::Vector4& vec)
		{
			_up	 = vec;
		}

	/// Return the current value of the Up Vector.
		inline const TM::Vector3& GetUpVector(void) const
		{
			return _up;
		}

//==========================================================================================================================
//Look
//==========================================================================================================================
	/// Set the direction of the Look vector.
	/// \param val is used to set all param of Look.
		inline void SetLookVector(F32 val)
		{
			_look = val;
		}

	/// Set the direction of the Look vector.
	/// \param xVal is the x direction of Up.
	/// \param yVal is the y direction of Up.
		inline void SetLookVector(F32 xVal, F32 yVal)
		{
			_look.x = xVal;
			_look.y = yVal;
		}

	/// Set the direction of the Look vector.
	/// \param xVal is the x direction of Up.
	/// \param yVal is the y direction of Up.
	/// \param zVal is the z direction of Up.
		inline void SetLookVector(F32 xVal, F32 yVal, F32 zVal)
		{
			_look.x = xVal;
			_look.y = yVal;
			_look.z = zVal;
		}

	/// Set the direction of the Look vector.
	/// \param vec is the new value for Look.
		inline void SetLookVector(const TM::Vector4& vec)
		{
			_look = vec;
		}

	/// Return the current value of Look.
		inline const TM::Vector3& GetLookVector(void) const
		{
			return _look;
		}

//==========================================================================================================================
//Right
//==========================================================================================================================
	/// Set the value of the Right vector.
	/// \param val is used to set all values of Right
		inline void SetRightVector(F32 val)
		{
			_right = val;
		}

	/// Set the value of the Right vector.
	/// \param xVal is the x direction of Right.
	/// \param yVal is the y direction of Right.
		inline void SetRightVector(F32 xVal, F32 yVal)
		{
			_right.x = xVal;
			_right.y = yVal;
		}

	/// Set the value of the Right vector.
	/// \param xVal is the x direction of Right.
	/// \param yVal is the y direction of Right.
	/// \param zVal is the z direction of Right.
		inline void SetRightVector(F32 xVal, F32 yVal, F32 zVal)
		{
			_right.x = xVal;
			_right.y = yVal;
			_right.z = zVal;
		}

	/// Set the value of the Right vector.
	/// \param vec is the new direction of Right.
		inline void SetRightVector(const TM::Vector4& vec)
		{
			_right = vec;
		}

	/// Return the current direction of the Right Vector.
		inline const TM::Vector3& GetRightVector(void) const
		{
			return _right;
		}
//==========================================================================================================================
//Mouse
//==========================================================================================================================
	/// Set how sensitive the mouse should be. This is a scaling value used on raw input.
	/// \param val is the new sensitivity. 
		inline void SetMouseSensitivity(F32 val)
		{
			_mouseSensitivity = val;
		}

	/// Return the current value of Mouse Sensitivity.
		inline F32 GetMouseSensitivity(void)
		{
			return _mouseSensitivity;
		}

//==========================================================================================================================
//Yaw
//==========================================================================================================================
	/// Return the current value of Yaw.
		inline F32 GetYaw(void) const
		{
			return _yaw;
		}

//==========================================================================================================================
//Pitch
//==========================================================================================================================		
	/// Return the current value of Pitch.		
		inline F32 GetPitch(void) const
		{
			return _pitch;
		}

//==========================================================================================================================
//Field of View
//==========================================================================================================================
	/// Set the Field of View for the Camera.
	/// \param val is the new value. 70 to 90 is a good range.
		inline void SetFOV(F32 val)
		{
			_fov = val;
		}

	/// Return the current value of Field of View
		inline F32 GetFOV(void) const
		{
			return _fov;
		}

	

	private:
	

//==========================================================================================================================
//
//Data
//
//==========================================================================================================================		
		Color  							_bgColor;				///< Background color of current level. Not in use yet.
		TM::Matrix4 					_projection;				///< Projection Matrix4 (Orthographic or Perspective). Not used 
		
	protected:
		/// Updates the internal vectors of the Camera based on changes or input. For instance, if Right changes, then Up may have to 
	/// adjust to match it. TODO:: This should maybe be moved to Protected. Currently there is no implementation.
		inline virtual void _v_UpdateCameraVectors(void)
		{
			DefaultUpdateCameraVectors();
		}

		TEMPEST_API void DefaultUpdateCameraVectors(void);
		
		TM::Point3  						_position;				///< Position of Camera in world space.
		TM::Point3 						_target;				///< Position the Camera should be aware of. Can be used for many purposes.
		TM::Vector3						_worldUp;			/// Direction of Up in the world or Level.
		TM::Vector3 					_up;					///< Direction, in world space, of up for the Camera.
		TM::Vector3 					_look;					///< Direction, in world space, that the Camear should point, or "look" at.
		TM::Vector3 					_right;					///< Direction, in world space, that is perpendicular, to the right.
		TM::Point3 						_currentMouseCoords;	///< Current position of the mouse cursor in screen space. Not currently used.
		TM::Point3 						_lastMouseCoords;		///< Last known position of the mouse cursor in screen space. Not currently used.
		F32								_mouseSensitivity;		///< Scaling factor used to make the mouse movments more drastice or pronounced. Not used in the default Camera.
		F32 							_yaw;					///< Yaw, or y orientation value.
		F32 							_pitch;					///< Pitch, or x orientation value.
		F32								_deltaYaw;				///< The difference between the current and last yaw.
		F32								_deltaPitch;			///< The difference between the current and last pitch.
		F32 							_fov;					///< Field of View for the camera. Affects the projection, specifically, when perspective is used how far away objects are skewed and what is culled.
	};//end Camera
	typedef shared_ptr<Camera> p_Camera;
}//end namespace