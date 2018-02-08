#include <Engine/Particle2D.h>

namespace KillerPhysics
{

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================	
	Particle2D::Particle2D(void) : _damping(0.0f), _inverseMass(0.0f), _velocity(0.0f), _acceleration(0.0f), _forceAccum()
	{  }

	Particle2D::~Particle2D(void) 
	{  }

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
//=====Velocity=====
	KM::Vector2& Particle2D::GetVelocity(void) 
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
	KM::Vector2& Particle2D::GetAcceleration(void)
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
	real Particle2D::GetMass(void)
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

}//end namespace