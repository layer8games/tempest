#pragma once

//===== Killer Includes =====
#include <Engine/Atom.h>
#include <Engine/Vector3.h>
#include <Engine/Point.h>


//===== Stnadard inlcudes =====
#include <cassert>

namespace KillerMath
{
	class Vector3;
	class Point;
//==========================================================================================================================
//Documentation
//==========================================================================================================================
/*! 
	A custom Vector4 class writen for the Killer Engine.

	The Vector4 is a 4 element 3D Vector4. The Vector4 consists of an x, y, z and w component represented by an array of F32 values. 
	They are refered as x, y, z and w through through documentation. In code, you would have to refered to them as their index 
	in the array (0 - 3). There is an alias set up in the Vector4, and enum, that lets you use x, y, z and w to represent the 
	indices natively. This is private to the Vector4. 

	The w element is what separates a Vector4 from a Vector4. A Vector4 is meant to represent a direction with a magnitude. This 
	has many uses in equations involving direction and distance. Because of what this represents, transforming a direction 
	does not make a lot of sense. It should be able to be rotated, stretched, shered, pretty much any of the affine trans-
	formations, but it should not be linearly transformed. This is represented by keeping the w component set to 0. 
*/
	class Vector4
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
/*! 
	Default construtor. Sets all values to 0, and _2D to false. W is set to 1.
*/		
		Vector4(void);

/*! 
	Single input conversion constructor. It will set the x, y and z components to the input. _2D is false. 
	\param val F32: Input value for x, y and z.
*/		
		explicit Vector4(F32 val);

/*! 
	Two input constructor. Set's x and y accordingly. Z is set to 0.0f. W is set to 1.
	\param x is the value for x.
	\param y is the value for y.
*/	
		Vector4(F32 x, F32 y);

/*! 
	Three input constructor. W is set to 1.
	\param x is the value for x.
	\param y is the value for y.
	\param z is the value for z.
*/
		Vector4(F32 x, F32 y, F32 z);

/*! 
	Four input constructor.
	\param x is the value for x.
	\param y is the value for y.
	\param z is the value for z.
	\param w is the value for w.
*/
		Vector4(F32 x, F32 y, F32 z, F32 w);

/*! 
	Copy Constructor. It explicitly copies all data into new Vector4. 
	\param v is the Vector4 to copy. 
*/
		Vector4(const Vector4& v);

/*! 
	Copy a Point into a Vector4. W is set to 0.
	\param  p will be converted into a Vector4.
*/
		explicit Vector4(const Point& p);

/*! 
	Destructor. It does not do anything. 
*/		
		~Vector4(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
//===== 2D checks =====		
/*! 
	Sets the Vector4 to act like a 2D Vector4 instead of a 3D Vector4 by setting _2D to true. This means that the z value wont 
	be copied or used in operations. 
*/		
		inline void Make2D(void)
		{
			_2D = true;
		}

/*! 
	Sets the Vector4 to act like a 3D Vector4 instead of a 3D Vector4 by settings _2D to true. This means that the z value will
	be copied and used in operations.
*/		
		inline void Make3D(void)
		{
			_2D = false;
		}

/*! 
	Returns that 2D state of the Vector4 stored in _2D;
*/		
		inline bool Is2D(void) const
		{
			return _2D;
		}

//===== Vector4 Special functions =====
/*!
	Performs a Dot or Scalar product in the order of this * other.
	\param vec is the left hand argument in the operation.	
*/
		F32 Dot(const Vector4& vec) const;

/*!
	Performs a Dot or Scalar product in the order of this * other.
	\param point is the left hand argument in the operation.	
*/
		F32 Dot(const Point& point) const;

/*!
	Performs a Cross or Vector4 production in the order of this % other.
	\param vec is the left hand argument in the operation.			
*/		
		Vector4 CrossProduct(const Vector4& vec) const;

/*!
	Returns the length of the Vector4. Caution, this uses the square root function.
*/
		F32 Magnitude(void);

/*!
	Returns the squard length of the Vector4. It avoids the cost of the square root function.
*/
		F32 SqrMagnitude(void);

/*!
	Changes the Vector4 into a unit Vector4 by converting its magnitude to exaclty 1.0. This is an expensive operation.
*/
		void Normalize(void);

/*!
	Sets all values to input. Does not check for _2D before changing z. 
	\param val is the value x, y and z will get. w is set to 1.0f. Default value is 0.0f.
*/
		void Reset(F32 val=0.0f);

//===== Math Helper Functions =====
/*!
	Adds a Vector4 scaled by a value to this Vector4. 
	\param vec is the Vector4 that will be added to this one. 
	\param scale is the amount the added Vector4 will be scaled by.
*/
		void AddScaledVector4(const Vector4& vec, F32 scale);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
/*!
	Returns the raw data for the Vector4.
*/
		inline const F32* GetElems(void) const
		{
			return _data;
		}

/*!
	A helper function to allow to quickly set x, y and z to different values.
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
	Allows you to index into the Vector4 to read the value.
	\param i is the index you wish to read. 0 = x, 1 = y, 2 = z, 3 = w.
*/
		inline const F32& operator[](int i) const
		{
			return _data[i];
		}

/*!
	Allows you to index into the Vector4 to change the value.
	\param i is the index you wish to change. 0 = x, 1 = y, 2 = z, 3 = w.
*/
		inline F32& operator[](int i)
		{
			return _data[i];
		}

//===== Copy Assignment =====		
/*!
	Copy assignment from Vector4.
	\param vec is the Vector4 to copy into this Vector4.
*/
		Vector4& operator=(const Vector4& vec);

		Vector4& operator=(const Point& point);

		Vector4& operator=(const Vector3& vec);

/*!
	Copy assignment from scalar.
	\param val is the value all elements will be set to. w is not affect. 2D check is done before z is changed.

*/
		Vector4& operator=(F32 val);

//===== Add by Vector4 =====
/*!
	Vector4 addtion. This is done componentwise.
	\param vec is the Vector4 to add into a new Vector4.
*/
		Vector4 operator+(const Vector4& vec) const;

/*!
	Vector4 addition equal. This is done componentwise.
	\param vec is the Vector4 to add into this Vector4.
*/
		Vector4& operator+=(const Vector4& vec);

/*!
	Vector3 addtion. This is done componentwise.
	\param vec is the Vector3 to add into a new Vector4.
*/
		Vector4 operator+(const Vector3& vec) const;

/*!
	Vector3 addition equal. This is done componentwise.
	\param vec is the Vector3 to add into this Vector4.
*/
		Vector4& operator+=(const Vector3& vec);

/*!
	Point addtion. This is done componentwise.
	\param vec is the Point to add into a new Vector4.
*/
		Vector4 operator+(const Point& Point) const;

/*!
	Point addition equal. This is done componentwise.
	\param vec is the Point to add into this Vector4.
*/
		Vector4& operator+=(const Point& vec);

//===== Add by scalar =====
/*!
	Scalar addition. Each value is added into. 2D check done before z is changed.
	\param val is added into the elements of a new Vector4.
*/
		Vector4 operator+(F32 val) const;

/*!
	Scalar addition. Each value is added into. 2D check done before z is changed.
	\param val is added into each element of this Vector4.
*/
		Vector4& operator+=(F32 val);

/*!
	Shared Pointer addition. A helper to allow arithmetic with shared_ptr<Vector4>.
	\param vec is the shared_ptr<Vector4> that is added into each element of a new Vector4.
*/
		Vector4 operator+(shared_ptr<Vector4> vec) const;

//===== Subtract by Vector4 =====
/*!
	Vector4 subtraction. This is done componentwise. 2D check done before z is changed. 
	\param vec is the Vector4 subtracted from the new Vector4.
*/
		Vector4 operator-(const Vector4& vec) const;

/*!
	Vector4 subtraction. This is done componenetwise. 2D check done before z is changed. 
	\param vec is the Vector4ed subtractd from this Vector4.
*/
		Vector4& operator-=(const Vector4& vec);

/*!
	Vector3 subtraction. This is done componentwise. 2D check done before z is changed. 
	\param vec is the Vector3 subtracted from the new Vector4.
*/
		Vector4 operator-(const Vector3& vec) const;

/*!
	Vector3 subtraction. This is done componenetwise. 2D check done before z is changed. 
	\param vec is the Vector3 subtracted from this Vector4.
*/
		Vector4& operator-=(const Vector3& vec);

/*!
	Point subtraction. This is done componentwise. 2D check done before z is changed. 
	\param vec is the Point subtracted from the new Vector4.
*/
		Vector4 operator-(const Point& vec) const;

/*!
	Point subtraction. This is done componenetwise. 2D check done before z is changed. 
	\param vec is the Point subtracted from this Vector4.
*/
		Vector4& operator-=(const Point& vec);

//===== Negation and increment =====
/*! 
	Changes the sign of each element of the Vector4. If 2D, z is not changed. w is also ignored. 
*/
		inline Vector4 operator-(void)
		{
			if(_2D)
			{
				return Vector4(-_data[x], -_data[y]);
			}

			return Vector4(-_data[x], -_data[y], -_data[z]);
		}

/*! 
	Prefix, Adds 1 to each element of the Vector4. If 2D, z is ignored. w is always ignored.  
*/
		inline Vector4& operator++(void)
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
	Postfix, Adds 1 to each element of the Vector4. If 2D, z is ignored. w is always ignored.  
*/
		inline Vector4 operator++(int)
		{
			if(_2D)
			{
				return Vector4(++_data[x], ++_data[y]);
			}

			return Vector4(++_data[x], ++_data[y], ++_data[z]);
		}

/*! 
	Prefix, Subtracts 1 to each element of the Vector4. If 2D, z is ignored. w is always ignored.  
*/
		inline Vector4& operator--(void)
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
	Postfix, Subtracts 1 to each element of the Vector4. If 2D, z is ignored. w is always ignored.   
*/
		inline Vector4 operator--(int)
		{
			if(_2D)
			{
				return Vector4(--_data[x], --_data[y]);
			}

			return Vector4(--_data[x], --_data[y], --_data[z]);
		}

//===== Subtract by scalar =====
/*!
	Scalar subtraction. 2D check is done before z is changed. 
	\param val is the scalar subtracted from the new Vector4.
*/
		Vector4 operator-(F32 val) const;

/*!
	Sclara subtraction. 2D check is done before z is changed. 
	\param val is the scalar subtracted from each element of this Vector4.
*/
		Vector4& operator-=(F32 val);

//===== Component-wise multiply by Vector4 =====
/*!
	Vector4 multiplication. This is a componentwise multiplication, scaling one Vector4 by another. 2D check done before z is changed.
	\param vec is the Vector4 multiplied by the new Vector4.
*/
		Vector4 operator*(const Vector4 vec) const;

/*!
	Vector4 multiplication. This is a componentwise multiplication, scaling one Vector4 by another. 2D check done before z is changed.
	\param vec is the Vector4 multiplied by this Vector4.
*/
		Vector4& operator*=(const Vector4 vec);

//===== Mutliply by Scalar =====
/*!
	Scalar multiplication. This is a componentwise multiplication, scaling the Vector4 by the scalar. 2D check done before z is changed.
	\param val is the scalar multiplied by the new Vector4.
*/
		Vector4 operator*(F32 val) const;

/*!
	Scalar multiplication. This is a componentwise multiplication, scaling the Vector4 by the scalar. 2D check done before z is changed.
	\param val is the scalar multiplied by this Vector4.
*/
		Vector4& operator*=(F32 val);

//===== Divide by scalar =====
/*!
	Scalar division. This is done componentwise. 2D check done before z is changed. 
	\param val is the scalar the new Vector4 is divided by.
*/
		Vector4 operator/(F32 val) const;

/*!
	Scalar division. This is done componentwise. 2D check done before z is changed. 
	\param val is the scalar this Vector4 is divided by.
*/
		Vector4& operator/=(F32 val);

//===== Comparison =====
/*!
	Greater than comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are greater than all elements of the other Vector4.
	\param vec is the Vector4 this Vector4 will be compared against.
*/
		bool operator>(const Vector4& vec) const;

/*!
	Less than comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are less than all elements of the other Vector4.
	\param vec is the Vector4 this Vector4 will be compared against.
*/
		bool operator<(const Vector4& vec) const;

/*!
	Greater than or equal to comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are greater than or equal to all elements of the other Vector4.
	\param vec is the Vector4 this Vector4 will be compared against.
*/
		bool operator>=(const Vector4& vec) const;

/*!
	Less than or equal to comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are less than or equal to all elements of the other Vector4.
	\param vec is the Vector4 this Vector4 will be compared against.
*/
		bool operator<=(const Vector4& vec) const;

/*!
	Equality comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are equal to all elements of other Vector4. 
	\param vec is the Vector4 this Vector4 will be compared against. 
*/
		bool operator==(const Vector4& vec) const;

/*!
	False equality comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are not equal to all elements of other Vector4. 
	\param vec is the Vector4 this Vector4 will be compared against. 
*/
		bool operator!=(const Vector4& vec) const;


	private:
//==========================================================================================================================
//
//Data
//
//==========================================================================================================================
		bool _2D;		///< Used to decide whether to use 2D or 3D logic in operators.
		F32  _data[4];	///< Array that stores the values for each element.
		//This is an idea for later. 
		//Find a value that you can invalidate if 
		//x y or z changes, that allows you to cache 
		//the mag and save on the sqrt call
		//F32  _magCache;
	};
}