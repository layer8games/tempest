#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/GameObject.h>
#include <Engine/RigidBody2D.h>
#include <Engine/Random.h>
#include <Engine/LevelManager.h>
#include <Engine/Level.h>
#include <Engine/Timer.h>
#include <Engine/Vector4.h>
#include <Engine/Point.h>
#include <Engine/Matrix4.h>

namespace KE = KillerEngine;
namespace KP = KillerPhysics;

//===== STL includes =====
#include <vector>

//===== Boxes Includes =====
#include <Boxes/Payload.h>

namespace Boxes
{
	typedef std::vector<shared_ptr<Payload>> PayloadPool;

	class Firework : public KE::GameObject
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		Firework(void);

		Firework(U32 levelID, U32 size);

		~Firework(void);
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
		inline void SetMaxSize(U32 size)
		{
			_maxSize = size;
		}

		inline U32 GetMaxSize(void)
		{
			return _maxSize;
		}

		inline void SetLevelID(U32 id)
		{
			_levelID = id;
		}

		inline U32 GetLevelID(void)
		{
			return _levelID;
		}

		inline void SetProjection(const KM::Matrix4 projection)
		{
			_projection = projection;
		}

		void Reset(U32 rule);

		void AddPayload(shared_ptr<Payload> payload)
		{
			_pool.push_back(payload);
		}

	private:
		PayloadPool 					 _pool;
		U32					 			 _levelID;
		U32 				 			 _maxSize;
		KM::Matrix4 					 _projection;
	};//end Class
	typedef shared_ptr<Firework> p_Firework;
}//end Namespace


/*
Backup

void Payload::Init(PayloadSpawnRule rule, const KM::Point& pos)
{	
	KM::Random random { };
	F32 speedModifier = 0.0f;

	switch(rule)
	{
	case DEFAULT: 
		speedModifier = 15.0f;
		for(U32 i = 1; i < 80; ++i)
		{
			
			GameObject::SetPosition(pos);
			GameObject::SetColor(1.0f, 1.0f, 0.25f);
			GameObject::SetScale(2.0f, 2.0f);
			p_body->SetVelocity(KM::Vector4((random.RandomFloat(-1.0f, 1.0f) * speedModifier), 
								   (random.RandomFloat(0.0f, speedModifier) * speedModifier)));
			p_body->SetAcceleration(KM::Vector4((random.RandomFloat(-1.0f, 1.0f) * speedModifier), -1.0f));
			p_body->SetMass(100.0f);
			p_body->SetDamping(0.5f);
			_timeAlive = random.RandomFloat(1.0f, 3.0f);
			GameObject::SetActive(true);
			_spawnNew = false;
			
		}		
	break;
	case FOUNTAIN:
		speedModifier = 80.0f;
		for(U32 i = 0; i < 75; ++i)
		{
			
			_pool[i]->RigidBody2D.SetPosition(pos);
			_pool[i]->RigidBody2D.SetColor(1.0f, 1.0f, 0.25f);
			_pool[i]->RigidBody2D.SetScale(1.0f, 1.0f);
			_pool[i]->RigidBody2D.SetVelocity(KM::Vector4((random.RandomFloat(-1.0f, 1.0f) * speedModifier), 0.0f));
			_pool[i]->RigidBody2D.SetAcceleration(KM::Vector4(0.0f, (random.RandomFloat(-1.0f, 1.0f) * speedModifier)));
			_pool[i]->RigidBody2D.SetMass(50.0f);
			_pool[i]->RigidBody2D.SetDamping(0.999f);
			_pool[i]->timeAlive = random.RandomFloat(1.0f, 3.0f);
			_pool[i]->RigidBody2D.SetActive(true);
			_pool[i]->spawnNew = false;
			
		}
	break;
	case BLOOM:
		speedModifier = 25.0f;
		for(int i = 0; i < 10; ++i)
		{
			
			_pool[i]->RigidBody2D.SetPosition(pos);
			_pool[i]->RigidBody2D.SetColor(1.0f, 1.0f, 0.25f);
			_pool[i]->RigidBody2D.SetScale(5.0f, 5.0f);
			_pool[i]->RigidBody2D.SetVelocity(KM::Vector4((random.RandomFloat(-1.0f, 1.0f) * speedModifier), 0.0f));
			_pool[i]->RigidBody2D.SetAcceleration(KM::Vector4(0.0f, (random.RandomFloat(-1.0f, 1.0f) * speedModifier)));
			_pool[i]->RigidBody2D.SetMass(50.0f);
			_pool[i]->RigidBody2D.SetDamping(0.999f);
			_pool[i]->timeAlive = random.RandomFloat(1.0f, 3.0f);
			_pool[i]->spawnNew = true;
			_pool[i]->RigidBody2D.SetActive(true);
			_pool[i]->spawnNewRule = 4;
				}
	break;
	case FAST:
		//U32 payloadSize = 25;
		//speedModifier = 75.0f;
		//U32 index = 0;
		//for(U32 count = 0; count < payloadSize; count)
		{
			//if(!_pool[index]->RigidBody2D.GetActive())
			{
								_pool[index]->RigidBody2D.SetPosition(pos);
				_pool[index]->RigidBody2D.SetColor(1.0f, 1.0f, 0.25f);
				_pool[index]->RigidBody2D.SetScale(5.0f, 5.0f);
				_pool[index]->RigidBody2D.SetVelocity(KM::Vector4((random.RandomFloat(-1.0f, 1.0f) * speedModifier)));
				_pool[index]->RigidBody2D.SetAcceleration(KM::Vector4(0.0f, (random.RandomFloat(-1.0f, 1.0f) * speedModifier)));
				_pool[index]->RigidBody2D.SetMass(50.0f);
				_pool[index]->RigidBody2D.SetDamping(0.999f);
				_pool[index]->timeAlive = random.RandomFloat(1.0f, 3.0f);
				_pool[index]->RigidBody2D.SetActive(true);
				_pool[index]->spawnNew = false;
			
				//++count;
			}

			//++index;
		}
	break;
	default:
		KE::ErrorManager::Instance()->SetError(KE::ErrorCode::APPLICATION, "Firework-> So such rule " + rule);
	break;
	};
}

*/