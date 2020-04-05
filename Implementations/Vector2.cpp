#include <Engine/Vector2.h>

using namespace TempestMath;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
Vector2::Vector2(void)
    :
    _data{0.0f, 0.0f}
{  }

Vector2::Vector2(real val)
    :
    _data{val, val}
{  }

Vector2::Vector2(real x, real y)
    :
    _data{x, y}
{  }

Vector2::Vector2(const Vector2& v)
    :
    _data{v[x], v[y]}
{  }

Vector2::Vector2(const Vector4& v)
    :
    _data{v[x], v[y]}
{  }

Vector2::Vector2(const Point2& p)
    :
    _data{p[x], p[y]}
{  }

Vector2::Vector2(const Point4& p)
    :
    _data{p[x], p[y]}
{  }

Vector2::~Vector2(void)
{  }

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
//===== Vector2 Special functions =====
real Vector2::Dot(const Vector2& vec) const
{
    return _data[x] * vec[x] +
           _data[y] * vec[y];
}

real Vector2::Magnitude(void)
{
    return real_sqrt(_data[x] * _data[x] + _data[y] * _data[y]);
}

real Vector2::SqrMagnitude(void)
{
    return _data[x] * _data[x] + _data[y] * _data[y];
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
    _data[x] = val;
    _data[y] = val;
}

//===== Math Helper Functions =====
void Vector2::AddScaledVector(const Vector2& vec, real scale)
{
    _data[x] += vec[x] * scale;
    _data[y] += vec[y] * scale;
}

void Vector2::AddScaledVector(const Vector4& vec, real scale)
{
    _data[x] += vec[x] * scale;
    _data[y] += vec[y] * scale;
}

void Vector2::AddScaledVector(const Point4& point, real scale)
{
    _data[x] += point[x] * scale;
    _data[y] += point[y] * scale;
}
//==========================================================================================================================
//
//Operator overloads
//
//==========================================================================================================================
//===== Copy Assignment =====		
Vector2& Vector2::operator=(const Vector2& vec)
{
    _data[x] = vec[x];
    _data[y] = vec[y];

    return *this;
}

Vector2& Vector2::operator=(real val)
{
    _data[x] = val;
    _data[y] = val;

    return *this;
}

//===== Add by Vector2 =====
Vector2 Vector2::operator+(const Vector2& vec) const
{
    return Vector2(_data[x] + vec[x],
                   _data[y] + vec[y]);
}

Vector2& Vector2::operator+=(const Vector2& vec)
{
    _data[x] += vec[x];
    _data[y] += vec[y];

    return *this;
}

Vector2 Vector2::operator+(shared_ptr<Vector2> vec) const
{
    const real* vals = vec->GetElems();

    return Vector2(_data[x] + vals[x],
                   _data[y] + vals[y]);
}

//===== Add by scalar =====
Vector2 Vector2::operator+(real val) const
{
    return Vector2(_data[x] + val,
                   _data[y] + val);
}

Vector2& Vector2::operator+=(real val)
{
    _data[x] += val;
    _data[y] += val;

    return *this;
}

//===== Subtract by Vector2 =====
Vector2 Vector2::operator-(const Vector2& vec) const
{
    return Vector2(_data[x] - vec[x],
                   _data[y] - vec[y]);
}

Vector2& Vector2::operator-=(const Vector2& vec)
{
    _data[x] -= vec[x];
    _data[y] -= vec[y];

    return *this;
}

Vector2& Vector2::operator-=(const Point2& vec)
{
    _data[x] -= vec[x];
    _data[y] -= vec[y];

    return *this;
}

Vector2& Vector2::operator-=(const Point3& vec)
{
    _data[x] -= vec[x];
    _data[y] -= vec[y];

    return *this;
}

//===== Subtract by scalar =====
Vector2 Vector2::operator-(real val) const
{
    return Vector2(_data[x] - val,
                   _data[y] - val);
}

Vector2& Vector2::operator-=(real val)
{
    _data[x] -= val;
    _data[y] -= val;

    return *this;
}

//===== Component-wise multiply by Vector2 =====
Vector2 Vector2::operator*(const Vector2 vec) const
{
    return Vector2(_data[x] * vec[x],
                   _data[y] * vec[y]);
}

Vector2& Vector2::operator*=(const Vector2 vec)
{
    _data[x] *= vec[x];
    _data[y] *= vec[y];

    return *this;
}

//===== Mutliply by Scalar =====
Vector2 Vector2::operator*(real val) const
{
    return Vector2(_data[x] * val,
                   _data[y] * val);
}

Vector2& Vector2::operator*=(real val)
{
    _data[x] *= val;
    _data[y] *= val;

    return *this;
}

//===== Divide by scalar =====
Vector2 Vector2::operator/(real val) const
{
    assert(val != 0.0f);
    return Vector2(_data[x] / val,
                   _data[y] / val);
}

Vector2& Vector2::operator/=(real val)
{
    assert(val != 0.0f);

    _data[x] /= val;
    _data[y] /= val;

    return *this;
}

//===== Comparison =====
bool Vector2::operator>(const Vector2& vec) const
{
    bool state = _data[x] > vec[x] && 
                 _data[y] > vec[y];

    return state;
}

bool Vector2::operator<(const Vector2& vec) const
{
    bool state = _data[x] < vec[x] &&
                 _data[y] < vec[y];

    return state;;
}

bool Vector2::operator>=(const Vector2& vec) const
{
    bool state = _data[x] >= vec[x] &&
                 _data[y] >= vec[y];

    return state;
}

bool Vector2::operator<=(const Vector2& vec) const
{
    bool state = _data[x] <= vec[x] &&
                 _data[y] <= vec[y];

    return state;
}

bool Vector2::operator==(const Vector2& vec) const
{
    bool state = _data[x] == vec[x] &&
                 _data[y] == vec[y];

    return state;
}

bool Vector2::operator!=(const Vector2& vec) const
{
    bool state = _data[x] != vec[x] &&
                 _data[y] != vec[y];

    return state;;
}