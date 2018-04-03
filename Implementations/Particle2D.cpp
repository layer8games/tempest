#include <Engine/Particle2D.h>

using namespace KillerPhysics;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================	
Particle2D::Particle2D(void) 
: 
_velocity(0.0f), 
_acceleration(0.0f), 
_inverseMass(0.0f), 
_damping(0.999f), 
_forceAccum()
{  }

Particle2D::Particle2D(const Particle2D* particle)
:
_velocity(0.0f), 
_acceleration(0.0f), 
_inverseMass(0.0f), 
_damping(0.999f), 
_forceAccum()
{
	_velocity = particle->GetVelocity();
	_acceleration = particle->GetAcceleration();
	_inverseMass = particle->GetInverseMass();
	_damping = particle->GetDamping();
}

Particle2D::Particle2D(const Particle2D& particle)
:
_velocity(0.0f), 
_acceleration(0.0f), 
_inverseMass(0.0f), 
_damping(0.999f), 
_forceAccum()
{
	_velocity = particle.GetVelocity();
	_acceleration = particle.GetAcceleration();
	_inverseMass = particle.GetInverseMass();
	_damping = particle.GetDamping();
}

Particle2D::~Particle2D(void) 
{  }

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
//=====Velocity=====
const KM::Vector2& Particle2D::GetVelocity(void) const
{ 
	return _velocity; 
}

void Particle2D::SetVelocity(KM::Vector2& v)
{ 
	_velocity = v; 
}

void Particle2D::SetVelocity(F32 x, F32 y) 
{ 
	_velocity = KM::Vector2(x, y); 
}

void Particle2D::AddScaledVelocity(const KM::Vector2& vec, F32 scale)
{
	_velocity.AddScaledVector(vec, scale);
}

//=====Acceleration=====
const KM::Vector2& Particle2D::GetAcceleration(void) const
{ 
	return _acceleration; 
}

void Particle2D::SetAcceleration(KM::Vector2& a)
{ 
	_acceleration = a; 
}

void Particle2D::SetAcceleration(F32 x, F32 y) 
{
 	_acceleration = KM::Vector2(x, y); 
}

void Particle2D::AddScaledAcceleration(const KM::Vector2& vec, F32 scale)
{
	_acceleration.AddScaledVector(vec, scale);
}
//=====Mass=====	
const real Particle2D::GetInverseMass(void) const
{
	return _inverseMass;
}

void Particle2D::SetInverseMass(real inverseMass)
{
	_inverseMass = inverseMass;
}

const real Particle2D::GetMass(void) const
{
	if(_inverseMass == 0) 
	{
		return REAL_MAX; 
	} 
	else 
	{
		return static_cast<real>(1.0f) / _inverseMass;
	} 		
}

void Particle2D::SetMass(const real mass)
{
	assert(mass != 0.0f);
	_inverseMass = static_cast<real>(1.0f) / mass;
}

bool Particle2D::HasFiniteMass(void)
{
	return _inverseMass >= 0.0f;
}

//==========================================================================================================================
//
//Particle Functions
//
//==========================================================================================================================
void Particle2D::v_Update(void)
{
	Integrate();
}

void Particle2D::Integrate(void) 
{
	//if there no mass, there is no update
	if(_inverseMass == 0)
	{
		return;
	} 

	F32 delta = KM::Timer::Instance()->DeltaTime();

	//Update position
	KE::GameObject2D::AddScaledPosition(_velocity, delta);

	//Work out acceleration. 
	//For now, only a use the current acceleration. 
	//Once forces are added, this will change
	KM::Vector2 resultingAcc = _acceleration;

	//Work out new velocity based on acceleration
	_velocity.AddScaledVector(resultingAcc, delta);

	//Add damping
	_velocity *= real_pow(_damping, delta);

	ClearAccumulator();
}

void Particle2D::ClearAccumulator(void)
{
	_forceAccum.Reset();
}

void Particle2D::AddForce(const KM::Vector2& force)
{
	_forceAccum += force;
}