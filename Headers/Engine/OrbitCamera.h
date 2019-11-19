#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Camera.h>
#include <Engine/Vector4.h>

namespace TM = TempestMath;

namespace Tempest
{
	class OrbitCamera : public Camera
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		TEMPEST_API OrbitCamera(void);

		TEMPEST_API ~OrbitCamera(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================		
		TEMPEST_API virtual void v_Rotate(void) final;

		TEMPEST_API virtual void v_Update(void) final;

		//to test later
		//If you use this, make sure to comment out the Vector4 update 
		//in the implementation
/*
		inline const virtual TM::Matrix4 GetViewMatrix4(void)
		{
			return TM::Matrix4::FPSView(_position, _yaw, _pitch);
		}
*/
		TEMPEST_API void Orbit(void);

		TEMPEST_API void Zoom(void);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================		
		//ToDO: Make the min and max member vairables
		//that can be changed per instance
		inline void SetRadius(F32 val)
		{
			_radius = FLOAT_CLAMP(val, 2.0f, 80.0f);
		}

	private:
		virtual void _v_UpdateCameraVectors(void);
//==========================================================================================================================
//
//Data
//
//==========================================================================================================================		
		F32 _radius;

	};//end OrbitCamera
	typedef shared_ptr<OrbitCamera> p_OrbitCamera;
}//end Namespace
