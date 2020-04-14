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
    _inverseMomentOfInertia(1.0f),
    _linearDamping(0.999f),
    _angularDamping(0.999f),
    _obj(nullptr),
    _rotation(0.0f),
    _velocity(0.0f),
    _acceleration(0.0f),
    _forceAccum(0.0f),
    _gravityForce(0.0f)
{  }

RigidBody2D::RigidBody2D(const RigidBody2D* otherBody)
    :
    _active(otherBody->GetActive()),
    _inverseMass(otherBody->GetInverseMass()),
    _inverseMomentOfInertia(otherBody->GetMomentOfInertia()),
    _linearDamping(otherBody->GetLinearDamping()),
    _obj(otherBody->GetGameObject()),
    _rotation(otherBody->GetRotation()),
    _velocity(otherBody->GetVelocity()),
    _acceleration(otherBody->GetAcceleration()),
    _forceAccum(otherBody->GetForces()),
    _gravityForce(otherBody->GetGravityForce())
{  }

RigidBody2D::RigidBody2D(const RigidBody2D& otherBody)
    :
    _active(otherBody.GetActive()),
    _inverseMass(otherBody.GetInverseMass()),
    _inverseMomentOfInertia(otherBody.GetMomentOfInertia()),
    _linearDamping(otherBody.GetLinearDamping()),
    _obj(otherBody.GetGameObject()),
    _rotation(otherBody.GetRotation()),
    _velocity(otherBody.GetVelocity()),
    _acceleration(otherBody.GetAcceleration()),
    _forceAccum(otherBody.GetForces()),
    _gravityForce(otherBody.GetGravityForce())
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
    if(_obj == nullptr)
    {
        TE::ErrorManager::Instance()->SetError(TE::PHYSICS, "RigidBody2D::Integrate: object not set!");
        return;
    }

    if(_inverseMass == 0) return;

    F32 delta = TM::Timer::Instance()->DeltaTime();
    assert(delta > 0.0f);

    TM::Vector2 accelerationLastFrame = _acceleration;
    real angularAcceleration = _torqueAccum * _inverseMomentOfInertia;
    
    _forceAccum += _gravityForce;

    accelerationLastFrame += _forceAccum * _inverseMass;
    
    _velocity += accelerationLastFrame * delta;
    _rotation += angularAcceleration * delta;

    _velocity *= real_pow(_linearDamping, delta);
    _rotation *= real_pow(_angularDamping, delta);

    _obj->AddPosition(_velocity * delta);
    _obj->AddOrientation(_rotation * delta);

    ClearAccumulator();
}

void RigidBody2D::ClearAccumulator(void)
{
    _forceAccum.Reset();
    _torqueAccum = 0.0f;
}

void RigidBody2D::UpdateVelocityAndAcceleration(const TE::SteeringOutput2D steering)
{
    _velocity += steering.linear * TM::Timer::Instance()->DeltaTime();
    _rotation += steering.angular * TM::Timer::Instance()->DeltaTime();
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

void RigidBody2D::AddForce(const TM::Vector2& force)
{
    _forceAccum += force;
}

void RigidBody2D::AddForceAtPoint(const TM::Vector2& force, const TM::Point2 point)
{
    _forceAccum += force;
    _torqueAccum = point.x * force.y - point.y * force.x;
}

void RigidBody2D::SetMomentOfInertia(real inertia)
{
    _inverseMomentOfInertia = 1 / inertia;
}

real RigidBody2D::GetMomentOfInertia(void) const
{
    return _inverseMomentOfInertia;
}

void RigidBody2D::SetAngularDamping(real angularDamping)
{
    _angularDamping = angularDamping;
}

real RigidBody2D::GetAngularDamping(void) const
{
    return _angularDamping;
}