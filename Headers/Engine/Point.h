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
	A custom Point class writen for the Killer Engine. 

	The Point is a 4 element 3D Point. The Point consists of an x, y, z and w component represented by an array of F32 values. They are refered as x, y, z and w through through documentation. In code, you would have to refered to them as their index in the array (0 - 3). There is an alias set up in the Point, and enum, that lets you use x, y, z and w to represent the indices natively. This is private to the Point. The w is included mostly used for convenience when multiplying with a 4X4 Matrix4. It follows all the rules of a Point and can be used for what you need it to be. 
*/
	class Point
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
		Point(void);

/*! 
	Single input conversion constructor. It will set the x, y and z components to the input. _2D is false. 
	\param val F32: Input value for x, y and z.
*/		
		explicit Point(F32 val);

/*! 
	Two input constructor. Set's x and y accordingly. Z is set to 0.0f. W is set to 1.0f
	\param x is the value for x.
	\param y is the value for y.
*/	
		Point(F32 x, F32 y);

/*! 
	Three input constructor. W is set to 1.0f.
	\param x is the value for x.
	\param y is the value for y.
	\param z is the value for z.
*/
		Point(F32 x, F32 y, F32 z);

/*! 
	Copy Constructor. It explicitly copies all data into new Point. 
	\param v is the Point to copy. 
*/
		Point(const Point& v);

/*! 
	Destructor. It does not do anything. 
*/		
		~Point(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
//===== 2D checks =====		
/*! 
	Sets the Point to act like a 2D Point instead of a 3D Point by setting _2D to true. This means that the z value wont 
	be copied or used in operations. 
*/		
		inline void Make2D(void)
		{
			_2D = true;
		}

/*! 
	Sets the Point to act like a 3D Point instead of a 3D Point by settings _2D to true. This means that the z value will
	be copied and used in operations.
*/		
		inline void Make3D(void)
		{
			_2D = false;
		}

/*! 
	Returns that 2D state of the Point stored in _2D;
*/		
		inline bool Is2D(void) const
		{
			return _2D;
		}

//===== Point Special functions =====
/*!
	Performs a Dot or Scalar product in the order of this * other.
	\param point is the left hand argument in the operation.	
*/
		F32 Dot(const Point& point) const;

/*!
	Performs a Cross or Point production in the order of this % other.
	\param point is the left hand argument in the operation.			
*/		
		Point CrossProduct(const Point& point) const;

/*!
	Returns the length of the Point. Caution, this uses the square root function.
*/
		F32 Magnitude(void);

/*!
	Returns the squard length of the Point. It avoids the cost of the square root function.
*/
		F32 SqrMagnitude(void);

/*!
	Changes the Point into a unit Point by converting its magnitude to exaclty 1.0. This is an expensive operation.
*/
		void Normalize(void);

/*!
	Sets all values to input. Does not check for _2D before changing z. 
	\param val is the value x, y and z will get. w is set to 1.0f. Default value is 0.0f.
*/
		void Reset(F32 val=0.0f);

//===== Math Helper Functions =====
/*!
	Adds a Point scaled by a value to this Point. 
	\param point is the Point that will be added to this one. 
	\param scale is the amount the added Point will be scaled by.
*/
		void AddScaledPoint(const Point& point, F32 scale);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
/*!
	Returns the raw data for the Point.
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
	Allows you to index into the Point to read the value.
	\param i is the index you wish to read. 0 = x, 1 = y, 2 = z, 3 = w.
*/
		inline const F32& operator[](int i) const
		{
			return _data[i];
		}

/*!
	Allows you to index into the Point to change the value.
	\param i is the index you wish to change. 0 = x, 1 = y, 2 = z, 3 = w.
*/
		inline F32& operator[](int i)
		{
			return _data[i];
		}

//===== Copy Assignment =====		
/*!
	Copy assignment from Point.
	\param point is the Point to copy into this Point.
*/
		Point& operator=(const Point& point);

/*!
	Copy assignment from scalar.
	\param val is the value all elements will be set to. w is not affect. 2D check is done before z is changed.

*/
		Point& operator=(F32 val);

//===== Add by Point =====
/*!
	Point addtion. This is done componentwise.
	\param point is the Point to add into a new Point.
*/
		Point operator+(const Point& point) const;

/*!
	Point addition equal. This is done componentwise.
	\param point is the Point to add into this Point.
*/
		Point& operator+=(const Point& point);

//===== Add by scalar =====
/*!
	Scalar addition. Each value is added into. 2D check done before z is changed.
	\param val is added into the elements of a new Point.
*/
		Point operator+(F32 val) const;

/*!
	Scalar addition. Each value is added into. 2D check done before z is changed.
	\param val is added into each element of this Point.
*/
		Point& operator+=(F32 val);

/*!
	Shared Pointer addition. A helper to allow arithmetic with shared_ptr<Point>.
	\param point is the shared_ptr<Point> that is added into each element of a new Point.
*/
		Point operator+(shared_ptr<Point> point) const;

//===== Subtract by Point =====
/*!
	Point subtraction. This is done componentwise. 2D check done before z is changed. 
	\param point is the Point subtracted from the new Point.
*/
		Point operator-(const Point& point) const;

/*!
	Point subtraction. This is done componenetwise. 2D check done before z is changed. 
	\param point is the Pointed subtractd from this Point.
*/
		Point& operator-=(const Point& point);

//===== Negation and increment =====
/*! 
	Changes the sign of each element of the Point. If 2D, z is not changed. w is also ignored. 
*/
		inline Point operator-(void)
		{
			if(_2D)
			{
				return Point(-_data[x], -_data[y]);
			}

			return Point(-_data[x], -_data[y], -_data[z]);
		}

/*! 
	Prefix, Adds 1 to each element of the Point. If 2D, z is ignored. w is always ignored.  
*/
		inline Point& operator++(void)
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
	Postfix, Adds 1 to each element of the Point. If 2D, z is ignored. w is always ignored.  
*/
		inline Point operator++(int)
		{
			Point temp = *this;
			++*this;
			return temp;
		}

/*! 
	Prefix, Subtracts 1 to each element of the Point. If 2D, z is ignored. w is always ignored.  
*/
		inline Point& operator--(void)
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
	Postfix, Subtracts 1 to each element of the Point. If 2D, z is ignored. w is always ignored.   
*/
		inline Point operator--(int)
		{
			Point temp = *this;
			--*this;
			return temp;
		}

//===== Subtract by scalar =====
/*!
	Scalar subtraction. 2D check is done before z is changed. 
	\param val is the scalar subtracted from the new Point.
*/
		Point operator-(F32 val) const;

/*!
	Sclara subtraction. 2D check is done before z is changed. 
	\param val is the scalar subtracted from each element of this Point.
*/
		Point& operator-=(F32 val);

//===== Component-wise multiply by Point =====
/*!
	Point multiplication. This is a componentwise multiplication, scaling one Point by another. 2D check done before z is changed.
	\param point is the Point multiplied by the new Point.
*/
		Point operator*(const Point point) const;

/*!
	Point multiplication. This is a componentwise multiplication, scaling one Point by another. 2D check done before z is changed.
	\param point is the Point multiplied by this Point.
*/
		Point& operator*=(const Point point);

//===== Mutliply by Scalar =====
/*!
	Scalar multiplication. This is a componentwise multiplication, scaling the Point by the scalar. 2D check done before z is changed.
	\param val is the scalar multiplied by the new Point.
*/
		Point operator*(F32 val) const;

/*!
	Scalar multiplication. This is a componentwise multiplication, scaling the Point by the scalar. 2D check done before z is changed.
	\param val is the scalar multiplied by this Point.
*/
		Point& operator*=(F32 val);

//===== Divide by scalar =====
/*!
	Scalar division. This is done componentwise. 2D check done before z is changed. 
	\param val is the scalar the new Point is divided by.
*/
		Point operator/(F32 val) const;

/*!
	Scalar division. This is done componentwise. 2D check done before z is changed. 
	\param val is the scalar this Point is divided by.
*/
		Point& operator/=(F32 val);

//===== Comparison =====
/*!
	Greater than comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are greater than all elements of the other Point.
	\param point is the Point this Point will be compared against.
*/
		bool operator>(const Point& point) const;

/*!
	Less than comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are less than all elements of the other Point.
	\param point is the Point this Point will be compared against.
*/
		bool operator<(const Point& point) const;

/*!
	Greater than or equal to comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are greater than or equal to all elements of the other Point.
	\param point is the Point this Point will be compared against.
*/
		bool operator>=(const Point& point) const;

/*!
	Less than or equal to comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are less than or equal to all elements of the other Point.
	\param point is the Point this Point will be compared against.
*/
		bool operator<=(const Point& point) const;

/*!
	Equality comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are equal to all elements of other Point. 
	\param point is the Point this Point will be compared against. 
*/
		bool operator==(const Point& point) const;

/*!
	False equality comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are not equal to all elements of other Point. 
	\param point is the Point this Point will be compared against. 
*/
		bool operator!=(const Point& point) const;


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