#include <Engine/Point2.h>

using namespace TempestMath;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
Point2::Point2(void)
    :
    _data{0.0f, 0.0f}
{  }

Point2::Point2(real val)
    :
    _data{val, val}
{  }

Point2::Point2(real x, real y)
    :
    _data{x, y}
{  }

Point2::Point2(const Point2& v)
    :
    _data{v[x], v[y]}
{  }

Point2::Point2(const Vector3& v)
    :
    _data{v[x], v[y]}
{  }

Point2::Point2(const Vector4& v)
    :
    _data{v[x], v[y]}
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
    return _data[x] * point[x] +
           _data[y] * point[y];
}

real Point2::Magnitude(void)
{
    real totals = (_data[x] * _data[x]) + (_data[y] * _data[y]);
    return real_sqrt(totals);
}

real Point2::SqrMagnitude(void)
{
    return (_data[x] * _data[x]) + (_data[y] * _data[y]);
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
    _data[x] = val;
    _data[y] = val;
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

//===== Math Helper Functions =====
void Point2::AddScaledPoint(const Point2& point, real scale)
{
    _data[x] += point[x] * scale;
    _data[y] += point[y] * scale;
}

void Point2::AddScaledVector(const Vector2& vec, real scale)
{
    _data[x] += vec[x] * scale;
    _data[y] += vec[y] * scale;	
}

void Point2::AddScaledVector(const Vector3& vec, real scale)
{
    _data[x] += vec[x] * scale;
    _data[y] += vec[y] * scale;	
}

void Point2::AddScaledVector(const Vector4& vec, real scale)
{
    _data[x] += vec[x] * scale;
    _data[y] += vec[y] * scale;
}
//==========================================================================================================================
//
//Operator overloads
//
//==========================================================================================================================
//===== Copy Assignment =====		
Point2& Point2::operator=(const Point2& point)
{
    _data[x] = point[x];
    _data[y] = point[y];

    return *this;
}

Point2& Point2::operator=(real val)
{
    _data[x] = val;
    _data[y] = val;
    _data[z] = val;

    return *this;
}

//===== Add by Point =====
Point2 Point2::operator+(const Point2& point) const
{
    return Point2(_data[x] + point[x],
                  _data[y] + point[y]);
}

Point2 Point2::operator+(const Vector4& vec) const
{
    return Point2(_data[x] + vec[x],
                  _data[y] + vec[y]);
}

Point2& Point2::operator+=(const Point2& point)
{
    _data[x] += point[x];
    _data[y] += point[y];

    return *this;
}

Point2& Point2::operator+=(const Vector4& vec)
{
    _data[x] += vec[x];
    _data[y] += vec[y];

    return *this;
}

Point2 Point2::operator+(const Vector3& vec) const
{
   return Point2(_data[x] + vec[x],
                 _data[y] + vec[y]);
}

Point2& Point2::operator+=(const Vector3& vec)
{
    _data[x] += vec[x];
    _data[y] += vec[y];

    return *this;
}

Point2 Point2::operator+(p_Point2 point) const
{
    const real* vals = point->GetElems();
    
    return Point2(_data[x] + vals[x],
                  _data[y] + vals[y]);
}

//===== Add by scalar =====
Point2 Point2::operator+(real val) const
{
    return Point2(_data[x] + val,
                  _data[y] + val);
}

Point2& Point2::operator+=(real val)
{
    _data[x] += val;
    _data[y] += val;

    return *this;
}

//===== Subtract by Point =====
Point2 Point2::operator-(const Point2& point) const
{
    return Point2(_data[x] - point[x],
                  _data[y] - point[y]);
}

Point2 Point2::operator-(const Vector3& vec) const
{
    return Point2(_data[x] - vec[x],
                  _data[y] - vec[y]);
}

Point2 Point2::operator-(const Vector4& vec) const
{
    return Point2(_data[x] - vec[x],
                  _data[y] - vec[y]);
}

Point2& Point2::operator-=(const Point2& point)
{
    _data[x] -= point[x];
    _data[y] -= point[y];

    return *this;
}

//===== Subtract by scalar =====
Point2 Point2::operator-(real val) const
{
    return Point2(_data[x] - val,
                  _data[y] - val);
}

Point2& Point2::operator-=(real val)
{
    _data[x] -= val;
    _data[y] -= val;
    
    return *this;
}

//===== Component-wise multiply by Point =====
Point2 Point2::operator*(const Point2 point) const
{
    return Point2(_data[x] * point[x],
                  _data[y] * point[y]);
}

Point2& Point2::operator*=(const Point2 point)
{
    _data[x] *= point[x];
    _data[y] *= point[y];

    return *this;
}

//===== Mutliply by Scalar =====
Point2 Point2::operator*(real val) const
{
    return Point2(_data[x] * val,
                  _data[y] * val);
}

Point2& Point2::operator*=(real val)
{
    _data[x] *= val;
    _data[y] *= val;

    return *this;
}

//===== Divide by scalar =====
Point2 Point2::operator/(real val) const
{
    assert(val != 0.0f);

    return Point2(_data[x] / val,
                  _data[y] / val);
}

Point2& Point2::operator/=(real val)
{
    assert(val != 0.0f);

    _data[x] /= val;
    _data[y] /= val;
    
    return *this;
}

//===== Comparison =====
bool Point2::operator>(const Point2& point) const
{
    bool state = _data[x] > point[x] && 
                 _data[y] > point[y];
    
    return state;
}

bool Point2::operator<(const Point2& point) const
{
    bool state = _data[x] < point[x] && 
                 _data[y] < point[y];
    
    return state;
}

bool Point2::operator>=(const Point2& point) const
{
    bool state = _data[x] >= point[x] && 
                 _data[y] >= point[y];
    
    return state;
}

bool Point2::operator<=(const Point2& point) const
{
    bool state = _data[x] <= point[x] && 
                 _data[y] <= point[y];
    
    return state;
}

bool Point2::operator==(const Point2& point) const
{
    bool state = _data[x] == point[x] && 
                 _data[y] == point[y];
    
    return state;
}

bool Point2::operator!=(const Point2& point) const
{
    bool state = _data[x] != point[x] && 
                 _data[y] != point[y];
    
    return state;
}