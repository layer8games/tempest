#include <Engine/ForceRegistry.h>

using namespace KillerPhysics;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
ForceRegistry::ForceRegistry(void)
:
_RigidBody2DRegistrations(),
_bodyRegistrations()
{  }

ForceRegistry::~ForceRegistry(void)
{  }

//==========================================================================================================================
//
//ForceRegistry functions
//
//==========================================================================================================================	
void ForceRegistry::Add(shared_ptr<RigidBody2D> RigidBody2D, shared_ptr<ForceGenerator> forceGen)
{
	_RigidBody2DForceRegistration registration;
	registration.RigidBody2D = RigidBody2D;
	registration.forceGen = forceGen;

	_RigidBody2DRegistrations.push_back(registration);
}

void ForceRegistry::Add(shared_ptr<RigidBody3D> body, shared_ptr<ForceGenerator> forceGen)
{
	_RigidBody3DRegistration registration;
	registration.body = body;
	registration.forceGen = forceGen;

	_bodyRegistrations.push_back(registration);
}

void ForceRegistry::Remove(shared_ptr<RigidBody2D> RigidBody2D, shared_ptr<ForceGenerator> forceGen)
{
	_RigidBody2DForceRegistration registration;
	registration.RigidBody2D = RigidBody2D;
	registration.forceGen = forceGen;

	auto it = std::find(_RigidBody2DRegistrations.begin(), _RigidBody2DRegistrations.end(), registration);

	if(it != _RigidBody2DRegistrations.end())
	{
		_RigidBody2DRegistrations.erase(it);
	}
}

void ForceRegistry::Remove(shared_ptr<RigidBody3D> body, shared_ptr<ForceGenerator> forceGen)
{
	_RigidBody3DRegistration registration;
	registration.body = body;
	registration.forceGen = forceGen;

	auto it = std::find(_bodyRegistrations.begin(), _bodyRegistrations.end(), registration);

	if(it != _bodyRegistrations.end())
	{
		_bodyRegistrations.erase(it);
	}
}

void ForceRegistry::Clear(void)
{
	_RigidBody2DRegistrations.clear();
}

void ForceRegistry::UpdateForces(void)
{
	for(auto i : _RigidBody2DRegistrations)
	{
		if(i.RigidBody2D->GetActive()) 
		{
			i.forceGen->v_UpdateForce(i.RigidBody2D);
		}
	}

	for(auto i : _bodyRegistrations)
	{
		if(i.body->GetActive())
		{
			i.forceGen->v_UpdateForce(i.body);
		}
	}
}