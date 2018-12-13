#include <Engine/ForceRegistry.h>

using namespace KillerPhysics;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
ForceRegistry::ForceRegistry(void)
:
_particleRegistrations(),
_bodyRegistrations()
{  }

ForceRegistry::~ForceRegistry(void)
{  }

//==========================================================================================================================
//
//ForceRegistry functions
//
//==========================================================================================================================	
void ForceRegistry::Add(shared_ptr<Particle> particle, shared_ptr<ForceGenerator> forceGen)
{
	ForceRegistry::_ParticleForceRegistration registration;
	registration.particle = particle;
	registration.forceGen = forceGen;

	_particleRegistrations.push_back(registration);
}

void ForceRegistry::Add(shared_ptr<RigidBody> body, shared_ptr<ForceGenerator> forceGen)
{
	ForceRegistry::_RigidBodyRegistration registration;
	registration.body = body;
	registration.forceGen = forceGen;

	_bodyRegistrations.push_back(registration);
}

void ForceRegistry::Remove(shared_ptr<Particle> particle, shared_ptr<ForceGenerator> forceGen)
{
	ForceRegistry::_ParticleForceRegistration registration;
	registration.particle = particle;
	registration.forceGen = forceGen;

	auto it = std::find(_particleRegistrations.begin(), _particleRegistrations.end(), registration);

	if(it != _particleRegistrations.end())
	{
		_particleRegistrations.erase(it);
	}
}

void ForceRegistry::Remove(shared_ptr<RigidBody> body, shared_ptr<ForceGenerator> forceGen)
{
	ForceRegistry::_RigidBodyRegistration registration;
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
	_particleRegistrations.clear();
}

void ForceRegistry::UpdateForces(void)
{
	for(auto i : _particleRegistrations)
	{
		if(i.particle->GetActive()) 
		{
			i.forceGen->v_UpdateForce(i.particle);
		}
	}
}