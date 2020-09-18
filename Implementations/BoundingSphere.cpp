#include "stdafx.h"
#include "Engine/BoundingSphere.h"
using namespace TempestCollisions;

BoundingSphere::BoundingSphere(void)
:
_center(0.0f), 
_radius(0.0f)
{  }

BoundingSphere::BoundingSphere(const TM::Point3& center, real radius)
:
_center(center),
_radius(radius)
{  }

BoundingSphere::BoundingSphere(const BoundingSphere& one, const BoundingSphere& two)
:
_center(0.0f),
_radius(0.0f)
{
    TM::Point3 centerOffset = two.GetCenter() - one.GetCenter();
    real distanceSquared = centerOffset.SqrMagnitude();
    real radiusDiff = two.GetRadius() - one.GetRadius();

    //Check if the larger contains the smaller in size
    if(radiusDiff * radiusDiff >= distanceSquared)
    {
        if(one.GetRadius() > two.GetRadius())
        {
            _center = one.GetCenter();
            _radius = one.GetRadius();
        }
        else
        {
            _center = two.GetCenter();
            _radius = two.GetRadius();
        }
    }
    //Otherwise, they are partially overlapping
    else
    {
        distanceSquared = real_sqrt(distanceSquared);
        _radius = (distanceSquared + one.GetRadius() + two.GetRadius()) * static_cast<real>(0.5f);

        //Center is based on one's center moved towards two's center proportional to the radii
        _center = one.GetCenter();
        if(distanceSquared > 0)
        {
            _center += centerOffset * ((_radius - one.GetRadius()) / distanceSquared);
        }
    }
}

BoundingSphere::~BoundingSphere(void)
{  }

bool BoundingSphere::TestCollision(const BoundingSphere& other) const
{
    TM::Point3 distance = _center - other.GetCenter();
    
    //The dot product of a Point and itself is the squred magnitude, but with less steps. 
    real distanceSquared = distance.Dot(distance);
    
    float radiusSum = _radius + other.GetRadius();

    return distanceSquared <= radiusSum * radiusSum;
}

real BoundingSphere::GetGrowth(BoundingSphere& other) const
{
    BoundingSphere newSphere(*this, other);

    //return value proportional to the change in surface area of the new sphere
    return newSphere.GetRadius() * newSphere.GetRadius() - _radius * _radius;
}

real BoundingSphere::GetSize(void) const
{
    return static_cast<real>(1.333333) * R_PI * _radius * _radius * _radius;
}

void BoundingSphere::SetCenter(const TM::Point3& pos)
{
    _center = pos;
}

void BoundingSphere::SetCenter(F32 x, F32 y, F32 z)
{
    _center.Set(x, y, z);
}

const TM::Point3& BoundingSphere::GetCenter(void) const
{
    return _center;
}

void BoundingSphere::SetRadius(real r)
{
    _radius = r;
}

real BoundingSphere::GetRadius(void) const
{
    return _radius;
}