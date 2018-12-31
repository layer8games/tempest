#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Vector.h>

namespace KM = KillerMath;

namespace KillerPhysics
{
	struct BoundingSphere
	{
//==========================================================================================================================
//
//Data
//
//==========================================================================================================================	
		KM::Vector center; 
		real 	   radius;

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		BoundingSphere(void);

		BoundingSphere(const KM::Vector& center, real radius);

		BoundingSphere(const BoundingSphere& one, const BoundingSphere& two);

		~BoundingSphere(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
		bool Overlaps(const BoundingSphere& other) const;

		real GetGrowth(BoundingSphere& other) const;

		inline real GetSize(void) const
		{
			return static_cast<real>(1.333333) * R_PI * radius * radius * radius;
		}

	};//end Class
}//end Namespace
