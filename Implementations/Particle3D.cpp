#include <Engine/Particle3D.h>

using namespace KillerPhysics;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================	
Particle3D::Particle3D(void) 
: 
_velocity(0.0f), 
_acceleration(0.0f), 
_inverseMass(0.0f), 
_damping(0.999f), 
_forceAccum()
{  }

Particle3D::Particle3D(const Particle3D* particle)
:
_velocity(particle->GetVelocity()),
_acceleration(particle->GetAcceleration()),
_forceAccum(particle->GetForces()),
_gravityForce(particle->GetGravityForce()),
_inverseMass(particle->GetInverseMass()),
_damping(particle->GetDamping())
{  }

Particle3D::Particle3D(const Particle3D& particle)
:
_velocity(particle.GetVelocity()),
_acceleration(particle.GetAcceleration()),
_forceAccum(particle.GetForces()),
_gravityForce(particle.GetGravityForce()),
_inverseMass(particle.GetInverseMass()),
_damping(particle.GetDamping())
{  }

Particle3D::~Particle3D(void) 
{  }

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
//==========================================================================================================================
//Mass
//==========================================================================================================================
const real Particle3D::GetMass(void) const
{
	if(_inverseMass == 0)
	{ 
		return REAL_MAX; 
	}
	else 
	{ 
		return real(1.0) / _inverseMass; 
	}
}

void Particle3D::SetMass(const real mass)
{
	assert(mass != 0);
	_inverseMass = real(1.0) / mass;
}

//==========================================================================================================================
//
//Particle Functions
//
//==========================================================================================================================
void Particle3D::v_Update(void)
{
	Integrate();
}

void Particle3D::Integrate(void) 
{
	//if there no mass, there is no update
	if(_inverseMass == 0) 
	{
		return;
	} 

	F32 delta = KM::Timer::Instance()->DeltaTime();

	//Update position
	KE::GameObject3D::AddScaledPosition(_velocity, delta);

	KM::Vector3 resultingAcc = _acceleration;

	_velocity.AddScaledVector(resultingAcc, delta);

	_velocity *= real_pow(_damping, delta);

	ClearAccumulator();
}