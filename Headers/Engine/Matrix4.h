#pragma once

//=====Killer1 includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/Point2.h>
#include <Engine/Point3.h>
#include <Engine/Point4.h>
#include <Engine/Vector2.h>
#include <Engine/Vector3.h>
#include <Engine/Vector4.h>
#include <Engine/Quaternion.h>

#include <vector>
#include <cassert>

namespace TempestMath 
{
    class Matrix4
    {
    public:
        TEMPEST_API Matrix4(void);

        TEMPEST_API Matrix4(const Vector4& x, const Vector4& y, const Vector4& z);

        TEMPEST_API Matrix4(const Vector4& x, const Vector4& y, const Vector4& z, const Vector4& w);

        TEMPEST_API explicit Matrix4(const real val);
        
        TEMPEST_API Matrix4( real m00, real m01, real m02, real m03,
                             real m10, real m11, real m12, real m13,
                             real m20, real m21, real m22, real m23,
                             real m30, real m31, real m32, real m33);

        TEMPEST_API Matrix4(const Matrix4& otherMatrix);

        TEMPEST_API const std::vector<real> GetElems(void) const;
        
        TEMPEST_API void MakeOrthographic(real left, real right, real bottom, real top, real nearPlane, real farPlane);

        TEMPEST_API void MakePerspective(real fieldOfView, real aspectRatio, real nearPlane, real farPlane);

        TEMPEST_API static Matrix4 Translate(real xVal, real yVal);

        TEMPEST_API static Matrix4 Translate(real xVal, real yVal, real zVal);

        TEMPEST_API static Matrix4 Translate(const Vector4& vec);

        TEMPEST_API void SetTranslate(real xVal, real yVal);

        TEMPEST_API void SetTranslate(real xVal, real yVal, real zVal);

        TEMPEST_API void SetTranslate(const Point2& point);
        
        TEMPEST_API void SetTranslate(const Vector2& vec);
        
        TEMPEST_API void SetTranslate(const Vector3& vec);
        
        TEMPEST_API void SetTranslate(const Vector4& vec);

        TEMPEST_API Vector4 TransformInverse(const Vector4& vec) const;

        TEMPEST_API Point4 TransformInverse(const Point4& vec) const;

        TEMPEST_API static Matrix4 Scale(real xVal, real yVal);

        TEMPEST_API static Matrix4 Scale(real xVal, real yVal, real zVal);

        TEMPEST_API static Matrix4 Scale(const Vector4& vec);

        TEMPEST_API static Matrix4 Scale(const Vector3& vec);

        TEMPEST_API static Matrix4 Scale(const Vector2& vec);

        TEMPEST_API void SetScale(real xVal, real yVal);

        TEMPEST_API void SetScale(real xVal, real yVal, real zVal);

        TEMPEST_API void SetScale(const Vector2& vec);

        TEMPEST_API void SetScale(const Vector3& vec);
        
        TEMPEST_API void SetScale(const Vector4& vec);

        TEMPEST_API static Matrix4 RotateX(real val);

        TEMPEST_API static Matrix4 RotateY(real val);

        TEMPEST_API static Matrix4 RotateZ(real val);

        TEMPEST_API void SetRotateX(real val);

        TEMPEST_API void AddRotateX(real val);

        TEMPEST_API void SetRotateY(real val);

        TEMPEST_API void AddRotateY(real val);

        TEMPEST_API void SetRotateZ(real val);

        TEMPEST_API void AddRotateZ(real val);

        TEMPEST_API void SetRotate(real xVal, real yVal, real zVal);

        TEMPEST_API void AddRotation(real xVal, real yVal, real zVal);

        TEMPEST_API void SetOrientation(const Quaternion& q);

        TEMPEST_API void SetOrientationAndPosition(const Quaternion& q, const Vector4& v);

        TEMPEST_API void SetOrientationAndPosition(const Quaternion& q, const Point2& p);

        TEMPEST_API void SetOrientationAndPosition(const Quaternion& q, const Point3& p);
        
        TEMPEST_API void SetOrientationAndPosition(const Quaternion& q, const Point4& p);
        
        TEMPEST_API void SetInverse(void);

        TEMPEST_API void SetAsInverse(const Matrix4& mat);

        TEMPEST_API Matrix4 GetInverse(void) const;

        TEMPEST_API real Determinate(void) const;
 
        void MakeIdentity(void)
        {
            Reset(1.0f);
        }	

        TEMPEST_API void Reset(real val=0.0f);
        
        TEMPEST_API void Transpose(void);

        TEMPEST_API void ComponentMulti(const Matrix4& M);

        TEMPEST_API Matrix4 Transform3x3(const Matrix4& mat) const;

        TEMPEST_API Vector4 Transform3x3(const Vector4& vec) const;

        TEMPEST_API static Matrix4 LookAt(const Point4& cameraPos, const Point4& target, const Vector4& up);

        TEMPEST_API static Matrix4 LookAt(const Point3& cameraPos, const Point3& target, const Vector3& up);

        TEMPEST_API void SetLookAt(const Vector4& cameraPos, const Vector4& target, const Vector4& up);

        TEMPEST_API static Matrix4 FPSView(const Vector4& cameraPos, real pitch, real yaw);

        TEMPEST_API void SetFPSView(const Vector4& cameraPos, real pitch, real yaw);
 
        TEMPEST_API Matrix4& operator=(const Matrix4& mat);
        
        TEMPEST_API Matrix4 operator*(const Matrix4& mat) const;
 
        TEMPEST_API Vector3 operator*(const Vector3& vec) const;
        
        TEMPEST_API Vector4 operator*(const Vector4& vec) const;

        TEMPEST_API Point3 operator*(const Point3& point) const;
        
        TEMPEST_API Point4 operator*(const Point4& point) const;

        TEMPEST_API Matrix4& operator/=(real val);

        Vector4 column1;
        Vector4 column2;
        Vector4 column3;
        Vector4 column4;

    private:
        real _Cofactor(const Vector4& col1, const Vector4& col2, const Vector4& col3) const;

    };
    typedef shared_ptr<Matrix4> p_Matrix4;
}//End namespace
