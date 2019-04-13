#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Point.h>

namespace KM = KillerMath;

namespace KillerCollisions
{
/*!
	The BoundingSphere is a basic bounding volume that can be used for simple, course collision tests. It is represented by
	a center position, located in the model space of the object it is attached to, and a radius, that describes its extent
	in all directions. 

	TestCollision functions can be added for each type of boudning volume it can intersect with. 
*/
	class BoundingSphere
	{

	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
/*! 
	Sets center and radius to 0. 
*/
		BoundingSphere(void);

/*! 
	Sets center and radius to args.
	\param center is the value for center. 
	\param radius is the value for radius. 
*/
		BoundingSphere(const KM::Point& center, real radius);

/*! 
	Special constructor that combines the volumes of 2 BoundingSpheres into one sphere that emcompasses both volumes. 
	\param one is the first sphere.
	\param two is the second sphere to combine with one. 
*/
		BoundingSphere(const BoundingSphere& one, const BoundingSphere& two);

/*!
	No implementation.
*/
		~BoundingSphere(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
/*! 
	Tests if another BoundingSphere is intersecting with this BoundingSphere. The distance between the centers is compared with
	the sum of the radii. We keep it squred to avoid having to call a sqrt function. 
	\param other is the BoundingSphere we are testing against.  
*/
		bool TestCollision(const BoundingSphere& other) const;

/*!
	Returns how much a Sphere would grow if it were combined with another Sphere. This size is not specified in specific units,
	but rather more closely reflect the surface area of the new sphere, so should be used to compare relative sizes, not specific
	sizes, since this would be unpredictable and far too much work to be with it. This function should be as a heuristic for tests
	between spheres.  
	\param other is the Sphere we are checking against. 
*/
		real GetGrowth(BoundingSphere& other) const;

/*!
	Returns the area of the Sphere. Untested. 
*/
		inline real GetSize(void) const
		{
			return static_cast<real>(1.333333) * R_PI * _radius * _radius * _radius;
		}

		inline void Make2D(bool state=true)
		{
			_center.Make2D(state);
		}

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
/*! 
	Set new center.
	\param pos is the new location of the center.
*/
		inline void SetCenter(const KM::Point& pos)
		{
			_center = pos;
		}

/*!
	Alternate setter for center.
	\param x is the value for x.
	\param y is the value for y.
	\param z is the value for z.
*/
		inline void SetCenter(F32 x, F32 y, F32 z)
		{
			_center[0] = x;
			_center[1] = y;
			_center[2] = z;
		}

/*! 
	Get the location of the center. 
*/
		inline const KM::Point& GetCenter(void) const
		{
			return _center;
		}

/*! 
	Set the radius.
	\param r is the new radius. 
*/
		inline void SetRadius(real r)
		{
			_radius = r;
		}

/*! 
	Get radius. 
*/
		inline real GetRadius(void) const
		{
			return _radius;
		}

	private:
//==========================================================================================================================
//
//Data
//
//==========================================================================================================================	
		KM::Point _center; 	///< Center of the sphere.
		real 	  _radius;	///< Radius of the sphere.

	};//end Class
}//end Namespace
