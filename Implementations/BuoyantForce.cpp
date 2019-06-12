#include <Engine/BuoyantForce.h>

using namespace KillerPhysics;


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
void BuoyantForce::v_UpdateForce(shared_ptr<RigidBody2D> RigidBody2D)
{
//=====Calculate Depth of object=====
	real depth = RigidBody2D->GetPosition()[1]; //Get the y val

	//Out of liquid check
	if(depth >= _liquidHeight + _maxDepth) 
	{
		return;
	}
	
	KM::Vector4 force(0.0f);

	//Max Depth check
	if(depth <= _liquidHeight - _maxDepth)
	{
		force[1] = _liquidDensity * _objectVolume;

		RigidBody2D->AddForce(force);
	}
	else
	{
		force[1] = _liquidDensity * _objectVolume * (depth - _maxDepth - _liquidHeight) / 2 * _maxDepth;

		RigidBody2D->AddForce(force);
	}	
}

//TODO: Implement
void BuoyantForce::v_UpdateForce(shared_ptr<RigidBody3D> body)
{
	real depth = body->GetPosition()[1];

	if(depth >= _liquidHeight + _maxDepth) 
	{
		return;
	}

	KM::Vector4 force(0.0f);

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