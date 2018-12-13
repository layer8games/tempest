/*========================================================================
Quaternions will handle the rotational math that the engine will use. This
class is the holder of these functions. 

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Vector.h>

#include <assert.h>

namespace KillerMath
{
	class Quaternion
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		Quaternion(void);
		
		explicit Quaternion(real value);

		Quaternion(real wVal, real xVal, real yVal, real zVal);

		Quaternion(const Quaternion& q);

		~Quaternion(void);
		
//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
//==========================================================================================================================
//Accessors
//==========================================================================================================================		
		const real* GetElems(void) const
		{
			return _data;
		}
//==========================================================================================================================
//
//Operators
//
//==========================================================================================================================
		inline const F32& operator[](int i) const
		{
			return _data[i];
		}

		inline F32& operator[](int i)
		{
			return _data[i];
		}

		Quaternion operator/(real d);

		Quaternion& operator/=(real d);

		Quaternion operator*(real m);

		Quaternion operator*(const Quaternion& q2);

		Quaternion& operator*=(real m);

		Quaternion& operator*=(const Quaternion& q2);

//==========================================================================================================================
//
//Quaternion Functions
//
//==========================================================================================================================
		real Magnitude(void);

		Quaternion Conjugate(void);

		Quaternion Inverse(void);

		Quaternion Difference(Quaternion& Q);

		real Dot(Quaternion& Q);

		void Negate(void);

		Quaternion Opposite(void);

		void Normalize(void);

		void AddScaledVector(const Vector& vec, F32 scale);
		
	private:
		enum 
		{
			w = 0,
			x = 1,
			y = 2,
			z = 3,
		};

		real _data[4];
	};//end Class
}//end Namespace