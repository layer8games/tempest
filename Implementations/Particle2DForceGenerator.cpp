#include <Engine/Particle2DForceGenerator.h>

using namespace KillerPhysics;
//==========================================================================================================================
//Force Generator
//==========================================================================================================================
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Particle2DForceGenerator::Particle2DForceGenerator(void)
{  }

Particle2DForceGenerator::~Particle2DForceGenerator(void)
{  }


/*
//==========================================================================================================================
//Force Registry
//==========================================================================================================================
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
Particle2DForceRegistry::Particle2DForceRegistry(void)
{  }

Particle2DForceRegistry::~Particle2DForceRegistry(void)
{  }

//==========================================================================================================================
//
//Particle2DForceRegistry functions
//
//==========================================================================================================================	
void Particle2DForceRegistry::Add(shared_ptr<Particle2D> particle, shared_ptr<Particle2DForceGenerator> forceGen)
{
	Particle2DForceRegistry::ParticleForceRegistration registration;
	registration.particle = particle;
	registration.forceGen = forceGen;

	_registrations.push_back(registration);
}

void Particle2DForceRegistry::Remove(shared_ptr<Particle2D> particle, shared_ptr<Particle2DForceGenerator> forceGen)
{
	Particle2DForceRegistry::ParticleForceRegistration registration;
	registration.particle = particle;
	registration.forceGen = forceGen;

	auto it = std::find(_registrations.begin(), _registrations.end(), registration);

	if(it != _registrations.end())
	{
		_registrations.erase(it);
	}
}

void Particle2DForceRegistry::Clear(void)
{
	_registrations.clear();
}

void Particle2DForceRegistry::UpdateForces(void)
{
	for(auto i : _registrations)
	{
		if(i.particle->GetActive()) 
		{
			i.forceGen->v_UpdateForce(i.particle);
		}
	}
}
*/