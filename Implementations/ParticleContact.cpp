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
_particles2D{nullptr, nullptr},
_particles3D{nullptr, nullptr},
_particle2DMovements{nullptr, nullptr},
_particle3DMovements{nullptr, nullptr},
_contactNormal2D(0.0f),
_contactNormal3D(0.0f),
_restitution(0.0f),
_penetration(0.0f)
{  }

ParticleContact::~ParticleContact(void)
{  }

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
void ParticleContact::SetContacts(shared_ptr<Particle2D> particle1, shared_ptr<Particle2D> particle2)
{
	if(_particles3D[0])
	{
		KE::ErrorManager::Instance()->SetError(KE::ErrorCode::EC_Physics, "ParticleContact::SetContacts, Cannot set both 2D and 3D contacts with single ParticleContact.");
		return;
	}

	_particles2D[0] = particle1;
	_particles2D[1] = particle2;
}

void ParticleContact::SetContacts(shared_ptr<Particle3D> particle1, shared_ptr<Particle3D> particle2)
{
	if(_particles2D[0])
	{
		KE::ErrorManager::Instance()->SetError(KE::ErrorCode::EC_Physics, "ParticleContact::SetContacts, Cannot set both 2D and 3D contacts with single ParticleContact.");
	}

	_particles3D[0] = particle1;
	_particles3D[1] = particle2;
}
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
	if(_particles2D[0])
	{
		KM::Vector2 relativeVelocity = _particles2D[0]->GetVelocity();

		if(_particles2D[1])
		{
			relativeVelocity -= _particles2D[1]->GetVelocity();
		}

		return relativeVelocity.DotProduct(_contactNormal2D);
	}
	else if(_particles3D[0])
	{
		KM::Vector3 relativeVelocity = _particles3D[0]->GetVelocity();

		if(_particles3D[1])
		{
			relativeVelocity -= _particles3D[1]->GetVelocity();
		}

		return relativeVelocity.DotProduct(_contactNormal3D);
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

	if(_particles2D[0])
	{
		//Check to see if velocity build up is due to acceleration only
		KM::Vector2 accelCausedVel = _particles2D[0]->GetAcceleration();

		if(_particles2D[1])
		{
			accelCausedVel -= _particles2D[1]->GetAcceleration();
		}

		accelCausedSeparatingVel = accelCausedVel.DotProduct(_contactNormal2D * KM::Timer::Instance()->DeltaTime());
	}
	else if(_particles3D[0])
	{
		//Check to see if velocity build up is due to acceleration only
		KM::Vector3 accelCausedVel = _particles3D[0]->GetAcceleration();

		if(_particles3D[1])
		{
			accelCausedVel -= _particles3D[1]->GetAcceleration();
		}

		accelCausedSeparatingVel = accelCausedVel.DotProduct(_contactNormal3D * KM::Timer::Instance()->DeltaTime());
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

	if(_particles2D[0])
	{
		//Apply the change in velocity to each object in
		//proportion to their inverse mass
		totalInverseMass = _particles2D[0]->GetInverseMass();

		if(_particles2D[1])
		{
			totalInverseMass += _particles2D[1]->GetInverseMass();
		}
	}
	else if(_particles3D[0])
	{
		//Apply the change in velocity to each object in
		//proportion to their inverse mass
		totalInverseMass = _particles3D[0]->GetInverseMass();

		if(_particles3D[1])
		{
			totalInverseMass += _particles3D[1]->GetInverseMass();
		}
	}
	
	//Check for infinite mass
	if(totalInverseMass <= 0) return;

	//Calculate impulse
	real impulse = deltaVelocity / totalInverseMass;


	if(_particles2D[0])
	{
		//Find amount of impulse per unit of inverse mass
		KM::Vector2 implusePerMass = _contactNormal2D * impulse;

		//Apply impulses: they are applied in the direction of the contact
		//and are proportional to the inverse mass
		_particles2D[0]->SetVelocity(_particles2D[0]->GetVelocity() + implusePerMass * _particles2D[0]->GetInverseMass());

		if(_particles2D[1])
		{
			//particle 1 goes in the opposite direciton
			_particles2D[1]->SetVelocity(_particles2D[1]->GetVelocity() + implusePerMass * -_particles2D[1]->GetInverseMass());
		}
	}
	else if(_particles3D[0])
	{
		//Find amount of impulse per unit of inverse mass
		KM::Vector3 implusePerMass = _contactNormal3D * impulse;

		//Apply impulses: they are applied in the direction of the contact
		//and are proportional to the inverse mass
		_particles3D[0]->SetVelocity(_particles3D[0]->GetVelocity() + implusePerMass * _particles3D[0]->GetInverseMass());

		if(_particles3D[1])
		{
			//particle 1 goes in the opposite direciton
			_particles3D[1]->SetVelocity(_particles3D[1]->GetVelocity() + implusePerMass * -_particles3D[1]->GetInverseMass());
		}
	}		
}

void ParticleContact::_ResolveInterpenetration(void)
{
	if(_penetration <= 0) return;

	real totalInverseMass;

	if(_particles2D[0])
	{
		totalInverseMass = _particles2D[0]->GetInverseMass();

		if(_particles2D[1])
		{
			totalInverseMass += _particles2D[1]->GetInverseMass();
		}
	}
	else if(_particles3D[0])
	{
		totalInverseMass = _particles3D[0]->GetInverseMass();

		if(_particles3D[1])
		{
			totalInverseMass += _particles3D[1]->GetInverseMass();
		}
	}

	//if all particles have infinite mass, do nothing
	if(totalInverseMass <= 0) return;

	if(_particles2D[0])
	{
		//Find amount of penetration per unit of inverse mass
		KM::Vector2 movePerMass = _contactNormal2D * (_penetration / totalInverseMass);

		//Calculate movement amounts
		_particle2DMovements[0] = shared_ptr<KM::Vector2>(new KM::Vector2(movePerMass * _particles2D[0]->GetInverseMass()));

		if(_particles2D[1])
		{
			_particle2DMovements[1] = shared_ptr<KM::Vector2>(new KM::Vector2(movePerMass * -_particles2D[1]->GetInverseMass()));
		}
		else
		{
			_particle2DMovements[1] = nullptr;
		}

		//Apply penetration resolution
		_particles2D[0]->SetPosition(_particles2D[0]->GetPosition() + _particle2DMovements[0]);

		if(_particles2D[1])
		{
			_particles2D[1]->SetPosition(_particles2D[1]->GetPosition() + _particle2DMovements[1]);
		}	
	}
	else if(_particles3D[0])
	{
		//Find amount of penetration per unit of inverse mass
		KM::Vector3 movePerMass = _contactNormal3D * (_penetration / totalInverseMass);

		//Calculate movement amounts
		_particle3DMovements[0] = shared_ptr<KM::Vector3>(new KM::Vector3(movePerMass * _particles3D[0]->GetInverseMass()));

		if(_particles3D[1])
		{
			_particle3DMovements[1] = shared_ptr<KM::Vector3>(new KM::Vector3(movePerMass * -_particles3D[1]->GetInverseMass()));
		}
		else
		{
			_particle3DMovements[1] = nullptr;
		}

		//Apply penetration resolution
		_particles3D[0]->SetPosition(_particles3D[0]->GetPosition() + _particle3DMovements[0]);

		if(_particles3D[1])
		{
			_particles3D[1]->SetPosition(_particles3D[1]->GetPosition() + _particle3DMovements[1]);
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