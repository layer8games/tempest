#include <Engine/Vector4.h>

using namespace TempestMath;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
Vector4::Vector4(void)
    :
    x(0.0f), 
    y(0.0f), 
    z(0.0f),
    w(0.0f)
{  }

Vector4::Vector4(real val)
    :
    x(val), 
    y(val), 
    z(val),
    w(0.0f)
{  }


Vector4::Vector4(real xVal, real yVal, real zVal, real wVal)
    :
    x(xVal), 
    y(yVal), 
    z(zVal),
    w(wVal)
{  }

Vector4::Vector4(const Vector4& v)
    :
    x(v.x), 
    y(v.y), 
    z(v.z),
    w(v.w)
{  }

Vector4::Vector4(const Point4& p)
    :
    x(p.x), 
    y(p.y), 
    z(p.z),
    w(0.0f)
{  }

Vector4::~Vector4(void)
{  }

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
//===== Vector4 Special functions =====
real Vector4::Dot(const Vector4& vec) const
{
    return x * vec.x +
           y * vec.y +
           z * vec.z;
}

real Vector4::Dot(const Point4& point) const
{
    return x * point.x +
           y * point.y +
           z * point.z;
}

real Vector4::Dot(const Point3& point) const
{
    return x * point.x +
           y * point.y +
           z * point.z;
}

Vector4 Vector4::CrossProduct(const Vector4& vec) const
{
    return Vector4(y * vec.z - z * vec.y,
                   z * vec.x - x * vec.z,
                   x * vec.y - y * vec.x,
                   0.0f);
}

real Vector4::Magnitude(void)
{
    return real_sqrt(x * x + y * y + z * z);
}

real Vector4::SqrMagnitude(void)
{
    return x * x + y * y + z * z;
}

void Vector4::Normalize(void)
{
    real mag = Magnitude();

    if(mag > 0 && mag != 1.0f)
    {
        (*this) *= 1 / mag;
    }
}

void Vector4::Reset(real val)
{
    x = val;
    y = val;
    z = val;
    w = 0.0f;
}

//===== Math Helper Functions =====
void Vector4::AddScaledVector(const Vector4& vec, real scale)
{
    x += vec.x * scale;
    y += vec.y * scale;
    z += vec.z * scale;
}

void Vector4::AddScaledVector(const Vector3& vec, real scale)
{
    x += vec.x * scale;
    y += vec.y * scale;
    z += vec.z * scale;
}

void Vector4::AddScaledPoint(const Point4& point, real scale)
{
    x += point.x * scale;
    y += point.y * scale;
    z += point.z * scale;
}
//==========================================================================================================================
//
//Operator overloads
//
//==========================================================================================================================
//===== Copy Assignment =====		
Vector4& Vector4::operator=(const Vector4& vec)
{
    x = vec.x;
    y = vec.y;
    z = vec.z;
    w = vec.w;

    return *this;
}

Vector4& Vector4::operator=(const Point4& point)
{
    x = point.x;
    y = point.y;
    z = point.z;
    w = 0.0f;

    return *this;
}

Vector4& Vector4::operator=(const Vector3& vec)
{
    x = vec.x;
    y = vec.y;
    z = vec.z;
    w = 0.0f;

    return *this;
}

Vector4& Vector4::operator=(real val)
{
    x = val;
    y = val;
    z = val;

    return *this;
}

//===== Add by Vector4 =====
Vector4 Vector4::operator+(const Vector4& vec) const
{
    return Vector4(x + vec.x,
                   y + vec.y,
                   z + vec.z,
                   0.0f);
}

Vector4& Vector4::operator+=(const Vector4& vec)
{
    x += vec.x;
    y += vec.y;
    z += vec.z;

    return *this;
}

Vector4 Vector4::operator+(const Vector3& vec) const
{
    return Vector4(x + vec.x,
                   y + vec.y,
                   z + vec.z,
                   0.0f);
}

Vector4& Vector4::operator+=(const Point3& point)
{
    x += point.x;
    y += point.y;
    z += point.z;

    return *this;
}

Vector4& Vector4::operator+=(const Point4& point)
{
    x += point.x;
    y += point.y;
    z += point.z;

    return *this;
}

Vector4 Vector4::operator+(const Point3& point) const
{
    return Vector4(x + point.x,
                   y + point.y,
                   z + point.z,
                   0.0f);
}

Vector4 Vector4::operator+(const Point4& point) const
{
    return Vector4(x + point.x,
                   y + point.y,
                   z + point.z,
                   0.0f);
}

Vector4& Vector4::operator+=(const Vector3& vec)
{
    x += vec.x;
    y += vec.y;
    z += vec.z;

    return *this;
}

//===== Add by scalar =====
Vector4 Vector4::operator+(real val) const
{
    return Vector4(x + val,
                   y + val,
                   z + val,
                   0.0f);
}

Vector4& Vector4::operator+=(real val)
{
    x += val;
    y += val;
    z += val;

    return *this;
}

//===== Subtract by Vector4 =====
Vector4 Vector4::operator-(const Vector4& vec) const
{
    return Vector4(x - vec.x,
                   y - vec.y,
                   z - vec.z,
                   0.0f);
}

Vector4& Vector4::operator-=(const Vector4& vec)
{
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;

    return *this;
}

Vector4 Vector4::operator-(const Vector3& vec) const
{
    return Vector4(x - vec.x,
                   y - vec.y,
                   z - vec.z,
                   0.0f);
}

Vector4& Vector4::operator-=(const Vector3& vec)
{
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;

    return *this;
}

Vector4 Vector4::operator-(const Point3& point) const
{
    return Vector4(x - point.x,
                   y - point.y,
                   z - point.z,
                   0.0f);
}

Vector4 Vector4::operator-(const Point4& point) const
{
    return Vector4(x - point.x,
                   y - point.y,
                   z - point.z,
                   0.0f);
}

Vector4& Vector4::operator-=(const Point3& point)
{
    x -= point.x;
    y -= point.y;
    z -= point.z;

    return *this;
}

Vector4& Vector4::operator-=(const Point4& point)
{
    x -= point.x;
    y -= point.y;
    z -= point.z;

    return *this;
}

//===== Subtract by scalar =====
Vector4 Vector4::operator-(real val) const
{
    return Vector4(x - val,
                   y - val,
                   z - val,
                   0.0f);
}

Vector4& Vector4::operator-=(real val)
{
    x -= val;
    y -= val;
    z -= val;

    return *this;
}

//===== Component-wise multiply by Vector4 =====
Vector4 Vector4::operator*(const Vector4 vec) const
{
    return Vector4(x * vec.x,
                   y * vec.y,
                   z * vec.z,
                   0.0f);
}

Vector4& Vector4::operator*=(const Vector4 vec)
{
    x *= vec.x;
    y *= vec.y;
    z *= vec.z;

    return *this;
}

//===== Mutliply by Scalar =====
Vector4 Vector4::operator*(real val) const
{
    return Vector4(x * val,
                   y * val,
                   z * val,
                   0.0f);
}

Vector4& Vector4::operator*=(real val)
{
    x *= val;
    y *= val;
    z *= val;

    return *this;
}

//===== Divide by scalar =====
Vector4 Vector4::operator/(real val) const
{
    assert(val != 0.0f);

    return Vector4(x / val,
                   y / val,
                   z / val,
                   0.0f);
}

Vector4& Vector4::operator/=(real val)
{
    assert(val != 0.0f);

    x /= val;
    y /= val;
    z /= val;

    return *this;
}

//===== Comparison =====
bool Vector4::operator>(const Vector4& vec) const
{
    bool state = x > vec.x && 
                 y > vec.y &&
                 z > vec.z &&
                 w >= vec.w;
    
    return state;
}

bool Vector4::operator<(const Vector4& vec) const
{
    bool state = x < vec.x && 
                 y < vec.y &&
                 z < vec.z &&
                 w <= vec.w;
    
    return state;
}

bool Vector4::operator>=(const Vector4& vec) const
{
   bool state = x >= vec.x && 
                y >= vec.y &&
                z >= vec.z &&
                w >= vec.w;
    
    return state;
}

bool Vector4::operator<=(const Vector4& vec) const
{
   bool state = x <= vec.x && 
                y <= vec.y &&
                z <= vec.z &&
                w <= vec.w;
    
    return state;
}

bool Vector4::operator==(const Vector4& vec) const
{
   bool state = x == vec.x && 
                y == vec.y &&
                z == vec.z &&
                w == vec.w;
    
    return state;
}

bool Vector4::operator!=(const Vector4& vec) const
{
    bool state = x != vec.x && 
                 y != vec.y &&
                 z != vec.z &&
                 w != vec.w;
    
    return state;
}