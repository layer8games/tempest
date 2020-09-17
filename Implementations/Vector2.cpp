#include "stdafx.h"
#include <Engine/Vector2.h>

using namespace TempestMath;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
Vector2::Vector2(void)
    :
    _data(0.0f)
{  }

Vector2::Vector2(real val)
    :
    _data(0.0f)
{  }

Vector2::Vector2(real xVal, real yVal)
    :
    _data(xVal, yVal)
{  }

Vector2::Vector2(const Vector2& p)
    :
    _data(p.GetX(), p.GetY())
{  }

Vector2::Vector2(const Vector3& v)
    :
    _data(v.GetX(), v.GetY())
{  }

Vector2::Vector2(const Vector4& v)
    :
    _data(v.GetX(), v.GetY())
{  }

Vector2::Vector2(glm::vec2 v)
    :
    _data(v)
{  }

Vector2::~Vector2(void)
{  }

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
//===== Point Special functions =====
real Vector2::Dot(const Vector2& point) const
{
    return glm::dot(_data, point.GetRawData());
}

real Vector2::Magnitude(void)
{
    return glm::length(_data);
}

real Vector2::SqrMagnitude(void)
{
    return glm::length2(_data);
}

void Vector2::Normalize(void)
{
    _data = glm::normalize(_data);
}

void Vector2::Reset(real val)
{
    _data.x = val;
    _data.y = val;
}

real Vector2::Distance(const Vector2& p) const
{
    return glm::distance(_data, p.GetRawData());
}

real Vector2::DistanceSquared(const Vector2& p) const
{
    return glm::distance2(_data, p.GetRawData());
}

real Vector2::DistanceSquared(const Vector3& v) const
{
    return glm::distance2(_data, glm::vec2(v.GetRawData()));
}

real Vector2::DistanceSquared(const Vector4& v) const
{
    Vector2 length = *this - v;
    return length.SqrMagnitude();
}

void Vector2::Set(real xVal, real yVal)
{
    _data.x = xVal;
    _data.y = yVal;
}

glm::vec2 Vector2::GetRawData(void) const
{
    return _data;
}

F32 Vector2::GetX(void) const
{
    return static_cast<F32>(_data.x);
}

F32 Vector2::GetY(void) const
{
    return static_cast<F32>(_data.y);
}

void Vector2::SetX(F32 val)
{
    _data.x = val;
}

void Vector2::SetY(F32 val)
{
    _data.y = val;
}

Vector2& Vector2::operator=(const Vector2& vector)
{
    _data = vector.GetRawData();

    return *this;
}

Vector2& Vector2::operator=(real val)
{
    _data.x = val;
    _data.y = val;

    return *this;
}

//===== Add by Point =====
Vector2 Vector2::operator+(const Vector2& vector) const
{
    return Vector2(_data + vector.GetRawData());
}

Vector2 Vector2::operator+(const Vector4& vec) const
{
    return Vector2(_data + glm::vec2(vec.GetRawData()));
}

Vector2& Vector2::operator+=(const Vector2& point)
{
    _data += point.GetRawData();

    return *this;
}

Vector2& Vector2::operator+=(const Vector4& vec)
{
    _data += vec.GetRawData();

    return *this;
}

Vector2 Vector2::operator+(const Vector3& vec) const
{
    return Vector2(_data + glm::vec2(vec.GetRawData()));
}

Vector2& Vector2::operator+=(const Vector3& vec)
{
    _data += vec.GetRawData();

    return *this;
}

Vector2 Vector2::operator+(real val) const
{
    return Vector2(_data + glm::vec2(val));
}

Vector2& Vector2::operator+=(real val)
{
    _data += glm::vec2(val);

    return *this;
}

Vector2 Vector2::operator-(const Vector2& vector) const
{
    return Vector2(_data - vector.GetRawData());
}

Vector2 Vector2::operator-(const Vector3& vector) const
{
    return Vector2(_data - glm::vec2(vector.GetRawData()));
}

Vector2 Vector2::operator-(const Vector4& vector) const
{
    return Vector2(_data - glm::vec2(vector.GetRawData()));
}

Vector2& Vector2::operator-=(const Vector2& point)
{
    _data -= point.GetRawData();

    return *this;
}

Vector2 Vector2::operator-(void)
{
    return Vector2(-_data);
}

Vector2& Vector2::operator++(void)
{
    _data++;

    return *this;
}

Vector2 Vector2::operator++(int)
{
    return Vector2(_data++);
}

Vector2& Vector2::operator--(void)
{
    _data--;

    return *this;
}

Vector2 Vector2::operator--(int)
{
    return Vector2(_data--);
}

Vector2 Vector2::operator-(real val) const
{
    return Vector2(_data - val);
}

Vector2& Vector2::operator-=(real val)
{
    _data -= val;
    
    return *this;
}

Vector2 Vector2::operator*(const Vector2 vector) const
{
    return Vector2(_data * vector.GetRawData());
}

Vector2& Vector2::operator*=(const Vector2 vector)
{
    _data *= vector.GetRawData();

    return *this;
}

Vector2 Vector2::operator*(real val) const
{
    return Vector2(_data * val);
}

Vector2& Vector2::operator*=(real val)
{
    _data *= glm::vec2(val);

    return *this;
}

//===== Divide by scalar =====
Vector2 Vector2::operator/(real val) const
{
    return Vector2(_data / val);
}

Vector2& Vector2::operator/=(real val)
{
    _data /= val;
    
    return *this;
}

//===== Comparison =====
bool Vector2::operator>(const Vector2& vector) const
{
    bool state = _data.x > vector.GetX() && 
                 _data.y > vector.GetY();
    
    return state;
}

bool Vector2::operator<(const Vector2& vector) const
{
    bool state = _data.x < vector.GetX() && 
                 _data.y < vector.GetY();
    
    return state;
}

bool Vector2::operator>=(const Vector2& vector) const
{
    bool state = _data.x >= vector.GetX() && 
                 _data.y >= vector.GetY();
    
    return state;
}

bool Vector2::operator<=(const Vector2& vector) const
{
    bool state = _data.x <= vector.GetX() && 
                 _data.y <= vector.GetY();
    
    return state;
}

bool Vector2::operator==(const Vector2& vector) const
{
    bool state = _data.x == vector.GetX() && 
                 _data.y == vector.GetY();
    
    return state;
}

bool Vector2::operator!=(const Vector2& vector) const
{
    bool state = _data.x != vector.GetX() && 
                 _data.y != vector.GetY();
    
    return state;
}