#pragma once

//===== Killer Includes =====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/Point2.h>
#include <Engine/Point3.h>
#include <Engine/Point4.h>
#include <Engine/Vector3.h>
#include <Engine/Vector4.h>


//===== Stnadard inlcudes =====
#include <cassert>

namespace TempestMath
{
    class Point2;
    class Point3;
    class Point4;
    class Vector3;
    class Vector4;

    class Vector2
    {
    public: 
        TEMPEST_API Vector2(void);

        TEMPEST_API explicit Vector2(real val);

        TEMPEST_API Vector2(real xVal, real yVal);

        TEMPEST_API Vector2(const Vector2& v);

        TEMPEST_API explicit Vector2(const Point2& p);
        
        TEMPEST_API explicit Vector2(const Point4& p);

        TEMPEST_API explicit Vector2(const Vector3& v);
        
        TEMPEST_API explicit Vector2(const Vector4& v);

        TEMPEST_API ~Vector2(void);

        TEMPEST_API real Dot(const Vector2& vec) const;

        TEMPEST_API real Magnitude(void) const;

        TEMPEST_API real SqrMagnitude(void) const;

        TEMPEST_API void Normalize(void);

        TEMPEST_API void Reset(real val=0.0f);

        TEMPEST_API Vector2 Perpendicular(void);

        inline void Set(real xVal, real yVal)
        {
            x = xVal;
            y = yVal;
        }
		
        TEMPEST_API Vector2& operator=(const Vector2& vec);

        TEMPEST_API Vector2& operator=(real val);

        TEMPEST_API Vector2& operator=(const Point2& point);

        TEMPEST_API Vector2 operator+(const Vector2& vec) const;

        TEMPEST_API Vector2& operator+=(const Vector2& vec);

        TEMPEST_API Vector2 operator+(real val) const;

        TEMPEST_API Vector2& operator+=(real val);

        TEMPEST_API Vector2 operator+(shared_ptr<Vector2> vec) const;

        TEMPEST_API Vector2 operator-(const Point2& vec) const;

        TEMPEST_API Vector2 operator-(const Point3& vec) const;

        TEMPEST_API Vector2 operator-(const Point4& vec) const;

        TEMPEST_API Vector2 operator-(const Vector2& vec) const;

        TEMPEST_API Vector2 operator-(const Vector3& vec) const;

        TEMPEST_API Vector2 operator-(const Vector4& vec) const;

        TEMPEST_API Vector2& operator-=(const Vector2& vec);

        TEMPEST_API Vector2& operator-=(const Point2& vec);

        TEMPEST_API Vector2& operator-=(const Point3& vec);

        inline Vector2 operator-(void)
        {
            return Vector2(-x, -y);
        }

        inline Vector2& operator++(void)
        {
            ++x;
            ++y;

            return *this;
        }

        inline Vector2 operator++(int)
        {
            return Vector2(++x, ++y);
        }

        inline Vector2& operator--(void)
        {
            --x;
            --y;

            return *this;
        }

        inline Vector2 operator--(int)
        {
            return Vector2(--x, --y);
        }

        TEMPEST_API Vector2 operator-(real val) const;

        TEMPEST_API Vector2& operator-=(real val);

        TEMPEST_API Vector2 operator*(const Vector2& vec) const;

        TEMPEST_API Vector2& operator*=(const Vector2& vec);

        TEMPEST_API Vector2 operator*(real val) const;

        TEMPEST_API Vector2& operator*=(real val);

        TEMPEST_API Vector2 operator/(real val) const;

        TEMPEST_API Vector2& operator/=(real val);

        TEMPEST_API bool operator>(const Vector2& vec) const;

        TEMPEST_API bool operator<(const Vector2& vec) const;

        TEMPEST_API bool operator>=(const Vector2& vec) const;

        TEMPEST_API bool operator<=(const Vector2& vec) const;

        TEMPEST_API bool operator==(const Vector2& vec) const;

        TEMPEST_API bool operator!=(const Vector2& vec) const;

        real x;
        real y;
    };// end class
    typedef shared_ptr<Vector2> p_Vector2;
}//end namespace