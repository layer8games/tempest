#include <Engine/ParticleSpringForces.h>
#include <iostream>

using namespace KillerPhysics;

//==========================================================================================================================
//ParticleSpringForce
//==========================================================================================================================
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
ParticleSpringForce::ParticleSpringForce(void) 
:
_otherEnd2D(),
_otherEnd3D(),
_springConstant(1),
_restLength(1),
_isBungie(false)
{  }

ParticleSpringForce::ParticleSpringForce(shared_ptr<Particle2D> otherEnd, real springConstatant, real restLength)
:
_otherEnd2D(otherEnd),
_otherEnd3D(),
_springConstant(springConstatant),
_restLength(restLength),
_isBungie(false)
{  }

ParticleSpringForce::ParticleSpringForce(shared_ptr<Particle3D> otherEnd, real springConstatant, real restLength)
:
_otherEnd2D(),
_otherEnd3D(otherEnd),
_springConstant(springConstatant),
_restLength(restLength),
_isBungie(false)
{  }

ParticleSpringForce::~ParticleSpringForce(void) 
{  }

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
void ParticleSpringForce::v_UpdateForce(shared_ptr<Particle2D> particle)
{
//=====Calculate Vector of the spring=====
	KM::Vector2 force = particle->GetPosition();
	force -= _otherEnd2D->GetPosition();

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

void ParticleSpringForce::v_UpdateForce(shared_ptr<Particle3D> particle)
{
//=====Calculate Vector of the spring=====
	KM::Vector3 force = particle->GetPosition();
	force -= _otherEnd3D->GetPosition();

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
//ParticleAnchoredSpring
//==========================================================================================================================
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
ParticleAnchoredSpring::ParticleAnchoredSpring(void)
{  }

ParticleAnchoredSpring::ParticleAnchoredSpring(KM::Vector2 anchor, real springConstant, real restLength)
:
_anchor2D(anchor),
_anchor3D(0.0f),
_springConstant(springConstant),
_restLength(restLength)
{  }

ParticleAnchoredSpring::ParticleAnchoredSpring(KM::Vector3 anchor, real springConstant, real restLength)
:
_anchor2D(0.0f),
_anchor3D(anchor),
_springConstant(springConstant),
_restLength(restLength)
{  }

ParticleAnchoredSpring::~ParticleAnchoredSpring(void)
{  }

void ParticleAnchoredSpring::v_UpdateForce(shared_ptr<Particle2D> particle)
{
	//Calculate the vector of the spring
	KM::Vector2 force = particle->GetPosition();
	force -= _anchor2D;

	//Calculate the magnitude of the force
	real magnitude = force.Magnitude();
	magnitude = (_restLength - magnitude) * _springConstant;

	//Calculate the final force and apply it
	force.Normalize();
	force *= static_cast<F32>(magnitude);
	particle->AddForce(force);
}

void ParticleAnchoredSpring::v_UpdateForce(shared_ptr<Particle3D> particle)
{
	//Calculate the vector of the spring
	KM::Vector3 force = particle->GetPosition();
	force -= _anchor3D;

	//Calculate the magnitude of the force
	real magnitude = force.Magnitude();
	magnitude = (_restLength - magnitude) * _springConstant;

	//Calculate the final force and apply it
	force.Normalize();
	force *= static_cast<F32>(magnitude);
	particle->AddForce(force);
}

//==========================================================================================================================
//ParticleBuoyantForce
//==========================================================================================================================
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
ParticleBuoyantForce::ParticleBuoyantForce(void) 
: 
_maxDepth(0), 
_objectVolume(0), 
_liquidHeight(0), 
_liquidDensity(1000.0f)
{  }

ParticleBuoyantForce::ParticleBuoyantForce(real maxDepth, real objVolume, real liquidHeight, real liquidDensity )
: 
_maxDepth(maxDepth), 
_objectVolume(objVolume), 
_liquidHeight(liquidHeight), 
_liquidDensity(liquidDensity)
{  }

ParticleBuoyantForce::~ParticleBuoyantForce(void) 
{  }

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
void ParticleBuoyantForce::v_UpdateForce(shared_ptr<Particle2D> particle)
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

void ParticleBuoyantForce::v_UpdateForce(shared_ptr<Particle3D> particle)
{
//=====Calculate Depth of object=====
	real depth = particle->GetPosition().GetY();

	//Out of liquid check
	if(depth >= _liquidHeight + _maxDepth) return;
	
	KM::Vector3 force(0.0f);

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