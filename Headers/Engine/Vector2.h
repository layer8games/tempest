#pragma once

//===== Killer Includes =====
#include <Engine/Atom.h>
#include <Engine/Point2.h>
#include <Engine/Point3.h>
#include <Engine/Point4.h>
#include <Engine/Vector3.h>
#include <Engine/Vector4.h>


//===== Stnadard inlcudes =====
#include <cassert>

namespace TempestMath
{
    class Point2;
    class Point3;
    class Point4;
    class Vector3;
    class Vector4;

//==========================================================================================================================
//Documentation
//==========================================================================================================================
    ///	A custom Vector2 class writen for the Killer Engine.
    ///	The Vector2 is a 3 element 3D Vector. The Vector2 consists of an x, y, and z component represented by an array of real values. 
    ///	They are refered as x, y, and z through documentation. In code, you can refere to them by x, y and z, due to an enum defined
    ///	in  Atom.h.  
    ///	Unlike the Vector4, there is no w, so there is no difference between a position and a direction, like in the Point4 vs Vector4
    ///	classes. This class exists for when something doesn't need that extra data that comes with the w element. This can save on 
    ///	memory and computation. The Matrix3 class uses it, for example.
    class Vector2
    {
    public:
//==========================================================================================================================
//
//Constructors
//
//========================================================================================================================== 
        ///	Default construtor. Sets all values to 0, and _2D to false.	
        TEMPEST_API Vector2(void);

        ///	Single input conversion constructor. It will set the x, y and z components to the input. _2D is false. 
        ///	\param val real: Input value for x, y and z.	
        TEMPEST_API explicit Vector2(real val);

        ///	Three input constructor.
        ///	\param x is the value for x.
        ///	\param y is the value for y.
        TEMPEST_API Vector2(real xVal, real yVal);

        ///	Copy Constructor. It explicitly copies all data into new Vector2. 
        ///	\param v is the Vector2 to copy. 
        //Add explicit key word and fix errors
        TEMPEST_API Vector2(const Vector2& v);

        /// Copy Constructor. It explicitely copies all data into new Vector2 from a Point4
        /// \param p is the Point4 to copy.
        TEMPEST_API explicit Vector2(const Point2& p);
        
        /// Copy Constructor. It explicitely copies all data into new Vector2 from a Point4
        /// \param p is the Point4 to copy.
        TEMPEST_API explicit Vector2(const Point4& p);

        ///	Convert a Vector4 into a Vector2.
        ///	\param v is the Vector4 to convert.
        TEMPEST_API explicit Vector2(const Vector4& v);

        ///	No implementation.	
        TEMPEST_API ~Vector2(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
//===== Vector2 Special functions =====
        ///	Performs a Dot or Scalar product in the order of this * other.
        ///	\param vec is the left hand argument in the operation.	
        TEMPEST_API real Dot(const Vector2& vec) const;

        ///	Returns the length of the Vector2. Caution, this uses the square root function.
        TEMPEST_API real Magnitude(void);

        ///	Returns the squard length of the Vector2. It avoids the cost of the square root function.
        TEMPEST_API real SqrMagnitude(void);

        ///	Changes the Vector2 into a unit Vector2 by converting its magnitude to exaclty 1.0. This is an expensive operation.
        TEMPEST_API void Normalize(void);

        ///	Sets all values to input. Does not check for _2D before changing z. 
        ///	\param val is the value x, y and z will get. Default value is 0.
        TEMPEST_API void Reset(real val=0.0f);

//===== Math Helper Functions =====
        ///	Adds a Vector2 scaled by a value to this Vector2. 
        ///	\param vec is the Vector2 that will be added to this one. 
        ///	\param scale is the amount the added Vector2 will be scaled by.
        TEMPEST_API void AddScaledVector(const Vector2& vec, real scale);

        TEMPEST_API void AddScaledVector(const Vector4& vec, real scale);

        TEMPEST_API void AddScaledVector(const Point4& point, real scale);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
        ///	A helper function to allow to quickly set x, y and z to different values. This is useful because it is only one function
        ///	call instead of the 3 it would take to call [] for each element. 
        ///	\param xVal is the value for x.
        ///	\param yVal is the vlaue for y.
        ///	\param zVal is the value for z. 
        inline void Set(real xVal, real yVal)
        {
            x = xVal;
            y = yVal;
        }

//==========================================================================================================================
//
//operator Overloads
//
//==========================================================================================================================
//===== Copy Assignment =====		
        ///	Copy assignment from Vector2.
        ///	\param vec is the Vector2 to copy into this Vector2.
        TEMPEST_API Vector2& operator=(const Vector2& vec);

        ///	Copy assignment from scalar.
        ///	\param val is the value all elements will be set to. 2D check is done before z is changed.
        TEMPEST_API Vector2& operator=(real val);

        ///	Copy assignment from scalar.
        ///	\param val is the value all elements will be set to. 2D check is done before z is changed.
        TEMPEST_API Vector2& operator=(const Point2& point);

//===== Add by Vector2 =====
        ///	Vector2 addtion. This is done componentwise.
        ///	\param vec is the Vector2 to add into a new Vector2.
        TEMPEST_API Vector2 operator+(const Vector2& vec) const;

        ///	Vector2 addition equal. This is done componentwise.
        ///	\param vec is the Vector2 to add into this Vector2.
        TEMPEST_API Vector2& operator+=(const Vector2& vec);

//===== Add by scalar =====
        ///	Scalar addition. Each value is added into.
        ///	\param val is added into the elements of a new Vector2.
        TEMPEST_API Vector2 operator+(real val) const;

        ///	Scalar addition. Each value is added into.
        ///	\param val is added into each element of this Vector2.
        TEMPEST_API Vector2& operator+=(real val);

        ///	Shared Pointer addition. A helper to allow arithmetic with shared_ptr<Vector2>.
        ///	\param vec is the shared_ptr<Vector2> that is added into each element of a new Vector2.
        TEMPEST_API Vector2 operator+(shared_ptr<Vector2> vec) const;

//===== Subtract by Vector =====
        ///	Vector2 subtraction. This is done componentwise.
        ///	\param vec is the Vector2 subtracted from the new Vector2.
        TEMPEST_API Vector2 operator-(const Point2& vec) const;

        ///	Vector2 subtraction. This is done componentwise.
        ///	\param vec is the Vector2 subtracted from the new Vector2.
        TEMPEST_API Vector2 operator-(const Point3& vec) const;

        ///	Vector2 subtraction. This is done componentwise.
        ///	\param vec is the Vector2 subtracted from the new Vector2.
        TEMPEST_API Vector2 operator-(const Point4& vec) const;

        ///	Vector2 subtraction. This is done componentwise.
        ///	\param vec is the Vector2 subtracted from the new Vector2.
        TEMPEST_API Vector2 operator-(const Vector2& vec) const;

        ///	Vector2 subtraction. This is done componentwise.
        ///	\param vec is the Vector2 subtracted from the new Vector2.
        TEMPEST_API Vector2 operator-(const Vector3& vec) const;

        ///	Vector2 subtraction. This is done componentwise.
        ///	\param vec is the Vector2 subtracted from the new Vector2.
        TEMPEST_API Vector2 operator-(const Vector4& vec) const;

        ///	Vector2 subtraction. This is done componenetwise.
        ///	\param vec is the Vector2ed subtractd from this Vector2.
        TEMPEST_API Vector2& operator-=(const Vector2& vec);

        ///	Vector2 subtraction. This is done componenetwise.
        ///	\param vec is the Vector2ed subtractd from this Vector2.
        TEMPEST_API Vector2& operator-=(const Point2& vec);

        ///	Vector2 subtraction. This is done componenetwise.
        ///	\param vec is the Vector2ed subtractd from this Vector2.
        TEMPEST_API Vector2& operator-=(const Point3& vec);

//===== Negation and increment =====
        ///	Changes the sign of each element of the Vector2.
        inline Vector2 operator-(void)
        {
            return Vector2(-x, -y);
        }

        ///	Prefix, Adds 1 to each element of the Vector2.
        inline Vector2& operator++(void)
        {
            ++x;
            ++y;

            return *this;
        }

        ///	Postfix, Adds 1 to each element of the Vector2.
        inline Vector2 operator++(int)
        {
            return Vector2(++x, ++y);
        }

        ///	Prefix, Subtracts 1 to each element of the Vector2.
        inline Vector2& operator--(void)
        {
            --x;
            --y;

            return *this;
        }

        ///	Postfix, Subtracts 1 to each element of the Vector2.
        inline Vector2 operator--(int)
        {
            return Vector2(--x, --y);
        }

//===== Subtract by scalar =====
        ///	Scalar subtraction. 2D check is done before z is changed. 
        ///	\param val is the scalar subtracted from the new Vector2.
        TEMPEST_API Vector2 operator-(real val) const;

        ///	Sclara subtraction. 2D check is done before z is changed. 
        ///	\param val is the scalar subtracted from each element of this Vector2.
        TEMPEST_API Vector2& operator-=(real val);

//===== Component-wise multiply by Vector2 =====
        ///	Vector2 multiplication. This is a componentwise multiplication, scaling one Vector2 by another.
        ///	\param vec is the Vector2 multiplied by the new Vector2.
        TEMPEST_API Vector2 operator*(const Vector2& vec) const;

        ///	Vector2 multiplication. This is a componentwise multiplication, scaling one Vector2 by another.
        ///	\param vec is the Vector2 multiplied by this Vector2.
        TEMPEST_API Vector2& operator*=(const Vector2& vec);

//===== Mutliply by Scalar =====
        ///	Scalar multiplication. This is a componentwise multiplication, scaling the Vector2 by the scalar.
        ///	\param val is the scalar multiplied by the new Vector2.
        TEMPEST_API Vector2 operator*(real val) const;

        ///	Scalar multiplication. This is a componentwise multiplication, scaling the Vector2 by the scalar.
        ///	\param val is the scalar multiplied by this Vector2.
        TEMPEST_API Vector2& operator*=(real val);

//===== Divide by scalar =====
        ///	Scalar division. This is done componentwise. 2D check done before z is changed. 
        ///	\param val is the scalar the new Vector2 is divided by.
        TEMPEST_API Vector2 operator/(real val) const;

        ///	Scalar division. This is done componentwise. 2D check done before z is changed. 
        ///	\param val is the scalar this Vector2 is divided by.
        TEMPEST_API Vector2& operator/=(real val);

//===== Comparison =====
        ///	Greater than comparison. 2D is used as an early out. Only true if all elements of this are 
        ///	greater than all elements of the other Vector2.
        ///	\param vec is the Vector2 this Vector2 will be compared against.
        TEMPEST_API bool operator>(const Vector2& vec) const;

        ///	Less than comparison. 2D is used as an early out. Only true if all elements of this are 
        ///	less than all elements of the other Vector2.
        ///	\param vec is the Vector2 this Vector2 will be compared against.
        TEMPEST_API bool operator<(const Vector2& vec) const;

        ///	Greater than or equal to comparison. 2D is used as an early out. Only true if all elements 
        ///	of this are greater than or equal to all elements of the other Vector2.
        ///	\param vec is the Vector2 this Vector2 will be compared against.
        TEMPEST_API bool operator>=(const Vector2& vec) const;

        ///	Less than or equal to comparison. 2D is used as an early out. Only true if all elements of 
        ///	this are less than or equal to all elements of the other Vector2.
        ///	\param vec is the Vector2 this Vector2 will be compared against.
        TEMPEST_API bool operator<=(const Vector2& vec) const;

        ///	Equality comparison. 2D is used as an early out. Only true if all elements of this are equal 
        ///	to all elements of other Vector2. 
        ///	\param vec is the Vector2 this Vector2 will be compared against. 
        TEMPEST_API bool operator==(const Vector2& vec) const;

        ///	False equality comparison. 2D is used as an early out. Only true if all elements of this are 
        ///	not equal to all elements of other Vector2. 
        ///	\param vec is the Vector2 this Vector2 will be compared against. 
        TEMPEST_API bool operator!=(const Vector2& vec) const;


//==========================================================================================================================
//
//Data
//
//==========================================================================================================================
        real x;
        real y;
    };// end class
    typedef shared_ptr<Vector2> p_Vector2;
}//end namespace