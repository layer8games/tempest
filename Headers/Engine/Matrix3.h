#pragma once

#include "stdafx.h"
#include "Engine/Atom.h"
#include "Engine/Vector2.h"
#include "Engine/Vector3.h"
#include "Engine/Vector4.h"
#include "Engine/Quaternion.h"

#include "glm/mat3x3.hpp"
#include "glm/geometric.hpp"
#include "glm/gtx/norm.hpp"

#include <vector>
#include <cassert>

namespace TempestMath 
{
    class Matrix3
    {
    public:
        TEMPEST_API Matrix3(void);

        TEMPEST_API Matrix3(const Vector3& x, const Vector3& y, const Vector3& z);

        TEMPEST_API Matrix3(const Vector4& x, const Vector4& y, const Vector4& z);

        TEMPEST_API explicit Matrix3(const real val);

        TEMPEST_API Matrix3( real m00, real m01, real m02,
                             real m10, real m11, real m12,
                             real m20, real m21, real m22 );
 
        TEMPEST_API Matrix3(const Matrix3& otherMatrix);

        TEMPEST_API static Matrix3 Scale(real xVal, real yVal);

        TEMPEST_API static Matrix3 Scale(real xVal, real yVal, real zVal);

        TEMPEST_API static Matrix3 Scale(const Vector3& vec);

        TEMPEST_API static Matrix3 Scale(const Vector4& vec);

        TEMPEST_API void SetScale(real xVal, real yVal);

        TEMPEST_API void SetScale(real xVal, real yVal, real zVal);

        TEMPEST_API void SetScale(const Vector2& vec);
        
        TEMPEST_API void SetScale(const Vector3& vec);

        TEMPEST_API void SetScale(const Vector4& vec);

        TEMPEST_API void RotateX(real val);
 
        TEMPEST_API void AddRotateX(real val);

        TEMPEST_API void RotateY(real val);

        TEMPEST_API void AddRotateY(real val);

        TEMPEST_API void RotateZ(real val);

        TEMPEST_API void AddRotateZ(real val);

        TEMPEST_API void SetRotate(real xVal, real yVal, real zVal);

        TEMPEST_API void AddRotation(real xVal, real yVal, real zVal);

        TEMPEST_API void SetOrientation(const Quaternion& q);
    
        TEMPEST_API void SetInverse(void);

        TEMPEST_API void SetAsInverse(const Matrix3& mat);

        TEMPEST_API Matrix3 GetInverse(void) const;

        TEMPEST_API real Determinate(void) const;

        TEMPEST_API void MakeIdentity(void);

        TEMPEST_API void Reset(real val=0.0f);
         
        TEMPEST_API void Transpose(void);

        TEMPEST_API void ComponentMulti(const Matrix3& M);

        TEMPEST_API Matrix3 Transform(const Matrix3& mat) const;

        TEMPEST_API Vector4 Transform(const Vector4& vec) const;

        TEMPEST_API Matrix3& operator=(const Matrix3& mat);
        
        TEMPEST_API Matrix3 operator*(const Matrix3& mat) const;

        TEMPEST_API Vector4 operator*(const Vector4& vec) const;

        TEMPEST_API Matrix3& operator/=(real val);

        TEMPEST_API glm::mat3 GetRawData(void) const;

    private:
        Matrix3(glm::mat3 matrix);
        
        real _Cofactor(real c00, real c01, real c10, real c11) const;
        
        glm::mat3 _data;

    };
    typedef shared_ptr<Matrix3> p_Matrix3;
}//End namespace
