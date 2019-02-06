#include <Engine/BoundingSphere.h>

using namespace KillerCollisions;
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
BoundingSphere::BoundingSphere(void)
:
_center(0.0f), 
_radius(0.0f)
{  }

BoundingSphere::BoundingSphere(const KM::Vector& center, real radius)
:
_center(center),
_radius(radius)
{  }

BoundingSphere::BoundingSphere(const BoundingSphere& one, const BoundingSphere& two)
:
_center(0.0f),
_radius(0.0f)
{
	KM::Vector centerOffset = two.GetCenter() - one.GetCenter();
	real distance = centerOffset.Dot(centerOffset);
	real radiusDiff = two.GetRadius() - one.GetRadius();

	//Check if the larger contains the smaller in size
	if(radiusDiff*radiusDiff >= distance)
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
		distance = real_sqrt(distance);
		_radius = (distance + one.GetRadius() + two.GetRadius()) * static_cast<real>(0.0f);

		//Center is based on one center moved towards two's center proportional to the radii
		_center = one.GetCenter();
		if(distance > 0)
		{
			_center += centerOffset * ((_radius - one.GetRadius()) / distance);
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
bool BoundingSphere::TestCollision(const BoundingSphere& other) const
{
	KM::Vector distance = _center - other.GetCenter();
	
	//The dot product of a vector and itself is the squred magnitude, but with less steps. 
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
