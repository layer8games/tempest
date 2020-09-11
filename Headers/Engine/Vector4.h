#pragma once

#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/Vector3.h>

#include <glm/vec4.hpp>

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

        TEMPEST_API explicit Vector4(const Point4& p);
 
        TEMPEST_API ~Vector4(void);

        TEMPEST_API real Dot(const Vector4& vec) const;

        TEMPEST_API real Dot(const Point4& point) const;
        
        TEMPEST_API real Dot(const Point3& point) const;

        TEMPEST_API Vector4 CrossProduct(const Vector4& vec) const;

        TEMPEST_API real Magnitude(void);

        TEMPEST_API real SqrMagnitude(void);

        TEMPEST_API void Normalize(void);

        TEMPEST_API void Reset(real val=0.0f);

        TEMPEST_API void AddScaledVector(const Vector4& vec, real scale);

        TEMPEST_API void AddScaledVector(const Vector3& vec, real scale);

        TEMPEST_API void AddScaledPoint(const Point4& point, real scale);

        inline void Set(real xVal, real yVal, real zVal)
        {
            x = xVal;
            y = yVal;
            z = zVal;
        }

        TEMPEST_API glm::vec4 GetRawData(void) const;

        TEMPEST_API F32 GetX() const;
        
        TEMPEST_API F32 GetY() const;
        
        TEMPEST_API F32 GetZ() const;

        TEMPEST_API Vector4& operator=(const Vector4& vec);

        TEMPEST_API Vector4& operator=(const Point4& point);

        TEMPEST_API Vector4& operator=(const Vector3& vec);

        TEMPEST_API Vector4& operator=(real val);

        TEMPEST_API Vector4 operator+(const Vector4& vec) const;

        TEMPEST_API Vector4& operator+=(const Vector4& vec);

        TEMPEST_API Vector4 operator+(const Vector3& vec) const;

        TEMPEST_API Vector4& operator+=(const Vector3& vec);

        TEMPEST_API Vector4 operator+(const Point3& Point) const;
        
        TEMPEST_API Vector4 operator+(const Point4& Point) const;

        TEMPEST_API Vector4& operator+=(const Point3& point);
        
        TEMPEST_API Vector4& operator+=(const Point4& point);

        TEMPEST_API Vector4 operator+(real val) const;

        TEMPEST_API Vector4& operator+=(real val);

        TEMPEST_API Vector4 operator-(const Vector4& vec) const;

        TEMPEST_API Vector4& operator-=(const Vector4& vec);

        TEMPEST_API Vector4 operator-(const Vector3& vec) const;

        TEMPEST_API Vector4& operator-=(const Vector3& vec);

        TEMPEST_API Vector4 operator-(const Point3& vec) const;
        
        TEMPEST_API Vector4 operator-(const Point4& vec) const;

        TEMPEST_API Vector4& operator-=(const Point3& vec);
        
        TEMPEST_API Vector4& operator-=(const Point4& vec);

        inline Vector4 operator-(void)
        {
            return Vector4(-x, -y, -z, 0.0f);
        }
 
        inline Vector4& operator++(void)
        {
            ++x;
            ++y;
            ++z;

            return *this;
        }

        inline Vector4 operator++(int)
        {
            return Vector4(++x, ++y, ++z, 0.0f);
        }

        inline Vector4& operator--(void)
        {
            --x;
            --y;
            --z;

            return *this;
        }
 
        inline Vector4 operator--(int)
        {
            return Vector4(--x, --y, --z, 0.0f);
        }

        TEMPEST_API Vector4 operator-(real val) const;

        TEMPEST_API Vector4& operator-=(real val);

        TEMPEST_API Vector4 operator*(const Vector4 vec) const;

        TEMPEST_API Vector4& operator*=(const Vector4 vec);

        TEMPEST_API Vector4 operator*(real val) const;

        TEMPEST_API Vector4& operator*=(real val);

        TEMPEST_API Vector4 operator/(real val) const;

        TEMPEST_API Vector4& operator/=(real val);

        TEMPEST_API bool operator>(const Vector4& vec) const;

        TEMPEST_API bool operator<(const Vector4& vec) const;

        TEMPEST_API bool operator>=(const Vector4& vec) const;

        TEMPEST_API bool operator<=(const Vector4& vec) const;

        TEMPEST_API bool operator==(const Vector4& vec) const;

        TEMPEST_API bool operator!=(const Vector4& vec) const;

        real x;
        real y;
        real z; 
        real w;

        private:
            glm::vec4 _data;

    };
    typedef shared_ptr<Vector4> p_Vector4;
    typedef Vector4 Point4;
    typedef shared_ptr<Point4> p_Point4;
}