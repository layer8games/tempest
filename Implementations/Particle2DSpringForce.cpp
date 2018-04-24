#include <Engine/Particle2DSpringForce.h>

using namespace KillerPhysics;

//==========================================================================================================================
//SpringForce
//==========================================================================================================================
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Particle2DSpringForce::Particle2DSpringForce(void) 
:
_otherEnd(),
_springConstant(1),
_restLength(1),
_isBungie(false)
{  }

Particle2DSpringForce::Particle2DSpringForce(shared_ptr<Particle2D> otherEnd, real springConstatant, real restLength)
:
_otherEnd(otherEnd),
_springConstant(springConstatant),
_restLength(restLength),
_isBungie(false)
{  }

Particle2DSpringForce::~Particle2DSpringForce(void) 
{  }

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
void Particle2DSpringForce::v_UpdateForce(shared_ptr<Particle2D> particle)
{
//=====Calculate Vector of the spring=====
	KM::Vector2 force = particle->GetPosition();
	force -= _otherEnd->GetPosition();

//=====Calculate magnitude of force=====
	real magnitude = force.Magnitude();

	//=====Bungie Checke=====
	if(magnitude <= _restLength) return;

	magnitude = real_abs(magnitude - _restLength) * _springConstant;

//=====Calculate final force=====
	force.Normalize();
	force *= static_cast<F32>(-magnitude);

	particle->AddForce(force);
}

//==========================================================================================================================
//AnchoredSpring
//==========================================================================================================================
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
Particle2DAnchoredSpring::Particle2DAnchoredSpring(void)
{  }

Particle2DAnchoredSpring::Particle2DAnchoredSpring(KM::Vector2 anchor, real springConstant, real restLength)
:
_anchor(anchor),
_springConstant(springConstant),
_restLength(restLength)
{  }

Particle2DAnchoredSpring::~Particle2DAnchoredSpring(void)
{  }

void Particle2DAnchoredSpring::v_UpdateForce(shared_ptr<Particle2D> particle)
{
	//Calculate the vector of the spring
	KM::Vector2 force = particle->GetPosition();
	force -= _anchor;

	//Calculate the magnitude of the force
	real magnitude = force.Magnitude();
	magnitude = (_restLength - magnitude) * _springConstant;

	//Calculate the final force and apply it
	force.Normalize();
	force *= static_cast<F32>(magnitude);
	particle->AddForce(force);
}