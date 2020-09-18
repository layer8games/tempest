#include "stdafx.h"
#include "Engine/Vector4.h"
using namespace TempestMath;

Vector4::Vector4(void)
    :
    _data(0.0f)
{  }

Vector4::Vector4(real val)
    :
    _data(0.0f)
{  }

Vector4::Vector4(real xVal, real yVal, real zVal, real wVal)
    :
    _data(xVal, yVal, zVal, wVal)
{  }

Vector4::Vector4(const Vector4& vector)
    :
    _data(vector.GetRawData())
{  }

Vector4::Vector4(glm::vec4 vector)
    :
    _data(vector)
{  }

Vector4::~Vector4(void)
{  }

real Vector4::Dot(const Vector4& vector) const
{
    return glm::dot(_data, vector.GetRawData());
}

real Vector4::Magnitude(void)
{
    return glm::length(_data);
}

real Vector4::SqrMagnitude(void)
{
    return glm::length2(_data);
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
    _data = glm::vec4(val);
}

void Vector4::AddScaledVector(const Vector4& vector, real scale)
{
    _data += vector.GetRawData() * scale;
}

void Vector4::Set(real xVal, real yVal, real zVal, real wVal)
{
    _data = glm::vec4(xVal, yVal, zVal, wVal);
}

glm::vec4 Vector4::GetRawData(void) const
{
    return _data;
}

F32 Vector4::GetX() const
{
    return _data.x;
}
        
F32 Vector4::GetY() const
{
    return _data.y;
}
        
F32 Vector4::GetZ() const
{
    return _data.z;
}

F32 Vector4::GetW() const
{
    return _data.w;
}

void Vector4::SetX(F32 val)
{
    _data.x = val;
}

void Vector4::SetY(F32 val)
{
    _data.y = val;
}

void Vector4::SetZ(F32 val)
{
    _data.z = val;
}

void Vector4::SetW(F32 val)
{
    _data.w = val;
}

Vector4& Vector4::operator=(const Vector4& vector)
{
    _data = vector.GetRawData();

    return *this;
}

Vector4& Vector4::operator=(const Vector3& vector)
{
    _data.x = vector.GetX();
    _data.y = vector.GetY();
    _data.z = vector.GetZ();

    return *this;
}

Vector4& Vector4::operator=(real val)
{
    _data = glm::vec4(val);

    return *this;
}

Vector4 Vector4::operator+(const Vector4& vector) const
{
    return Vector4(_data + vector.GetRawData());
}

Vector4& Vector4::operator+=(const Vector4& vector)
{
    _data += vector.GetRawData();

    return *this;
}

Vector4 Vector4::operator+(real val) const
{
    return Vector4(_data + val);
}

Vector4& Vector4::operator+=(real val)
{
    _data += val;

    return *this;
}

Vector4 Vector4::operator-(const Vector4& vector) const
{
    return Vector4(_data - vector.GetRawData());
}

Vector4& Vector4::operator-=(const Vector4& vector)
{
    _data -= vector.GetRawData();

    return *this;
}

Vector4 Vector4::operator-(void) const
{
    return Vector4(-_data);
}

Vector4& Vector4::operator++(void)
{
    _data++;

    return *this;
}

Vector4 Vector4::operator++(int)
{
    return Vector4(++_data);
}

Vector4& Vector4::operator--(void)
{
    _data--;

    return *this;
}

Vector4 Vector4::operator--(int)
{
    return Vector4(--_data);
}

Vector4 Vector4::operator-(real val) const
{
    return Vector4(_data - val);
}

Vector4& Vector4::operator-=(real val)
{
    _data -= val;

    return *this;
}

Vector4 Vector4::operator*(const Vector4 vector) const
{
    return Vector4(_data * vector.GetRawData());
}

Vector4& Vector4::operator*=(const Vector4 vector)
{
    _data *= vector.GetRawData();

    return *this;
}

Vector4 Vector4::operator*(real val) const
{
    return Vector4(_data * val);
}

Vector4& Vector4::operator*=(real val)
{
    _data *= val;

    return *this;
}

Vector4 Vector4::operator/(real val) const
{
    return Vector4(_data / val);
}

Vector4& Vector4::operator/=(real val)
{
    _data /= val;

    return *this;
}

bool Vector4::operator>(const Vector4& vector) const
{
    bool state = _data.x > vector.GetX() && 
                 _data.y > vector.GetY() &&
                 _data.z > vector.GetZ();

    return state;
}

bool Vector4::operator<(const Vector4& vector) const
{
    bool state = _data.x < vector.GetX() &&
                 _data.y < vector.GetY() &&
                 _data.z < vector.GetZ();

    return state;;
}

bool Vector4::operator>=(const Vector4& vector) const
{
    bool state = _data.x >= vector.GetX() &&
                 _data.y >= vector.GetY() &&
                 _data.z >= vector.GetZ();

    return state;
}

bool Vector4::operator<=(const Vector4& vector) const
{
    bool state = _data.x <= vector.GetX() &&
                 _data.y <= vector.GetY() &&
                 _data.z <= vector.GetZ();

    return state;
}

bool Vector4::operator==(const Vector4& vector) const
{
    bool state = _data.x == vector.GetX() &&
                 _data.y == vector.GetY() &&
                 _data.z == vector.GetZ();

    return state;
}

bool Vector4::operator!=(const Vector4& vector) const
{
    bool state = _data.x != vector.GetX() &&
                 _data.y != vector.GetY() &&
                 _data.z != vector.GetZ();

    return state;;
}