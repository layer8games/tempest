#include <Engine/SpringForces.h>

using namespace KillerPhysics;

//==========================================================================================================================
//SpringForce
//==========================================================================================================================
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
SpringForce::SpringForce(void) 
:
_otherEnd(),
_springConstant(1),
_restLength(1),
_isBungie(false)
{  }

SpringForce::SpringForce(shared_ptr<Particle> otherEnd, real springConstatant, real restLength)
:
_otherEnd(otherEnd),
_springConstant(springConstatant),
_restLength(restLength),
_isBungie(false)
{  }

SpringForce::~SpringForce(void) 
{  }

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
void SpringForce::v_UpdateForce(shared_ptr<Particle> particle)
{
//=====Calculate Vector of the spring=====
	KM::Vector force = particle->GetPosition();
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

//TODO: Implement
void SpringForce::v_UpdateForce(shared_ptr<RigidBody> body)
{
	KM::Vector force = body->GetPosition();
	force -= _otherEnd->GetPosition();

	real magnitude = force.Magnitude();

	if(_isBungie && magnitude <= _restLength)
	{
		return;
	}

	magnitude = real_abs(magnitude - _restLength) * _springConstant;

	force.Normalize();
	force *= static_cast<F32>(-magnitude);

	body->AddForce(force);
}

//==========================================================================================================================
//AnchoredSpring
//==========================================================================================================================
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
AnchoredSpring::AnchoredSpring(void)
{  }

AnchoredSpring::AnchoredSpring(KM::Vector anchor, real springConstant, real restLength)
:
_anchor(anchor),
_springConstant(springConstant),
_restLength(restLength)
{  }

AnchoredSpring::~AnchoredSpring(void)
{  }

void AnchoredSpring::v_UpdateForce(shared_ptr<Particle> particle)
{
	//Calculate the vector of the spring
	KM::Vector force = particle->GetPosition();
	force -= _anchor;

	//Calculate the magnitude of the force
	real magnitude = force.Magnitude();
	magnitude = (_restLength - magnitude) * _springConstant;

	//Calculate the final force and apply it
	force.Normalize();
	force *= static_cast<F32>(magnitude);
	particle->AddForce(force);
}

//TODO: Implement
void AnchoredSpring::v_UpdateForce(shared_ptr<RigidBody> body)
{
	KM::Vector force = body->GetPosition();
	force -= _anchor;

	real magnitude = force.Magnitude();
	magnitude = (_restLength - magnitude) * _springConstant;

	force.Normalize();
	force *= static_cast<F32>(magnitude);
	body->AddForce(force);
}

//==========================================================================================================================
//BuoyantForce
//==========================================================================================================================
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
BuoyantForce::BuoyantForce(void) 
: 
_maxDepth(0), 
_objectVolume(0), 
_liquidHeight(0), 
_liquidDensity(1000.0f)
{  }

BuoyantForce::BuoyantForce(real maxDepth, real objVolume, real liquidHeight, real liquidDensity )
: 
_maxDepth(maxDepth), 
_objectVolume(objVolume), 
_liquidHeight(liquidHeight), 
_liquidDensity(liquidDensity)
{  }

BuoyantForce::~BuoyantForce(void) 
{  }

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
void BuoyantForce::v_UpdateForce(shared_ptr<Particle> particle)
{
//=====Calculate Depth of object=====
	real depth = particle->GetPosition()[1]; //Get the y val

	//Out of liquid check
	if(depth >= _liquidHeight + _maxDepth) 
	{
		return;
	}
	
	KM::Vector force(0.0f);

	//Max Depth check
	if(depth <= _liquidHeight - _maxDepth)
	{
		force[1] = _liquidDensity * _objectVolume;

		particle->AddForce(force);
	}
	else
	{
		force[1] = _liquidDensity * _objectVolume * (depth - _maxDepth - _liquidHeight) / 2 * _maxDepth;

		particle->AddForce(force);
	}	
}

//TODO: Implement
void BuoyantForce::v_UpdateForce(shared_ptr<RigidBody> body)
{
	real depth = body->GetPosition()[1];

	if(depth >= _liquidHeight + _maxDepth) 
	{
		return;
	}

	KM::Vector force(0.0f);

	if(depth <= _liquidHeight - _maxDepth)
	{
		force[1] = _liquidDensity * _objectVolume;

		body->AddForce(force);
		return;
	}
	else
	{
		force[1] = _liquidDensity * _objectVolume * (depth - _maxDepth - _liquidHeight) / 2 * _maxDepth;

		body->AddForce(force);
	}

}