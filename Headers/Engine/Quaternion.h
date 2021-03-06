#pragma once

#include "stdafx.h"
#include "Engine/Atom.h"
#include "Engine/Vector4.h"

#include "glm/gtx/quaternion.hpp"

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
        
        TEMPEST_API glm::quat GetRawData(void) const;
        
        TEMPEST_API Quaternion operator/(real d);
 
        TEMPEST_API Quaternion& operator/=(real d);

        TEMPEST_API Quaternion operator*(real m);

        TEMPEST_API Quaternion operator*(const Quaternion& q2);

        TEMPEST_API Quaternion& operator*=(real m);

        TEMPEST_API Quaternion& operator*=(const Quaternion& q2);

        TEMPEST_API real Magnitude(void) const;

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

        TEMPEST_API real GetW(void) const;
        
        TEMPEST_API real GetX(void) const;
        
        TEMPEST_API real GetY(void) const;
        
        TEMPEST_API real GetZ(void) const;

        TEMPEST_API void SetW(F32 val);
        
        TEMPEST_API void SetX(F32 val);
        
        TEMPEST_API void SetY(F32 val);
        
        TEMPEST_API void SetZ(F32 val);

    private:
        Quaternion(glm::quat);
        
        glm::quat _data;

    };//end Class
    typedef shared_ptr<Quaternion> p_Quaternion;
}//end Namespace