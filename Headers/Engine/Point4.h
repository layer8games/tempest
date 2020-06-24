#pragma once

//===== Killer Includes =====
#include "stdafx.h"
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

    class Point4
    {
    public:
        TEMPEST_API Point4(void);

        TEMPEST_API explicit Point4(real val);

        TEMPEST_API Point4(real xVal, real yVal, real zVal, real wVal);
 
        TEMPEST_API Point4(const Point4& p);

        TEMPEST_API explicit Point4(const Vector3& v);

        TEMPEST_API explicit Point4(const Vector4& v);

        TEMPEST_API ~Point4(void);

        TEMPEST_API real Dot(const Point4& point) const;

        TEMPEST_API Point4 CrossProduct(const Point4& point) const;

        TEMPEST_API real Magnitude(void);

        TEMPEST_API real SqrMagnitude(void);

        TEMPEST_API void Normalize(void);

        TEMPEST_API void Reset(real val=0.0f);

        TEMPEST_API real Distance(const Point4& p) const;

        TEMPEST_API real DistanceSquared(const Point4& p) const;

        TEMPEST_API real DistanceSquared(const Vector3& v) const;

        TEMPEST_API real DistanceSquared(const Vector4& v) const;

        TEMPEST_API void AddScaledPoint(const Point4& point, real scale);

        TEMPEST_API void AddScaledVector(const Vector3& vec, real scale);

        TEMPEST_API void AddScaledVector(const Vector4& vec, real scale);

        inline void Set(real xVal, real yVal, real zVal)
        {
            x = xVal;
            y = yVal;
            z = zVal;
        }

        inline void Set(real xVal, real yVal)
        {
            x = xVal;
            y = yVal;
        }
        
        TEMPEST_API Point4& operator=(const Point4& point);

        TEMPEST_API Point4& operator=(real val);

        TEMPEST_API Point4 operator+(const Point4& point) const;

        TEMPEST_API Point4 operator+(const Vector4& vec) const;

        TEMPEST_API Point4 operator+(const Vector3& vec) const;

        TEMPEST_API Point4& operator+=(const Point4& point);

        TEMPEST_API Point4& operator+=(const Vector4& vec);

        TEMPEST_API Point4& operator+=(const Vector3& vec);

        TEMPEST_API Point4 operator+(real val) const;

        TEMPEST_API Point4& operator+=(real val);

        TEMPEST_API Point4 operator-(const Point4& point) const;

        TEMPEST_API Point4 operator-(const Vector3& vec) const;

        TEMPEST_API Point4 operator-(const Vector4& vec) const;

        TEMPEST_API Point4& operator-=(const Point4& point);

        inline Point4 operator-(void)
        {
            return Point4(-x, -y, -z, 1.0f);
        }

        inline Point4& operator++(void)
        {
            ++x;
            ++y;
            ++z;

            return *this;
        }

        inline Point4 operator++(int)
        {
            Point4 temp = *this;
            ++*this;
            return temp;
        }
 
        inline Point4& operator--(void)
        {
            --x;
            --y;
            --z;

            return *this;
        }

        inline Point4 operator--(int)
        {
            Point4 temp = *this;
            --*this;
            return temp;
        }

        TEMPEST_API Point4 operator-(real val) const;

        TEMPEST_API Point4& operator-=(real val);

        TEMPEST_API Point4 operator*(const Point4 Point4) const;

        TEMPEST_API Point4& operator*=(const Point4 Point4);

        TEMPEST_API Point4 operator*(real val) const;

        TEMPEST_API Point4& operator*=(real val);

        TEMPEST_API Point4 operator/(real val) const;

        TEMPEST_API Point4& operator/=(real val);

        TEMPEST_API bool operator>(const Point4& point) const;

        TEMPEST_API bool operator<(const Point4& point) const;

        TEMPEST_API bool operator>=(const Point4& point) const;

        TEMPEST_API bool operator<=(const Point4& point) const;

        TEMPEST_API bool operator==(const Point4& point) const;

        TEMPEST_API bool operator!=(const Point4& point) const;

        real x;
        real y;
        real z;
        real w;
    };// end class
    typedef shared_ptr<Point4> p_Point4;
}// end namespace