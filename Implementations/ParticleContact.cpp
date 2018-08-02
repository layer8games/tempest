#include <Engine/ParticleContact.h>

using namespace KillerPhysics;
//==========================================================================================================================
//ParticleContact
//==========================================================================================================================
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
ParticleContact::ParticleContact(void)
:
_particles{nullptr, nullptr},
_particleMovements{nullptr, nullptr},
_contactNormal(0.0f),
_restitution(0.0f),
_penetration(0.0f)
{  }

ParticleContact::~ParticleContact(void)
{  }

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
void ParticleContact::Resolve(void)
{
	_ResolveImpulseVelocity();
	_ResolveInterpenetration();
}

real ParticleContact::CalculateSeparatingVelocity(void) const
{
	if(_particles[0])
	{
		KM::Vector relativeVelocity = _particles[0]->GetVelocity();

		if(_particles[1])
		{
			relativeVelocity -= _particles[1]->GetVelocity();
		}

		return relativeVelocity.DotProduct(_contactNormal);
	}		
}

void ParticleContact::_ResolveImpulseVelocity(void)
{
	real separatingVelocity = CalculateSeparatingVelocity();

	//if no separatingVelocity, the contact is either
	//separating or stationary. No impulse
	if(separatingVelocity > 0) return;

	real newSeparatingVelocity = -separatingVelocity * _restitution;

	real accelCausedSeparatingVel;

	if(_particles[0])
	{
		//Check to see if velocity build up is due to acceleration only
		KM::Vector accelCausedVel = _particles[0]->GetAcceleration();

		if(_particles[1])
		{
			accelCausedVel -= _particles[1]->GetAcceleration();
		}

		accelCausedSeparatingVel = accelCausedVel.DotProduct(_contactNormal * KM::Timer::Instance()->DeltaTime());
	}	

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

	real totalInverseMass;

	if(_particles[0])
	{
		//Apply the change in velocity to each object in
		//proportion to their inverse mass
		totalInverseMass = _particles[0]->GetInverseMass();

		if(_particles[1])
		{
			totalInverseMass += _particles[1]->GetInverseMass();
		}
	}
	
	//Check for infinite mass
	if(totalInverseMass <= 0) return;

	//Calculate impulse
	real impulse = deltaVelocity / totalInverseMass;


	if(_particles[0])
	{
		//Find amount of impulse per unit of inverse mass
		KM::Vector implusePerMass = _contactNormal * impulse;

		//Apply impulses: they are applied in the direction of the contact
		//and are proportional to the inverse mass
		_particles[0]->SetVelocity(_particles[0]->GetVelocity() + implusePerMass * _particles[0]->GetInverseMass());

		if(_particles[1])
		{
			//particle 1 goes in the opposite direciton
			_particles[1]->SetVelocity(_particles[1]->GetVelocity() + implusePerMass * -_particles[1]->GetInverseMass());
		}
	}		
}

void ParticleContact::_ResolveInterpenetration(void)
{
	if(_penetration <= 0) return;

	real totalInverseMass;

	if(_particles[0])
	{
		totalInverseMass = _particles[0]->GetInverseMass();

		if(_particles[1])
		{
			totalInverseMass += _particles[1]->GetInverseMass();
		}
	}

	//if all particles have infinite mass, do nothing
	if(totalInverseMass <= 0) return;

	if(_particles[0])
	{
		//Find amount of penetration per unit of inverse mass
		KM::Vector movePerMass = _contactNormal * (_penetration / totalInverseMass);

		//Calculate movement amounts
		_particleMovements[0] = shared_ptr<KM::Vector>(new KM::Vector(movePerMass * _particles[0]->GetInverseMass()));

		if(_particles[1])
		{
			_particleMovements[1] = shared_ptr<KM::Vector>(new KM::Vector(movePerMass * -_particles[1]->GetInverseMass()));
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
}

//==========================================================================================================================
//ParticleContactResolver
//==========================================================================================================================
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
ParticleContactResolver::ParticleContactResolver(void)
:
_iterations(0),
_iterationsUsed(0)
{  }

ParticleContactResolver::ParticleContactResolver(U32 iterations)
:
_iterations(iterations),
_iterationsUsed(0)
{  }

ParticleContactResolver::~ParticleContactResolver(void)
{  }

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
void ParticleContactResolver::ResolveContacts(ParticleContact* contactArray, U32 numContacts)
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