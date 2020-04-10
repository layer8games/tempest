#pragma once

//===== Killer Includes =====
#include <Engine/Atom.h>
#include <Engine/Point2.h>
#include <Engine/Point3.h>
#include <Engine/Point4.h>
#include <Engine/Vector2.h>
#include <Engine/Vector4.h>


//===== Stnadard inlcudes =====
#include <cassert>

namespace TempestMath
{
    class Point2;
    class Point3;
    class Point4;
    class Vector2;
    class Vector4;
    
//==========================================================================================================================
//Documentation
//==========================================================================================================================
    ///	A custom Vector3 class writen for the Killer Engine.
    ///	The Vector3 is a 3 element 3D Vector. The Vector3 consists of an x, y, and z component represented by an array of real values. 
    ///	They are refered as x, y, and z through documentation. In code, you can refere to them by x, y and z, due to an enum defined
    ///	in  Atom.h.  
    ///	Unlike the Vector4, there is no w, so there is no difference between a position and a direction, like in the Point4 vs Vector4
    ///	classes. This class exists for when something doesn't need that extra data that comes with the w element. This can save on 
    ///	memory and computation. The Matrix3 class uses it, for example.
    class Vector3
    {
    public:
//==========================================================================================================================
//
//Constructors
//
//========================================================================================================================== 
        ///	Default construtor. Sets all values to 0, and _2D to false.	
        TEMPEST_API Vector3(void);

        ///	Single input conversion constructor. It will set the x, y and z components to the input. _2D is false. 
        ///	\param val real: Input value for x, y and z.	
        TEMPEST_API explicit Vector3(real val);

        ///	Three input constructor.
        ///	\param x is the value for x.
        ///	\param y is the value for y.
        ///	\param z is the value for z.
        TEMPEST_API Vector3(real xVal, real yVal, real zVal);

        /// Copy Constructor. It explicitely copies all data into new Vector3 from a Point4
        /// \param p is the Point4 to copy.
        TEMPEST_API explicit Vector3(const Point3& p);
        
        /// Copy Constructor. It explicitely copies all data into new Vector3 from a Point4
        /// \param p is the Point4 to copy.
        TEMPEST_API Vector3(const Point4& p);
 
        ///	Copy Constructor. It explicitly copies all data into new Vector3. 
        ///	\param v is the Vector3 to copy. 
        TEMPEST_API Vector3(const Vector3& v);

        ///	Convert a Vector4 into a Vector3.
        ///	\param v is the Vector4 to convert.
        TEMPEST_API Vector3(const Vector4& v);

        ///	No implementation.	
        TEMPEST_API ~Vector3(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
//===== Vector3 Special functions =====
        ///	Performs a Dot or Scalar product in the order of this * other.
        ///	\param vec is the left hand argument in the operation.	
        TEMPEST_API real Dot(const Vector3& vec) const;

        ///	Performs a Dot or Scalar product in the order of this * other.
        ///	\param vec is the left hand argument in the operation.	
        TEMPEST_API real Dot(const Point3& point) const;

        ///	Performs a Cross or Vector3 production in the order of this cross other.
        ///	\param vec is the left hand argument in the operation.				
        TEMPEST_API Vector3 CrossProduct(const Vector3& vec) const;

        ///	Returns the length of the Vector3. Caution, this uses the square root function.
        TEMPEST_API real Magnitude(void);

        ///	Returns the squard length of the Vector3. It avoids the cost of the square root function.
        TEMPEST_API real SqrMagnitude(void);

        ///	Changes the Vector3 into a unit Vector3 by converting its magnitude to exaclty 1.0. This is an expensive operation.
        TEMPEST_API void Normalize(void);

        ///	Sets all values to input. Does not check for _2D before changing z. 
        ///	\param val is the value x, y and z will get. Default value is 0.
        TEMPEST_API void Reset(real val=0.0f);

//===== Math Helper Functions =====
        ///	Adds a Vector3 scaled by a value to this Vector3. 
        ///	\param vec is the Vector3 that will be added to this one. 
        ///	\param scale is the amount the added Vector3 will be scaled by.
        TEMPEST_API void AddScaledVector(const Vector3& vec, real scale);

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
        inline void Set(real xVal, real yVal, real zVal)
        {
            x = xVal;
            y = yVal;
            z = zVal;
        }

//==========================================================================================================================
//
//operator Overloads
//
//==========================================================================================================================
//===== Copy Assignment =====		
        ///	Copy assignment from Vector3.
        ///	\param vec is copied to this Vector
        TEMPEST_API Vector3& operator=(const Vector2& vec);

        ///	Copy assignment from Vector3.
        ///	\param vec is copied to this Vector
        TEMPEST_API Vector3& operator=(const Vector3& vec);

        ///	Copy assignment from Vector3.
        ///	\param vec is copied to this Vector
        TEMPEST_API Vector3& operator=(const Vector4& vec);

        ///	Copy assignment from Vector3.
        ///	\param point is copied to this Vector
        TEMPEST_API Vector3& operator=(const Point2& point);

        ///	Copy assignment from Vector3.
        ///	\param point is copied to this Vector
        TEMPEST_API Vector3& operator=(const Point3& point);

        ///	Copy assignment from Vector3.
        ///	\param point is copied to this Vector
        TEMPEST_API Vector3& operator=(const Point4& point);

        ///	Copy assignment from scalar.
        ///	\param val is the value all elements will be set to. 2D check is done before z is changed.
        TEMPEST_API Vector3& operator=(real val);

//===== Add by Vector3 =====
        ///	Vector3 addtion. This is done componentwise.
        ///	\param vec is the Vector3 to add into a new Vector3.
        TEMPEST_API Vector3 operator+(const Vector3& vec) const;

        ///	Vector3 addition equal. This is done componentwise.
        ///	\param vec is the Vector3 to add into this Vector3.
        TEMPEST_API Vector3& operator+=(const Vector3& vec);

//===== Add by scalar =====
        ///	Scalar addition. Each value is added into. 2D check done before z is changed.
        ///	\param val is added into the elements of a new Vector3.
        TEMPEST_API Vector3 operator+(real val) const;

        ///	Scalar addition. Each value is added into. 2D check done before z is changed.
        ///	\param val is added into each element of this Vector3.
        TEMPEST_API Vector3& operator+=(real val);

        ///	Shared Pointer addition. A helper to allow arithmetic with shared_ptr<Vector3>.
        ///	\param vec is the shared_ptr<Vector3> that is added into each element of a new Vector3.
        TEMPEST_API Vector3 operator+(shared_ptr<Vector3> vec) const;

//===== Subtract by Vector =====
        ///	Vector3 subtraction. This is done componentwise. 2D check done before z is changed. 
        ///	\param vec is the Vector3 subtracted from the new Vector3.
        TEMPEST_API Vector3 operator-(const Vector3& vec) const;

        ///	Vector3 subtraction. This is done componenetwise. 2D check done before z is changed. 
        ///	\param vec is the Vector3ed subtractd from this Vector3.
        TEMPEST_API Vector3& operator-=(const Vector3& vec);

        ///	Vector3 subtraction. This is done componenetwise. 2D check done before z is changed. 
        ///	\param vec is the Vector3ed subtractd from this Vector3.
        TEMPEST_API Vector3& operator-=(const Vector4& vec);

        ///	Vector3 subtraction. This is done componenetwise. 2D check done before z is changed. 
        ///	\param vec is the Vector3ed subtractd from this Vector3.
        TEMPEST_API Vector3& operator-=(const Point2& point);

        ///	Vector3 subtraction. This is done componenetwise. 2D check done before z is changed. 
        ///	\param vec is the Vector3ed subtractd from this Vector3.
        TEMPEST_API Vector3& operator-=(const Point3& point);

        ///	Vector3 subtraction. This is done componenetwise. 2D check done before z is changed. 
        ///	\param vec is the Vector3ed subtractd from this Vector3.
        TEMPEST_API Vector3& operator-=(const Point4& point);

//===== Negation and increment =====
        ///	Changes the sign of each element of the Vector3. If 2D, z is not changed.
        inline Vector3 operator-(void)
        {
            return Vector3(-x, -y, -z);
        }
 
        ///	Prefix, Adds 1 to each element of the Vector3. If 2D, z is ignored. 
        inline Vector3& operator++(void)
        {
            ++x;
            ++y;
            ++z;
            
            return *this;
        }

        ///	Postfix, Adds 1 to each element of the Vector3. If 2D, z is ignored. 
        inline Vector3 operator++(int)
        {
            return Vector3(++x, ++y, ++z);
        }
 
        ///	Prefix, Subtracts 1 to each element of the Vector3. If 2D, z is ignored. 
        inline Vector3& operator--(void)
        {
            --x;
            --y;
            --z;

            return *this;
        }
    
        ///	Postfix, Subtracts 1 to each element of the Vector3. If 2D, z is ignored.  
        inline Vector3 operator--(int)
        {
            return Vector3(--x, --y, --z);
        }

//===== Subtract by scalar =====
        ///	Scalar subtraction. 2D check is done before z is changed. 
        ///	\param val is the scalar subtracted from the new Vector3.
        TEMPEST_API Vector3 operator-(real val) const;

        ///	Sclara subtraction. 2D check is done before z is changed. 
        ///	\param val is the scalar subtracted from each element of this Vector3.
        TEMPEST_API Vector3& operator-=(real val);

//===== Component-wise multiply by Vector3 =====
        ///	Vector3 multiplication. This is a componentwise multiplication, scaling one Vector3 by another. 2D check done before z is changed.
        ///	\param vec is the Vector3 multiplied by the new Vector3.
        TEMPEST_API Vector3 operator*(const Vector3 vec) const;

        ///	Vector3 multiplication. This is a componentwise multiplication, scaling one Vector3 by another. 2D check done before z is changed.
        ///	\param vec is the Vector3 multiplied by this Vector3.
        TEMPEST_API Vector3& operator*=(const Vector3 vec);

//===== Mutliply by Scalar =====
        ///	Scalar multiplication. This is a componentwise multiplication, scaling the Vector3 by the scalar. 2D check done before z is changed.
        ///	\param val is the scalar multiplied by the new Vector3.
        TEMPEST_API Vector3 operator*(real val) const;

        ///	Scalar multiplication. This is a componentwise multiplication, scaling the Vector3 by the scalar. 2D check done before z is changed.
        ///	\param val is the scalar multiplied by this Vector3.
        TEMPEST_API Vector3& operator*=(real val);

//===== Divide by scalar =====
        ///	Scalar division. This is done componentwise. 2D check done before z is changed. 
        ///	\param val is the scalar the new Vector3 is divided by.
        TEMPEST_API Vector3 operator/(real val) const;

        ///	Scalar division. This is done componentwise. 2D check done before z is changed. 
        ///	\param val is the scalar this Vector3 is divided by.
        TEMPEST_API Vector3& operator/=(real val);

//===== Comparison =====
        ///	Greater than comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are 
        ///	greater than all elements of the other Vector3.
        ///	\param vec is the Vector3 this Vector3 will be compared against.
        TEMPEST_API bool operator>(const Vector3& vec) const;

        ///	Less than comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are 
        ///	less than all elements of the other Vector3.
        ///	\param vec is the Vector3 this Vector3 will be compared against.
        TEMPEST_API bool operator<(const Vector3& vec) const;

        ///	Greater than or equal to comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements 
        ///	of this are greater than or equal to all elements of the other Vector3.
        ///	\param vec is the Vector3 this Vector3 will be compared against.
        TEMPEST_API bool operator>=(const Vector3& vec) const;

        ///	Less than or equal to comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of 
        ///	this are less than or equal to all elements of the other Vector3.
        ///	\param vec is the Vector3 this Vector3 will be compared against.
        TEMPEST_API bool operator<=(const Vector3& vec) const;

        ///	Equality comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are equal 
        ///	to all elements of other Vector3. 
        ///	\param vec is the Vector3 this Vector3 will be compared against. 
        TEMPEST_API bool operator==(const Vector3& vec) const;

        ///	False equality comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are 
        ///	not equal to all elements of other Vector3. 
        ///	\param vec is the Vector3 this Vector3 will be compared against. 
        TEMPEST_API bool operator!=(const Vector3& vec) const;

//==========================================================================================================================
//
//Data
//
//==========================================================================================================================
        real x;
        real y;
        real z;
    };// end class
    typedef shared_ptr<Vector3> p_Vector3;
}//end namespace