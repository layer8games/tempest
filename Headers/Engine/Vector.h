#pragma once

//===== Killer Includes =====
#include <Engine/Atom.h>


//===== Stnadard inlcudes =====
#include <cassert>

namespace KillerMath
{
//==========================================================================================================================
//Documentation
//==========================================================================================================================
/*! 
	A custom Vector class writen for the Killer Engine. 

	The Vector is a 4 element 3D vector. The Vector consists of an x, y, z and w component represented by an array of F32 values. They are refered as x, y, z and w through through documentation. In code, you would have to refered to them as their index in the array (0 - 3). There is an alias set up in the Vector, and enum, that lets you use x, y, z and w to represent the indices natively. This is private to the Vector. The w is included mostly used for convenience when multiplying with a 4X4 Matrix4. It follows all the rules of a Vector and can be used for what you need it to be. 
*/
	class Vector
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
		Vector(void);

/*! 
	Single input conversion constructor. It will set the x, y and z components to the input. _2D is false. 
	\param val F32: Input value for x, y and z.
*/		
		explicit Vector(F32 val);

/*! 
	Two input constructor. Set's x and y accordingly. Z is set to 0.0f. W is set to 1.
	\param x is the value for x.
	\param y is the value for y.
*/	
		Vector(F32 x, F32 y);

/*! 
	Three input constructor. W is set to 1.
	\param x is the value for x.
	\param y is the value for y.
	\param z is the value for z.
*/
		Vector(F32 x, F32 y, F32 z);

/*! 
	Four input constructor.
	\param x is the value for x.
	\param y is the value for y.
	\param z is the value for z.
	\param w is the value for w.
*/
		Vector(F32 x, F32 y, F32 z, F32 w);

/*! 
	Copy Constructor. It explicitly copies all data into new Vector. 
	\param v is the vector to copy. 
*/
		Vector(const Vector& v);

/*! 
	Destructor. It does not do anything. 
*/		
		~Vector(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
//===== 2D checks =====		
/*! 
	Sets the Vector to act like a 2D vector instead of a 3D Vector by setting _2D to true. This means that the z value wont 
	be copied or used in operations. 
*/		
		inline void Make2D(void)
		{
			_2D = true;
		}

/*! 
	Sets the Vector to act like a 3D Vector instead of a 3D vector by settings _2D to true. This means that the z value will
	be copied and used in operations.
*/		
		inline void Make3D(void)
		{
			_2D = false;
		}

/*! 
	Returns that 2D state of the Vector stored in _2D;
*/		
		inline bool Is2D(void) const
		{
			return _2D;
		}

//===== Vector Special functions =====
/*!
	Performs a Dot or Scalar product in the order of this * other.
	\param vec is the left hand argument in the operation.	
*/
		F32 Dot(const Vector& vec) const;

/*!
	Performs a Cross or Vector production in the order of this % other.
	\param vec is the left hand argument in the operation.			
*/		
		Vector CrossProduct(const Vector& vec) const;

/*!
	Returns the length of the Vector. Caution, this uses the square root function.
*/
		F32 Magnitude(void);

/*!
	Returns the squard length of the Vector. It avoids the cost of the square root function.
*/
		F32 SqrMagnitude(void);

/*!
	Changes the Vector into a unit vector by converting its magnitude to exaclty 1.0. This is an expensive operation.
*/
		void Normalize(void);

/*!
	Sets all values to input. Does not check for _2D before changing z. 
	\param val is the value x, y and z will get. w is set to 1.0f. Default value is 0.0f.
*/
		void Reset(F32 val=0.0f);

//===== Math Helper Functions =====
/*!
	Adds a Vector scaled by a value to this Vector. 
	\param vec is the vector that will be added to this one. 
	\param scale is the amount the added vector will be scaled by.
*/
		void AddScaledVector(const Vector& vec, F32 scale);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
/*!
	Returns the raw data for the Vector.
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
	Allows you to index into the Vector to read the value.
	\param i is the index you wish to read. 0 = x, 1 = y, 2 = z, 3 = w.
*/
		inline const F32& operator[](int i) const
		{
			return _data[i];
		}

/*!
	Allows you to index into the Vector to change the value.
	\param i is the index you wish to change. 0 = x, 1 = y, 2 = z, 3 = w.
*/
		inline F32& operator[](int i)
		{
			return _data[i];
		}

//===== Copy Assignment =====		
/*!
	Copy assignment from Vector.
	\param vec is the vector to copy into this vector.
*/
		Vector& operator=(const Vector& vec);

/*!
	Copy assignment from scalar.
	\param val is the value all elements will be set to. w is not affect. 2D check is done before z is changed.

*/
		Vector& operator=(F32 val);

//===== Add by Vector =====
/*!
	Vector addtion. This is done componentwise.
	\param vec is the Vector to add into a new Vector.
*/
		Vector operator+(const Vector& vec) const;

/*!
	Vector addition equal. This is done componentwise.
	\param vec is the Vector to add into this Vector.
*/
		Vector& operator+=(const Vector& vec);

//===== Add by scalar =====
/*!
	Scalar addition. Each value is added into. 2D check done before z is changed.
	\param val is added into the elements of a new Vector.
*/
		Vector operator+(F32 val) const;

/*!
	Scalar addition. Each value is added into. 2D check done before z is changed.
	\param val is added into each element of this Vector.
*/
		Vector& operator+=(F32 val);

/*!
	Shared Pointer addition. A helper to allow arithmetic with shared_ptr<Vector>.
	\param vec is the shared_ptr<Vector> that is added into each element of a new Vector.
*/
		Vector operator+(shared_ptr<Vector> vec) const;

//===== Subtract by Vector =====
/*!
	Vector subtraction. This is done componentwise. 2D check done before z is changed. 
	\param vec is the Vector subtracted from the new Vector.
*/
		Vector operator-(const Vector& vec) const;

/*!
	Vector subtraction. This is done componenetwise. 2D check done before z is changed. 
	\param vec is the Vectored subtractd from this Vector.
*/
		Vector& operator-=(const Vector& vec);

//===== Negation and increment =====
/*! 
	Changes the sign of each element of the Vector. If 2D, z is not changed. w is also ignored. 
*/
		inline Vector operator-(void)
		{
			if(_2D)
			{
				return Vector(-_data[x], -_data[y]);
			}

			return Vector(-_data[x], -_data[y], -_data[z]);
		}

/*! 
	Prefix, Adds 1 to each element of the Vector. If 2D, z is ignored. w is always ignored.  
*/
		inline Vector& operator++(void)
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
	Postfix, Adds 1 to each element of the Vector. If 2D, z is ignored. w is always ignored.  
*/
		inline Vector operator++(int)
		{
			if(_2D)
			{
				return Vector(++_data[x], ++_data[y]);
			}

			return Vector(++_data[x], ++_data[y], ++_data[z]);
		}

/*! 
	Prefix, Subtracts 1 to each element of the Vector. If 2D, z is ignored. w is always ignored.  
*/
		inline Vector& operator--(void)
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
	Postfix, Subtracts 1 to each element of the Vector. If 2D, z is ignored. w is always ignored.   
*/
		inline Vector operator--(int)
		{
			if(_2D)
			{
				return Vector(--_data[x], --_data[y]);
			}

			return Vector(--_data[x], --_data[y], --_data[z]);
		}

//===== Subtract by scalar =====
/*!
	Scalar subtraction. 2D check is done before z is changed. 
	\param val is the scalar subtracted from the new Vector.
*/
		Vector operator-(F32 val) const;

/*!
	Sclara subtraction. 2D check is done before z is changed. 
	\param val is the scalar subtracted from each element of this Vector.
*/
		Vector& operator-=(F32 val);

//===== Component-wise multiply by vector =====
/*!
	Vector multiplication. This is a componentwise multiplication, scaling one Vector by another. 2D check done before z is changed.
	\param vec is the Vector multiplied by the new Vector.
*/
		Vector operator*(const Vector vec) const;

/*!
	Vector multiplication. This is a componentwise multiplication, scaling one Vector by another. 2D check done before z is changed.
	\param vec is the Vector multiplied by this Vector.
*/
		Vector& operator*=(const Vector vec);

//===== Mutliply by Scalar =====
/*!
	Scalar multiplication. This is a componentwise multiplication, scaling the Vector by the scalar. 2D check done before z is changed.
	\param val is the scalar multiplied by the new Vector.
*/
		Vector operator*(F32 val) const;

/*!
	Scalar multiplication. This is a componentwise multiplication, scaling the Vector by the scalar. 2D check done before z is changed.
	\param val is the scalar multiplied by this Vector.
*/
		Vector& operator*=(F32 val);

//===== Divide by scalar =====
/*!
	Scalar division. This is done componentwise. 2D check done before z is changed. 
	\param val is the scalar the new Vector is divided by.
*/
		Vector operator/(F32 val) const;

/*!
	Scalar division. This is done componentwise. 2D check done before z is changed. 
	\param val is the scalar this Vector is divided by.
*/
		Vector& operator/=(F32 val);

//===== Comparison =====
/*!
	Greater than comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are greater than all elements of the other Vector.
	\param vec is the Vector this Vector will be compared against.
*/
		bool operator>(const Vector& vec) const;

/*!
	Less than comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are less than all elements of the other Vector.
	\param vec is the Vector this Vector will be compared against.
*/
		bool operator<(const Vector& vec) const;

/*!
	Greater than or equal to comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are greater than or equal to all elements of the other Vector.
	\param vec is the Vector this Vector will be compared against.
*/
		bool operator>=(const Vector& vec) const;

/*!
	Less than or equal to comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are less than or equal to all elements of the other Vector.
	\param vec is the Vector this Vector will be compared against.
*/
		bool operator<=(const Vector& vec) const;

/*!
	Equality comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are equal to all elements of other Vector. 
	\param vec is the Vector this Vector will be compared against. 
*/
		bool operator==(const Vector& vec) const;

/*!
	False equality comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are not equal to all elements of other Vector. 
	\param vec is the Vector this Vector will be compared against. 
*/
		bool operator!=(const Vector& vec) const;


	private:
/*!
	Alias set up to allow a refernce to each element that is more human readable in the code.
*/
		enum 
		{
			x = 0,
			y = 1,
			z = 2,
			w = 3
		};

		bool _2D;		///< Used to decide whether to use 2D or 3D logic in operators.
		F32  _data[4];	///< Array that stores the values for each element.
		//This is an idea for later. 
		//Find a value that you can invalidate if 
		//x y or z changes, that allows you to cache 
		//the mag and save on the sqrt call
		//F32  _magCache;
	};
}