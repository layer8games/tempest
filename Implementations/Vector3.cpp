#include "stdafx.h"
#include <Engine/Vector3.h>
using namespace TempestMath;

Vector3::Vector3(void)
    :
    _data(0.0f)
{  }

Vector3::Vector3(real val)
    :
    _data(0.0f)
{  }

Vector3::Vector3(real xVal, real yVal, real zVal)
    :
    _data(xVal, yVal, zVal)
{  }

Vector3::Vector3(const Vector3& v)
    :
    _data(v.GetX(), v.GetY(), v.GetZ())
{  }

Vector3::Vector3(const Vector4& v)
    :
    _data(v.GetRawData())
{  }

Vector3::Vector3(glm::vec3 v)
    :
    _data(v)
{  }

Vector3::~Vector3(void)
{  }

real Vector3::Dot(const Vector3& vector) const
{
    return glm::dot(_data, vector.GetRawData());
}

Vector3 Vector3::CrossProduct(const Vector3& vector) const
{
    return Vector3(glm::cross(_data, vector.GetRawData()));
}

real Vector3::Magnitude(void)
{
    return glm::length(_data);
}

real Vector3::SqrMagnitude(void)
{
    return glm::length2(_data);
}

void Vector3::Normalize(void)
{
    _data = glm::normalize(_data);
}

void Vector3::Reset(real val)
{
    _data = glm::vec3(val);
}

void Vector3::AddScaledVector(const Vector3& vector, real scale)
{
    _data += vector.GetRawData() * scale;
}

void Vector3::AddScaledVector(const Vector4& vector, real scale)
{
    _data += vector.GetRawData() * scale;
}

void Vector3::Set(real xVal, real yVal, real zVal)
{
    _data = glm::vec3(xVal, yVal, zVal);
}

glm::vec3 Vector3::GetRawData(void) const
{
    return _data;
}

F32 Vector3::GetX() const
{
    return _data.x;
}
        
F32 Vector3::GetY() const
{
    return _data.y;
}
        
F32 Vector3::GetZ() const
{
    return _data.z;
}

Vector3& Vector3::operator=(const Vector2& vector)
{
    _data.x = vector.GetX();
    _data.y = vector.GetY();
    _data.z = 0.0f;

    return *this;
}

Vector3& Vector3::operator=(const Vector3& vector)
{
    _data = vector.GetRawData();

    return *this;
}

Vector3& Vector3::operator=(const Vector4& vector)
{
    _data = glm::vec3(vector.GetRawData());

    return *this;
}

Vector3& Vector3::operator=(real val)
{
    _data = glm::vec3(val);

    return *this;
}

Vector3 Vector3::operator+(const Vector3& vector) const
{
    return Vector3(_data + vector.GetRawData());
}

Vector3& Vector3::operator+=(const Vector3& vector)
{
    _data += vector.GetRawData();

    return *this;
}

Vector3 Vector3::operator+(shared_ptr<Vector3> vector) const
{
    return Vector3(_data + vector->GetRawData());
}

Vector3 Vector3::operator+(real val) const
{
    return Vector3(_data + val);
}

Vector3& Vector3::operator+=(real val)
{
    _data += val;

    return *this;
}

Vector3 Vector3::operator-(const Vector3& vector) const
{
    return Vector3(_data - vector.GetRawData());
}

Vector3& Vector3::operator-=(const Vector3& vector)
{
    _data -= vector.GetRawData();

    return *this;
}

Vector3& Vector3::operator-=(const Vector4& vector)
{
    _data -= glm::vec3(vector.GetRawData());

    return *this;
}

Vector3 Vector3::operator-(void) const
{
    return Vector3(-_data);
}

Vector3& Vector3::operator++(void)
{
    _data++;

    return *this;
}

Vector3 Vector3::operator++(int)
{
    return Vector3(++_data);
}

Vector3& Vector3::operator--(void)
{
    _data--;

    return *this;
}

Vector3 Vector3::operator--(int)
{
    return Vector3(--_data);
}

Vector3 Vector3::operator-(real val) const
{
    return Vector3(_data - val);
}

Vector3& Vector3::operator-=(real val)
{
    _data -= val;

    return *this;
}

Vector3 Vector3::operator*(const Vector3 vector) const
{
    return Vector3(_data * vector.GetRawData());
}

Vector3& Vector3::operator*=(const Vector3 vector)
{
    _data *= vector.GetRawData();

    return *this;
}

Vector3 Vector3::operator*(real val) const
{
    return Vector3(_data * val);
}

Vector3& Vector3::operator*=(real val)
{
    _data *= val;

    return *this;
}

Vector3 Vector3::operator/(real val) const
{
    return Vector3(_data / val);
}

Vector3& Vector3::operator/=(real val)
{
    _data /= val;

    return *this;
}

bool Vector3::operator>(const Vector3& vector) const
{
    bool state = _data.x > vector.GetX() && 
                 _data.y > vector.GetY() &&
                 _data.z > vector.GetZ();

    return state;
}

bool Vector3::operator<(const Vector3& vector) const
{
    bool state = _data.x < vector.GetX() &&
                 _data.y < vector.GetY() &&
                 _data.z < vector.GetZ();

    return state;;
}

bool Vector3::operator>=(const Vector3& vector) const
{
    bool state = _data.x >= vector.GetX() &&
                 _data.y >= vector.GetY() &&
                 _data.z >= vector.GetZ();

    return state;
}

bool Vector3::operator<=(const Vector3& vector) const
{
    bool state = _data.x <= vector.GetX() &&
                 _data.y <= vector.GetY() &&
                 _data.z <= vector.GetZ();

    return state;
}

bool Vector3::operator==(const Vector3& vector) const
{
    bool state = _data.x == vector.GetX() &&
                 _data.y == vector.GetY() &&
                 _data.z == vector.GetZ();

    return state;
}

bool Vector3::operator!=(const Vector3& vector) const
{
    bool state = _data.x != vector.GetX() &&
                 _data.y != vector.GetY() &&
                 _data.z != vector.GetZ();

    return state;;
}