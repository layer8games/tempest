#include <Boxes/Firework.h>

using namespace Boxes;

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Firework::Firework(void)
:
_pool(),
_levelID(0),
_maxSize(0)
{
	GameObject::MakeSprite();
}

Firework::Firework(U32 worldID, U32 size)
:
_pool(),
_levelID(worldID),
_maxSize(size)
{
	GameObject::MakeSprite();
}


Firework::~Firework(void)
{  }

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
void Firework::v_Update(void)
{
	for(U32 i = 0; i < _pool.size(); ++i)
	{
		if(_pool[i]->timeAlive > 0.0f && _pool[i]->RigidBody2D.GetActive())
		{
			_pool[i]->timeAlive -= KM::Timer::Instance()->DeltaTime();
		}
		else if(_pool[i]->RigidBody2D.GetActive())
		{
			_pool[i]->RigidBody2D.SetActive(false);
			
			if(_pool[i]->spawnNew)
			{
				_pool[i]->spawnNew = false;
				InitPayload(_pool[i]->spawnNewRule, _pool[i]->RigidBody2D.GetPosition());
				break;
			}
		}
	}
}


//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
void Firework::Reset(U32 rule)
{
	for(U32 i = 0; i < _pool.size(); ++i)
	{
		/*
		_pool[i]->RigidBody2D.SetPosition(0.0f, 0.0f);
		_pool[i]->RigidBody2D.SetColor(0.0f, 0.0f, 0.0f);
		_pool[i]->RigidBody2D.SetScale(0.0f, 0.0f);
		_pool[i]->RigidBody2D.SetVelocity(0.0f, 0.0f);
		_pool[i]->RigidBody2D.SetAcceleration(0.0f, 0.0f);
		_pool[i]->RigidBody2D.SetMass(0.001f);
		_pool[i]->RigidBody2D.SetDamping(0.0f);
		_pool[i]->timeAlive = 0.0f;
		_pool[i]->RigidBody2D.SetActive(false);
		*/
	}

	InitPayload(rule, GameObject::GetPosition());
}