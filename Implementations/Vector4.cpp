#include <Engine/Vector4.h>

using namespace TempestMath;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
Vector4::Vector4(void)
    :
    _data{0.0f, 0.0f, 0.0f, 0.0f}
{  }

Vector4::Vector4(real val)
    :
    _data{val, val, val, 0.0f}
{  }


Vector4::Vector4(real x, real y, real z, real w)
    :
    _data{x, y, z, w}
{  }

Vector4::Vector4(const Vector4& v)
    :
    _data{v[x], v[y], v[z], v[w]}
{  }

Vector4::Vector4(const Point4& p)
    :
    _data{p[x], p[y], p[z], 0.0f}
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
    return _data[x] * vec[x] +
           _data[y] * vec[y] +
           _data[z] * vec[z];
}

real Vector4::Dot(const Point4& point) const
{
    return _data[x] * point[x] +
           _data[y] * point[y] +
           _data[z] * point[z];
}

Vector4 Vector4::CrossProduct(const Vector4& vec) const
{
    return Vector4(_data[y] * vec[z] - _data[z] * vec[y],
                   _data[z] * vec[x] - _data[x] * vec[z],
                   _data[x] * vec[y] - _data[y] * vec[x],
                   0.0f);
}

real Vector4::Magnitude(void)
{
    return real_sqrt(_data[x] * _data[x] + _data[y] * _data[y] + _data[z] * _data[z]);
}

real Vector4::SqrMagnitude(void)
{
    return _data[x] * _data[x] + _data[y] * _data[y] + _data[z] * _data[z];
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
    _data[x] = val;
    _data[y] = val;
    _data[z] = val;
    _data[w] = 0.0f;
}

//===== Math Helper Functions =====
void Vector4::AddScaledVector(const Vector4& vec, real scale)
{
    _data[x] += vec[x] * scale;
    _data[y] += vec[y] * scale;
    _data[z] += vec[z] * scale;
}

void Vector4::AddScaledVector(const Vector3& vec, real scale)
{
    _data[x] += vec[x] * scale;
    _data[y] += vec[y] * scale;
    _data[z] += vec[z] * scale;
}

void Vector4::AddScaledPoint(const Point4& point, real scale)
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
Vector4& Vector4::operator=(const Vector4& vec)
{
    _data[x] = vec[x];
    _data[y] = vec[y];
    _data[z] = vec[z];
    _data[w] = vec[w];

    return *this;
}

Vector4& Vector4::operator=(const Point4& point)
{
    _data[x] = point[x];
    _data[y] = point[y];
    _data[z] = point[z];
    _data[w] = 0.0f;

    return *this;
}

Vector4& Vector4::operator=(const Vector3& vec)
{
    _data[x] = vec[x];
    _data[y] = vec[y];
    _data[z] = vec[z];
    _data[w] = 0.0f;

    return *this;
}

Vector4& Vector4::operator=(real val)
{
    _data[x] = val;
    _data[y] = val;
    _data[z] = val;

    return *this;
}

//===== Add by Vector4 =====
Vector4 Vector4::operator+(const Vector4& vec) const
{
    return Vector4(_data[x] + vec[x],
                   _data[y] + vec[y],
                   _data[z] + vec[z],
                   0.0f);
}

Vector4& Vector4::operator+=(const Vector4& vec)
{
    _data[x] += vec[x];
    _data[y] += vec[y];
    _data[z] += vec[z];

    return *this;
}

Vector4 Vector4::operator+(const Vector3& vec) const
{
    return Vector4(_data[x] + vec[x],
                   _data[y] + vec[y],
                   _data[z] + vec[z],
                   0.0f);
}

Vector4& Vector4::operator+=(const Point4& vec)
{
    _data[x] += vec[x];
    _data[y] += vec[y];
    _data[z] += vec[z];

    return *this;
}

Vector4 Vector4::operator+(const Point4& vec) const
{
    return Vector4(_data[x] + vec[x],
                   _data[y] + vec[y],
                   _data[z] + vec[z],
                   0.0f);
}

Vector4& Vector4::operator+=(const Vector3& vec)
{
    _data[x] += vec[x];
    _data[y] += vec[y];
    _data[z] += vec[z];

    return *this;
}

Vector4 Vector4::operator+(shared_ptr<Vector4> vec) const
{
    const real* vals = vec->GetElems();

    return Vector4(_data[x] + vals[x],
                   _data[y] + vals[y],
                   _data[z] + vals[z],
                   0.0f);
}

//===== Add by scalar =====
Vector4 Vector4::operator+(real val) const
{
    return Vector4(_data[x] + val,
                   _data[y] + val,
                   _data[z] + val,
                   0.0f);
}

Vector4& Vector4::operator+=(real val)
{
    _data[x] += val;
    _data[y] += val;
    _data[z] += val;

    return *this;
}

//===== Subtract by Vector4 =====
Vector4 Vector4::operator-(const Vector4& vec) const
{
    return Vector4(_data[x] - vec[x],
                   _data[y] - vec[y],
                   _data[z] - vec[z],
                   0.0f);
}

Vector4& Vector4::operator-=(const Vector4& vec)
{
    _data[x] -= vec[x];
    _data[y] -= vec[y];
    _data[z] -= vec[z];

    return *this;
}

Vector4 Vector4::operator-(const Vector3& vec) const
{
    return Vector4(_data[x] - vec[x],
                   _data[y] - vec[y],
                   _data[z] - vec[z],
                   0.0f);
}

Vector4& Vector4::operator-=(const Vector3& vec)
{
    _data[x] -= vec[x];
    _data[y] -= vec[y];
    _data[z] -= vec[z];

    return *this;
}

Vector4 Vector4::operator-(const Point4& vec) const
{
    return Vector4(_data[x] - vec[x],
                   _data[y] - vec[y],
                   _data[z] - vec[z],
                   0.0f);
}

Vector4& Vector4::operator-=(const Point4& vec)
{
    _data[x] -= vec[x];
    _data[y] -= vec[y];
    _data[z] -= vec[z];

    return *this;
}

//===== Subtract by scalar =====
Vector4 Vector4::operator-(real val) const
{
    return Vector4(_data[x] - val,
                   _data[y] - val,
                   _data[z] - val,
                   0.0f);
}

Vector4& Vector4::operator-=(real val)
{
    _data[x] -= val;
    _data[y] -= val;
    _data[z] -= val;

    return *this;
}

//===== Component-wise multiply by Vector4 =====
Vector4 Vector4::operator*(const Vector4 vec) const
{
    return Vector4(_data[x] * vec[x],
                   _data[y] * vec[y],
                   _data[z] * vec[z],
                   0.0f);
}

Vector4& Vector4::operator*=(const Vector4 vec)
{
    _data[x] *= vec[x];
    _data[y] *= vec[y];
    _data[z] *= vec[z];

    return *this;
}

//===== Mutliply by Scalar =====
Vector4 Vector4::operator*(real val) const
{
    return Vector4(_data[x] * val,
                   _data[y] * val,
                   _data[z] * val,
                   0.0f);
}

Vector4& Vector4::operator*=(real val)
{
    _data[x] *= val;
    _data[y] *= val;
    _data[z] *= val;

    return *this;
}

//===== Divide by scalar =====
Vector4 Vector4::operator/(real val) const
{
    assert(val != 0.0f);

    return Vector4(_data[x] / val,
                   _data[y] / val,
                   _data[z] / val,
                   0.0f);
}

Vector4& Vector4::operator/=(real val)
{
    assert(val != 0.0f);

    _data[x] /= val;
    _data[y] /= val;
    _data[z] /= val;

    return *this;
}

//===== Comparison =====
bool Vector4::operator>(const Vector4& vec) const
{
    bool state = _data[x] > vec[x] && 
                 _data[y] > vec[y] &&
                 _data[z] > vec[z] &&
                 _data[w] >= vec[w];
    
    return state;
}

bool Vector4::operator<(const Vector4& vec) const
{
    bool state = _data[x] < vec[x] && 
                 _data[y] < vec[y] &&
                 _data[z] < vec[z] &&
                 _data[w] <= vec[w];
    
    return state;
}

bool Vector4::operator>=(const Vector4& vec) const
{
   bool state = _data[x] >= vec[x] && 
                _data[y] >= vec[y] &&
                _data[z] >= vec[z] &&
                _data[w] >= vec[w];
    
    return state;
}

bool Vector4::operator<=(const Vector4& vec) const
{
   bool state = _data[x] <= vec[x] && 
                _data[y] <= vec[y] &&
                _data[z] <= vec[z] &&
                _data[w] <= vec[w];
    
    return state;
}

bool Vector4::operator==(const Vector4& vec) const
{
   bool state = _data[x] == vec[x] && 
                _data[y] == vec[y] &&
                _data[z] == vec[z] &&
                _data[w] == vec[w];
    
    return state;
}

bool Vector4::operator!=(const Vector4& vec) const
{
    bool state = _data[x] != vec[x] && 
                 _data[y] != vec[y] &&
                 _data[z] != vec[z] &&
                 _data[w] != vec[w];
    
    return state;
}