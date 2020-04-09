#include <Engine/Vector3.h>

using namespace TempestMath;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
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

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
//===== Vector3 Special functions =====
real Vector3::Dot(const Vector3& vec) const
{
    return x * vec.x +
           y * vec.y +
           z * vec.z;
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

//===== Math Helper Functions =====
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
//==========================================================================================================================
//
//Operator overloads
//
//==========================================================================================================================
//===== Copy Assignment =====		
Vector3& Vector3::operator=(const Vector3& vec)
{
    x = vec.x;
    y = vec.y;
    z = vec.z;

    return *this;
}

Vector3& Vector3::operator=(real val)
{
    x = val;
    y = val;
    z = val;

    return *this;
}

//===== Add by Vector3 =====
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

//===== Add by scalar =====
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

//===== Subtract by Vector3 =====
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

//===== Subtract by scalar =====
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

//===== Component-wise multiply by Vector3 =====
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

//===== Mutliply by Scalar =====
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

//===== Divide by scalar =====
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

//===== Comparison =====
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