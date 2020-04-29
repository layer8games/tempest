#include "stdafx.h"
#include <Engine/Point4.h>

using namespace TempestMath;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
Point4::Point4(void)
    :
    x(0.0f), 
    y(0.0f),
    z(0.0f),
    w(0.0f)
{  }

Point4::Point4(real val)
    :
    x(val),
    y(val),
    z(val),
    w(1.0f)
{  }

Point4::Point4(real xVal, real yVal, real zVal, real wVal)
    :
    x(xVal),
    y(yVal),
    z(zVal),
    w(wVal)
{  }

Point4::Point4(const Point4& p)
    :
    x(p.x),
    y(p.y),
    z(p.z),
    w(p.w)
{  }

Point4::Point4(const Vector3& v)
    :
    x(v.x),
    y(v.y),
    z(v.z),
    w(1.0f)
{  }

Point4::Point4(const Vector4& v)
    :
    x(v.x),
    y(v.y),
    z(v.z),
    w(1.0f)
{  }

Point4::~Point4(void)
{  }

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
//===== Point Special functions =====
real Point4::Dot(const Point4& point) const
{
    return x * point.x +
           y * point.y +
           z * point.z;
}

Point4 Point4::CrossProduct(const Point4& point) const
{
    return Point4(y * point.z - z * point.y,
                  z * point.x - x * point.z,
                  x * point.y - y * point.x,
                  1.0f);
}

real Point4::Magnitude(void)
{
    real totals = (x * x) + (y * y) + (z * z);
    return real_sqrt(totals);
}

real Point4::SqrMagnitude(void)
{
    return (x * x) + (y * y) + (z * z);
}

void Point4::Normalize(void)
{
    real mag = Magnitude();

    if(mag > 0 && mag != 1.0f)
    {
        (*this) *= 1 / mag;
    }
}

void Point4::Reset(real val)
{
    x = val;
    y = val;
    z = val;
    w = 1.0f;
}

real Point4::Distance(const Point4& p) const
{
    Point4 length = *this - p;
    return length.Magnitude();
}

real Point4::DistanceSquared(const Point4& p) const
{
    Point4 length = *this - p;
    return length.SqrMagnitude();
}

real Point4::DistanceSquared(const Vector3& v) const
{
    Point4 length = *this - v;
    return length.SqrMagnitude();
}

real Point4::DistanceSquared(const Vector4& v) const
{
    Point4 length = *this - v;
    return length.SqrMagnitude();
}

//===== Math Helper Functions =====
void Point4::AddScaledPoint(const Point4& point, real scale)
{
    x += point.x * scale;
    y += point.y * scale;
    z += point.z * scale;
}

void Point4::AddScaledVector(const Vector3& vec, real scale)
{
    x += vec.x * scale;
    y += vec.y * scale;
    z += vec.z * scale;	
}

void Point4::AddScaledVector(const Vector4& vec, real scale)
{
    x += vec.x * scale;
    y += vec.y * scale;
    z += vec.z * scale;
}
//==========================================================================================================================
//
//Operator overloads
//
//==========================================================================================================================
//===== Copy Assignment =====		
Point4& Point4::operator=(const Point4& point)
{
    x = point.x;
    y = point.y;
    z = point.z;
    w = point.w;

    return *this;
}

Point4& Point4::operator=(real val)
{
    x = val;
    y = val;
    z = val;

    return *this;
}

//===== Add by Point =====
Point4 Point4::operator+(const Point4& point) const
{
    return Point4(x + point.x,
                 y + point.y,
                 z + point.z,
                 1.0f);
}

Point4 Point4::operator+(const Vector4& vec) const
{
    return Point4(x + vec.x,
                  y + vec.y,
                  z + vec.z,
                  1.0f);
}

Point4& Point4::operator+=(const Point4& point)
{
    x += point.x;
    y += point.y;
    z += point.z;

    return *this;
}

Point4& Point4::operator+=(const Vector4& vec)
{
    x += vec.x;
    y += vec.y;
    z += vec.z;

    return *this;
}

Point4 Point4::operator+(const Vector3& vec) const
{
   return Point4(x + vec.x,
                 y + vec.y,
                 z + vec.z,
                 1.0f);
}

Point4& Point4::operator+=(const Vector3& vec)
{
    x += vec.x;
    y += vec.y;
    z += vec.z;

    return *this;
}

Point4 Point4::operator+(p_Point4 point) const
{
    return Point4(x + point->x,
                  y + point->y,
                  z + point->z,
                  1.0f);
}

//===== Add by scalar =====
Point4 Point4::operator+(real val) const
{
    return Point4(x + val,
                  y + val,
                  z + val,
                  1.0f);
}

Point4& Point4::operator+=(real val)
{
    x += val;
    y += val;
    z += val;

    return *this;
}

//===== Subtract by Point =====
Point4 Point4::operator-(const Point4& point) const
{
    return Point4(x - point.x,
                  y - point.y,
                  z - point.z,
                  1.0f);
}

Point4 Point4::operator-(const Vector3& vec) const
{
    return Point4(x - vec.x,
                  y - vec.y,
                  z - vec.z,
                  1.0f);
}

Point4 Point4::operator-(const Vector4& vec) const
{
    return Point4(x - vec.x,
                  y - vec.y,
                  z - vec.z,
                  1.0f);
}

Point4& Point4::operator-=(const Point4& point)
{
    x -= point.x;
    y -= point.y;
    z -= point.z;

    return *this;
}

//===== Subtract by scalar =====
Point4 Point4::operator-(real val) const
{
    return Point4(x - val,
                  y - val,
                  z - val,
                  1.0f);
}

Point4& Point4::operator-=(real val)
{
    x -= val;
    y -= val;
    z -= val;
    
    return *this;
}

//===== Component-wise multiply by Point =====
Point4 Point4::operator*(const Point4 point) const
{
    return Point4(x * point.x,
                  y * point.y,
                  z * point.z,
                  1.0f);
}

Point4& Point4::operator*=(const Point4 point)
{
    x *= point.x;
    y *= point.y;
    z *= point.z;

    return *this;
}

//===== Mutliply by Scalar =====
Point4 Point4::operator*(real val) const
{
    return Point4(x * val,
                  y * val,
                  z * val,
                  1.0f);
}

Point4& Point4::operator*=(real val)
{
    x *= val;
    y *= val;
    z *= val;

    return *this;
}

//===== Divide by scalar =====
Point4 Point4::operator/(real val) const
{
    assert(val != 0.0f);

    return Point4(x / val,
                  y / val,
                  z / val,
                  1.0f);
}

Point4& Point4::operator/=(real val)
{
    assert(val != 0.0f);

    x /= val;
    y /= val;
    z /= val;
    
    return *this;
}

//===== Comparison =====
bool Point4::operator>(const Point4& point) const
{
    bool state = x > point.x && 
                 y > point.y &&
                 z > point.z &&
                 w >= point.w;
    
    return state;
}

bool Point4::operator<(const Point4& point) const
{
    bool state = x < point.x && 
                 y < point.y &&
                 z < point.z &&
                 w <= point.w;
    
    return state;
}

bool Point4::operator>=(const Point4& point) const
{
    bool state = x >= point.x && 
                 y >= point.y &&
                 z >= point.z &&
                 w >= point.w;
    
    return state;
}

bool Point4::operator<=(const Point4& point) const
{
    bool state = x <= point.x && 
                 y <= point.y &&
                 z <= point.z &&
                 w <= point.w;
    
    return state;
}

bool Point4::operator==(const Point4& point) const
{
    bool state = x == point.x && 
                 y == point.y &&
                 z == point.z &&
                 w == point.w;
    
    return state;
}

bool Point4::operator!=(const Point4& point) const
{
    bool state = x != point.x && 
                 y != point.y &&
                 z != point.z &&
                 w != point.w;
    
    return state;
}