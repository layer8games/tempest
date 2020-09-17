#pragma once

//===== Killer Includes =====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/Vector3.h>
#include <Engine/Vector4.h>

namespace TE = Tempest;

#include <glm/vec2.hpp>
#include <glm/geometric.hpp>
#include <glm/gtx/norm.hpp>

//===== Stnadard inlcudes =====
#include <cassert>

namespace TempestMath
{
    class Vector3;
    class Vector4;

    class Vector2
    {
    public:
        TEMPEST_API Vector2(void);

        TEMPEST_API explicit Vector2(real val);

        TEMPEST_API Vector2(real xVal, real yVal);
 
        TEMPEST_API Vector2(const Vector2& p);

        TEMPEST_API explicit Vector2(const Vector3& v);

        TEMPEST_API explicit Vector2(const Vector4& v);

        TEMPEST_API ~Vector2(void);

        TEMPEST_API real Dot(const Vector2& point) const;

        TEMPEST_API real Magnitude(void);

        TEMPEST_API real SqrMagnitude(void);

        TEMPEST_API void Normalize(void);

        TEMPEST_API void Reset(real val=0.0f);

        TEMPEST_API real Distance(const Vector2& p) const;

        TEMPEST_API real DistanceSquared(const Vector2& p) const;

        TEMPEST_API real DistanceSquared(const Vector3& v) const;

        TEMPEST_API real DistanceSquared(const Vector4& v) const;

        TEMPEST_API void Set(real xVal, real yVal);

        TEMPEST_API glm::vec2 GetRawData(void) const;

        TEMPEST_API F32 GetX(void) const;

        TEMPEST_API F32 GetY(void) const;

        TEMPEST_API void SetX(F32 val);

        TEMPEST_API void SetY(F32 val);

        TEMPEST_API Vector2& operator=(const Vector2& vector);

        TEMPEST_API Vector2& operator=(real val);

        TEMPEST_API Vector2 operator+(const Vector2& vector) const;

        TEMPEST_API Vector2 operator+(const Vector4& vec) const;

        TEMPEST_API Vector2 operator+(const Vector3& vec) const;

        TEMPEST_API Vector2& operator+=(const Vector2& vector);

        TEMPEST_API Vector2& operator+=(const Vector4& vector);

        TEMPEST_API Vector2& operator+=(const Vector3& vector);

        TEMPEST_API Vector2 operator+(real val) const;

        TEMPEST_API Vector2& operator+=(real val);

        TEMPEST_API Vector2 operator-(const Vector2& vector) const;
        
        TEMPEST_API Vector2 operator-(const Vector3& vector) const;

        TEMPEST_API Vector2 operator-(const Vector4& vector) const;

        TEMPEST_API Vector2& operator-=(const Vector2& vector);
 
        TEMPEST_API Vector2 operator-(void);

        TEMPEST_API Vector2& operator++(void);

        TEMPEST_API Vector2 operator++(int);
 
        TEMPEST_API Vector2& operator--(void);

        TEMPEST_API Vector2 operator--(int);

        TEMPEST_API Vector2 operator-(real val) const;

        TEMPEST_API Vector2& operator-=(real val);

        TEMPEST_API Vector2 operator*(const Vector2 vector) const;

        TEMPEST_API Vector2& operator*=(const Vector2 vector);

        TEMPEST_API Vector2 operator*(real val) const;

        TEMPEST_API Vector2& operator*=(real val);

        TEMPEST_API Vector2 operator/(real val) const;

        TEMPEST_API Vector2& operator/=(real val);

        TEMPEST_API bool operator>(const Vector2& vector) const;

        TEMPEST_API bool operator<(const Vector2& vector) const;

        TEMPEST_API bool operator>=(const Vector2& vector) const;

        TEMPEST_API bool operator<=(const Vector2& vector) const;

        TEMPEST_API bool operator==(const Vector2& vector) const;

        TEMPEST_API bool operator!=(const Vector2& vector) const;

    private:
        Vector2(glm::vec2);

        glm::vec2 _data;

    };// end class
    typedef shared_ptr<Vector2> p_Vector2;
    typedef Vector2 Point2;
    typedef shared_ptr<Vector2> p_Point2;
}// end namespace