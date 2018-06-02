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
void ParticleForceRegistry::Add(shared_ptr<Particle2D> particle, shared_ptr<ParticleForceGenerator> forceGen)
{
	ParticleForceRegistry::_Particle2DForceRegistration registration;
	registration.particle = particle;
	registration.forceGen = forceGen;

	_registrations2D.push_back(registration);
}

void ParticleForceRegistry::Add(shared_ptr<Particle3D> particle, shared_ptr<ParticleForceGenerator> forceGen)
{
	ParticleForceRegistry::_Particle3DForceRegistration registration;
	registration.particle = particle;
	registration.forceGen = forceGen;

	_registrations3D.push_back(registration);
}

void ParticleForceRegistry::Remove(shared_ptr<Particle2D> particle, shared_ptr<ParticleForceGenerator> forceGen)
{
	ParticleForceRegistry::_Particle2DForceRegistration registration;
	registration.particle = particle;
	registration.forceGen = forceGen;

	auto it = std::find(_registrations2D.begin(), _registrations2D.end(), registration);

	if(it != _registrations2D.end())
	{
		_registrations2D.erase(it);
	}
}

void ParticleForceRegistry::Remove(shared_ptr<Particle3D> particle, shared_ptr<ParticleForceGenerator> forceGen)
{
	ParticleForceRegistry::_Particle3DForceRegistration registration;
	registration.particle = particle;
	registration.forceGen = forceGen;

	auto it = std::find(_registrations3D.begin(), _registrations3D.end(), registration);

	if(it != _registrations3D.end())
	{
		_registrations3D.erase(it);
	}
}

void ParticleForceRegistry::Clear(void)
{
	_registrations2D.clear();
	_registrations3D.clear();
}

void ParticleForceRegistry::UpdateForces(void)
{
	for(auto i : _registrations2D)
	{
		if(i.particle->GetActive()) 
		{
			i.forceGen->v_UpdateForce(i.particle);
		}
	}

	for(auto i : _registrations3D)
	{
		if(i.particle->GetActive()) 
		{
			i.forceGen->v_UpdateForce(i.particle);
		}
	}
}