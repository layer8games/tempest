#include <Engine/Point3.h>

using namespace TempestMath;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
Point3::Point3(void)
    :
    _data{0.0f, 0.0f, 0.0f}
{  }

Point3::Point3(real val)
    :
    _data{val, val, val}
{  }

Point3::Point3(real x, real y, real z)
    :
    _data{x, y, z}
{  }

Point3::Point3(const Point3& v)
    :
    _data{v[x], v[y], v[z]}
{  }

Point3::Point3(const Vector3& v)
    :
    _data{v[x], v[y], v[z]}
{  }

Point3::Point3(const Vector4& v)
    :
    _data{v[x], v[y], v[z]}
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
    return _data[x] * point[x] +
           _data[y] * point[y] +
           _data[z] * point[z];
}

Point3 Point3::CrossProduct(const Point3& point) const
{
    return Point3(_data[y] * point[z] - _data[z] * point[y],
                  _data[z] * point[x] - _data[x] * point[z],
                  _data[x] * point[y] - _data[y] * point[x]);
}

real Point3::Magnitude(void)
{
    real totals = (_data[x] * _data[x]) + (_data[y] * _data[y]) + (_data[z] * _data[z]);
    return real_sqrt(totals);
}

real Point3::SqrMagnitude(void)
{
    return (_data[x] * _data[x]) + (_data[y] * _data[y]) + (_data[z] * _data[z]);
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
    _data[x] = val;
    _data[y] = val;
    _data[z] = val;
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
    _data[x] += point[x] * scale;
    _data[y] += point[y] * scale;
    _data[z] += point[z] * scale;
}

void Point3::AddScaledVector(const Vector3& vec, real scale)
{
    _data[x] += vec[x] * scale;
    _data[y] += vec[y] * scale;
    _data[z] += vec[z] * scale;	
}

void Point3::AddScaledVector(const Vector4& vec, real scale)
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
Point3& Point3::operator=(const Point3& point)
{
    _data[x] = point[x];
    _data[y] = point[y];
    _data[z] = point[z];

    return *this;
}

Point3& Point3::operator=(real val)
{
    _data[x] = val;
    _data[y] = val;
    _data[z] = val;

    return *this;
}

//===== Add by Point =====
Point3 Point3::operator+(const Point3& point) const
{
    return Point3(_data[x] + point[x],
                 _data[y] + point[y],
                 _data[z] + point[z]);
}

Point3 Point3::operator+(const Vector4& vec) const
{
    return Point3(_data[x] + vec[x],
                  _data[y] + vec[y],
                  _data[z] + vec[z]);
}

Point3& Point3::operator+=(const Point3& point)
{
    _data[x] += point[x];
    _data[y] += point[y];
    _data[z] += point[z];

    return *this;
}

Point3& Point3::operator+=(const Vector4& vec)
{
    _data[x] += vec[x];
    _data[y] += vec[y];
    _data[z] += vec[z];

    return *this;
}

Point3 Point3::operator+(const Vector3& vec) const
{
   return Point3(_data[x] + vec[x],
                 _data[y] + vec[y],
                 _data[z] + vec[z]);
}

Point3& Point3::operator+=(const Vector3& vec)
{
    _data[x] += vec[x];
    _data[y] += vec[y];
    _data[z] += vec[z];

    return *this;
}

Point3 Point3::operator+(shared_ptr<Point3> point) const
{
    const real* vals = point->GetElems();
    
    return Point3(_data[x] + vals[x],
                  _data[y] + vals[y],
                  _data[z] + vals[z]);
}

//===== Add by scalar =====
Point3 Point3::operator+(real val) const
{
    return Point3(_data[x] + val,
                  _data[y] + val,
                  _data[z] + val);
}

Point3& Point3::operator+=(real val)
{
    _data[x] += val;
    _data[y] += val;
    _data[z] += val;

    return *this;
}

//===== Subtract by Point =====
Point3 Point3::operator-(const Point3& point) const
{
    return Point3(_data[x] - point[x],
                  _data[y] - point[y],
                  _data[z] - point[z]);
}

Point3 Point3::operator-(const Vector3& vec) const
{
    return Point3(_data[x] - vec[x],
                  _data[y] - vec[y],
                  _data[z] - vec[z]);
}

Point3 Point3::operator-(const Vector4& vec) const
{
    return Point3(_data[x] - vec[x],
                  _data[y] - vec[y],
                  _data[z] - vec[z]);
}

Point3& Point3::operator-=(const Point3& point)
{
    _data[x] -= point[x];
    _data[y] -= point[y];
    _data[z] -= point[z];

    return *this;
}

//===== Subtract by scalar =====
Point3 Point3::operator-(real val) const
{
    return Point3(_data[x] - val,
                  _data[y] - val,
                  _data[z] - val);
}

Point3& Point3::operator-=(real val)
{
    _data[x] -= val;
    _data[y] -= val;
    _data[z] -= val;
    
    return *this;
}

//===== Component-wise multiply by Point =====
Point3 Point3::operator*(const Point3 point) const
{
    return Point3(_data[x] * point[x],
                  _data[y] * point[y],
                  _data[z] * point[z]);
}

Point3& Point3::operator*=(const Point3 point)
{
    _data[x] *= point[x];
    _data[y] *= point[y];
    _data[z] *= point[z];

    return *this;
}

//===== Mutliply by Scalar =====
Point3 Point3::operator*(real val) const
{
    return Point3(_data[x] * val,
                  _data[y] * val,
                  _data[z] * val);
}

Point3& Point3::operator*=(real val)
{
    _data[x] *= val;
    _data[y] *= val;
    _data[z] *= val;

    return *this;
}

//===== Divide by scalar =====
Point3 Point3::operator/(real val) const
{
    assert(val != 0.0f);

    return Point3(_data[x] / val,
                  _data[y] / val,
                  _data[z] / val);
}

Point3& Point3::operator/=(real val)
{
    assert(val != 0.0f);

    _data[x] /= val;
    _data[y] /= val;
    _data[z] /= val;
    
    return *this;
}

//===== Comparison =====
bool Point3::operator>(const Point3& point) const
{
    bool state = _data[x] > point[x] && 
                 _data[y] > point[y] &&
                 _data[z] > point[z];
    
    return state;
}

bool Point3::operator<(const Point3& point) const
{
    bool state = _data[x] < point[x] && 
                 _data[y] < point[y] &&
                 _data[z] < point[z];
    
    return state;
}

bool Point3::operator>=(const Point3& point) const
{
    bool state = _data[x] >= point[x] && 
                 _data[y] >= point[y] &&
                 _data[z] >= point[z];
    
    return state;
}

bool Point3::operator<=(const Point3& point) const
{
    bool state = _data[x] <= point[x] && 
                 _data[y] <= point[y] &&
                 _data[z] <= point[z];
    
    return state;
}

bool Point3::operator==(const Point3& point) const
{
    bool state = _data[x] == point[x] && 
                 _data[y] == point[y] &&
                 _data[z] == point[z];
    
    return state;
}

bool Point3::operator!=(const Point3& point) const
{
    bool state = _data[x] != point[x] && 
                 _data[y] != point[y] &&
                 _data[z] != point[z];
    
    return state;
}