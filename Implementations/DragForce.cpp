#include <Engine/DragForce.h>

using namespace KillerPhysics;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
DragForce::DragForce(void)
:
_drag(0.0f),
_dragSqr(0.0f)
{  }

DragForce::DragForce(real drag) 
: 
_drag(drag), 
_dragSqr(_drag * _drag)
{  }

DragForce::~DragForce(void) 
{  }

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
void DragForce::v_UpdateForce(shared_ptr<Particle> particle)
{
	KM::Vector4 force = particle->GetVelocity();

	real dragCoeff = force.Magnitude();
	dragCoeff = _drag * dragCoeff  + _dragSqr * dragCoeff * dragCoeff;

	force.Normalize();
	force *= -dragCoeff;

	particle->AddForce(force);
}

void DragForce::v_UpdateForce(shared_ptr<RigidBody> body)
{
	KM::Vector4 force = body->GetVelocity();

	real dragCoeff = force.Magnitude();
	dragCoeff = _drag * dragCoeff  + _dragSqr * dragCoeff * dragCoeff;

	force.Normalize();
	force *= -dragCoeff;

	body->AddForce(force);
}