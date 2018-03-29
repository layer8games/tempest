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

Particle3D::~Particle3D(void) 
{  }

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
//==========================================================================================================================
//Velocity
//==========================================================================================================================
KM::Vector3& Particle3D::GetVelocity(void)
{
	return _velocity;
}

void Particle3D::SetVelocity(KM::Vector3& vel)
{
	_velocity = vel;
}

void Particle3D::SetVelocity(F32 x, F32 y, F32 z)
{
	_velocity = KM::Vector3(x, y, z);
}

void Particle3D::AddScaledVelocity(const KM::Vector3 v, F32 scale)
{
	_velocity.AddScaledVector(v, scale);
}

//==========================================================================================================================
//Acceleration
//==========================================================================================================================
KM::Vector3& Particle3D::GetAcceleration(void)
{
	return _acceleration;
}

void Particle3D::SetAcceleration(KM::Vector3& acc)
{
	_acceleration = acc;
}

void Particle3D::SetAcceleration(F32 x, F32 y, F32 z)
{
	_acceleration = KM::Vector3(x, y, z);
}

void Particle3D::AddScaledAcceleration(const KM::Vector3& v, F32 scale)
{
	_acceleration.AddScaledVector(v, scale);
}

//==========================================================================================================================
//Damping
//==========================================================================================================================
real Particle3D::GetDamping(void)
{
	return _damping;
}

void Particle3D::SetDamping(real damp)
{
	_damping = damp;
}

//==========================================================================================================================
//Mass
//==========================================================================================================================
real Particle3D::GetInverseMass(void)
{
	return _inverseMass;
}

void Particle3D::SetInverseMass(real inverseMass)
{
	_inverseMass = inverseMass;
}

real Particle3D::GetMass(void)
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

bool Particle3D::HasFiniteMass(void)
{
	return _inverseMass >= 0.0f;
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

	//=====clear force accumulator will go here when it is written=====
}