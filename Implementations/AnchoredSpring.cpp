#include <Engine/AnchoredSpring.h>

using namespace KillerPhysics;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
AnchoredSpring::AnchoredSpring(void)
:
_anchor(0.0f),
_springConstant(1),
_restLength(1)
{  }

AnchoredSpring::AnchoredSpring(const KM::Point& anchor, real springConstant, real restLength)
:
_anchor(anchor),
_springConstant(springConstant),
_restLength(restLength)
{  }

AnchoredSpring::~AnchoredSpring(void)
{  }

void AnchoredSpring::v_UpdateForce(shared_ptr<RigidBody2D> RigidBody2D)
{
	//Calculate the Vector4 of the spring
	KM::Vector4 force {};
	force = RigidBody2D->GetPosition();
	force -= _anchor;

	//Calculate the magnitude of the force
	real magnitude = force.Magnitude();
	magnitude = (_restLength - magnitude) * _springConstant;

	//Calculate the final force and apply it
	force.Normalize();
	force *= static_cast<F32>(magnitude);
	RigidBody2D->AddForce(force);
}

//TODO: Implement
void AnchoredSpring::v_UpdateForce(shared_ptr<RigidBody3D> body)
{
	KM::Vector4 force {}; 
	force = body->GetPosition();
	force -= _anchor;

	real magnitude = force.Magnitude();
	magnitude = (_restLength - magnitude) * _springConstant;

	force.Normalize();
	force *= static_cast<F32>(magnitude);
	body->AddForce(force);
}
