#include <Engine/ParticleForceRegistry.h>

using namespace KillerPhysics;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
ParticleForceRegistry::ParticleForceRegistry(void)
{  }

ParticleForceRegistry::~ParticleForceRegistry(void)
{  }

//==========================================================================================================================
//
//ParticleForceRegistry functions
//
//==========================================================================================================================	
void ParticleForceRegistry::Add(shared_ptr<Particle> particle, shared_ptr<ParticleForceGenerator> forceGen)
{
	ParticleForceRegistry::_ParticleForceRegistration registration;
	registration.particle = particle;
	registration.forceGen = forceGen;

	_registrations.push_back(registration);
}

void ParticleForceRegistry::Remove(shared_ptr<Particle> particle, shared_ptr<ParticleForceGenerator> forceGen)
{
	ParticleForceRegistry::_ParticleForceRegistration registration;
	registration.particle = particle;
	registration.forceGen = forceGen;

	auto it = std::find(_registrations.begin(), _registrations.end(), registration);

	if(it != _registrations.end())
	{
		_registrations.erase(it);
	}
}

void ParticleForceRegistry::Clear(void)
{
	_registrations.clear();
}

void ParticleForceRegistry::UpdateForces(void)
{
	for(auto i : _registrations)
	{
		if(i.particle->GetActive()) 
		{
			i.forceGen->v_UpdateForce(i.particle);
		}
	}
}