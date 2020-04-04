#include <Engine/Point4.h>

using namespace TempestMath;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
Point4::Point4(void)
    :
    _data{0.0f, 0.0f, 0.0f, 1.0f}
{  }

Point4::Point4(real val)
    :
    _data{val, val, val, 1.0f}
{  }

Point4::Point4(real x, real y, real z, real w)
    :
    _data{x, y, z, w}
{  }

Point4::Point4(const Point4& v)
    :
    _data{v[x], v[y], v[z], v[w]}
{  }

Point4::Point4(const Vector3& v)
    :
    _data{v[x], v[y], v[z], v[w]}
{  }

Point4::Point4(const Vector4& v)
    :
    _data{v[x], v[y], v[z], v[w]}
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
    return _data[x] * point[x] +
           _data[y] * point[y] +
           _data[z] * point[z];
}

Point4 Point4::CrossProduct(const Point4& point) const
{
    return Point4(_data[y] * point[z] - _data[z] * point[y],
                  _data[z] * point[x] - _data[x] * point[z],
                  _data[x] * point[y] - _data[y] * point[x],
                  1.0f);
}

real Point4::Magnitude(void)
{
    real totals = (_data[x] * _data[x]) + (_data[y] * _data[y]) + (_data[z] * _data[z]);
    return real_sqrt(totals);
}

real Point4::SqrMagnitude(void)
{
    return (_data[x] * _data[x]) + (_data[y] * _data[y]) + (_data[z] * _data[z]);
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
    _data[x] = val;
    _data[y] = val;
    _data[z] = val;
    _data[w] = 1.0f;
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
    _data[x] += point[x] * scale;
    _data[y] += point[y] * scale;
    _data[z] += point[z] * scale;
}

void Point4::AddScaledVector(const Vector3& vec, real scale)
{
    _data[x] += vec[x] * scale;
    _data[y] += vec[y] * scale;
    _data[z] += vec[z] * scale;	
}

void Point4::AddScaledVector(const Vector4& vec, real scale)
{
    _data[x] += vec[x] * scale;
    _data[y] += vec[y] * scale;
    _data[z] += vec[z] * scale;
}
//==========================================================================================================================
//
//Operator overloads
//
//==========================================================================================================================
//===== Copy Assignment =====		
Point4& Point4::operator=(const Point4& point)
{
    _data[x] = point[x];
    _data[y] = point[y];
    _data[z] = point[z];
    _data[w] = point[w];

    return *this;
}

Point4& Point4::operator=(real val)
{
    _data[x] = val;
    _data[y] = val;
    _data[z] = val;

    return *this;
}

//===== Add by Point =====
Point4 Point4::operator+(const Point4& point) const
{
    return Point4(_data[x] + point[x],
                 _data[y] + point[y],
                 _data[z] + point[z],
                 1.0f);
}

Point4 Point4::operator+(const Vector4& vec) const
{
    return Point4(_data[x] + vec[x],
                  _data[y] + vec[y],
                  _data[z] + vec[z],
                  1.0f);
}

Point4& Point4::operator+=(const Point4& point)
{
    _data[x] += point[x];
    _data[y] += point[y];
    _data[z] += point[z];

    return *this;
}

Point4& Point4::operator+=(const Vector4& vec)
{
    _data[x] += vec[x];
    _data[y] += vec[y];
    _data[z] += vec[z];

    return *this;
}

Point4 Point4::operator+(const Vector3& vec) const
{
   return Point4(_data[x] + vec[x],
                 _data[y] + vec[y],
                 _data[z] + vec[z],
                 1.0f);
}

Point4& Point4::operator+=(const Vector3& vec)
{
    _data[x] += vec[x];
    _data[y] += vec[y];
    _data[z] += vec[z];

    return *this;
}

Point4 Point4::operator+(p_Point4 point) const
{
    const real* vals = point->GetElems();
    
    return Point4(_data[x] + vals[x],
                  _data[y] + vals[y],
                  _data[z] + vals[z],
                  1.0f);
}

//===== Add by scalar =====
Point4 Point4::operator+(real val) const
{
    return Point4(_data[x] + val,
                  _data[y] + val,
                  _data[z] + val,
                  1.0f);
}

Point4& Point4::operator+=(real val)
{
    _data[x] += val;
    _data[y] += val;
    _data[z] += val;

    return *this;
}

//===== Subtract by Point =====
Point4 Point4::operator-(const Point4& point) const
{
    return Point4(_data[x] - point[x],
                  _data[y] - point[y],
                  _data[z] - point[z],
                  1.0f);
}

Point4 Point4::operator-(const Vector3& vec) const
{
    return Point4(_data[x] - vec[x],
                  _data[y] - vec[y],
                  _data[z] - vec[z],
                  1.0f);
}

Point4 Point4::operator-(const Vector4& vec) const
{
    return Point4(_data[x] - vec[x],
                  _data[y] - vec[y],
                  _data[z] - vec[z],
                  1.0f);
}

Point4& Point4::operator-=(const Point4& point)
{
    _data[x] -= point[x];
    _data[y] -= point[y];
    _data[z] -= point[z];

    return *this;
}

//===== Subtract by scalar =====
Point4 Point4::operator-(real val) const
{
    return Point4(_data[x] - val,
                  _data[y] - val,
                  _data[z] - val,
                  1.0f);
}

Point4& Point4::operator-=(real val)
{
    _data[x] -= val;
    _data[y] -= val;
    _data[z] -= val;
    
    return *this;
}

//===== Component-wise multiply by Point =====
Point4 Point4::operator*(const Point4 point) const
{
    return Point4(_data[x] * point[x],
                  _data[y] * point[y],
                  _data[z] * point[z],
                  1.0f);
}

Point4& Point4::operator*=(const Point4 point)
{
    _data[x] *= point[x];
    _data[y] *= point[y];
    _data[z] *= point[z];

    return *this;
}

//===== Mutliply by Scalar =====
Point4 Point4::operator*(real val) const
{
    return Point4(_data[x] * val,
                  _data[y] * val,
                  _data[z] * val,
                  1.0f);
}

Point4& Point4::operator*=(real val)
{
    _data[x] *= val;
    _data[y] *= val;
    _data[z] *= val;

    return *this;
}

//===== Divide by scalar =====
Point4 Point4::operator/(real val) const
{
    assert(val != 0.0f);

    return Point4(_data[x] / val,
                  _data[y] / val,
                  _data[z] / val,
                  1.0f);
}

Point4& Point4::operator/=(real val)
{
    assert(val != 0.0f);

    _data[x] /= val;
    _data[y] /= val;
    _data[z] /= val;
    
    return *this;
}

//===== Comparison =====
bool Point4::operator>(const Point4& point) const
{
    bool state = _data[x] > point[x] && 
                 _data[y] > point[y] &&
                 _data[z] > point[z] &&
                 _data[w] >= point[w];
    
    return state;
}

bool Point4::operator<(const Point4& point) const
{
    bool state = _data[x] < point[x] && 
                 _data[y] < point[y] &&
                 _data[z] < point[z] &&
                 _data[w] <= point[w];
    
    return state;
}

bool Point4::operator>=(const Point4& point) const
{
    bool state = _data[x] >= point[x] && 
                 _data[y] >= point[y] &&
                 _data[z] >= point[z] &&
                 _data[w] >= point[w];
    
    return state;
}

bool Point4::operator<=(const Point4& point) const
{
    bool state = _data[x] <= point[x] && 
                 _data[y] <= point[y] &&
                 _data[z] <= point[z] &&
                 _data[w] <= point[w];
    
    return state;
}

bool Point4::operator==(const Point4& point) const
{
    bool state = _data[x] == point[x] && 
                 _data[y] == point[y] &&
                 _data[z] == point[z] &&
                 _data[w] == point[w];
    
    return state;
}

bool Point4::operator!=(const Point4& point) const
{
    bool state = _data[x] != point[x] && 
                 _data[y] != point[y] &&
                 _data[z] != point[z] &&
                 _data[w] != point[w];
    
    return state;
}