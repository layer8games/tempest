#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Camera.h>
#include <Engine/Vector4.h>

namespace KM = KillerMath;

namespace KillerEngine
{
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

		//to test later
		//If you use this, make sure to comment out the Vector4 update 
		//in the implementation
/*
		inline const virtual KM::Matrix4 GetViewMatrix4(void)
		{
			return KM::Matrix4::FPSView(_position, _yaw, _pitch);
		}
*/
		void Orbit(void);

		void Zoom(void);

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
}//end Namespace
