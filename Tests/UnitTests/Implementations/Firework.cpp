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
		if(_pool[i]->timeAlive > 0.0f && _pool[i]->particle.GetActive())
		{
			_pool[i]->timeAlive -= KM::Timer::Instance()->DeltaTime();
		}
		else if(_pool[i]->particle.GetActive())
		{
			_pool[i]->particle.SetActive(false);
			
			if(_pool[i]->spawnNew)
			{
				_pool[i]->spawnNew = false;
				InitPayload(_pool[i]->spawnNewRule, _pool[i]->particle.GetPosition());
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

void Firework::InitPayload(U32 rule, KM::Point pos)
{
	KM::Random random { };

	if(rule == 1)
	{
		F32 speedModifier = 15.0f;

		for(U32 i = 1; i < 80; ++i)
		{
			_pool[i]->particle.SetPosition(pos);
			_pool[i]->particle.SetColor(1.0f, 1.0f, 0.25f);
			_pool[i]->particle.SetScale(2.0f, 2.0f);
			_pool[i]->particle.SetVelocity(KM::Vector4((random.RandomFloat(-1.0f, 1.0f) * speedModifier), 
								   (random.RandomFloat(0.0f, speedModifier) * speedModifier)));
			_pool[i]->particle.SetAcceleration(KM::Vector4((random.RandomFloat(-1.0f, 1.0f) * speedModifier), -1.0f));
			_pool[i]->particle.SetMass(100.0f);
			_pool[i]->particle.SetDamping(0.5f);
			_pool[i]->timeAlive = random.RandomFloat(1.0f, 3.0f);
			_pool[i]->particle.SetActive(true);
			_pool[i]->spawnNew = false;
		}		
	}
	else if(rule == 2)
	{
		F32 speedModifier = 80.0f;
		for(U32 i = 0; i < 75; ++i)
		{
			_pool[i]->particle.SetPosition(pos);
			_pool[i]->particle.SetColor(1.0f, 1.0f, 0.25f);
			_pool[i]->particle.SetScale(1.0f, 1.0f);
			_pool[i]->particle.SetVelocity(KM::Vector4((random.RandomFloat(-1.0f, 1.0f) * speedModifier), 0.0f));
			_pool[i]->particle.SetAcceleration(KM::Vector4(0.0f, (random.RandomFloat(-1.0f, 1.0f) * speedModifier)));
			_pool[i]->particle.SetMass(50.0f);
			_pool[i]->particle.SetDamping(0.999f);
			_pool[i]->timeAlive = random.RandomFloat(1.0f, 3.0f);
			_pool[i]->particle.SetActive(true);
			_pool[i]->spawnNew = false;
		}
	}
	else if(rule == 3)
	{
		F32 speedModifier = 25.0f;
		for(int i = 0; i < 10; ++i)
		{
			_pool[i]->particle.SetPosition(pos);
			_pool[i]->particle.SetColor(1.0f, 1.0f, 0.25f);
			_pool[i]->particle.SetScale(5.0f, 5.0f);
			_pool[i]->particle.SetVelocity(KM::Vector4((random.RandomFloat(-1.0f, 1.0f) * speedModifier), 0.0f));
			_pool[i]->particle.SetAcceleration(KM::Vector4(0.0f, (random.RandomFloat(-1.0f, 1.0f) * speedModifier)));
			_pool[i]->particle.SetMass(50.0f);
			_pool[i]->particle.SetDamping(0.999f);
			_pool[i]->timeAlive = random.RandomFloat(1.0f, 3.0f);
			_pool[i]->spawnNew = true;
			_pool[i]->particle.SetActive(true);
			_pool[i]->spawnNewRule = 4;
		}
	}	
	else if(rule == 4)
	{
		U32 payloadSize = 25;
		F32 speedModifier = 75.0f;
		U32 index = 0;
		for(U32 count = 0; count < payloadSize; count)
		{
			if(!_pool[index]->particle.GetActive())
			{
				_pool[index]->particle.SetPosition(pos);
				_pool[index]->particle.SetColor(1.0f, 1.0f, 0.25f);
				_pool[index]->particle.SetScale(5.0f, 5.0f);
				_pool[index]->particle.SetVelocity(KM::Vector4((random.RandomFloat(-1.0f, 1.0f) * speedModifier)));
				_pool[index]->particle.SetAcceleration(KM::Vector4(0.0f, (random.RandomFloat(-1.0f, 1.0f) * speedModifier)));
				_pool[index]->particle.SetMass(50.0f);
				_pool[index]->particle.SetDamping(0.999f);
				_pool[index]->timeAlive = random.RandomFloat(1.0f, 3.0f);
				_pool[index]->particle.SetActive(true);
				_pool[index]->spawnNew = false;
				++count;
			}

			++index;
			
			if(index >= _pool.size())
			{
				break;
			}
		}
	}
	else
	{
		KE::ErrorManager::Instance()->SetError(KE::ErrorCode::APPLICATION, "Firework-> So such rule " + rule);
	}
}

void Firework::Reset(U32 rule)
{
	for(U32 i = 0; i < _pool.size(); ++i)
	{
		_pool[i]->particle.SetPosition(0.0f, 0.0f);
		_pool[i]->particle.SetColor(0.0f, 0.0f, 0.0f);
		_pool[i]->particle.SetScale(0.0f, 0.0f);
		_pool[i]->particle.SetVelocity(0.0f, 0.0f);
		_pool[i]->particle.SetAcceleration(0.0f, 0.0f);
		_pool[i]->particle.SetMass(0.001f);
		_pool[i]->particle.SetDamping(0.0f);
		_pool[i]->timeAlive = 0.0f;
		_pool[i]->particle.SetActive(false);
	}

	InitPayload(rule, GameObject::GetPosition());
}