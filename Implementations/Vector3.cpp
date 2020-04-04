#include <Engine/Vector3.h>

using namespace TempestMath;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
Vector3::Vector3(void)
    :
    _data{0.0f, 0.0f, 0.0f}
{  }

Vector3::Vector3(real val)
    :
    _data{val, val, val}
{  }

Vector3::Vector3(real x, real y, real z)
    :
    _data{x, y, z}
{  }

Vector3::Vector3(const Vector3& v)
    :
    _data{v[x], v[y], v[z]}
{  }

Vector3::Vector3(const Vector4& v)
    :
    _data{v[x], v[y], v[z]}
{  }

Vector3::Vector3(const Point4& p)
    :
    _data{p[x], p[y], p[z]}
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
    return _data[x] * vec[x] +
           _data[y] * vec[y] +
           _data[z] * vec[z];
}

Vector3 Vector3::CrossProduct(const Vector3& vec) const
{
    return Vector3( _data[y] * vec[z] - _data[z] * vec[y],
                    _data[z] * vec[x] - _data[x] * vec[z],
                    _data[x] * vec[y] - _data[y] * vec[x] );
}

real Vector3::Magnitude(void)
{
    return real_sqrt(_data[x] * _data[x] + _data[y] * _data[y] + _data[z] * _data[z]);
}

real Vector3::SqrMagnitude(void)
{
    return _data[x] * _data[x] + _data[y] * _data[y] + _data[z] * _data[z];
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
    _data[x] = val;
    _data[y] = val;
    _data[z] = val;
}

//===== Math Helper Functions =====
void Vector3::AddScaledVector(const Vector3& vec, real scale)
{
    _data[x] += vec[x] * scale;
    _data[y] += vec[y] * scale;
    _data[z] += vec[z] * scale;
}

void Vector3::AddScaledVector(const Vector4& vec, real scale)
{
    _data[x] += vec[x] * scale;
    _data[y] += vec[y] * scale;
    _data[z] += vec[z] * scale;
}

void Vector3::AddScaledVector(const Point4& point, real scale)
{
    _data[x] += point[x] * scale;
    _data[y] += point[y] * scale;
    _data[z] += point[z] * scale;
}
//==========================================================================================================================
//
//Operator overloads
//
//==========================================================================================================================
//===== Copy Assignment =====		
Vector3& Vector3::operator=(const Vector3& vec)
{
    _data[x] = vec[x];
    _data[y] = vec[y];
    _data[z] = vec[z];

    return *this;
}

Vector3& Vector3::operator=(real val)
{
    _data[x] = val;
    _data[y] = val;
    _data[z] = val;

    return *this;
}

//===== Add by Vector3 =====
Vector3 Vector3::operator+(const Vector3& vec) const
{
    return Vector3(_data[x] + vec[x],
                   _data[y] + vec[y],
                   _data[z] + vec[z]);
}

Vector3& Vector3::operator+=(const Vector3& vec)
{
    _data[x] += vec[x];
    _data[y] += vec[y];
    _data[z] += vec[z];

    return *this;
}

Vector3 Vector3::operator+(shared_ptr<Vector3> vec) const
{
    const real* vals = vec->GetElems();

    return Vector3( _data[x] + vals[x],
                    _data[y] + vals[y],
                    _data[z] + vals[z] );
}

//===== Add by scalar =====
Vector3 Vector3::operator+(real val) const
{
    return Vector3( _data[x] + val,
                    _data[y] + val,
                    _data[z] + val );
}

Vector3& Vector3::operator+=(real val)
{
    _data[x] += val;
    _data[y] += val;
    _data[z] += val;

    return *this;
}

//===== Subtract by Vector3 =====
Vector3 Vector3::operator-(const Vector3& vec) const
{
    return Vector3( _data[x] - vec[x],
                    _data[y] - vec[y],
                    _data[z] - vec[z] );
}

Vector3& Vector3::operator-=(const Vector3& vec)
{
    _data[x] -= vec[x];
    _data[y] -= vec[y];
    _data[z] -= vec[z];

    return *this;
}

//===== Subtract by scalar =====
Vector3 Vector3::operator-(real val) const
{
    return Vector3( _data[x] - val,
                    _data[y] - val,
                    _data[z] - val );
}

Vector3& Vector3::operator-=(real val)
{
    _data[x] -= val;
    _data[y] -= val;
    _data[z] -= val;

    return *this;
}

//===== Component-wise multiply by Vector3 =====
Vector3 Vector3::operator*(const Vector3 vec) const
{
    return Vector3( _data[x] * vec[x],
                    _data[y] * vec[y],
                    _data[z] * vec[z] );
}

Vector3& Vector3::operator*=(const Vector3 vec)
{
    _data[x] *= vec[x];
    _data[y] *= vec[y];
    _data[z] *= vec[z];

    return *this;
}

//===== Mutliply by Scalar =====
Vector3 Vector3::operator*(real val) const
{
    return Vector3( _data[x] * val,
                    _data[y] * val,
                    _data[z] * val );
}

Vector3& Vector3::operator*=(real val)
{
    _data[x] *= val;
    _data[y] *= val;
    _data[z] *= val;

    return *this;
}

//===== Divide by scalar =====
Vector3 Vector3::operator/(real val) const
{
    assert(val != 0.0f);
    return Vector3( _data[x] / val,
                    _data[y] / val,
                    _data[z] / val );
}

Vector3& Vector3::operator/=(real val)
{
    assert(val != 0.0f);

    _data[x] /= val;
    _data[y] /= val;
    _data[z] /= val;

    return *this;
}

//===== Comparison =====
bool Vector3::operator>(const Vector3& vec) const
{
    bool state = _data[x] > vec[x] && 
                 _data[y] > vec[y] &&
                 _data[z] > vec[z];

    return state;
}

bool Vector3::operator<(const Vector3& vec) const
{
    bool state = _data[x] < vec[x] &&
                 _data[y] < vec[y] &&
                 _data[z] < vec[z];

    return state;;
}

bool Vector3::operator>=(const Vector3& vec) const
{
    bool state = _data[x] >= vec[x] &&
                 _data[y] >= vec[y] &&
                 _data[z] >= vec[z];

    return state;
}

bool Vector3::operator<=(const Vector3& vec) const
{
    bool state = _data[x] <= vec[x] &&
                 _data[y] <= vec[y] &&
                 _data[z] <= vec[z];

    return state;
}

bool Vector3::operator==(const Vector3& vec) const
{
    bool state = _data[x] == vec[x] &&
                 _data[y] == vec[y] &&
                 _data[z] == vec[z];

    return state;
}

bool Vector3::operator!=(const Vector3& vec) const
{
    bool state = _data[x] != vec[x] &&
                 _data[y] != vec[y] &&
                 _data[z] != vec[z];

    return state;;
}