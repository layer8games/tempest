#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Vector2.h>
#include <Engine/SteeringOutput2D.h>

namespace TM = TempestMath;


namespace Tempest
{
	class Steering2D
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		TEMPEST_API Steering2D(void);
		
		TEMPEST_API ~Steering2D(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
		TEMPEST_API real GetNewOrientation(real currentOrientation, const TM::Vector2& velocity);

		TEMPEST_API virtual SteeringOutput2D v_GetSteering(void)=0;

	private:


	};//end Class
	typedef shared_ptr<Steering2D> p_Steering2D;
}
