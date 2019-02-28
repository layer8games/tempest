#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Camera.h>

namespace KillerEngine
{
	class FPSCamera : public Camera
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================		
		FPSCamera(void);

		FPSCamera(const KM::Vector4 position, F32 yaw, F32 pitch);

		~FPSCamera(void);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
		virtual void v_Update(void);

		virtual void v_Rotate(void);

		virtual void v_Move(const KM::Vector4 offset);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
	 	inline void SetWorldUp(const KM::Vector4 vec)
		{
			_worldUp = vec;
		}

		inline const KM::Vector4& GetWorldUp(void)
		{
			return _worldUp;
		}

		inline void SetZoom(F64 val)
		{
			_zoomSensitivity = val;
		}

		inline F64 GetZoom(void)
		{
			return _zoomSensitivity;
		}

		inline void SetMoveSpeed(F32 val)
		{
			_moveSpeed = val;
		}

		inline F32 GetMoveSpeed(void)
		{
			return _moveSpeed;
		}

		inline void SetDeadZone(F32 val)
		{
			_deadZone = val;
		}

	private:
		virtual void _v_UpdateCameraVector4s(void);

//==========================================================================================================================
//
//Data
//
//==========================================================================================================================
		KM::Vector4 _worldUp;
		F64 	   _zoomSensitivity;
		F32 	   _moveSpeed;
		F32		   _deadZone;

	};//end FPSCamera
}//end Namespace
