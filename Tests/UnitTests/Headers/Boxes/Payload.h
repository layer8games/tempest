#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/GameObject.h>
#include <Engine/RigidBody2D.h>
#include <Engine/Point.h>
#include <Engine/Random.h>

namespace KE = KillerEngine;
namespace KP = KillerPhysics;
namespace KM = KillerMath;

//===== Boxes Includes =====
#include <Boxes/ProjectFactory.h>

namespace Boxes
{
	enum PayloadSpawnRule
	{
		DEFAULT,
		FOUNTAIN,
		BLOOM,
		FAST
	};

	class Payload : public KE::GameObject
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		Payload(void);

		~Payload(void);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
		void v_Update(void) final;

//==========================================================================================================================
//
//Fucntions
//
//==========================================================================================================================
		void SetBody(KP::p_RigidBody2D body);

		void Init(PayloadSpawnRule rule, KM::Point pos);

	private:
		KP::p_RigidBody2D 	p_body;
		F32 				_timeAlive;
		PayloadSpawnRule 	_spawnNewRule;
		bool	 			_spawnNew;
		
	};//end Class
	
	typedef shared_ptr<Payload> p_Payload;
}//end Namespace
