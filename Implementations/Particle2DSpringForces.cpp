#include <Engine/Particle2DSpringForces.h>
#include <iostream>

using namespace KillerPhysics;

//==========================================================================================================================
//Particle2DSpringForce
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
	if(_isBungie && magnitude <= _restLength) 
	{
		return;
	}

	magnitude = real_abs(magnitude - _restLength) * _springConstant;

//=====Calculate final force=====
	force.Normalize();
	force *= static_cast<F32>(-magnitude);

	particle->AddForce(force);
}

//==========================================================================================================================
//Particle2DAnchoredSpring
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

//==========================================================================================================================
//Particle2DBuoyantForce
//==========================================================================================================================
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Particle2DBuoyantForce::Particle2DBuoyantForce(void) 
: 
_maxDepth(0), 
_objectVolume(0), 
_liquidHeight(0), 
_liquidDensity(1000.0f)
{  }

Particle2DBuoyantForce::Particle2DBuoyantForce(real maxDepth, real objVolume, real liquidHeight, real liquidDensity )
: 
_maxDepth(maxDepth), 
_objectVolume(objVolume), 
_liquidHeight(liquidHeight), 
_liquidDensity(liquidDensity)
{  }

Particle2DBuoyantForce::~Particle2DBuoyantForce(void) 
{  }

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
void Particle2DBuoyantForce::v_UpdateForce(shared_ptr<Particle2D> particle)
{
//=====Calculate Depth of object=====
	real depth = particle->GetPosition().GetY();

	//Out of liquid check
	if(depth >= _liquidHeight + _maxDepth) return;
	
	KM::Vector2 force(0.0f);

	//Max Depth check
	if(depth <= _liquidHeight - _maxDepth)
	{
		force.SetY(_liquidDensity * _objectVolume);

		particle->AddForce(force);
		return;
	}

	force.SetY(_liquidDensity * _objectVolume * (depth - _maxDepth - _liquidHeight) / 2 * _maxDepth);

	particle->AddForce(force);	
}