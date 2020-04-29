#pragma once

//===== Killer Includes =====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/Vector2.h>
#include <Engine/Vector3.h>
#include <Engine/Vector4.h>

namespace TE = Tempest;


//===== Stnadard inlcudes =====
#include <cassert>

namespace TempestMath
{
    class Vector2;
    class Vector3;
    class Vector4;

    class Point2
    {
    public:
        TEMPEST_API Point2(void);

        TEMPEST_API explicit Point2(real val);

        TEMPEST_API Point2(real xVal, real yVal);
 
        TEMPEST_API Point2(const Point2& p);

        TEMPEST_API explicit Point2(const Vector3& v);

        TEMPEST_API explicit Point2(const Vector4& v);

        TEMPEST_API ~Point2(void);

        TEMPEST_API real Dot(const Point2& point) const;

        TEMPEST_API real Magnitude(void);

        TEMPEST_API real SqrMagnitude(void);

        TEMPEST_API void Normalize(void);

        TEMPEST_API void Reset(real val=0.0f);

        TEMPEST_API real Distance(const Point2& p) const;

        TEMPEST_API real DistanceSquared(const Point2& p) const;

        TEMPEST_API real DistanceSquared(const Vector3& v) const;

        TEMPEST_API real DistanceSquared(const Vector4& v) const;

        inline void Set(real xVal, real yVal, real zVal)
        {
            x = xVal;
            y = yVal;
        }

        inline void Set(real xVal, real yVal)
        {
            x = xVal;
            y = yVal;
        }
		
        TEMPEST_API Point2& operator=(const Point2& point);

        TEMPEST_API Point2& operator=(real val);

        TEMPEST_API Point2 operator+(const Point2& point) const;

        TEMPEST_API Point2 operator+(const Vector4& vec) const;

        TEMPEST_API Point2 operator+(const Vector3& vec) const;

        TEMPEST_API Point2& operator+=(const Point2& point);

        TEMPEST_API Point2& operator+=(const Vector4& vec);

        TEMPEST_API Point2& operator+=(const Vector3& vec);

        TEMPEST_API Point2& operator+=(const Vector2& vec);

        TEMPEST_API Point2 operator+(real val) const;

        TEMPEST_API Point2& operator+=(real val);

        TEMPEST_API Point2 operator-(const Point2& point) const;

        TEMPEST_API Point2 operator-(const Point3& point) const;

        TEMPEST_API Point2 operator-(const Point4& point) const;

        TEMPEST_API Point2 operator-(const Vector2& vec) const;
        
        TEMPEST_API Point2 operator-(const Vector3& vec) const;

        TEMPEST_API Point2 operator-(const Vector4& vec) const;

        TEMPEST_API Point2& operator-=(const Point2& point);
 
        inline Point2 operator-(void)
        {
            return Point2(-x, -y);
        }

        inline Point2& operator++(void)
        {
            ++x;
            ++y;

            return *this;
        }

        inline Point2 operator++(int)
        {
            Point2 temp = *this;
            ++*this;
            return temp;
        }
 
        inline Point2& operator--(void)
        {
            --x;
            --y;

            return *this;
        }

        inline Point2 operator--(int)
        {
            Point2 temp = *this;
            --*this;
            return temp;
        }

        TEMPEST_API Point2 operator-(real val) const;

        TEMPEST_API Point2& operator-=(real val);

        TEMPEST_API Point2 operator*(const Point2 Point2) const;

        TEMPEST_API Point2& operator*=(const Point2 Point2);

        TEMPEST_API Point2 operator*(real val) const;

        TEMPEST_API Point2& operator*=(real val);

        TEMPEST_API Point2 operator/(real val) const;

        TEMPEST_API Point2& operator/=(real val);

        TEMPEST_API bool operator>(const Point2& point) const;

        TEMPEST_API bool operator<(const Point2& point) const;

        TEMPEST_API bool operator>=(const Point2& point) const;

        TEMPEST_API bool operator<=(const Point2& point) const;

        TEMPEST_API bool operator==(const Point2& point) const;

        TEMPEST_API bool operator!=(const Point2& point) const;

        real x;
        real y; 

    };// end class
    typedef shared_ptr<Point2> p_Point2;
}// end namespace