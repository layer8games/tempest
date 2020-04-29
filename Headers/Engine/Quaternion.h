#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/Vector4.h>

#include <assert.h>

namespace TempestMath
{
    class Quaternion
    {
    public:
        TEMPEST_API Quaternion(void);

        TEMPEST_API explicit Quaternion(real value);

        TEMPEST_API Quaternion(real xVal, real yVal, real zVal, real wVal);

        TEMPEST_API Quaternion(const Quaternion& q);

        TEMPEST_API ~Quaternion(void);
        
        TEMPEST_API Quaternion operator/(real d);
 
        TEMPEST_API Quaternion& operator/=(real d);

        TEMPEST_API Quaternion operator*(real m);

        TEMPEST_API Quaternion operator*(const Quaternion& q2);

        TEMPEST_API Quaternion& operator*=(real m);

        TEMPEST_API Quaternion& operator*=(const Quaternion& q2);

        TEMPEST_API real Magnitude(void);

        TEMPEST_API Quaternion Conjugate(void);

        TEMPEST_API Quaternion Inverse(void);

        TEMPEST_API Quaternion Difference(Quaternion& Q);

        TEMPEST_API real Dot(Quaternion& Q);

        TEMPEST_API void Negate(void);

        TEMPEST_API Quaternion Opposite(void);

        TEMPEST_API void Normalize(void);

        TEMPEST_API void RotateByEuler(const Vector3& vec);

        TEMPEST_API void RotateByEuler(real yaw, real pitch, real roll);

        TEMPEST_API void AddEuler(const Vector3& vec);

        TEMPEST_API void AddEuler(real yaw, real pitch, real roll);
        
        real w;
        real x;
        real y;
        real z;
    };//end Class
    typedef shared_ptr<Quaternion> p_Quaternion;
}//end Namespace