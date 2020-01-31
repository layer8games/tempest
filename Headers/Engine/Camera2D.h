#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Camera.h>

namespace Tempest
{
	class Camera2D : public Camera
	{
	public:
		//==========================================================================================================================
		//
		//Constructors	 	
		//
		//==========================================================================================================================
		TEMPEST_API Camera2D(void);

		TEMPEST_API ~Camera2D(void) final;

		//==========================================================================================================================
		//
		//Functions
		//
		//==========================================================================================================================
		/// No implemenations. This is meant to overloaded.				
		TEMPEST_API void v_Move(const TM::Vector4& offset) final;
		
		TEMPEST_API void v_Move(F32 xVal, F32 yVal);
		
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
	private:
		F32 	    _moveSpeed;			/// How fast the Camera can v_Move.

	};//end Class
	typedef shared_ptr<Camera2D> p_Camera2D;
}
