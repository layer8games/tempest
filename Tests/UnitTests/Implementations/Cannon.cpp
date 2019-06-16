#include <Boxes/Cannon.h>

using namespace Boxes;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
Cannon::Cannon(void) 
: 
_movementSpeed(1.0f),
_bottomBoundary(0.0f),
_topBoundary(700.0f),
_upDirection(0.0f, 1.0f),
_downDirection(0.0f, -1.0f),
_projectilePool()
{
	GameObject::MakeSprite();
}

Cannon::~Cannon(void)
{
	_projectilePool.clear();
}
//==========================================================================================================================
//
//Update
//
//==========================================================================================================================
void Cannon::v_Update(void)
{
	//_forceRegistry.UpdateForces();

	//std::cout << ""

	F32 yPos = KE::GameObject::GetPosition()[1];

	if(yPos > _bottomBoundary && yPos < _topBoundary)
	{
		if(KE::Controller::Instance()->GetKeyHeld(KE::W))
		{
			KE::GameObject::AddScaledPosition(_upDirection, _movementSpeed * KM::Timer::Instance()->DeltaTime());
		}
		else if(KE::Controller::Instance()->GetKeyHeld(KE::S))
		{
			KE::GameObject::AddScaledPosition(_downDirection, _movementSpeed * KM::Timer::Instance()->DeltaTime());
		}
	}
	else
	{
		if(yPos <= _bottomBoundary)
		{
			KE::GameObject::AddScaledPosition(_upDirection, _movementSpeed);
		}
		else if(yPos >= _topBoundary)
		{
			KE::GameObject::AddScaledPosition(_downDirection, _movementSpeed);
		}
	}	
}

void Cannon::Fire(const KM::Vector4& heading, ProjectileType type)
{
	for(auto projectile : _projectilePool)
	{
		if(!projectile->GetActive())
		{
			projectile->SetPosition(GameObject::GetPosition());
			projectile->SetType(type);
			projectile->AddScaledVelocity(heading, projectile->GetSpeedScale());
			projectile->SetActive(true);
			return;
		}
	}
}