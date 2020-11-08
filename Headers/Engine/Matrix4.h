#pragma once

//=====Killer1 includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/Vector2.h>
#include <Engine/Vector3.h>
#include <Engine/Vector4.h>
#include <Engine/Quaternion.h>

#include "glm/mat4x4.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/norm.hpp"
#include "glm/gtx/quaternion.hpp"

#include <vector>
#include <cassert>

namespace TempestMath 
{
    class Matrix4
    {
    public:
        TEMPEST_API Matrix4(void);

        TEMPEST_API explicit Matrix4(const real val);

        TEMPEST_API Matrix4(const Matrix4& otherMatrix);

        TEMPEST_API glm::mat4 GetRawData(void) const;

        TEMPEST_API void MakeOrthographic(real left, real right, real bottom, real top, real nearPlane, real farPlane);

        TEMPEST_API void MakePerspective(real fieldOfView, real aspectRatio, real nearPlane, real farPlane);

        TEMPEST_API static Matrix4 CreateTranslationMatrix(real xVal, real yVal);

        TEMPEST_API static Matrix4 CreateTranslationMatrix(real xVal, real yVal, real zVal);

        TEMPEST_API static Matrix4 CreateTranslationMatrix(const Vector3& vec);

        TEMPEST_API void Translate(real xVal, real yVal);

        TEMPEST_API void Translate(real xVal, real yVal, real zVal);

        TEMPEST_API void Translate(const Vector2& vec);

        TEMPEST_API void Translate(const Vector3& vec);

        TEMPEST_API void Translate(const Vector4& vec);

        TEMPEST_API Vector4 TransformInverse(const Vector4& vec) const;

        TEMPEST_API Vector3 TransformInverse(const Vector3& vec) const;

        TEMPEST_API static Matrix4 CreateScale(real xVal, real yVal);

        TEMPEST_API static Matrix4 CreateScale(real xVal, real yVal, real zVal);

        TEMPEST_API static Matrix4 CreateScale(const Vector3& vec);

        TEMPEST_API static Matrix4 CreateScale(const Vector2& vec);

        TEMPEST_API void Scale(real xVal, real yVal);

        TEMPEST_API void Scale(real xVal, real yVal, real zVal);

        TEMPEST_API void Scale(const Vector2& vec);

        TEMPEST_API void Scale(const Vector3& vec);

        TEMPEST_API void RotateX(real val);

        TEMPEST_API void AddRotateX(real val);

        TEMPEST_API void RotateY(real val);

        TEMPEST_API void AddRotateY(real val);

        TEMPEST_API void RotateZ(real val);

        TEMPEST_API void AddRotateZ(real val);

        TEMPEST_API void Rotate(const Quaternion& q);

        TEMPEST_API void SetInverse(void);

        TEMPEST_API void SetAsInverse(const Matrix4& mat);

        TEMPEST_API Matrix4 GetInverse(void) const;

        TEMPEST_API real Determinate(void) const;
 
        TEMPEST_API void MakeIdentity(void);

        TEMPEST_API void Reset(real val=0.0f);

        TEMPEST_API void Transpose(void);

        TEMPEST_API Matrix4 LookAt(const Point3& cameraPos, const Point3& target, const Vector3& up);

        TEMPEST_API void SetLookAt(const Point3& cameraPos, const Point3& target, const Vector3& up);

        TEMPEST_API static Matrix4 FPSView(const Vector4& cameraPos, real pitch, real yaw);

        TEMPEST_API void SetFPSView(const Vector4& cameraPos, real pitch, real yaw);
 
        TEMPEST_API Matrix4& operator=(const Matrix4& mat);

        TEMPEST_API Matrix4 operator*(const Matrix4& mat) const;
 
        TEMPEST_API Vector2 operator*(const Vector2& vec) const;

        TEMPEST_API Vector3 operator*(const Vector3& vec) const;

        TEMPEST_API Vector4 operator*(const Vector4& vec) const;

        TEMPEST_API Matrix4& operator/=(real val);

    private:
        Matrix4(glm::mat4 matrix);

        glm::mat4 _data;

    };
    typedef shared_ptr<Matrix4> p_Matrix4;
}//End namespace
