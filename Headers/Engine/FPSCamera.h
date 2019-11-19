#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Camera.h>

namespace Tempest
{
	class FPSCamera : public Camera
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================		
		TEMPEST_API FPSCamera(void);

		TEMPEST_API FPSCamera(const TM::Point& position, F32 yaw, F32 pitch);

		TEMPEST_API ~FPSCamera(void);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
		TEMPEST_API virtual void v_Update(void) final;

		TEMPEST_API virtual void v_Rotate(void) final;

		TEMPEST_API virtual void v_Move(const TM::Vector4& offset) final;

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
	 	inline void SetWorldUp(const TM::Vector4 vec)
		{
			_worldUp = vec;
		}

		inline const TM::Vector4& GetWorldUp(void)
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
		TM::Vector4 _worldUp;
		F64 	    _zoomSensitivity;
		F32 	    _moveSpeed;
		F32		    _deadZone;

	};//end FPSCamera
	typedef shared_ptr<FPSCamera> p_FPSCamera;
}//end Namespace
