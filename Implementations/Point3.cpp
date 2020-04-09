#include <Engine/Point3.h>

using namespace TempestMath;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
Point3::Point3(void)
    :
    x(0.0f), 
    y(0.0f),
    z(0.0f)
{  }

Point3::Point3(real val)
    :
    x(val),
    y(val),
    z(val)
{  }

Point3::Point3(real xVal, real yVal, real zVal)
    :
    x(xVal),
    y(yVal),
    z(zVal)
{  }

Point3::Point3(const Point3& v)
    :
    x(v.x),
    y(v.y),
    z(v.z)
{  }

Point3::Point3(const Vector3& v)
    :
    x(v.x),
    y(v.y),
    z(v.z)
{  }

Point3::Point3(const Vector4& v)
    :
    x(v.x),
    y(v.y),
    z(v.z)
{  }

Point3::~Point3(void)
{  }

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
//===== Point Special functions =====
real Point3::Dot(const Point3& point) const
{
    return x * point.x +
           y * point.y +
           z * point.z;
}

Point3 Point3::CrossProduct(const Point3& point) const
{
    return Point3(y * point.z - z * point.y,
                  z * point.x - x * point.z,
                  x * point.y - y * point.x);
}

real Point3::Magnitude(void)
{
    real totals = (x * x) + (y * y) + (z * z);
    return real_sqrt(totals);
}

real Point3::SqrMagnitude(void)
{
    return (x * x) + (y * y) + (z * z);
}

void Point3::Normalize(void)
{
    real mag = Magnitude();

    if(mag > 0 && mag != 1.0f)
    {
        (*this) *= 1 / mag;
    }
}

void Point3::Reset(real val)
{
    x = val;
    y = val;
    z = val;
}

real Point3::Distance(const Point3& p) const
{
    Point3 length = *this - p;
    return length.Magnitude();
}

real Point3::DistanceSquared(const Point3& p) const
{
    Point3 length = *this - p;
    return length.SqrMagnitude();
}

real Point3::DistanceSquared(const Vector3& v) const
{
    Point3 length = *this - v;
    return length.SqrMagnitude();
}

real Point3::DistanceSquared(const Vector4& v) const
{
    Point3 length = *this - v;
    return length.SqrMagnitude();
}

//===== Math Helper Functions =====
void Point3::AddScaledPoint(const Point3& point, real scale)
{
    x += point.x * scale;
    y += point.y * scale;
    z += point.z * scale;
}

void Point3::AddScaledVector(const Vector3& vec, real scale)
{
    x += vec.x * scale;
    y += vec.y * scale;
    z += vec.z * scale;	
}

void Point3::AddScaledVector(const Vector4& vec, real scale)
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
Point3& Point3::operator=(const Point2& point)
{
    x = point.x;
    y = point.y;
    z = 0.0f;

    return *this;
}

Point3& Point3::operator=(const Point3& point)
{
    x = point.x;
    y = point.y;
    z = point.z;

    return *this;
}

Point3& Point3::operator=(real val)
{
    x = val;
    y = val;
    z = val;

    return *this;
}

//===== Add by Point =====
Point3 Point3::operator+(const Point3& point) const
{
    return Point3(x + point.x,
                 y + point.y,
                 z + point.z);
}

Point3 Point3::operator+(const Vector4& vec) const
{
    return Point3(x + vec.x,
                  y + vec.y,
                  z + vec.z);
}

Point3& Point3::operator+=(const Point3& point)
{
    x += point.x;
    y += point.y;
    z += point.z;

    return *this;
}

Point3& Point3::operator+=(const Vector4& vec)
{
    x += vec.x;
    y += vec.y;
    z += vec.z;

    return *this;
}

Point3 Point3::operator+(const Vector3& vec) const
{
   return Point3(x + vec.x,
                 y + vec.y,
                 z + vec.z);
}

Point3& Point3::operator+=(const Vector3& vec)
{
    x += vec.x;
    y += vec.y;
    z += vec.z;

    return *this;
}

Point3 Point3::operator+(shared_ptr<Point3> point) const
{
    return Point3(x + point->x,
                  y + point->y,
                  z + point->z);
}

//===== Add by scalar =====
Point3 Point3::operator+(real val) const
{
    return Point3(x + val,
                  y + val,
                  z + val);
}

Point3& Point3::operator+=(real val)
{
    x += val;
    y += val;
    z += val;

    return *this;
}

//===== Subtract by Point =====
Point3 Point3::operator-(const Point3& point) const
{
    return Point3(x - point.x,
                  y - point.y,
                  z - point.z);
}

Point3 Point3::operator-(const Vector3& vec) const
{
    return Point3(x - vec.x,
                  y - vec.y,
                  z - vec.z);
}

Point3 Point3::operator-(const Vector4& vec) const
{
    return Point3(x - vec.x,
                  y - vec.y,
                  z - vec.z);
}

Point3& Point3::operator-=(const Point3& point)
{
    x -= point.x;
    y -= point.y;
    z -= point.z;

    return *this;
}

//===== Subtract by scalar =====
Point3 Point3::operator-(real val) const
{
    return Point3(x - val,
                  y - val,
                  z - val);
}

Point3& Point3::operator-=(real val)
{
    x -= val;
    y -= val;
    z -= val;
    
    return *this;
}

//===== Component-wise multiply by Point =====
Point3 Point3::operator*(const Point3 point) const
{
    return Point3(x * point.x,
                  y * point.y,
                  z * point.z);
}

Point3& Point3::operator*=(const Point3 point)
{
    x *= point.x;
    y *= point.y;
    z *= point.z;

    return *this;
}

//===== Mutliply by Scalar =====
Point3 Point3::operator*(real val) const
{
    return Point3(x * val,
                  y * val,
                  z * val);
}

Point3& Point3::operator*=(real val)
{
    x *= val;
    y *= val;
    z *= val;

    return *this;
}

//===== Divide by scalar =====
Point3 Point3::operator/(real val) const
{
    assert(val != 0.0f);

    return Point3(x / val,
                  y / val,
                  z / val);
}

Point3& Point3::operator/=(real val)
{
    assert(val != 0.0f);

    x /= val;
    y /= val;
    z /= val;
    
    return *this;
}

//===== Comparison =====
bool Point3::operator>(const Point3& point) const
{
    bool state = x > point.x && 
                 y > point.y &&
                 z > point.z;
    
    return state;
}

bool Point3::operator<(const Point3& point) const
{
    bool state = x < point.x && 
                 y < point.y &&
                 z < point.z;
    
    return state;
}

bool Point3::operator>=(const Point3& point) const
{
    bool state = x >= point.x && 
                 y >= point.y &&
                 z >= point.z;
    
    return state;
}

bool Point3::operator<=(const Point3& point) const
{
    bool state = x <= point.x && 
                 y <= point.y &&
                 z <= point.z;
    
    return state;
}

bool Point3::operator==(const Point3& point) const
{
    bool state = x == point.x && 
                 y == point.y &&
                 z == point.z;
    
    return state;
}

bool Point3::operator!=(const Point3& point) const
{
    bool state = x != point.x && 
                 y != point.y &&
                 z != point.z;
    
    return state;
}