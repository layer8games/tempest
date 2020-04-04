#pragma once

//===== Killer Includes =====
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/Vector4.h>
#include <Engine/Vector3.h>

namespace TE = Tempest;


//===== Stnadard inlcudes =====
#include <cassert>

namespace TempestMath
{
    class Vector4;
    class Vector3;

//==========================================================================================================================
//Documentation
//========================================================================================================================== 
///	A custom Point4 class writen for the Killer Engine.
///	The Point4 is a 4 element 3D Point4. The Point4 consists of an x, y, z and w component represented by an array of real values. 
///	They are refered as x, y, z and w through through documentation. In code, you would have to refered to them as their index 
///	in the array (0 - 3). There is an alias set up in the Point4, and enum, that lets you use x, y, z and w to represent the 
///	indices natively. This is private to the Point4. 
///	The w element is what separates a Vector4 from a Point4. A Point4 is meant to represent a Point4 in space. This can also be 
///	thought of as a displayment from the origin of the planes. This is expressed mathematically by always having the w 
///	component be 1, which allows the Point4 to be transformed by a Matrix with transformation values added. 
    class Point4
    {
    public:
//==========================================================================================================================
//
//Constructors
//
//========================================================================================================================== 
///	Default construtor. Sets all values to 0, and _2D to false.		
        TEMPEST_API Point4(void);

///	Single input conversion constructor. It will set the x, y and z components to the input. _2D is false. W is set to 0.
///	\param val real: Input value for x, y and z.	
        TEMPEST_API explicit Point4(real val);

///	Four input constructor. W variable in this constructor.
///	\param x is the value for x.
///	\param y is the value for y.
///	\param z is the value for z.
///	\param w is the value for w.
        TEMPEST_API Point4(real x, real y, real z, real w);
 
///	Copy Constructor. It explicitly copies all data into new Point4. 
///	\param v is the Point4 to copy. 
        TEMPEST_API Point4(const Point4& p);

        /// Convert a Vector3 into a Point4
        TEMPEST_API Point4(const Vector3& v);

        /// Convert a Vector4 into a Point4
        TEMPEST_API Point4(const Vector4& v);

///	Destructor. It does not do anything. 	
        TEMPEST_API ~Point4(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
//===== Point4 Special functions =====
///	Performs a Dot or Scalar product in the order of this * other.
///	\param Point4 is the left hand argument in the operation.	
        TEMPEST_API real Dot(const Point4& point) const;

///	Performs a Cross or Point4 production in the order of this % other.
///	\param Point4 is the left hand argument in the operation.				
        TEMPEST_API Point4 CrossProduct(const Point4& point) const;

///	Returns the length of the Point4. Caution, this uses the square root function.
        TEMPEST_API real Magnitude(void);

///	Returns the squard length of the Point4. It avoids the cost of the square root function.
        TEMPEST_API real SqrMagnitude(void);

///	Changes the Point4 into a unit Point4 by converting its magnitude to exaclty 1.0. This is an expensive operation.
        TEMPEST_API void Normalize(void);

///	Sets all values to input. Does not check for _2D before changing z. 
///	\param val is the value x, y and z will get. w is set to 1.0f. Default value is 0.0f.
        TEMPEST_API void Reset(real val=0.0f);

/// Gives the distance from this to another Point4. Creates a Point4 and calls Mag.
/// \param other is the Point4 we are getting the distance to. 
        TEMPEST_API real Distance(const Point4& p) const;

        /// Return the distance between two Point4s, without calling sqrt.
        TEMPEST_API real DistanceSquared(const Point4& p) const;

        /// Return the distance between this Point4 and a Vector3, without calling sqrt.
        TEMPEST_API real DistanceSquared(const Vector3& v) const;

        /// Return the distance between this Point4 and a Vector34, without calling sqrt.
        TEMPEST_API real DistanceSquared(const Vector4& v) const;

//===== Math Helper Functions =====
///	Adds a Point4 scaled by a value to this Point4. 
///	\param Point4 is the Point4 that will be added to this one. 
///	\param scale is the amount the added Point4 will be scaled by.
        TEMPEST_API void AddScaledPoint(const Point4& point, real scale);

        TEMPEST_API void AddScaledVector(const Vector3& vec, real scale);

        TEMPEST_API void AddScaledVector(const Vector4& vec, real scale);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
///	Returns the raw data for the Point4.
        inline const real* GetElems(void) const
        {
            return _data;
        }

///	A helper function to allow to quickly set x, y and z to different values.
///	\param xVal is the value for x.
///	\param yVal is the vlaue for y.
///	\param zVal is the value for z. 
        inline void Set(real xVal, real yVal, real zVal)
        {
            _data[x] = xVal;
            _data[y] = yVal;
            _data[z] = zVal;
        }

        inline void Set(real xVal, real yVal)
        {
            _data[x] = xVal;
            _data[y] = yVal;
        }

//==========================================================================================================================
//
//operator Overloads
//
//==========================================================================================================================
///	Allows you to index into the Point4 to read the value.
///	\param i is the index you wish to read. 0 = x, 1 = y, 2 = z, 3 = w.
        inline const real& operator[](int i) const
        {
            return _data[i];
        }

///	Allows you to index into the Point4 to change the value.
///	\param i is the index you wish to change. 0 = x, 1 = y, 2 = z, 3 = w.
        inline real& operator[](int i)
        {
            return _data[i];
        }

//===== Copy Assignment =====		
///	Copy assignment from Point4.
///	\param Point4 is the Point4 to copy into this Point4.
        TEMPEST_API Point4& operator=(const Point4& point);

///	Copy assignment from scalar.
///	\param val is the value all elements will be set to. w is not affect. 2D check is done before z is changed.
        TEMPEST_API Point4& operator=(real val);

//===== Add by Point4 =====
///	Point4 addtion. This is done componentwise.
///	\param Point4 is the Point4 to add into a new Point4.
        TEMPEST_API Point4 operator+(const Point4& point) const;

///	Point4 addtion. This is done componentwise.
///	\param vec is added into a new Point4.
        TEMPEST_API Point4 operator+(const Vector4& vec) const;

/// Point4 addtion. This is done componentwise.
/// \param ved is added into a new Point4.
        TEMPEST_API Point4 operator+(const Vector3& vec) const;

///	Point4 addition equal. This is done componentwise.
///	\param Point4 is the Point4 to add into this Point4.
        TEMPEST_API Point4& operator+=(const Point4& point);

///	Point4 addition equal. This is done componentwise.
///	\param vec is the Vector4 to add into this Point4.
        TEMPEST_API Point4& operator+=(const Vector4& vec);

/// Point4 addition equal. This is done componentwise.
/// \param vec is the Vector4 to add into this Point4.
        TEMPEST_API Point4& operator+=(const Vector3& vec);

//===== Add by scalar =====
///	Scalar addition. Each value is added into. 2D check done before z is changed.
///	\param val is added into the elements of a new Point4.
        TEMPEST_API Point4 operator+(real val) const;

///	Scalar addition. Each value is added into. 2D check done before z is changed.
///	\param val is added into each element of this Point4.
        TEMPEST_API Point4& operator+=(real val);

///	Shared Point4er addition. A helper to allow arithmetic with p_Point4.
///	\param Point4 is the p_Point4 that is added into each element of a new Point4.
        TEMPEST_API Point4 operator+(shared_ptr<Point4> Point4) const;

//===== Subtract by Point4 =====
///	Point4 subtraction. This is done componentwise. 2D check done before z is changed. 
///	\param Point4 is the Point4 subtracted from the new Point4.
        TEMPEST_API Point4 operator-(const Point4& point) const;

        /// Subtract a Vector3 from this Point4, return result.
        TEMPEST_API Point4 operator-(const Vector3& vec) const;

        /// Subtract a Vector4 from this Point4, return result.
        TEMPEST_API Point4 operator-(const Vector4& vec) const;

///	Point4 subtraction. This is done componenetwise. 2D check done before z is changed. 
///	\param Point4 is the Point4ed subtractd from this Point4.
        TEMPEST_API Point4& operator-=(const Point4& point);

//===== Negation and increment ===== 
///	Changes the sign of each element of the Point4. If 2D, z is not changed. w is also ignored. 
        inline Point4 operator-(void)
        {
            return Point4(-_data[x], -_data[y], -_data[z], 1.0f);
        }

///	Prefix, Adds 1 to each element of the Point4. If 2D, z is ignored. w is always ignored.  
        inline Point4& operator++(void)
        {
            ++_data[x];
            ++_data[y];
            ++_data[z];

            return *this;
        }

///	Postfix, Adds 1 to each element of the Point4. If 2D, z is ignored. w is always ignored.  
        inline Point4 operator++(int)
        {
            Point4 temp = *this;
            ++*this;
            return temp;
        }
 
///	Prefix, Subtracts 1 to each element of the Point4. If 2D, z is ignored. w is always ignored.  
        inline Point4& operator--(void)
        {
            --_data[x];
            --_data[y];
            --_data[z];

            return *this;
        }

///	Postfix, Subtracts 1 to each element of the Point4. If 2D, z is ignored. w is always ignored.   
        inline Point4 operator--(int)
        {
            Point4 temp = *this;
            --*this;
            return temp;
        }

//===== Subtract by scalar =====
///	Scalar subtraction. 2D check is done before z is changed. 
///	\param val is the scalar subtracted from the new Point4.
        TEMPEST_API Point4 operator-(real val) const;

///	Sclara subtraction. 2D check is done before z is changed. 
///	\param val is the scalar subtracted from each element of this Point4.
        TEMPEST_API Point4& operator-=(real val);

//===== Component-wise multiply by Point4 =====
///	Point4 multiplication. This is a componentwise multiplication, scaling one Point4 by another. 2D check done before z is changed.
///	\param Point4 is the Point4 multiplied by the new Point4.
        TEMPEST_API Point4 operator*(const Point4 Point4) const;

///	Point4 multiplication. This is a componentwise multiplication, scaling one Point4 by another. 2D check done before z is changed.
///	\param Point4 is the Point4 multiplied by this Point4.
        TEMPEST_API Point4& operator*=(const Point4 Point4);

//===== Mutliply by Scalar =====
///	Scalar multiplication. This is a componentwise multiplication, scaling the Point4 by the scalar. 2D check done before z is changed.
///	\param val is the scalar multiplied by the new Point4.
        TEMPEST_API Point4 operator*(real val) const;

///	Scalar multiplication. This is a componentwise multiplication, scaling the Point4 by the scalar. 2D check done before z is changed.
///	\param val is the scalar multiplied by this Point4.
        TEMPEST_API Point4& operator*=(real val);

//===== Divide by scalar =====
///	Scalar division. This is done componentwise. 2D check done before z is changed. 
///	\param val is the scalar the new Point4 is divided by.
        TEMPEST_API Point4 operator/(real val) const;

///	Scalar division. This is done componentwise. 2D check done before z is changed. 
///	\param val is the scalar this Point4 is divided by.
        TEMPEST_API Point4& operator/=(real val);

//===== Comparison =====
///	Greater than comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are greater than all elements of the other Point4.
///	\param Point4 is the Point4 this Point4 will be compared against.
        TEMPEST_API bool operator>(const Point4& point) const;

///	Less than comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are less than all elements of the other Point4.
///	\param Point4 is the Point4 this Point4 will be compared against.
        TEMPEST_API bool operator<(const Point4& point) const;

///	Greater than or equal to comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are greater than or equal to all elements of the other Point4.
///	\param Point4 is the Point4 this Point4 will be compared against.
        TEMPEST_API bool operator>=(const Point4& point) const;

///	Less than or equal to comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are less than or equal to all elements of the other Point4.
///	\param Point4 is the Point4 this Point4 will be compared against.
        TEMPEST_API bool operator<=(const Point4& point) const;

///	Equality comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are equal to all elements of other Point4. 
///	\param Point4 is the Point4 this Point4 will be compared against. 
        TEMPEST_API bool operator==(const Point4& point) const;

///	False equality comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are not equal to all elements of other Point4. 
///	\param Point4 is the Point4 this Point4 will be compared against. 
        TEMPEST_API bool operator!=(const Point4& point) const;

    private:
        real  _data[4];	///< Array that stores the values for each element.
    };// end class
    typedef shared_ptr<Point4> p_Point4;
}// end namespace