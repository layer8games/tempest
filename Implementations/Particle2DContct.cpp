#include <Engine/Particle2DContact.h>

using namespace KillerPhysics;
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Particle2DContact::Particle2DContact(void)
:
_particles{nullptr, nullptr},
_contactNormal(0.0f),
_restitution(0.0f)
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

}