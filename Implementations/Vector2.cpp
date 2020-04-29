#include "stdafx.h"
#include <Engine/Vector2.h>
using namespace TempestMath;

Vector2::Vector2(void)
    :
    x(0.0f),
    y(0.0f)
{  }

Vector2::Vector2(real val)
    :
    x(val),
    y(val)
{  }

Vector2::Vector2(real xVal, real yVal)
    :
    x(xVal),
    y(yVal)
{  }

Vector2::Vector2(const Vector2& otherVec)
    :
    x(otherVec.x),
    y(otherVec.y)
{  }

Vector2::Vector2(const Vector3& otherVec)
    :
    x(otherVec.x),
    y(otherVec.y)
{  }

Vector2::Vector2(const Vector4& otherVec)
    :
    x(otherVec.x),
    y(otherVec.y)
{  }

Vector2::Vector2(const Point2& otherVec)
    :
    x(otherVec.x),
    y(otherVec.y)
{  }

Vector2::Vector2(const Point4& otherVec)
    :
    x(otherVec.x),
    y(otherVec.y)
{  }

Vector2::~Vector2(void)
{  }

real Vector2::Dot(const Vector2& otherVec) const
{
    return x * otherVec.x +
           y * otherVec.y;
}

real Vector2::Magnitude(void) const
{
    return real_sqrt(x * x + y * y);
}

real Vector2::SqrMagnitude(void) const
{
    return x * x + y * y;
}

void Vector2::Normalize(void)
{
    real mag = Magnitude();

    if(mag > 0 && mag != 1.0f)
    {
        (*this) *= 1 / mag;
    }
}

void Vector2::Reset(real val)
{
    x = val;
    y = val;
}

Vector2 Vector2::Perpendicular(void)
{
    return Vector2(-y, x);
}

Vector2& Vector2::operator=(const Vector2& otherVec)
{
    x = otherVec.x;
    y = otherVec.y;

    return *this;
}

Vector2& Vector2::operator=(real val)
{
    x = val;
    y = val;

    return *this;
}

Vector2& Vector2::operator=(const Point2& point)
{
    x = point.x;
    y = point.y;

    return *this;
}

Vector2 Vector2::operator+(const Vector2& otherVec) const
{
    return Vector2(x + otherVec.x,
                   y + otherVec.y);
}

Vector2& Vector2::operator+=(const Vector2& otherVec)
{
    x += otherVec.x;
    y += otherVec.y;

    return *this;
}

Vector2 Vector2::operator+(shared_ptr<Vector2> otherVec) const
{
    return Vector2(x + otherVec->x,
                   y + otherVec->y);
}

Vector2 Vector2::operator+(real val) const
{
    return Vector2(x + val,
                   y + val);
}

Vector2& Vector2::operator+=(real val)
{
    x += val;
    y += val;

    return *this;
}

Vector2 Vector2::operator-(const Point2& otherVec) const
{
    return Vector2(x - otherVec.x,
                   y - otherVec.y);
}

Vector2 Vector2::operator-(const Point3& otherVec) const
{
    return Vector2(x - otherVec.x,
                   y - otherVec.y);
}

Vector2 Vector2::operator-(const Point4& otherVec) const
{
    return Vector2(x - otherVec.x,
                   y - otherVec.y);
}

Vector2 Vector2::operator-(const Vector2& otherVec) const
{
    return Vector2(x - otherVec.x,
                   y - otherVec.y);
}

Vector2 Vector2::operator-(const Vector3& otherVec) const
{
    return Vector2(x - otherVec.x,
                   y - otherVec.y);
}

Vector2 Vector2::operator-(const Vector4& otherVec) const
{
    return Vector2(x - otherVec.x,
                   y - otherVec.y);
}

Vector2& Vector2::operator-=(const Vector2& otherVec)
{
    x -= otherVec.x;
    y -= otherVec.y;

    return *this;
}

Vector2& Vector2::operator-=(const Point2& otherVec)
{
    x -= otherVec.x;
    y -= otherVec.y;

    return *this;
}

Vector2& Vector2::operator-=(const Point3& otherVec)
{
    x -= otherVec.x;
    y -= otherVec.y;

    return *this;
}

Vector2 Vector2::operator-(real val) const
{
    return Vector2(x - val,
                   y - val);
}

Vector2& Vector2::operator-=(real val)
{
    x -= val;
    y -= val;

    return *this;
}

Vector2 Vector2::operator*(const Vector2& otherVec) const
{
    return Vector2(x * otherVec.x,
                   y * otherVec.y);
}

Vector2& Vector2::operator*=(const Vector2& otherVec)
{
    x *= otherVec.x;
    y *= otherVec.y;

    return *this;
}

Vector2 Vector2::operator*(real val) const
{
    return Vector2(x * val,
                   y * val);
}

Vector2& Vector2::operator*=(real val)
{
    x *= val;
    y *= val;

    return *this;
}

Vector2 Vector2::operator/(real val) const
{
    assert(val != 0.0f);
    return Vector2(x / val,
                   y / val);
}

Vector2& Vector2::operator/=(real val)
{
    assert(val != 0.0f);

    x /= val;
    y /= val;

    return *this;
}

bool Vector2::operator>(const Vector2& otherVec) const
{
    bool state = x > otherVec.x && 
                 y > otherVec.y;

    return state;
}

bool Vector2::operator<(const Vector2& otherVec) const
{
    bool state = x < otherVec.x &&
                 y < otherVec.y;

    return state;;
}

bool Vector2::operator>=(const Vector2& otherVec) const
{
    bool state = x >= otherVec.x &&
                 y >= otherVec.y;

    return state;
}

bool Vector2::operator<=(const Vector2& otherVec) const
{
    bool state = x <= otherVec.x &&
                 y <= otherVec.y;

    return state;
}

bool Vector2::operator==(const Vector2& otherVec) const
{
    bool state = x == otherVec.x &&
                 y == otherVec.y;

    return state;
}

bool Vector2::operator!=(const Vector2& otherVec) const
{
    bool state = x != otherVec.x &&
                 y != otherVec.y;

    return state;;
}