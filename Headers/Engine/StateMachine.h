#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>

namespace Tempest
{
	class StateMachine
	{
	public:
		//==========================================================================================================================
		//
		//Constructors	 	
		//
		//==========================================================================================================================

		~StateMachine(void);

		//==========================================================================================================================
		//
		//Functions
		//
		//==========================================================================================================================
		static shared_ptr<StateMachine> Instance(void);
	protected:
		StateMachine(void);

	private:
		static shared_ptr<StateMachine> _instance;

	};//end Class
	typedef shared_ptr<StateMachine> p_StateMachine;
}
