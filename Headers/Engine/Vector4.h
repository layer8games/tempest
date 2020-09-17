#pragma once

#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/Vector3.h>

#include <glm/vec4.hpp>
#include <glm/geometric.hpp>
#include <glm/gtx/norm.hpp>

#include <cassert>

namespace TempestMath
{
    class Vector3;

    class Vector4
    {
    public:
        TEMPEST_API Vector4(void);

        TEMPEST_API explicit Vector4(real val);

        TEMPEST_API Vector4(real xVal, real yVal, real zVal, real wVal);

        TEMPEST_API Vector4(const Vector4& v);
 
        TEMPEST_API ~Vector4(void);

        TEMPEST_API real Dot(const Vector4& vector) const;

        TEMPEST_API real Magnitude(void);

        TEMPEST_API real SqrMagnitude(void);

        TEMPEST_API void Normalize(void);

        TEMPEST_API void Reset(real val=0.0f);

        TEMPEST_API void AddScaledVector(const Vector4& vector, real scale);

        TEMPEST_API void AddScaledVector(const Vector3& vec, real scale);

        TEMPEST_API void Set(real xVal, real yVal, real zVal, real wVal);

        TEMPEST_API glm::vec4 GetRawData(void) const;

        TEMPEST_API F32 GetX() const;
        
        TEMPEST_API F32 GetY() const;
        
        TEMPEST_API F32 GetZ() const;

        TEMPEST_API F32 GetW() const;

        TEMPEST_API void SetX(F32 val);

        TEMPEST_API void SetY(F32 val);

        TEMPEST_API void SetZ(F32 val);

        TEMPEST_API void SetW(F32 val);

        TEMPEST_API Vector4& operator=(const Vector4& vector);

        TEMPEST_API Vector4& operator=(const Vector3& vec);

        TEMPEST_API Vector4& operator=(real val);

        TEMPEST_API Vector4 operator+(const Vector4& vector) const;

        TEMPEST_API Vector4& operator+=(const Vector4& vector);

        TEMPEST_API Vector4 operator+(real val) const;

        TEMPEST_API Vector4& operator+=(real val);

        TEMPEST_API Vector4 operator-(const Vector4& vector) const;

        TEMPEST_API Vector4& operator-=(const Vector4& vector);

        TEMPEST_API Vector4 operator-(void) const;
 
        TEMPEST_API Vector4& operator++(void);

        TEMPEST_API Vector4 operator++(int);

        TEMPEST_API Vector4& operator--(void);
 
        TEMPEST_API Vector4 operator--(int);

        TEMPEST_API Vector4 operator-(real val) const;

        TEMPEST_API Vector4& operator-=(real val);

        TEMPEST_API Vector4 operator*(const Vector4 vector) const;

        TEMPEST_API Vector4& operator*=(const Vector4 vector);

        TEMPEST_API Vector4 operator*(real val) const;

        TEMPEST_API Vector4& operator*=(real val);

        TEMPEST_API Vector4 operator/(real val) const;

        TEMPEST_API Vector4& operator/=(real val);

        TEMPEST_API bool operator>(const Vector4& vector) const;

        TEMPEST_API bool operator<(const Vector4& vector) const;

        TEMPEST_API bool operator>=(const Vector4& vector) const;

        TEMPEST_API bool operator<=(const Vector4& vector) const;

        TEMPEST_API bool operator==(const Vector4& vector) const;

        TEMPEST_API bool operator!=(const Vector4& vector) const;

        private:
            Vector4(glm::vec4);
            
            glm::vec4 _data;

    };
    typedef shared_ptr<Vector4> p_Vector4;
    typedef Vector4 Point4;
    typedef shared_ptr<Point4> p_Point4;
}