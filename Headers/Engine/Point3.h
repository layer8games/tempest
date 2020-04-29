#pragma once

//===== Killer Includes =====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/Point2.h>
#include <Engine/Vector4.h>
#include <Engine/Vector3.h>

namespace TE = Tempest;


//===== Stnadard inlcudes =====
#include <cassert>

namespace TempestMath
{
    class Point2;
    class Vector4;
    class Vector3;

    class Point3
    {
    public: 
        TEMPEST_API Point3(void);

        TEMPEST_API explicit Point3(real val);

        TEMPEST_API Point3(real xVal, real yVal, real zVal);
 
        TEMPEST_API Point3(const Point3& p);

        TEMPEST_API explicit Point3(const Vector3& v);

        TEMPEST_API explicit Point3(const Vector4& v);

        TEMPEST_API ~Point3(void);

        TEMPEST_API real Dot(const Point3& point) const;

        TEMPEST_API Point3 CrossProduct(const Point3& point) const;

        TEMPEST_API real Magnitude(void);

        TEMPEST_API real SqrMagnitude(void);

        TEMPEST_API void Normalize(void);

        TEMPEST_API void Reset(real val=0.0f);

        TEMPEST_API real Distance(const Point3& p) const;

        TEMPEST_API real DistanceSquared(const Point3& p) const;

        TEMPEST_API real DistanceSquared(const Vector3& v) const;

        TEMPEST_API real DistanceSquared(const Vector4& v) const;

        TEMPEST_API void AddScaledPoint(const Point3& point, real scale);

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
        
        TEMPEST_API Point3& operator=(const Point2& point);

        TEMPEST_API Point3& operator=(const Point3& point);

        TEMPEST_API Point3& operator=(real val);

        TEMPEST_API Point3 operator+(const Point3& point) const;

        TEMPEST_API Point3 operator+(const Vector4& vec) const;

        TEMPEST_API Point3 operator+(const Vector3& vec) const;

        TEMPEST_API Point3& operator+=(const Point3& point);

        TEMPEST_API Point3& operator+=(const Vector4& vec);

        TEMPEST_API Point3& operator+=(const Vector3& vec);

        TEMPEST_API Point3 operator+(real val) const;

        TEMPEST_API Point3& operator+=(real val);

        TEMPEST_API Point3 operator+(shared_ptr<Point3> point) const;

        TEMPEST_API Point3 operator-(const Point3& point) const;

        TEMPEST_API Point3 operator-(const Vector3& vec) const;

        TEMPEST_API Point3 operator-(const Vector4& vec) const;

        TEMPEST_API Point3& operator-=(const Point3& point);
 
        inline Point3 operator-(void)
        {
            return Point3(-x, -y, -z);
        }

        inline Point3& operator++(void)
        {
            ++x;
            ++y;
            ++z;

            return *this;
        }

        inline Point3 operator++(int)
        {
            Point3 temp = *this;
            ++*this;
            return temp;
        }
 
        inline Point3& operator--(void)
        {
            --x;
            --y;
            --z;

            return *this;
        }

        inline Point3 operator--(int)
        {
            Point3 temp = *this;
            --*this;
            return temp;
        }

        TEMPEST_API Point3 operator-(real val) const;

        TEMPEST_API Point3& operator-=(real val);

        TEMPEST_API Point3 operator*(const Point3 Point3) const;

        TEMPEST_API Point3& operator*=(const Point3 Point3);

        TEMPEST_API Point3 operator*(real val) const;

        TEMPEST_API Point3& operator*=(real val);

        TEMPEST_API Point3 operator/(real val) const;

        TEMPEST_API Point3& operator/=(real val);

        TEMPEST_API bool operator>(const Point3& point) const;

        TEMPEST_API bool operator<(const Point3& point) const;

        TEMPEST_API bool operator>=(const Point3& point) const;

        TEMPEST_API bool operator<=(const Point3& point) const;

        TEMPEST_API bool operator==(const Point3& point) const;

        TEMPEST_API bool operator!=(const Point3& point) const;

        real x;
        real y;
        real z;
    };// end class
    typedef shared_ptr<Point3> p_Point3;
}// end namespace