#include "stdafx.h"
#include <Engine/Point2.h>

using namespace TempestMath;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
Point2::Point2(void)
    :
    x(0.0f), 
    y(0.0f)
{  }

Point2::Point2(real val)
    :
    x(0.0f), 
    y(0.0f)
{  }

Point2::Point2(real xVal, real yVal)
    :
    x(xVal),
    y(yVal)
{  }

Point2::Point2(const Point2& p)
    :
    x(p.x),
    y(p.y)
{  }

Point2::Point2(const Vector3& v)
    :
    x(v.x),
    y(v.y)
{  }

Point2::Point2(const Vector4& v)
    :
    x(v.x),
    y(v.y)
{  }

Point2::~Point2(void)
{  }

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
//===== Point Special functions =====
real Point2::Dot(const Point2& point) const
{
    return x * point.x +
           y * point.y;
}

real Point2::Magnitude(void)
{
    real totals = (x * x) + (y * y);
    return real_sqrt(totals);
}

real Point2::SqrMagnitude(void)
{
    return (x * x) + (y * y);
}

void Point2::Normalize(void)
{
    real mag = Magnitude();

    if(mag > 0 && mag != 1.0f)
    {
        (*this) *= 1 / mag;
    }
}

void Point2::Reset(real val)
{
    x = val;
    y = val;
}

real Point2::Distance(const Point2& p) const
{
    Point2 length = *this - p;
    return length.Magnitude();
}

real Point2::DistanceSquared(const Point2& p) const
{
    Point2 length = *this - p;
    return length.SqrMagnitude();
}

real Point2::DistanceSquared(const Vector3& v) const
{
    Point2 length = *this - v;
    return length.SqrMagnitude();
}

real Point2::DistanceSquared(const Vector4& v) const
{
    Point2 length = *this - v;
    return length.SqrMagnitude();
}

//==========================================================================================================================
//
//Operator overloads
//
//==========================================================================================================================
//===== Copy Assignment =====		
Point2& Point2::operator=(const Point2& point)
{
    x = point.x;
    y = point.y;

    return *this;
}

Point2& Point2::operator=(real val)
{
    x = val;
    y = val;

    return *this;
}

//===== Add by Point =====
Point2 Point2::operator+(const Point2& point) const
{
    return Point2(x + point.x,
                  y + point.y);
}

Point2 Point2::operator+(const Vector4& vec) const
{
    return Point2(x + vec.x,
                  y + vec.y);
}

Point2& Point2::operator+=(const Point2& point)
{
    x += point.x;
    y += point.y;

    return *this;
}

Point2& Point2::operator+=(const Vector4& vec)
{
    x += vec.x;
    y += vec.y;

    return *this;
}

Point2 Point2::operator+(const Vector3& vec) const
{
   return Point2(x + vec.x,
                 y + vec.y);
}

Point2& Point2::operator+=(const Vector3& vec)
{
    x += vec.x;
    y += vec.y;

    return *this;
}

Point2& Point2::operator+=(const Vector2& vec)
{
    x += vec.x;
    y += vec.y;

    return *this;
}

Point2 Point2::operator+(p_Point2 point) const
{
    return Point2(x + point->x,
                  y + point->y);
}

//===== Add by scalar =====
Point2 Point2::operator+(real val) const
{
    return Point2(x + val,
                  y + val);
}

Point2& Point2::operator+=(real val)
{
    x += val;
    y += val;

    return *this;
}

//===== Subtract by Point =====
Point2 Point2::operator-(const Point2& point) const
{
    return Point2(x - point.x,
                  y - point.y);
}

Point2 Point2::operator-(const Point3& point) const
{
    return Point2(x - point.x,
                  y - point.y);
}

Point2 Point2::operator-(const Point4& point) const
{
    return Point2(x - point.x,
                  y - point.y);
}

Point2 Point2::operator-(const Vector2& vec) const
{
    return Point2(x - vec.x,
                  y - vec.y);
}

Point2 Point2::operator-(const Vector3& vec) const
{
    return Point2(x - vec.x,
                  y - vec.y);
}

Point2 Point2::operator-(const Vector4& vec) const
{
    return Point2(x - vec.x,
                  y - vec.y);
}

Point2& Point2::operator-=(const Point2& point)
{
    x -= point.x;
    y -= point.y;

    return *this;
}

//===== Subtract by scalar =====
Point2 Point2::operator-(real val) const
{
    return Point2(x - val,
                  y - val);
}

Point2& Point2::operator-=(real val)
{
    x -= val;
    y -= val;
    
    return *this;
}

//===== Component-wise multiply by Point =====
Point2 Point2::operator*(const Point2 point) const
{
    return Point2(x * point.x,
                  y * point.y);
}

Point2& Point2::operator*=(const Point2 point)
{
    x *= point.x;
    y *= point.y;

    return *this;
}

//===== Mutliply by Scalar =====
Point2 Point2::operator*(real val) const
{
    return Point2(x * val,
                  y * val);
}

Point2& Point2::operator*=(real val)
{
    x *= val;
    y *= val;

    return *this;
}

//===== Divide by scalar =====
Point2 Point2::operator/(real val) const
{
    assert(val != 0.0f);

    return Point2(x / val,
                  y / val);
}

Point2& Point2::operator/=(real val)
{
    assert(val != 0.0f);

    x /= val;
    y /= val;
    
    return *this;
}

//===== Comparison =====
bool Point2::operator>(const Point2& point) const
{
    bool state = x > point.x && 
                 y > point.y;
    
    return state;
}

bool Point2::operator<(const Point2& point) const
{
    bool state = x < point.x && 
                 y < point.y;
    
    return state;
}

bool Point2::operator>=(const Point2& point) const
{
    bool state = x >= point.x && 
                 y >= point.y;
    
    return state;
}

bool Point2::operator<=(const Point2& point) const
{
    bool state = x <= point.x && 
                 y <= point.y;
    
    return state;
}

bool Point2::operator==(const Point2& point) const
{
    bool state = x == point.x && 
                 y == point.y;
    
    return state;
}

bool Point2::operator!=(const Point2& point) const
{
    bool state = x != point.x && 
                 y != point.y;
    
    return state;
}