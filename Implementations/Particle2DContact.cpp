#include <Engine/Particle2DContact.h>

using namespace KillerPhysics;
//==========================================================================================================================
//Particle2DContact
//==========================================================================================================================
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Particle2DContact::Particle2DContact(void)
:
_particles{nullptr, nullptr},
_particleMovements{nullptr, nullptr},
_contactNormal(0.0f),
_restitution(0.0f),
_penetration(0.0f)
{  }

Particle2DContact::~Particle2DContact(void)
{  }

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
void Particle2DContact::Resolve(void)
{
	_ResolveImpulseVelocity();
	_ResolveInterpenetration();
}

real Particle2DContact::CalculateSeparatingVelocity(void) const
{
	KM::Vector2 relativeVelocity = _particles[0]->GetVelocity();

	if(_particles[1])
	{
		relativeVelocity -= _particles[1]->GetVelocity();
	}

	return relativeVelocity.DotProduct(_contactNormal);
}

void Particle2DContact::_ResolveImpulseVelocity(void)
{
	real separatingVelocity = CalculateSeparatingVelocity();

	//if no separatingVelocity, the contact is either
	//separating or stationary. No impulse
	if(separatingVelocity > 0) return;

	real newSeparatingVelocity = -separatingVelocity * _restitution;

	//Check to see if velocity build up is due to acceleration only
	KM::Vector2 accelCausedVel = _particles[0]->GetAcceleration();

	if(_particles[1])
	{
		accelCausedVel -= _particles[1]->GetAcceleration();
	}

	real accelCausedSeparatingVel = accelCausedVel.DotProduct(_contactNormal * KM::Timer::Instance()->DeltaTime());

	//If we have an acceleration, remove it. 
	if(accelCausedSeparatingVel < 0)
	{
		newSeparatingVelocity += _restitution * accelCausedSeparatingVel;

		//Make sure we didn't take too much
		if(newSeparatingVelocity < 0 )
		{
			newSeparatingVelocity = 0;
		}
	}

	real deltaVelocity = newSeparatingVelocity - separatingVelocity;

	//Apply the change in velocity to each object in
	//proportion to their inverse mass
	real totalInverseMass = _particles[0]->GetInverseMass();

	if(_particles[1])
	{
		totalInverseMass += _particles[1]->GetInverseMass();
	}

	//Check for infinite mass
	if(totalInverseMass <= 0) return;

	//Calculate impulse
	real impulse = deltaVelocity / totalInverseMass;

	//Find amount of impulse per unit of inverse mass
	KM::Vector2 implusePerMass = _contactNormal * impulse;

	//Apply impulses: they are applied in the direction of the contact
	//and are proportional to the inverse mass
	_particles[0]->SetVelocity(_particles[0]->GetVelocity() + implusePerMass * _particles[0]->GetInverseMass());

	if(_particles[1])
	{
		//particle 1 goes in the opposite direciton
		_particles[1]->SetVelocity(_particles[1]->GetVelocity() + implusePerMass * -_particles[1]->GetInverseMass());
	}
}

void Particle2DContact::_ResolveInterpenetration(void)
{
	if(_penetration <= 0) return;

	real totalInverseMass = _particles[0]->GetInverseMass();

	if(_particles[1])
	{
		totalInverseMass += _particles[1]->GetInverseMass();
	}

	//if all particles have infinite mass, do nothing
	if(totalInverseMass <= 0) return;

	//Find amount of penetration per unit of inverse mass
	KM::Vector2 movePerMass = _contactNormal * (_penetration / totalInverseMass);

	//Calculate movement amounts
	_particleMovements[0] = shared_ptr<KM::Vector2>(new KM::Vector2(movePerMass * _particles[0]->GetInverseMass()));

	if(_particles[1])
	{
		_particleMovements[1] = shared_ptr<KM::Vector2>(new KM::Vector2(movePerMass * -_particles[1]->GetInverseMass()));
	}
	else
	{
		_particleMovements[1] = nullptr;
	}

	//Apply penetration resolution
	_particles[0]->SetPosition(_particles[0]->GetPosition() + _particleMovements[0]);

	if(_particles[1])
	{
		_particles[1]->SetPosition(_particles[1]->GetPosition() + _particleMovements[1]);
	}
}

//==========================================================================================================================
//Particle2DContactResolver
//==========================================================================================================================
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
Particle2DContactResolver::Particle2DContactResolver(void)
:
_iterations(0),
_iterationsUsed(0)
{  }

Particle2DContactResolver::Particle2DContactResolver(U32 iterations)
:
_iterations(iterations),
_iterationsUsed(0)
{  }

Particle2DContactResolver::~Particle2DContactResolver(void)
{  }

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
void Particle2DContactResolver::ResolveContacts(Particle2DContact* contactArray, U32 numContacts)
{
	U32 i;
	_iterationsUsed = 0;

	while(_iterationsUsed < _iterations)
	{
		//Find the contact with the largest closing velocity
		real max = REAL_MAX;
		U32 maxIndex = numContacts;
		for(int i = 0; i < numContacts; ++i)
		{
			real sepVal = contactArray[i].CalculateSeparatingVelocity();
			if(sepVal < max && (sepVal < 0 || contactArray[i].GetPenetration() > 0))
			{
				max = sepVal;
				maxIndex = i;
			}
		}

		//If nothing is found, end it
		if(maxIndex == numContacts) break;

		contactArray[maxIndex].Resolve();
		++_iterationsUsed;
	}
}