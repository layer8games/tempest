#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Vector.h>

namespace KM = KillerMath;

namespace KillerCollisions
{
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
		BoundingSphere(const KM::Vector& center, real radius);

/*! 
	Special constructor that combined the volumes of 2 BoundingSpheres into one sphere that emcompasses both volumes. 
	\param one is the first sphere.
	\param two is the second sphere to combine with one. 
*/
		BoundingSphere(const BoundingSphere& one, const BoundingSphere& two);

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

		real GetGrowth(BoundingSphere& other) const;

		inline real GetSize(void) const
		{
			return static_cast<real>(1.333333) * R_PI * _radius * _radius * _radius;
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
		inline void SetCenter(const KM::Vector& pos)
		{
			_center = pos;
		}

/*! 
	Get the location of the center. 
*/
		inline const KM::Vector& GetCenter(void) const
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
		KM::Vector _center; 	///< Center of the sphere.
		real 	   _radius;		///< Radius of the sphere.

	};//end Class
}//end Namespace
