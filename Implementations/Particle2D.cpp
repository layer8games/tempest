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
_forceAccum(),
_gravityForce(0.0f),
_inverseMass(0.0f),
_damping(0.999f)
{  }

Particle2D::Particle2D(const Particle2D* particle)
:
_velocity(0.0f),
_acceleration(0.0f),
_forceAccum(),
_gravityForce(0.0f),
_inverseMass(0.0f),
_damping(0.999f)
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
_forceAccum(),
_gravityForce(0.0f),
_inverseMass(0.0f),
_damping(0.999f)
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
//=====Mass=====	
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