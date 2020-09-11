#pragma once

//===== Killer Includes =====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/Vector2.h>
#include <Engine/Vector4.h>

#include <glm/vec3.hpp>

//===== Stnadard inlcudes =====
#include <cassert>

namespace TempestMath
{
    class Vector2;
    class Vector4;
    
    class Vector3
    {
    public:
        TEMPEST_API Vector3(void);

        TEMPEST_API explicit Vector3(real val);

        TEMPEST_API Vector3(real xVal, real yVal, real zVal);

        TEMPEST_API explicit Vector3(const Point3& p);
        
        TEMPEST_API Vector3(const Point4& p);
 
        TEMPEST_API Vector3(const Vector3& v);

        TEMPEST_API Vector3(const Vector4& v);

        TEMPEST_API ~Vector3(void);

        TEMPEST_API real Dot(const Vector3& vec) const;

        TEMPEST_API real Dot(const Point3& point) const;

        TEMPEST_API Vector3 CrossProduct(const Vector3& vec) const;

        TEMPEST_API real Magnitude(void);

        TEMPEST_API real SqrMagnitude(void);

        TEMPEST_API void Normalize(void);

        TEMPEST_API void Reset(real val=0.0f);

        TEMPEST_API void AddScaledVector(const Vector3& vec, real scale);

        TEMPEST_API void AddScaledVector(const Vector4& vec, real scale);

        TEMPEST_API void AddScaledVector(const Point4& point, real scale);


        inline void Set(real xVal, real yVal, real zVal)
        {
            x = xVal;
            y = yVal;
            z = zVal;
        }

        TEMPEST_API glm::vec3 GetRawData(void) const;
        
        TEMPEST_API F32 GetX() const;
        
        TEMPEST_API F32 GetY() const;
        
        TEMPEST_API F32 GetZ() const;

        TEMPEST_API Vector3& operator=(const Vector2& vec);

        TEMPEST_API Vector3& operator=(const Vector3& vec);

        TEMPEST_API Vector3& operator=(const Vector4& vec);

        TEMPEST_API Vector3& operator=(const Point2& point);

        TEMPEST_API Vector3& operator=(const Point3& point);

        TEMPEST_API Vector3& operator=(const Point4& point);

        TEMPEST_API Vector3& operator=(real val);

        TEMPEST_API Vector3 operator+(const Vector3& vec) const;

        TEMPEST_API Vector3& operator+=(const Vector3& vec);

        TEMPEST_API Vector3 operator+(real val) const;

        TEMPEST_API Vector3& operator+=(real val);

        TEMPEST_API Vector3 operator+(shared_ptr<Vector3> vec) const;

        TEMPEST_API Vector3 operator-(const Vector3& vec) const;

        TEMPEST_API Vector3& operator-=(const Vector3& vec);

        TEMPEST_API Vector3& operator-=(const Vector4& vec);

        TEMPEST_API Vector3& operator-=(const Point2& point);

        TEMPEST_API Vector3& operator-=(const Point3& point);

        TEMPEST_API Vector3& operator-=(const Point4& point);

        inline Vector3 operator-(void)
        {
            return Vector3(-x, -y, -z);
        }
 
        inline Vector3& operator++(void)
        {
            ++x;
            ++y;
            ++z;
            
            return *this;
        }

        inline Vector3 operator++(int)
        {
            return Vector3(++x, ++y, ++z);
        }
 
        inline Vector3& operator--(void)
        {
            --x;
            --y;
            --z;

            return *this;
        }
    
        inline Vector3 operator--(int)
        {
            return Vector3(--x, --y, --z);
        }

        TEMPEST_API Vector3 operator-(real val) const;

        TEMPEST_API Vector3& operator-=(real val);

        TEMPEST_API Vector3 operator*(const Vector3 vec) const;

        TEMPEST_API Vector3& operator*=(const Vector3 vec);

        TEMPEST_API Vector3 operator*(real val) const;

        TEMPEST_API Vector3& operator*=(real val);

        TEMPEST_API Vector3 operator/(real val) const;

        TEMPEST_API Vector3& operator/=(real val);

        TEMPEST_API bool operator>(const Vector3& vec) const;

        TEMPEST_API bool operator<(const Vector3& vec) const;

        TEMPEST_API bool operator>=(const Vector3& vec) const;

        TEMPEST_API bool operator<=(const Vector3& vec) const;

        TEMPEST_API bool operator==(const Vector3& vec) const;

        TEMPEST_API bool operator!=(const Vector3& vec) const;

        real x;
        real y;
        real z;

        glm::vec3 _data;

    };// end class
    typedef shared_ptr<Vector3> p_Vector3;
    typedef Vector3 Point3;
    typedef shared_ptr<Point3> p_Point3;
}//end namespace