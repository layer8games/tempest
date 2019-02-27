#pragma once

//===== Killer Includes =====
#include <Engine/Atom.h>
#include <Engine/Vector4.h>
#include <Engine/Point.h>


//===== Stnadard inlcudes =====
#include <cassert>

namespace KillerMath
{
	class Vector4;
	class Point;

//==========================================================================================================================
//Documentation
//==========================================================================================================================
/*! 
	A custom Vector3 class writen for the Killer Engine.

	The Vector3 is a 3 element 3D Vector. The Vector3 consists of an x, y, and z component represented by an array of F32 values. 
	They are refered as x, y, and z through documentation. In code, you can refere to them by x, y and z, due to an enum defined
	in  Atom.h.  

	Unlike the Vector4, there is no w, so there is no difference between a position and a direction, like in the Point vs Vector4
	classes. This class exists for when something doesn't need that extra data that comes with the w element. This can save on 
	memory and computation. The Matrix3 class uses it, for example.
*/
	class Vector3
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
/*! 
	Default construtor. Sets all values to 0, and _2D to false.
*/		
		Vector3(void);

/*! 
	Single input conversion constructor. It will set the x, y and z components to the input. _2D is false. 
	\param val F32: Input value for x, y and z.
*/		
		explicit Vector3(F32 val);

/*! 
	Two input constructor. Set's x and y accordingly. Z is set to 0.
	\param x is the value for x.
	\param y is the value for y.
*/	
		Vector3(F32 x, F32 y);

/*! 
	Three input constructor.
	\param x is the value for x.
	\param y is the value for y.
	\param z is the value for z.
*/
		Vector3(F32 x, F32 y, F32 z);

/*! 
	Copy Constructor. It explicitly copies all data into new Vector3. 
	\param v is the Vector3 to copy. 
*/
		Vector3(const Vector3& v);

/*!
	Convert a Vector4 into a Vector3.
	\param v is the Vector4 to convert.
*/
		explicit Vector3(const Vector4& v);

/*! 
	No implementation.
*/		
		~Vector3(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
//===== 2D checks =====		
/*! 
	Sets the Vector3 to act like a 2D Vector3 instead of a 3D Vector3 by setting _2D to true. This means that the z value wont 
	be copied or used in operations. 
*/		
		inline void Make2D(void)
		{
			_2D = true;
		}

/*! 
	Sets the Vector3 to act like a 3D Vector3 instead of a 3D Vector3 by settings _2D to true. This means that the z value will
	be copied and used in operations.
*/		
		inline void Make3D(void)
		{
			_2D = false;
		}

/*! 
	Returns that 2D state of the Vector3 stored in _2D;
*/		
		inline bool Is2D(void) const
		{
			return _2D;
		}

//===== Vector3 Special functions =====
/*!
	Performs a Dot or Scalar product in the order of this * other.
	\param vec is the left hand argument in the operation.	
*/
		F32 Dot(const Vector3& vec) const;

/*!
	Performs a Cross or Vector3 production in the order of this cross other.
	\param vec is the left hand argument in the operation.			
*/		
		Vector3 CrossProduct(const Vector3& vec) const;

/*!
	Returns the length of the Vector3. Caution, this uses the square root function.
*/
		F32 Magnitude(void);

/*!
	Returns the squard length of the Vector3. It avoids the cost of the square root function.
*/
		F32 SqrMagnitude(void);

/*!
	Changes the Vector3 into a unit Vector3 by converting its magnitude to exaclty 1.0. This is an expensive operation.
*/
		void Normalize(void);

/*!
	Sets all values to input. Does not check for _2D before changing z. 
	\param val is the value x, y and z will get. Default value is 0.
*/
		void Reset(F32 val=0.0f);

//===== Math Helper Functions =====
/*!
	Adds a Vector3 scaled by a value to this Vector3. 
	\param vec is the Vector3 that will be added to this one. 
	\param scale is the amount the added Vector3 will be scaled by.
*/
		void AddScaledVector3(const Vector3& vec, F32 scale);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
/*!
	Returns the raw data for the Vector3.
*/
		inline const F32* GetElems(void) const
		{
			return _data;
		}

/*!
	A helper function to allow to quickly set x, y and z to different values. This is useful because it is only one function
	call instead of the 3 it would take to call [] for each element. 
	\param xVal is the value for x.
	\param yVal is the vlaue for y.
	\param zVal is the value for z. 
*/
		inline void Set(F32 xVal, F32 yVal, F32 zVal)
		{
			_data[x] = xVal;
			_data[y] = yVal;
			_data[z] = zVal;
		}

//==========================================================================================================================
//
//operator Overloads
//
//==========================================================================================================================
/*!
	Allows you to index into the Vector3 to read the value.
	\param i is the index you wish to read. 0 = x, 1 = y, 2 = z.
*/
		inline const F32& operator[](int i) const
		{
			return _data[i];
		}

/*!
	Allows you to index into the Vector3 to change the value.
	\param i is the index you wish to change. 0 = x, 1 = y, 2 = z.
*/
		inline F32& operator[](int i)
		{
			return _data[i];
		}

//===== Copy Assignment =====		
/*!
	Copy assignment from Vector3.
	\param vec is the Vector3 to copy into this Vector3.
*/
		Vector3& operator=(const Vector3& vec);

/*!
	Copy assignment from scalar.
	\param val is the value all elements will be set to. 2D check is done before z is changed.

*/
		Vector3& operator=(F32 val);

//===== Add by Vector3 =====
/*!
	Vector3 addtion. This is done componentwise.
	\param vec is the Vector3 to add into a new Vector3.
*/
		Vector3 operator+(const Vector3& vec) const;

/*!
	Vector3 addition equal. This is done componentwise.
	\param vec is the Vector3 to add into this Vector3.
*/
		Vector3& operator+=(const Vector3& vec);

//===== Add by scalar =====
/*!
	Scalar addition. Each value is added into. 2D check done before z is changed.
	\param val is added into the elements of a new Vector3.
*/
		Vector3 operator+(F32 val) const;

/*!
	Scalar addition. Each value is added into. 2D check done before z is changed.
	\param val is added into each element of this Vector3.
*/
		Vector3& operator+=(F32 val);

/*!
	Shared Pointer addition. A helper to allow arithmetic with shared_ptr<Vector3>.
	\param vec is the shared_ptr<Vector3> that is added into each element of a new Vector3.
*/
		Vector3 operator+(shared_ptr<Vector3> vec) const;

//===== Subtract by Vector3 =====
/*!
	Vector3 subtraction. This is done componentwise. 2D check done before z is changed. 
	\param vec is the Vector3 subtracted from the new Vector3.
*/
		Vector3 operator-(const Vector3& vec) const;

/*!
	Vector3 subtraction. This is done componenetwise. 2D check done before z is changed. 
	\param vec is the Vector3ed subtractd from this Vector3.
*/
		Vector3& operator-=(const Vector3& vec);

//===== Negation and increment =====
/*! 
	Changes the sign of each element of the Vector3. If 2D, z is not changed.
*/
		inline Vector3 operator-(void)
		{
			if(_2D)
			{
				return Vector3(-_data[x], -_data[y]);
			}

			return Vector3(-_data[x], -_data[y], -_data[z]);
		}

/*! 
	Prefix, Adds 1 to each element of the Vector3. If 2D, z is ignored. 
*/
		inline Vector3& operator++(void)
		{
			++_data[x];
			++_data[y];

			if(!_2D)
			{
				++_data[z];
			}

			return *this;
		}

/*! 
	Postfix, Adds 1 to each element of the Vector3. If 2D, z is ignored. 
*/
		inline Vector3 operator++(int)
		{
			if(_2D)
			{
				return Vector3(++_data[x], ++_data[y]);
			}

			return Vector3(++_data[x], ++_data[y], ++_data[z]);
		}

/*! 
	Prefix, Subtracts 1 to each element of the Vector3. If 2D, z is ignored. 
*/
		inline Vector3& operator--(void)
		{
			--_data[x];
			--_data[y];

			if(!_2D)
			{
				--_data[z];
			}

			return *this;
		}

/*! 
	Postfix, Subtracts 1 to each element of the Vector3. If 2D, z is ignored.  
*/
		inline Vector3 operator--(int)
		{
			if(_2D)
			{
				return Vector3(--_data[x], --_data[y]);
			}

			return Vector3(--_data[x], --_data[y], --_data[z]);
		}

//===== Subtract by scalar =====
/*!
	Scalar subtraction. 2D check is done before z is changed. 
	\param val is the scalar subtracted from the new Vector3.
*/
		Vector3 operator-(F32 val) const;

/*!
	Sclara subtraction. 2D check is done before z is changed. 
	\param val is the scalar subtracted from each element of this Vector3.
*/
		Vector3& operator-=(F32 val);

//===== Component-wise multiply by Vector3 =====
/*!
	Vector3 multiplication. This is a componentwise multiplication, scaling one Vector3 by another. 2D check done before z is changed.
	\param vec is the Vector3 multiplied by the new Vector3.
*/
		Vector3 operator*(const Vector3 vec) const;

/*!
	Vector3 multiplication. This is a componentwise multiplication, scaling one Vector3 by another. 2D check done before z is changed.
	\param vec is the Vector3 multiplied by this Vector3.
*/
		Vector3& operator*=(const Vector3 vec);

//===== Mutliply by Scalar =====
/*!
	Scalar multiplication. This is a componentwise multiplication, scaling the Vector3 by the scalar. 2D check done before z is changed.
	\param val is the scalar multiplied by the new Vector3.
*/
		Vector3 operator*(F32 val) const;

/*!
	Scalar multiplication. This is a componentwise multiplication, scaling the Vector3 by the scalar. 2D check done before z is changed.
	\param val is the scalar multiplied by this Vector3.
*/
		Vector3& operator*=(F32 val);

//===== Divide by scalar =====
/*!
	Scalar division. This is done componentwise. 2D check done before z is changed. 
	\param val is the scalar the new Vector3 is divided by.
*/
		Vector3 operator/(F32 val) const;

/*!
	Scalar division. This is done componentwise. 2D check done before z is changed. 
	\param val is the scalar this Vector3 is divided by.
*/
		Vector3& operator/=(F32 val);

//===== Comparison =====
/*!
	Greater than comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are 
	greater than all elements of the other Vector3.
	\param vec is the Vector3 this Vector3 will be compared against.
*/
		bool operator>(const Vector3& vec) const;

/*!
	Less than comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are 
	less than all elements of the other Vector3.
	\param vec is the Vector3 this Vector3 will be compared against.
*/
		bool operator<(const Vector3& vec) const;

/*!
	Greater than or equal to comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements 
	of this are greater than or equal to all elements of the other Vector3.
	\param vec is the Vector3 this Vector3 will be compared against.
*/
		bool operator>=(const Vector3& vec) const;

/*!
	Less than or equal to comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of 
	this are less than or equal to all elements of the other Vector3.
	\param vec is the Vector3 this Vector3 will be compared against.
*/
		bool operator<=(const Vector3& vec) const;

/*!
	Equality comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are equal 
	to all elements of other Vector3. 
	\param vec is the Vector3 this Vector3 will be compared against. 
*/
		bool operator==(const Vector3& vec) const;

/*!
	False equality comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are 
	not equal to all elements of other Vector3. 
	\param vec is the Vector3 this Vector3 will be compared against. 
*/
		bool operator!=(const Vector3& vec) const;


	private:
//==========================================================================================================================
//
//Data
//
//==========================================================================================================================
		bool _2D;		///< Used to decide whether to use 2D or 3D logic in operators.
		F32  _data[3];	///< Array that stores the values for each element.
	};
}