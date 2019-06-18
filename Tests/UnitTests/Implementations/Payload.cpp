#include <Boxes/Payload.h>

using namespace Boxes;
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Payload::Payload(void)
:
p_body(nullptr),
_spawnNewRule(DEFAULT),
_timeAlive(0.0f),
_spawnNew(false)
{  }

Payload::~Payload(void)
{  }

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
void Payload::v_Update(void)
{
	if(_timeAlive > 0.0f)
	{
		_timeAlive -= KM::Timer::Instance()->DeltaTime();
	}
	else
	{
		GameObject::SetActive(false);
	}
}

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
void Payload::SetBody(KP::p_RigidBody2D body)
{
	p_body = body;
	p_body->SetObject(this);
}

void Payload::Init(PayloadSpawnRule rule, const KM::Point& pos)
{	
	KM::Random random { };
	F32 speedModifier = 0.0f;

	switch(rule)
	{
	case DEFAULT: 
		speedModifier = 15.0f;
			
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
	break;
	case FOUNTAIN:
		speedModifier = 80.0f;
	
		/*
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
		*/	
	break;
	case BLOOM:
		speedModifier = 25.0f;
		/*
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
		*/
	break;
	case FAST:
		speedModifier = 75.0f;
		/*
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
		*/
	break;
	default:
		KE::ErrorManager::Instance()->SetError(KE::ErrorCode::APPLICATION, "Firework-> So such rule " + rule);
	break;
	};
}
