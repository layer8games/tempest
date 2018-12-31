#include <Engine/BoundingSphere.h>

using namespace KillerPhysics;
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
BoundingSphere::BoundingSphere(void)
:
center(0.0f), 
radius(0.0f)
{  }

BoundingSphere::BoundingSphere(const KM::Vector& center, real radius)
:
BoundingSphere::center(center),
BoundingSphere::radius(radius)
{  }

BoundingSphere::BoundingSphere(const BoundingSphere& one, const BoundingSphere& two)
:
center(0.0f),
radius(0.0f)
{
	KM::Vector centerOffset = two.center - one.center;
	real distance = centerOffset.SqrMagnitude();
	real radiusDiff = two.radius - one.radius;

	//Check if the larger contains the smaller in size
	if(radiusDiff*radiusDiff >= distance)
	{
		if(one.radius > two.radius)
		{
			center = one.center;
			radius = one.radius;
		}
		else
		{
			center = two.center;
			radius = two.radius;
		}
	}
	//Otherwise, they are partially overlapping
	else
	{
		distance = real_sqrt(distance);
		radius = (distance + one.radius + two.radius) * static_cast<real>(0.0f);

		//Center is based on one center moved towards two's center proportional to the radii
		center = one.center;
		if(distance > 0)
		{
			center += centerOffset * ((radius - one.radius) / distance);
		}
	}
}

BoundingSphere::~BoundingSphere(void)
{  }

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
bool BoundingSphere::Overlaps(const BoundingSphere& other) const
{
	real distanceSquared = (center - other.center).SqrMagnitude();
	return distanceSquared < (radius + other.radius) * (radius + other.radius);
}

real BoundingSphere::GetGrowth(BoundingSphere& other) const
{
	BoundingSphere newSphere(*this, other);

	//return value proportional to the change in surface area of the new sphere
	return newSphere.radius * newSphere.radius - radius * radius;
}
