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
	for(auto payload : _pool)
	{
		else if(payload->GetActive())
		{
			payload->SetActive(false);
			
			if(payload->GetSpawnNew())
			{
				InitPayload(payload->GetSpawnNewRule(), payload->GetPosition());
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
	for(auto payload : _pool)
	{
		
		payload->SetPosition(0.0f, 0.0f);
		payload->SetColor(0.0f, 0.0f, 0.0f);
		payload->SetScale(0.0f, 0.0f);
		payload->GetBody()->SetVelocity(0.0f, 0.0f);
		payload->GetBody()->SetAcceleration(0.0f, 0.0f);
		payload->GetBody()->SetMass(0.001f);
		payload->GetBody()->SetDamping(0.0f);
		payload->SetTimeAlive(0.0f);
		payload->SetActive(false);
	}
}