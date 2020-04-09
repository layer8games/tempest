#include <Engine/BuoyantForce.h>

using namespace TempestPhysics;


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
	real depth = RigidBody2D->GetPosition().y;

	//Out of liquid check
	if(depth >= _liquidHeight + _maxDepth) 
	{
		return;
	}
	
	TM::Vector2 force(0.0f);

	//Max Depth check
	if(depth <= _liquidHeight - _maxDepth)
	{
		force.y = _liquidDensity * _objectVolume;

		RigidBody2D->AddForce(force);
	}
	else
	{
		force.y = _liquidDensity * _objectVolume * (depth - _maxDepth - _liquidHeight) / 2 * _maxDepth;

		RigidBody2D->AddForce(force);
	}	
}

//TODO: Implement
void BuoyantForce::v_UpdateForce(shared_ptr<RigidBody3D> body)
{
	real depth = body->GetPosition().y;

	if(depth >= _liquidHeight + _maxDepth) 
	{
		return;
	}

	TM::Vector3 force(0.0f);

	if(depth <= _liquidHeight - _maxDepth)
	{
		force.y = _liquidDensity * _objectVolume;

		body->AddForce(force);
		return;
	}
	else
	{
		force.y = _liquidDensity * _objectVolume * (depth - _maxDepth - _liquidHeight) / 2 * _maxDepth;

		body->AddForce(force);
	}

}