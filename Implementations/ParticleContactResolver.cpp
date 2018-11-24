#include <Engine/ParticleContactResolver.h>

using namespace KillerPhysics;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
ParticleContactResolver::ParticleContactResolver(void)
:
_iterations(0),
_iterationsUsed(0)
{  }

ParticleContactResolver::ParticleContactResolver(U32 iterations)
:
_iterations(iterations),
_iterationsUsed(0)
{  }

ParticleContactResolver::~ParticleContactResolver(void)
{  }

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
void ParticleContactResolver::ResolveContacts(ParticleContact* contactArray, U32 numContacts)
{
	_iterationsUsed = 0;

	while(_iterationsUsed < _iterations)
	{
		//Find the contact with the largest closing velocity
		real max = REAL_MAX;
		U32 maxIndex = numContacts;
		for(U32 i = 0; i < numContacts; ++i)
		{
			real sepVal = contactArray[i].CalculateSeparatingVelocity();
			if(sepVal < max && (sepVal < 0 || contactArray[i].GetPenetration() > 0))
			{
				max = sepVal;
				maxIndex = i;
			}
		}

		//If nothing is found, end it
		if(maxIndex == numContacts) break;

		contactArray[maxIndex].Resolve();
		++_iterationsUsed;
	}
}