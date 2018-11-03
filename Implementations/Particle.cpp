#include <Engine/Particle.h>
#include <iostream>

using namespace KillerPhysics;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
Particle::Particle(void)
:
_velocity(0.0f),
_acceleration(0.0f),
_forceAccum(0.0f),
_gravityForce(0.0f),
_inverseMass(1.0f),
_damping(0.999f)
{  }

Particle::Particle(const Particle* particle)
:
_velocity(particle->GetVelocity()),
_acceleration(particle->GetAcceleration()),
_forceAccum(particle->GetForces()),
_gravityForce(particle->GetGravityForce()),
_inverseMass(particle->GetInverseMass()),
_damping(particle->GetDamping())
{  }

Particle::Particle(const Particle& particle)
:
_velocity(particle.GetVelocity()),
_acceleration(particle.GetAcceleration()),
_forceAccum(particle.GetForces()),
_gravityForce(particle.GetGravityForce()),
_inverseMass(particle.GetInverseMass()),
_damping(particle.GetDamping())
{  }

Particle::~Particle(void)
{  }

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
void Particle::v_Update()
{

}

void Particle::Integrate(void)
{
	if(_inverseMass == 0) return;

	F32 delta = KM::Timer::Instance()->DeltaTime();

	assert(delta > 0.0f);

	KE::GameObject::AddScaledPosition(_velocity, delta);

	KM::Vector resultingAcc = _acceleration;
	
	resultingAcc += _gravityForce;

	resultingAcc.AddScaledVector(_forceAccum, delta);

	_velocity.AddScaledVector(resultingAcc, delta);

	_velocity *= real_pow(_damping, delta);

	ClearAccumulator();
}

void Particle::ClearAccumulator(void)
{
	_forceAccum.Reset();
}

void Particle::AddForce(const KM::Vector force)
{
	_forceAccum += force;
}

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
const real Particle::GetMass(void)
{
	if(_inverseMass == 0.0f)
	{
		return REAL_MAX;
	}
	else
	{
		return static_cast<real>(1.0f) / _inverseMass;
	}
}