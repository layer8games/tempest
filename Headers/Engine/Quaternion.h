#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Vector.h>

#include <assert.h>

namespace KillerMath
{
//==========================================================================================================================
//Documentation
//==========================================================================================================================
/*! 
	Quaternions will handle the rotational math that the engine will use. This class is the holder of these functions. The
	Quaternion is represent by an Array of 4 F32 values. These include w, x, y, z. Unlike the Vector, w is the first element.
*/	
	class Quaternion
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================		
/*! 
	Default Constructor. Sets  
*/
		Quaternion(void);

/*! 
	 Conversion constructor. Sets all elements to the same value.
	 \param value is what each element will be set to.
*/
		explicit Quaternion(real value);

/*! 
	Four value constructor. 
	\param wVal is the value that w will be set to.
	\param xVal is the value that x will be set to.
	\param yVal is the value that y will be set to.
	\param zVal is the value that z will be set to.

*/
		Quaternion(real wVal, real xVal, real yVal, real zVal);

/*! 
	Copy constructor. Calls the [] operator to get the elements to copy into this Quaternion.
	\param q is the Quaternion that will be copied. 
*/
		Quaternion(const Quaternion& q);

/*! 
	Default Destructor. Has no direct function at this time. 
*/
		~Quaternion(void);
		
//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
//==========================================================================================================================
//Accessors
//==========================================================================================================================		
/*! 
	Returns the pointer to the array of elements. 
*/
		const real* GetElems(void) const
		{
			return _data;
		}
//==========================================================================================================================
//
//Operators
//
//==========================================================================================================================
/*!
	Allows you to index into the Quaternion to read the value.
	\param i is the index you wish to read. 0 = x, 1 = y, 2 = z, 3 = w.
*/
		inline const F32& operator[](int i) const
		{
			return _data[i];
		}

/*!
	Allows you to index into the Quaternion to change the value.
	\param i is the index you wish to change. 0 = x, 1 = y, 2 = z, 3 = w.
*/
		inline F32& operator[](int i)
		{
			return _data[i];
		}

/*! 
	Scalar division. Performs a component wise division
	\param d is the value that all elements of the new Quaternion will be divided by. 
*/
		Quaternion operator/(real d);

/*! 
	Scalar division. Performs a component wise division
	\param d is the value that all elements of this Quaternion will be divided by. 
*/
		Quaternion& operator/=(real d);

/*! 
	Scalar multiplication. Performs a compoenent wise multiplication.
	\param m is the value that all the elements of the new Quaternion will be multiplied by. 
*/
		Quaternion operator*(real m);

/*! 
	Quaternion multiplication. Similar to the Vector::CrossProduct. 
	\param q2 is the Quaternion that the new Quaternion will be multiplied with. 
*/
		Quaternion operator*(const Quaternion& q2);

/*! 
	Scalar multiplication. Performs a component wise operation.
	\param m is the value by which this Quaternion will be multiplied by. 
*/
		Quaternion& operator*=(real m);

/*! 
	 Quaternion multiplication. Similar to the Vector::CrossProduct. 
	\param q2 is the Quaternion that this Quaternion will be multiplied with.
*/
		Quaternion& operator*=(const Quaternion& q2);

//==========================================================================================================================
//
//Quaternion Functions
//
//==========================================================================================================================
/*! 
	Returns the length of the rotation that this Quaternion represents. 
*/
		real Magnitude(void);

/*! 
	Returns a new Quaternion that represents the negation of the vector portion of the Quaternion. 
*/
		Quaternion Conjugate(void);

/*! 
	Returns a new Quaternion that represents the Conjugate divided by the Magnitude of this Quaternion. 
*/
		Quaternion Inverse(void);

/*! 
	Returns a Quaternion that reprsents the angular displacement between this Quaternion and another.
	\param Q is the other Quaternion in the displacement. 
*/
		Quaternion Difference(Quaternion& Q);

/*! 
	Returns the Dot Product between this Quaternion and another. 
	\param Q is the other Quaternion that this Quaterion will perform the operation against. 
*/
		real Dot(Quaternion& Q);

/*! 
	\bug This should be changed to be the - operator. Multiplies all elements of this Quaternion by -1. 
*/
		void Negate(void);

/*! 
	Like Negate, but returns the result. Should probably be removed later. 
*/
		Quaternion Opposite(void);

/*! 
	 Makes the length of the rotation that this Quaternion represents be exactly 1.  
*/
		void Normalize(void);

/*! 
	 Adds a scaled Vector into this one. 
	 \param q is the Quaternion to be added. 
	 \param scale is the amount q will be scaled by.
*/
		void AddScaledVector(const Vector& vec, F32 scale);
		
	private:
/*!
	Alias set up to allow a refernce to each element that is more human readable in the code.
*/
		enum 
		{
			w = 0,
			x = 1,
			y = 2,
			z = 3,
		};

		real _data[4]; ///< Array that stores the values for each element.
	};//end Class
}//end Namespace