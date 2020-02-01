#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Camera.h>

namespace Tempest
{
/// First Person Camera. This is your standard fps mode of moving. It will follow the mouse as you move it across the screen
/// resetting the position of the mouse to the center of the screen each frame. 
	class FPSCamera : public Camera
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================		
/// Sets the initial position to 0, yaw to R_PIE and pitch to 0. 		
		TEMPEST_API FPSCamera(void);

/// Sets up the initial values for the position, yaw and pitch of the camera. 
/// \param position is the initial position of the Camera. 
/// \param yaw is the rotation along the y axis. The left/right look.
/// \param pitch is the rotation along the x axis. The up/down look.
		TEMPEST_API FPSCamera(const TM::Point& position, F32 yaw, F32 pitch);

/// No implementation.
		TEMPEST_API ~FPSCamera(void);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
/// Called once per frame, this will get the latest mouse coordinates, the screen dimensions and it will update the rotation 
/// of the view port based on these values.
		TEMPEST_API void v_Update(void) final;

/// Uses the values set in Update to actually move the Camera based on the current values of position, yaw and pitch.		
		TEMPEST_API void v_Rotate(void) final;

/// Updates the position of the Camera based on the param. 
/// \param offset is how much the camera should move. This is a unit Vector. (verify, if its not, it should be).
		TEMPEST_API void v_Move(const TM::Vector4& offset) final;

		TEMPEST_API void v_Move(F32 xVal, F32 yVal) final;

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
/// Sets the Up vector for the Level or World that the Camera is in. This is used for v_Rotate.
/// \param vec is the new Up Vector.
		inline void SetWorldUp(const TM::Vector4 vec)
		{
			_worldUp = vec;
		}

/// Returns the current Up Vector for the world or Level the camera is in. 
		inline const TM::Vector4& GetWorldUp(void)
		{
			return _worldUp;
		}

/// Untested, this will zoom the view of the camera forward. 
/// \param val is the amount to zoom the camear. Can be negative or positive, in theory. 
		inline void SetZoom(F64 val)
		{
			_zoomSensitivity = val;
		}

/// Returns the current zoom amount for the camera. 
		inline F64 GetZoom(void)
		{
			return _zoomSensitivity;
		}

/// Set the speed at which v_Move will update the Camera. I don't know if this should be here, or in the game logic. 
/// \param val is the new max rate of change of the position.
		inline void SetMoveSpeed(F32 val)
		{
			_moveSpeed = val;
		}

/// Returns the current speed of the Camera. 
		inline F32 GetMoveSpeed(void)
		{
			return _moveSpeed;
		}

/// Sets up the size of a dead zone for input. This helps to stop stuttering and will change how sensitive the Camera is. 
		inline void SetDeadZone(F32 val)
		{
			_deadZone = val;
		}

	private:
/// Updates all the Vectors for the Camera. This is a more expensive operation.
		//virtual void _v_UpdateCameraVector4s(void);

//==========================================================================================================================
//
//Data
//
//==========================================================================================================================
		F64 	    _zoomSensitivity;	/// How far zoomed in the Camera is.
		F32 	    _moveSpeed;			/// How fast the Camera can v_Move.
		F32		    _deadZone;			/// The Dead zone used for sensitivity of rotation.

	};//end FPSCamera
	typedef shared_ptr<FPSCamera> p_FPSCamera;
}//end Namespace
