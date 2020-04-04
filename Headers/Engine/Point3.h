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
///	A custom Point3 class writen for the Killer Engine.
///	The Point3 is a 4 element 3D Point3. The Point3 consists of an x, y, z and w component represented by an array of real values. 
///	They are refered as x, y, z and w through through documentation. In code, you would have to refered to them as their index 
///	in the array (0 - 3). There is an alias set up in the Point3, and enum, that lets you use x, y, z and w to represent the 
///	indices natively. This is private to the Point3. 
///	The w element is what separates a Vector4 from a Point3. A Point3 is meant to represent a Point3 in space. This can also be 
///	thought of as a displayment from the origin of the planes. This is expressed mathematically by always having the w 
///	component be 1, which allows the Point3 to be transformed by a Matrix with transformation values added. 
    class Point3
    {
    public:
//==========================================================================================================================
//
//Constructors
//
//========================================================================================================================== 
///	Default construtor. Sets all values to 0, and _2D to false.		
        TEMPEST_API Point3(void);

///	Single input conversion constructor. It will set the x, y and z components to the input. _2D is false. W is set to 0.
///	\param val real: Input value for x, y and z.	
        TEMPEST_API explicit Point3(real val);

///	Four input constructor. W variable in this constructor.
///	\param x is the value for x.
///	\param y is the value for y.
///	\param z is the value for z.
///	\param w is the value for w.
        TEMPEST_API Point3(real x, real y, real z);
 
///	Copy Constructor. It explicitly copies all data into new Point3. 
///	\param v is the Point3 to copy. 
        TEMPEST_API Point3(const Point3& p);

        /// Convert a Vector3 into a Point3
        TEMPEST_API Point3(const Vector3& v);

        /// Convert a Vector4 into a Point3
        TEMPEST_API Point3(const Vector4& v);

///	Destructor. It does not do anything. 	
        TEMPEST_API ~Point3(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
//===== Point3 Special functions =====
///	Performs a Dot or Scalar product in the order of this * other.
///	\param Point3 is the left hand argument in the operation.	
        TEMPEST_API real Dot(const Point3& point) const;

///	Performs a Cross or Point3 production in the order of this % other.
///	\param Point3 is the left hand argument in the operation.				
        TEMPEST_API Point3 CrossProduct(const Point3& point) const;

///	Returns the length of the Point3. Caution, this uses the square root function.
        TEMPEST_API real Magnitude(void);

///	Returns the squard length of the Point3. It avoids the cost of the square root function.
        TEMPEST_API real SqrMagnitude(void);

///	Changes the Point3 into a unit Point3 by converting its magnitude to exaclty 1.0. This is an expensive operation.
        TEMPEST_API void Normalize(void);

///	Sets all values to input. Does not check for _2D before changing z. 
///	\param val is the value x, y and z will get. w is set to 1.0f. Default value is 0.0f.
        TEMPEST_API void Reset(real val=0.0f);

/// Gives the distance from this to another Point3. Creates a Point3 and calls Mag.
/// \param other is the Point3 we are getting the distance to. 
        TEMPEST_API real Distance(const Point3& p) const;

        /// Return the distance between two Point3s, without calling sqrt.
        TEMPEST_API real DistanceSquared(const Point3& p) const;

        /// Return the distance between this Point3 and a Vector3, without calling sqrt.
        TEMPEST_API real DistanceSquared(const Vector3& v) const;

        /// Return the distance between this Point3 and a Vector34, without calling sqrt.
        TEMPEST_API real DistanceSquared(const Vector4& v) const;

//===== Math Helper Functions =====
///	Adds a Point3 scaled by a value to this Point3. 
///	\param Point3 is the Point3 that will be added to this one. 
///	\param scale is the amount the added Point3 will be scaled by.
        TEMPEST_API void AddScaledPoint(const Point3& point, real scale);

        TEMPEST_API void AddScaledVector(const Vector3& vec, real scale);

        TEMPEST_API void AddScaledVector(const Vector4& vec, real scale);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
///	Returns the raw data for the Point3.
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
///	Allows you to index into the Point3 to read the value.
///	\param i is the index you wish to read. 0 = x, 1 = y, 2 = z, 3 = w.
        inline const real& operator[](int i) const
        {
            return _data[i];
        }

///	Allows you to index into the Point3 to change the value.
///	\param i is the index you wish to change. 0 = x, 1 = y, 2 = z, 3 = w.
        inline real& operator[](int i)
        {
            return _data[i];
        }

//===== Copy Assignment =====		
///	Copy assignment from Point3.
///	\param Point3 is the Point3 to copy into this Point3.
        TEMPEST_API Point3& operator=(const Point3& point);

///	Copy assignment from scalar.
///	\param val is the value all elements will be set to. w is not affect. 2D check is done before z is changed.
        TEMPEST_API Point3& operator=(real val);

//===== Add by Point3 =====
///	Point3 addtion. This is done componentwise.
///	\param Point3 is the Point3 to add into a new Point3.
        TEMPEST_API Point3 operator+(const Point3& point) const;

///	Point3 addtion. This is done componentwise.
///	\param vec is added into a new Point3.
        TEMPEST_API Point3 operator+(const Vector4& vec) const;

/// Point3 addtion. This is done componentwise.
/// \param ved is added into a new Point3.
        TEMPEST_API Point3 operator+(const Vector3& vec) const;

///	Point3 addition equal. This is done componentwise.
///	\param Point3 is the Point3 to add into this Point3.
        TEMPEST_API Point3& operator+=(const Point3& point);

///	Point3 addition equal. This is done componentwise.
///	\param vec is the Vector4 to add into this Point3.
        TEMPEST_API Point3& operator+=(const Vector4& vec);

/// Point3 addition equal. This is done componentwise.
/// \param vec is the Vector4 to add into this Point3.
        TEMPEST_API Point3& operator+=(const Vector3& vec);

//===== Add by scalar =====
///	Scalar addition. Each value is added into. 2D check done before z is changed.
///	\param val is added into the elements of a new Point3.
        TEMPEST_API Point3 operator+(real val) const;

///	Scalar addition. Each value is added into. 2D check done before z is changed.
///	\param val is added into each element of this Point3.
        TEMPEST_API Point3& operator+=(real val);

///	Shared Point3er addition. A helper to allow arithmetic with p_Point3.
///	\param Point3 is the p_Point3 that is added into each element of a new Point3.
        TEMPEST_API Point3 operator+(shared_ptr<Point3> point) const;

//===== Subtract by Point3 =====
///	Point3 subtraction. This is done componentwise. 2D check done before z is changed. 
///	\param Point3 is the Point3 subtracted from the new Point3.
        TEMPEST_API Point3 operator-(const Point3& point) const;

        /// Subtract a Vector3 from this Point3, return result.
        TEMPEST_API Point3 operator-(const Vector3& vec) const;

        /// Subtract a Vector4 from this Point3, return result.
        TEMPEST_API Point3 operator-(const Vector4& vec) const;

///	Point3 subtraction. This is done componenetwise. 2D check done before z is changed. 
///	\param Point3 is the Point3ed subtractd from this Point3.
        TEMPEST_API Point3& operator-=(const Point3& point);

//===== Negation and increment ===== 
///	Changes the sign of each element of the Point3. If 2D, z is not changed. w is also ignored. 
        inline Point3 operator-(void)
        {
            return Point3(-_data[x], -_data[y], -_data[z]);
        }

///	Prefix, Adds 1 to each element of the Point3. If 2D, z is ignored. w is always ignored.  
        inline Point3& operator++(void)
        {
            ++_data[x];
            ++_data[y];
            ++_data[z];

            return *this;
        }

///	Postfix, Adds 1 to each element of the Point3. If 2D, z is ignored. w is always ignored.  
        inline Point3 operator++(int)
        {
            Point3 temp = *this;
            ++*this;
            return temp;
        }
 
///	Prefix, Subtracts 1 to each element of the Point3. If 2D, z is ignored. w is always ignored.  
        inline Point3& operator--(void)
        {
            --_data[x];
            --_data[y];
            --_data[z];

            return *this;
        }

///	Postfix, Subtracts 1 to each element of the Point3. If 2D, z is ignored. w is always ignored.   
        inline Point3 operator--(int)
        {
            Point3 temp = *this;
            --*this;
            return temp;
        }

//===== Subtract by scalar =====
///	Scalar subtraction. 2D check is done before z is changed. 
///	\param val is the scalar subtracted from the new Point3.
        TEMPEST_API Point3 operator-(real val) const;

///	Sclara subtraction. 2D check is done before z is changed. 
///	\param val is the scalar subtracted from each element of this Point3.
        TEMPEST_API Point3& operator-=(real val);

//===== Component-wise multiply by Point3 =====
///	Point3 multiplication. This is a componentwise multiplication, scaling one Point3 by another. 2D check done before z is changed.
///	\param Point3 is the Point3 multiplied by the new Point3.
        TEMPEST_API Point3 operator*(const Point3 Point3) const;

///	Point3 multiplication. This is a componentwise multiplication, scaling one Point3 by another. 2D check done before z is changed.
///	\param Point3 is the Point3 multiplied by this Point3.
        TEMPEST_API Point3& operator*=(const Point3 Point3);

//===== Mutliply by Scalar =====
///	Scalar multiplication. This is a componentwise multiplication, scaling the Point3 by the scalar. 2D check done before z is changed.
///	\param val is the scalar multiplied by the new Point3.
        TEMPEST_API Point3 operator*(real val) const;

///	Scalar multiplication. This is a componentwise multiplication, scaling the Point3 by the scalar. 2D check done before z is changed.
///	\param val is the scalar multiplied by this Point3.
        TEMPEST_API Point3& operator*=(real val);

//===== Divide by scalar =====
///	Scalar division. This is done componentwise. 2D check done before z is changed. 
///	\param val is the scalar the new Point3 is divided by.
        TEMPEST_API Point3 operator/(real val) const;

///	Scalar division. This is done componentwise. 2D check done before z is changed. 
///	\param val is the scalar this Point3 is divided by.
        TEMPEST_API Point3& operator/=(real val);

//===== Comparison =====
///	Greater than comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are greater than all elements of the other Point3.
///	\param Point3 is the Point3 this Point3 will be compared against.
        TEMPEST_API bool operator>(const Point3& point) const;

///	Less than comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are less than all elements of the other Point3.
///	\param Point3 is the Point3 this Point3 will be compared against.
        TEMPEST_API bool operator<(const Point3& point) const;

///	Greater than or equal to comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are greater than or equal to all elements of the other Point3.
///	\param Point3 is the Point3 this Point3 will be compared against.
        TEMPEST_API bool operator>=(const Point3& point) const;

///	Less than or equal to comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are less than or equal to all elements of the other Point3.
///	\param Point3 is the Point3 this Point3 will be compared against.
        TEMPEST_API bool operator<=(const Point3& point) const;

///	Equality comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are equal to all elements of other Point3. 
///	\param Point3 is the Point3 this Point3 will be compared against. 
        TEMPEST_API bool operator==(const Point3& point) const;

///	False equality comparison. 2D is used as an early out. 2D is also checked before z is compared. Only true if all elements of this are not equal to all elements of other Point3. 
///	\param Point3 is the Point3 this Point3 will be compared against. 
        TEMPEST_API bool operator!=(const Point3& point) const;

    private:
        real  _data[3];	///< Array that stores the values for each element.
    };// end class
    typedef shared_ptr<Point3> p_Point3;
}// end namespace