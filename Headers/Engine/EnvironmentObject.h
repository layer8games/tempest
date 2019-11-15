/*========================================================================


This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#pragma once

//===== Engine Includes =====
#include <Engine/Atom.h>
#include <Engine/GameObject.h>
#include <Engine/Point.h>

namespace TM = TempestMath;

//===== STL Includes =====
#include <memory>

namespace Tempest
{
//==========================================================================================================================
//Documentation
//==========================================================================================================================
/*! 
	This is an implementation of a GameObject which will reprents static, unmoving background objects which the player will 
	not be allowed to pass through. These are things like rocks, trees, houses, etc.  
*/	
	class EnvironmentObject : public GameObject
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
/*! 
	Default Constructor. No special actions taken. 
*/
		EnvironmentObject(void);

/*! 
	Calls GameObject::SetPosition and GameObject::SetDimensions. 
*/		
		EnvironmentObject(const TM::Point& pos, F32 w, F32 h);

/*! Default Destructor. No special action taken. */		
		~EnvironmentObject(void);
//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
/*! 
	Empty function, needed because its a pure virtual function. 
*/
		inline void v_Update(void) final
		{  }

	private:
		
	};//end Class
}//end Namespace