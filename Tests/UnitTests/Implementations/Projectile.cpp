#include <Boxes/Projectile.h>

using namespace Boxes;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
Projectile::Projectile(void) 
: 
_maxDistance(25),
_distanceTraveled(0),
_speedScale(0),
_type()
{
	GameObject::MakeSprite();
	GameObject::SetActive(false);
}

Projectile::~Projectile(void)
{  }

//==========================================================================================================================
//
//Virtual GameObject functions
//
//==========================================================================================================================
void Projectile::v_Update(void)
{		
	_distanceTraveled += KM::Timer::Instance()->DeltaTime();
	
	if(_distanceTraveled >= _maxDistance) 
	{ 
		GameObject::SetActive(false);
		_distanceTraveled = 0;
		//RigidBody2D::SetVelocity(0.0f, 0.0f);
	}
}

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================	
void Projectile::SetMaxDistance(F32 dist)
{
	_maxDistance = dist;
}

F32 Projectile::GetMaxDistance(void)
{
	return _maxDistance;
}

void Projectile::SetSpeedScale(F32 scale)
{
	_speedScale = scale;
}

F32 Projectile::GetSpeedScale(void)
{
	return _speedScale;
}

void Projectile::SetType(ProjectileType type)
{
	switch(type)
	{
		case BULLET:
			_maxDistance = 3.0f;
			//RigidBody2D::SetMass(25.0f);
			//RigidBody2D::SetDamping(0.99f);
			//RigidBody2D::SetAcceleration(0.0f, 0.0f);
			GameObject::SetScale(5.0f, 5.0f);
			GameObject::SetTexture(KE::TextureManager::Instance()->GetTexture(301));
			_speedScale = 300.0f;
			break;
		case ARTILLERY:
			_maxDistance = 4.0f;
			//RigidBody2D::SetMass(75.0f);
			//RigidBody2D::SetDamping(0.6f);
			//RigidBody2D::SetAcceleration(0.0f, 0.0f);
			GameObject::SetScale(15.0f, 15.0f);
			GameObject::SetTexture(KE::TextureManager::Instance()->GetTexture(302));
			_speedScale = 350.0f;
			break;
		case MISSILE:
			_maxDistance = 6.0f;
			//RigidBody2D::SetMass(50.0f);
			//RigidBody2D::SetDamping(0.99f);
			//RigidBody2D::SetAcceleration(50.0f, 0.0f);
			GameObject::SetScale(20.0f, 20.0f);
			GameObject::SetTexture(KE::TextureManager::Instance()->GetTexture(303));
			_speedScale = 200.0f;
			break;
		case FIRE_BALL:
			_maxDistance = 3.0f;
			//RigidBody2D::SetMass(50.0f);
			//RigidBody2D::SetDamping(0.99f);
			//RigidBody2D::SetAcceleration(10.0f, 0.0f);
			GameObject::SetScale(7.5f, 7.5f);
			GameObject::SetTexture(KE::TextureManager::Instance()->GetTexture(304));
			_speedScale = 250.0;
			break;
		case LAZER:
			_maxDistance = 10.0f;
			//RigidBody2D::SetMass(0.1f);
			//RigidBody2D::SetDamping(0.99f);
			//RigidBody2D::SetAcceleration(0.0f, 0.0f);
			GameObject::SetScale(10.0f, 7.5f);
			GameObject::SetTexture(KE::TextureManager::Instance()->GetTexture(305));
			_speedScale	= 900.0f;
			break;
		case GRENADE:
			_maxDistance = 3.0f;
			//RigidBody2D::SetMass(75.0f);
			//RigidBody2D::SetDamping(0.25f);
			//RigidBody2D::SetAcceleration(0.0f, 0.0f);
			GameObject::SetScale(15.0f, 15.0f);
			GameObject::SetTexture(KE::TextureManager::Instance()->GetTexture(306));
			_speedScale	= 350.0f;
			break;
		default:
			KE::ErrorManager::Instance()->SetError(KE::ErrorCode::APPLICATION, "Boxes::Projectile -> No ProjectileType provided in constructor.");
		break;
	}
}

ProjectileType Projectile::GetType(void)
{
	return _type;
}
