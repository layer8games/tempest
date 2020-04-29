#pragma once

//===== Killer Includes =====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/Vector2.h>
#include <Engine/Vector3.h>
#include <Engine/Vector4.h>

namespace TE = Tempest;


//===== Stnadard inlcudes =====
#include <cassert>

namespace TempestMath
{
    class Vector2;
    class Vector3;
    class Vector4;

//==========================================================================================================================
//Documentation
//========================================================================================================================== 
        ///	A custom Point2 class writen for the Killer Engine.
        ///	The Point2 is a 4 element 3D Point2. The Point2 consists of an x, y, z and w component represented by an array of real values. 
        ///	They are refered as x, y, z and w through through documentation. In code, you would have to refered to them as their index 
        ///	in the array (0 - 3). There is an alias set up in the Point2, and enum, that lets you use x, y, z and w to represent the 
        ///	indices natively. This is private to the Point2. 
        ///	The w element is what separates a Vector4 from a Point2. A Point2 is meant to represent a Point2 in space. This can also be 
        ///	thought of as a displayment from the origin of the planes. This is expressed mathematically by always having the w 
        ///	component be 1, which allows the Point2 to be transformed by a Matrix with transformation values added. 
    class Point2
    {
    public:
//==========================================================================================================================
//
//Constructors
//
//========================================================================================================================== 
        ///	Default construtor. Sets all values to 0, and _2D to false.		
        TEMPEST_API Point2(void);

        ///	Single input conversion constructor. It will set the x, y and z components to the input. _2D is false. W is set to 0.
        ///	\param val real: Input value for x, y and z.	
        TEMPEST_API explicit Point2(real val);

        ///	Four input constructor. W variable in this constructor.
        ///	\param xVal is the value for x.
        ///	\param yVal is the value for y.
        TEMPEST_API Point2(real xVal, real yVal);
 
        ///	Copy Constructor. It explicitly copies all data into new Point2. 
        ///	\param v is the Point2 to copy. 
        TEMPEST_API Point2(const Point2& p);

                /// Convert a Vector3 into a Point2
        TEMPEST_API explicit Point2(const Vector3& v);

                /// Convert a Vector4 into a Point2
        TEMPEST_API explicit Point2(const Vector4& v);

        ///	Destructor. It does not do anything. 	
        TEMPEST_API ~Point2(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
//===== Point2 Special functions =====
        ///	Performs a Dot or Scalar product in the order of this * other.
        ///	\param Point2 is the left hand argument in the operation.	
        TEMPEST_API real Dot(const Point2& point) const;

        ///	Returns the length of the Point2. Caution, this uses the square root function.
        TEMPEST_API real Magnitude(void);

        ///	Returns the squard length of the Point2. It avoids the cost of the square root function.
        TEMPEST_API real SqrMagnitude(void);

        ///	Changes the Point2 into a unit Point2 by converting its magnitude to exaclty 1.0. This is an expensive operation.
        TEMPEST_API void Normalize(void);

        ///	Sets all values to input. Does not check for _2D before changing z. 
        ///	\param val is the value x, y and z will get. w is set to 1.0f. Default value is 0.0f.
        TEMPEST_API void Reset(real val=0.0f);

        /// Gives the distance from this to another Point2. Creates a Point2 and calls Mag.
        /// \param other is the Point2 we are getting the distance to. 
        TEMPEST_API real Distance(const Point2& p) const;

                /// Return the distance between two Point2s, without calling sqrt.
        TEMPEST_API real DistanceSquared(const Point2& p) const;

                /// Return the distance between this Point2 and a Vector3, without calling sqrt.
        TEMPEST_API real DistanceSquared(const Vector3& v) const;

                /// Return the distance between this Point2 and a Vector34, without calling sqrt.
        TEMPEST_API real DistanceSquared(const Vector4& v) const;


//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
        ///	A helper function to allow to quickly set x, y and z to different values.
        ///	\param xVal is the value for x.
        ///	\param yVal is the vlaue for y.
        ///	\param zVal is the value for z. 
        inline void Set(real xVal, real yVal, real zVal)
        {
            x = xVal;
            y = yVal;
        }

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
        ///	Copy assignment from Point2.
        ///	\param Point2 is the Point2 to copy into this Point2.
        TEMPEST_API Point2& operator=(const Point2& point);

        ///	Copy assignment from scalar.
        ///	\param val is the value all elements will be set to. w is not affect. 2D check is done before z is changed.
        TEMPEST_API Point2& operator=(real val);

//===== Add by Point2 =====
        ///	Point2 addtion. This is done componentwise.
        ///	\param Point2 is the Point2 to add into a new Point2.
        TEMPEST_API Point2 operator+(const Point2& point) const;

        ///	Point2 addtion. This is done componentwise.
        ///	\param vec is added into a new Point2.
        TEMPEST_API Point2 operator+(const Vector4& vec) const;

        /// Point2 addtion. This is done componentwise.
        /// \param ved is added into a new Point2.
        TEMPEST_API Point2 operator+(const Vector3& vec) const;

        ///	Point2 addition equal. This is done componentwise.
        ///	\param Point2 is the Point2 to add into this Point2.
        TEMPEST_API Point2& operator+=(const Point2& point);

        ///	Point2 addition equal. This is done componentwise.
        ///	\param vec is the Vector4 to add into this Point2.
        TEMPEST_API Point2& operator+=(const Vector4& vec);

        /// Point2 addition equal. This is done componentwise.
        /// \param vec is the Vector4 to add into this Point2.
        TEMPEST_API Point2& operator+=(const Vector3& vec);

         /// Point2 addition equal. This is done componentwise.
        /// \param vec is the Vector4 to add into this Point2.
        TEMPEST_API Point2& operator+=(const Vector2& vec);

//===== Add by scalar =====
        ///	Scalar addition. Each value is added into. 2D check done before z is changed.
        ///	\param val is added into the elements of a new Point2.
        TEMPEST_API Point2 operator+(real val) const;

        ///	Scalar addition. Each value is added into. 2D check done before z is changed.
        ///	\param val is added into each element of this Point2.
        TEMPEST_API Point2& operator+=(real val);

        ///	Shared Point2er addition. A helper to allow arithmetic with p_Point2.
        ///	\param Point2 is the p_Point2 that is added into each element of a new Point2.
        TEMPEST_API Point2 operator+(shared_ptr<Point2> Point2) const;

//===== Subtract by Point2 =====
        ///	Point2 subtraction. This is done componentwise. 2D check done before z is changed. 
        ///	\param Point2 is the Point2 subtracted from the new Point2.
        TEMPEST_API Point2 operator-(const Point2& point) const;

        ///	Point2 subtraction. This is done componentwise. 2D check done before z is changed. 
        ///	\param Point2 is the Point2 subtracted from the new Point2.
        TEMPEST_API Point2 operator-(const Point3& point) const;

        ///	Point2 subtraction. This is done componentwise. 2D check done before z is changed. 
        ///	\param Point2 is the Point2 subtracted from the new Point2.
        TEMPEST_API Point2 operator-(const Point4& point) const;

        /// Subtract a Vector3 from this Point2, return result.
        TEMPEST_API Point2 operator-(const Vector2& vec) const;
        
        /// Subtract a Vector3 from this Point2, return result.
        TEMPEST_API Point2 operator-(const Vector3& vec) const;

        /// Subtract a Vector4 from this Point2, return result.
        TEMPEST_API Point2 operator-(const Vector4& vec) const;

        ///	Point2 subtraction. This is done componenetwise. 2D check done before z is changed. 
        ///	\param Point2 is the Point2ed subtractd from this Point2.
        TEMPEST_API Point2& operator-=(const Point2& point);

//===== Negation and increment ===== 
        ///	Changes the sign of each element of the Point2. If 2D, z is not changed. w is also ignored. 
        inline Point2 operator-(void)
        {
            return Point2(-x, -y);
        }

        ///	Prefix, Adds 1 to each element of the Point2. If 2D, z is ignored. w is always ignored.  
        inline Point2& operator++(void)
        {
            ++x;
            ++y;

            return *this;
        }

        ///	Postfix, Adds 1 to each element of the Point2. If 2D, z is ignored. w is always ignored.  
        inline Point2 operator++(int)
        {
            Point2 temp = *this;
            ++*this;
            return temp;
        }
 
        ///	Prefix, Subtracts 1 to each element of the Point2. If 2D, z is ignored. w is always ignored.  
        inline Point2& operator--(void)
        {
            --x;
            --y;

            return *this;
        }

        ///	Postfix, Subtracts 1 to each element of the Point2. If 2D, z is ignored. w is always ignored.   
        inline Point2 operator--(int)
        {
            Point2 temp = *this;
            --*this;
            return temp;
        }

//===== Subtract by scalar =====
        ///	Scalar subtraction. 2D check is done before z is changed. 
        ///	\param val is the scalar subtracted from the new Point2.
        TEMPEST_API Point2 operator-(real val) const;

        ///	Sclara subtraction. 2D check is done before z is changed. 
        ///	\param val is the scalar subtracted from each element of this Point2.
        TEMPEST_API Point2& operator-=(real val);

//===== Component-wise multiply by Point2 =====
        ///	Point2 multiplication. This is a componentwise multiplication, scaling one Point2 by another. 2D check done before z is changed.
        ///	\param Point2 is the Point2 multiplied by the new Point2.
        TEMPEST_API Point2 operator*(const Point2 Point2) const;

        ///	Point2 multiplication. This is a componentwise multiplication, scaling one Point2 by another. 2D check done before z is changed.
        ///	\param Point2 is the Point2 multiplied by this Point2.
        TEMPEST_API Point2& operator*=(const Point2 Point2);

//===== Mutliply by Scalar =====
        ///	Scalar multiplication. This is a componentwise multiplication, scaling the Point2 by the scalar. 2D check done before z is changed.
        ///	\param val is the scalar multiplied by the new Point2.
        TEMPEST_API Point2 operator*(real val) const;

        ///	Scalar multiplication. This is a componentwise multiplication, scaling the Point2 by the scalar. 2D check done before z is changed.
        ///	\param val is the scalar multiplied by this Point2.
        TEMPEST_API Point2& operator*=(real val);

//===== Divide by scalar =====
        ///	Scalar division. This is done componentwise. 2D check done before z is changed. 
        ///	\param val is the scalar the new Point2 is divided by.
        TEMPEST_API Point2 operator/(real val) const;

        ///	Scalar division. This is done componentwise. 2D check done before z is changed. 
        ///	\param val is the scalar this Point2 is divided by.
        TEMPEST_API Point2& operator/=(real val);

//===== Comparison =====
        ///	Greater than comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are greater than all elements of the other Point2.
        ///	\param Point2 is the Point2 this Point2 will be compared against.
        TEMPEST_API bool operator>(const Point2& point) const;

        ///	Less than comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are less than all elements of the other Point2.
        ///	\param Point2 is the Point2 this Point2 will be compared against.
        TEMPEST_API bool operator<(const Point2& point) const;

        ///	Greater than or equal to comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are greater than or equal to all elements of the other Point2.
        ///	\param Point2 is the Point2 this Point2 will be compared against.
        TEMPEST_API bool operator>=(const Point2& point) const;

        ///	Less than or equal to comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are less than or equal to all elements of the other Point2.
        ///	\param Point2 is the Point2 this Point2 will be compared against.
        TEMPEST_API bool operator<=(const Point2& point) const;

        ///	Equality comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are equal to all elements of other Point2. 
        ///	\param Point2 is the Point2 this Point2 will be compared against. 
        TEMPEST_API bool operator==(const Point2& point) const;

        ///	False equality comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are not equal to all elements of other Point2. 
        ///	\param Point2 is the Point2 this Point2 will be compared against. 
        TEMPEST_API bool operator!=(const Point2& point) const;

//==========================================================================================================================
//
// Data
//
//==========================================================================================================================
        real x;
        real y; 

    };// end class
    typedef shared_ptr<Point2> p_Point2;
}// end namespace