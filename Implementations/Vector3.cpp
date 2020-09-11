#include "stdafx.h"
#include <Engine/Vector3.h>
using namespace TempestMath;

Vector3::Vector3(void)
    :
    x(0.0f), 
    y(0.0f), 
    z(0.0f)
{  }

Vector3::Vector3(real val)
    :
    x(val),
    y(val),
    z(val)
{  }

Vector3::Vector3(real xVal, real yVal, real zVal)
    :
    x(xVal),
    y(yVal),
    z(zVal)
{  }

Vector3::Vector3(const Point3& p)
    :
    x(p.x),
    y(p.y),
    z(p.z)
{  }

Vector3::Vector3(const Point4& p)
    :
    x(p.x),
    y(p.y),
    z(p.z)
{  }

Vector3::Vector3(const Vector3& v)
    :
    x(v.x),
    y(v.y),
    z(v.z)
{  }

Vector3::Vector3(const Vector4& v)
    :
    x(v.x),
    y(v.y),
    z(v.z)
{  }


Vector3::~Vector3(void)
{  }

real Vector3::Dot(const Vector3& vec) const
{
    return x * vec.x +
           y * vec.y +
           z * vec.z;
}

real Vector3::Dot(const Point3& point) const
{
    return x * point.x +
           y * point.y +
           z * point.z;
}

Vector3 Vector3::CrossProduct(const Vector3& vec) const
{
    return Vector3( y * vec.z - z * vec.y,
                    z * vec.x - x * vec.z,
                    x * vec.y - y * vec.x );
}

real Vector3::Magnitude(void)
{
    return real_sqrt(x * x + y * y + z * z);
}

real Vector3::SqrMagnitude(void)
{
    return x * x + y * y + z * z;
}

void Vector3::Normalize(void)
{
    real mag = Magnitude();

    if(mag > 0 && mag != 1.0f)
    {
        (*this) *= 1 / mag;
    }
}

void Vector3::Reset(real val)
{
    x = val;
    y = val;
    z = val;
}

void Vector3::AddScaledVector(const Vector3& vec, real scale)
{
    x += vec.x * scale;
    y += vec.y * scale;
    z += vec.z * scale;
}

void Vector3::AddScaledVector(const Vector4& vec, real scale)
{
    x += vec.x * scale;
    y += vec.y * scale;
    z += vec.z * scale;
}

void Vector3::AddScaledVector(const Point4& point, real scale)
{
    x += point.x * scale;
    y += point.y * scale;
    z += point.z * scale;
}

glm::vec3 Vector3::GetRawData(void) const
{
    return _data;
}

F32 Vector3::GetX() const
{
    return x;
}
        
F32 Vector3::GetY() const
{
    return y;
}
        
F32 Vector3::GetZ() const
{
    return z;
}

Vector3& Vector3::operator=(const Vector2& vec)
{
    x = vec.x;
    y = vec.y;
    z = 0.0f;

    return *this;
}

Vector3& Vector3::operator=(const Vector3& vec)
{
    x = vec.x;
    y = vec.y;
    z = vec.z;

    return *this;
}

Vector3& Vector3::operator=(const Vector4& vec)
{
    x = vec.x;
    y = vec.y;
    z = vec.z;

    return *this;
}

Vector3& Vector3::operator=(const Point2& point)
{
    x = point.x;
    y = point.y;
    z = 0.0f;

    return *this;
}

Vector3& Vector3::operator=(const Point3& point)
{
    x = point.x;
    y = point.y;
    z = point.z;

    return *this;
}

Vector3& Vector3::operator=(const Point4& point)
{
    x = point.x;
    y = point.y;
    z = point.z;

    return *this;
}

Vector3& Vector3::operator=(real val)
{
    x = val;
    y = val;
    z = val;

    return *this;
}

Vector3 Vector3::operator+(const Vector3& vec) const
{
    return Vector3(x + vec.x,
                   y + vec.y,
                   z + vec.z);
}

Vector3& Vector3::operator+=(const Vector3& vec)
{
    x += vec.x;
    y += vec.y;
    z += vec.z;

    return *this;
}

Vector3 Vector3::operator+(shared_ptr<Vector3> vec) const
{
    return Vector3(x + vec->x,
                   y + vec->y,
                   z + vec->z);
}

Vector3 Vector3::operator+(real val) const
{
    return Vector3(x + val,
                   y + val,
                   z + val);
}

Vector3& Vector3::operator+=(real val)
{
    x += val;
    y += val;
    z += val;

    return *this;
}

Vector3 Vector3::operator-(const Vector3& vec) const
{
    return Vector3( x - vec.x,
                    y - vec.y,
                    z - vec.z );
}

Vector3& Vector3::operator-=(const Vector3& vec)
{
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;

    return *this;
}

Vector3& Vector3::operator-=(const Vector4& vec)
{
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;

    return *this;
}

Vector3& Vector3::operator-=(const Point2& point)
{
    x -= point.x;
    y -= point.y;
    z = 0.0f;

    return *this;
}

Vector3& Vector3::operator-=(const Point3& point)
{
    x -= point.x;
    y -= point.y;
    z -= point.z;

    return *this;
}

Vector3& Vector3::operator-=(const Point4& point)
{
    x -= point.x;
    y -= point.y;
    z -= point.z;

    return *this;
}

Vector3 Vector3::operator-(real val) const
{
    return Vector3( x - val,
                    y - val,
                    z - val );
}

Vector3& Vector3::operator-=(real val)
{
    x -= val;
    y -= val;
    z -= val;

    return *this;
}

Vector3 Vector3::operator*(const Vector3 vec) const
{
    return Vector3( x * vec.x,
                    y * vec.y,
                    z * vec.z );
}

Vector3& Vector3::operator*=(const Vector3 vec)
{
    x *= vec.x;
    y *= vec.y;
    z *= vec.z;

    return *this;
}

Vector3 Vector3::operator*(real val) const
{
    return Vector3( x * val,
                    y * val,
                    z * val );
}

Vector3& Vector3::operator*=(real val)
{
    x *= val;
    y *= val;
    z *= val;

    return *this;
}

Vector3 Vector3::operator/(real val) const
{
    assert(val != 0.0f);
    return Vector3( x / val,
                    y / val,
                    z / val );
}

Vector3& Vector3::operator/=(real val)
{
    assert(val != 0.0f);

    x /= val;
    y /= val;
    z /= val;

    return *this;
}

bool Vector3::operator>(const Vector3& vec) const
{
    bool state = x > vec.x && 
                 y > vec.y &&
                 z > vec.z;

    return state;
}

bool Vector3::operator<(const Vector3& vec) const
{
    bool state = x < vec.x &&
                 y < vec.y &&
                 z < vec.z;

    return state;;
}

bool Vector3::operator>=(const Vector3& vec) const
{
    bool state = x >= vec.x &&
                 y >= vec.y &&
                 z >= vec.z;

    return state;
}

bool Vector3::operator<=(const Vector3& vec) const
{
    bool state = x <= vec.x &&
                 y <= vec.y &&
                 z <= vec.z;

    return state;
}

bool Vector3::operator==(const Vector3& vec) const
{
    bool state = x == vec.x &&
                 y == vec.y &&
                 z == vec.z;

    return state;
}

bool Vector3::operator!=(const Vector3& vec) const
{
    bool state = x != vec.x &&
                 y != vec.y &&
                 z != vec.z;

    return state;;
}