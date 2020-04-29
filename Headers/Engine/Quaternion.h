#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/Vector4.h>

#include <assert.h>

namespace TempestMath
{
//==========================================================================================================================
//Documentation
//========================================================================================================================== 
    ///	Quaternions will handle the rotational math that the engine will use. This class is the holder of these functions. The
    ///	Quaternion is represent by an Array of 4 F32 values. These include w, x, y, z. Unlike the Vector4, w is the first element.
    class Quaternion
    {
    public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================		 
        ///	Default Constructor. Sets  
        TEMPEST_API Quaternion(void);

        ///	 Conversion constructor. Sets all elements to the same value.
        ///	 \param value is what each element will be set to.
        TEMPEST_API explicit Quaternion(real value);

        ///	Four value constructor. 
        ///	\param wVal is the value that w will be set to.
        ///	\param xVal is the value that x will be set to.
        ///	\param yVal is the value that y will be set to.
        ///	\param zVal is the value that z will be set to.
        TEMPEST_API Quaternion(real xVal, real yVal, real zVal, real wVal);

        ///	Copy constructor. Calls the [] operator to get the elements to copy into this Quaternion.
        ///	\param q is the Quaternion that will be copied. 
        TEMPEST_API Quaternion(const Quaternion& q);

        ///	Default Destructor. Has no direct function at this time. 
        TEMPEST_API ~Quaternion(void);
        
//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
//==========================================================================================================================
//
//Operators
//
//==========================================================================================================================
        ///	Scalar division. Performs a component wise division
        ///	\param d is the value that all elements of the new Quaternion will be divided by. 
        TEMPEST_API Quaternion operator/(real d);
 
        ///	Scalar division. Performs a component wise division
        ///	\param d is the value that all elements of this Quaternion will be divided by. 
        TEMPEST_API Quaternion& operator/=(real d);

        ///	Scalar multiplication. Performs a compoenent wise multiplication.
        ///	\param m is the value that all the elements of the new Quaternion will be multiplied by. 
        TEMPEST_API Quaternion operator*(real m);

        ///	Quaternion multiplication. Similar to the Vector4::CrossProduct. 
        ///	\param q2 is the Quaternion that the new Quaternion will be multiplied with. 
        TEMPEST_API Quaternion operator*(const Quaternion& q2);

        ///	Scalar multiplication. Performs a component wise operation.
        ///	\param m is the value by which this Quaternion will be multiplied by. 
        TEMPEST_API Quaternion& operator*=(real m);

        ///	 Quaternion multiplication. Similar to the Vector4::CrossProduct. 
        ///	\param q2 is the Quaternion that this Quaternion will be multiplied with.
        TEMPEST_API Quaternion& operator*=(const Quaternion& q2);

//==========================================================================================================================
//
//Quaternion Functions
//
//==========================================================================================================================
        ///	Returns the length of the rotation that this Quaternion represents. 
        TEMPEST_API real Magnitude(void);

        ///	Returns a new Quaternion that represents the negation of the Vector4 portion of the Quaternion. 
        TEMPEST_API Quaternion Conjugate(void);

        ///	Returns a new Quaternion that represents the Conjugate divided by the Magnitude of this Quaternion. 
        TEMPEST_API Quaternion Inverse(void);

        ///	Returns a Quaternion that reprsents the angular displacement between this Quaternion and another.
        ///	\param Q is the other Quaternion in the displacement. 
        TEMPEST_API Quaternion Difference(Quaternion& Q);

        ///	Returns the Dot Product between this Quaternion and another. 
        ///	\param Q is the other Quaternion that this Quaterion will perform the operation against. 
        TEMPEST_API real Dot(Quaternion& Q);

        ///	\bug This should be changed to be the - operator. Multiplies all elements of this Quaternion by -1. 
        TEMPEST_API void Negate(void);

        ///	Like Negate, but returns the result. Should probably be removed later. 
        TEMPEST_API Quaternion Opposite(void);

        ///	 Makes the length of the rotation that this Quaternion represents be exactly 1.  
        TEMPEST_API void Normalize(void);

        /// Rotate the Quaternion by the Euler Angle, represented by a Vector3.
        /// \param vec is the Euler Angle that is converted into a Quaternion
        TEMPEST_API void RotateByEuler(const Vector3& vec);

        /// Rotate the Quaternion by the Euler Angle represented by 3 reals
        /// \param yaw
        /// \param pitch 
        /// \param roll
        TEMPEST_API void RotateByEuler(real yaw, real pitch, real roll);

        /// Add the current Quaternion to a new Quaternion, using an Euler Angle, represented by a 
        /// Vector3. 
        /// \param vec is the Euler Angle to add to this one. 
        TEMPEST_API void AddEuler(const Vector3& vec);

        /// Add the current Quaternion to a new Quaternion, using an Euler Angle, represent by 3 reals.
        /// \param yaw
        /// \param pitch 
        /// \param roll
        TEMPEST_API void AddEuler(real yaw, real pitch, real roll);
        
//==========================================================================================================================
//
//Data
//
//==========================================================================================================================
        real w;
        real x;
        real y;
        real z;
    };//end Class
    typedef shared_ptr<Quaternion> p_Quaternion;
}//end Namespace