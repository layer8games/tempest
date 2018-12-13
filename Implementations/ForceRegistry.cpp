#include <Engine/ForceRegistry.h>

using namespace KillerPhysics;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
ForceRegistry::ForceRegistry(void)
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

	_registrations.push_back(registration);
}

void ForceRegistry::Remove(shared_ptr<Particle> particle, shared_ptr<ForceGenerator> forceGen)
{
	ForceRegistry::_ParticleForceRegistration registration;
	registration.particle = particle;
	registration.forceGen = forceGen;

	auto it = std::find(_registrations.begin(), _registrations.end(), registration);

	if(it != _registrations.end())
	{
		_registrations.erase(it);
	}
}

void ForceRegistry::Clear(void)
{
	_registrations.clear();
}

void ForceRegistry::UpdateForces(void)
{
	for(auto i : _registrations)
	{
		if(i.particle->GetActive()) 
		{
			i.forceGen->v_UpdateForce(i.particle);
		}
	}
}