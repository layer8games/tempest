#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/GameObject.h>
#include <Engine/RigidBody2D.h>
#include <Engine/Random.h>
#include <Engine/Point.h>
#include <Engine/Timer.h>

namespace KE = KillerEngine;
namespace KP = KillerPhysics;
namespace KM = KillerMath;

namespace Boxes
{
	class ProjectFactory;

	enum PayloadSpawnRule
	{
		DEFAULT,
		FOUNTAIN,
		BLOOM,
		FAST,
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
		void v_Update(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
		void SetBody(KP::p_RigidBody2D body);

		KP::p_RigidBody2D GetBody(void)
		{
			return p_body;
		}

		void Init(PayloadSpawnRule rule, const KM::Point& pos);

		inline void SetTimeAlive(F32 t)
		{
			_timeAlive = t;
		}

		inline F32 GetTimeAlive(void) const
		{
			return _timeAlive;
		}

		inline PayloadSpawnRule GetSpawnNewRule(void)
		{
			return _spawnNewRule;
		}

		inline bool GetSpawnNew(void) const
		{
			return _spawnNew;
		}

	private:
		KP::p_RigidBody2D 	p_body;
		F32 				_timeAlive;
		PayloadSpawnRule 	_spawnNewRule;
		bool	 			_spawnNew;
	};//end Class
	typedef shared_ptr<Payload> p_Payload;
}//end Namespace
