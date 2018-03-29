#include <Engine/Particle2DDragForce.h>

using namespace KillerPhysics;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
Particle2DDragForce::Particle2DDragForce(void) 
{  }

Particle2DDragForce::Particle2DDragForce(real k1, real k2) 
: 
_k1(k1), 
_k2(k2)
{  }

Particle2DDragForce::~Particle2DDragForce(void) 
{  }

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
void Particle2DDragForce::v_UpdateForce(Particle2D& particle)
{
	KM::Vector2 force = particle.GetVelocity();

	real dragCoeff = force.Magnitude();
	dragCoeff = _k1 * dragCoeff  + _k2 * dragCoeff * dragCoeff;

	force.Normalise();
	force *= -dragCoeff;

	particle.AddForce(force);
}