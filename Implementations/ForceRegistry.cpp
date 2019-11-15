#include <Engine/ForceRegistry.h>

using namespace TempestPhysics;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
ForceRegistry::ForceRegistry(void)
:
_body2DRegistrations(),
_body3DRegistrations()
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

	_body2DRegistrations.push_back(registration);
}

void ForceRegistry::Add(shared_ptr<RigidBody3D> body, shared_ptr<ForceGenerator> forceGen)
{
	_RigidBody3DRegistration registration;
	registration.body = body;
	registration.forceGen = forceGen;

	_body3DRegistrations.push_back(registration);
}

void ForceRegistry::Remove(shared_ptr<RigidBody2D> RigidBody2D, shared_ptr<ForceGenerator> forceGen)
{
	_RigidBody2DForceRegistration registration;
	registration.RigidBody2D = RigidBody2D;
	registration.forceGen = forceGen;

	auto it = std::find(_body2DRegistrations.begin(), _body2DRegistrations.end(), registration);

	if(it != _body2DRegistrations.end())
	{
		_body2DRegistrations.erase(it);
	}
}

void ForceRegistry::Remove(shared_ptr<RigidBody3D> body, shared_ptr<ForceGenerator> forceGen)
{
	_RigidBody3DRegistration registration;
	registration.body = body;
	registration.forceGen = forceGen;

	auto it = std::find(_body3DRegistrations.begin(), _body3DRegistrations.end(), registration);

	if(it != _body3DRegistrations.end())
	{
		_body3DRegistrations.erase(it);
	}
}

void ForceRegistry::Clear(void)
{
	_body2DRegistrations.clear();
}

void ForceRegistry::UpdateForces(void)
{
	for(auto i : _body2DRegistrations)
	{
		if(i.RigidBody2D->GetActive()) 
		{
			i.forceGen->v_UpdateForce(i.RigidBody2D);
		}
	}

	for(auto i : _body3DRegistrations)
	{
		if(i.body->GetActive())
		{
			i.forceGen->v_UpdateForce(i.body);
		}
	}
}