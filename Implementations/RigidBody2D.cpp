#include <Engine/RigidBody2D.h>


using namespace TempestPhysics;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
RigidBody2D::RigidBody2D(void)
:
_active(true),
_inverseMass(1.0f),
_damping(0.999f),
_obj(nullptr),
_velocity(0.0f),
_acceleration(0.0f),
_forceAccum(0.0f),
_gravityForce(0.0f)
{  }

RigidBody2D::RigidBody2D(const RigidBody2D* RigidBody2D)
:
_velocity(RigidBody2D->GetVelocity()),
_acceleration(RigidBody2D->GetAcceleration()),
_forceAccum(RigidBody2D->GetForces()),
_gravityForce(RigidBody2D->GetGravityForce()),
_inverseMass(RigidBody2D->GetInverseMass()),
_damping(RigidBody2D->GetDamping())
{  }

RigidBody2D::RigidBody2D(const RigidBody2D& RigidBody2D)
:
_velocity(RigidBody2D.GetVelocity()),
_acceleration(RigidBody2D.GetAcceleration()),
_forceAccum(RigidBody2D.GetForces()),
_gravityForce(RigidBody2D.GetGravityForce()),
_inverseMass(RigidBody2D.GetInverseMass()),
_damping(RigidBody2D.GetDamping())
{  }

RigidBody2D::~RigidBody2D(void)
{
    _obj = nullptr;
}

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
void RigidBody2D::Integrate(void)
{
    //if(_obj.expired())
    if(_obj == nullptr)
    {
        TE::ErrorManager::Instance()->SetError(TE::PHYSICS, "RigidBody2D::Integrate: object not set!");
        return;
    }

    if(_inverseMass == 0) return;

    F32 delta = TM::Timer::Instance()->DeltaTime();
    assert(delta > 0.0f);

    _obj->AddScaledPosition(_velocity, delta);

    TM::Vector2 resultingAcc = _acceleration;
    
    resultingAcc += _gravityForce;

    resultingAcc.AddScaledVector(_forceAccum, delta);

    _velocity.AddScaledVector(resultingAcc, delta);

    _velocity *= real_pow(_damping, delta);

    ClearAccumulator();
}

void RigidBody2D::ClearAccumulator(void)
{
    _forceAccum.Reset();
}

void RigidBody2D::AddForce(real xVal, real yVal)
{
    _forceAccum.x += xVal;
    _forceAccum.y += yVal;
}

void RigidBody2D::AddForce(const TM::Vector2 force)
{
    _forceAccum += force;
}

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
bool RigidBody2D::GetActive(void) const
{
    if(_obj != nullptr)
    {
        return _obj->GetActive() && _active;
    }

    return _active;
}

const TM::Point2 RigidBody2D::GetPosition(void) const
{
    if(_obj != nullptr)
   {
        return _obj->GetPosition();
   }
   else
   {
       TE::ErrorManager::Instance()->SetError(TE::PHYSICS, "RigidBody2D::GetPosition Set the GameObject before calling GetPosition");
       return TM::Point2(0.0f);
   }
}

const real RigidBody2D::GetMass(void)
{
    if(_inverseMass == 0.0f)
    {
        return REAL_MAX;
    }
    else
    {
        return static_cast<real>(1.0f) / _inverseMass;
    }
}