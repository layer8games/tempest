#include "stdafx.h"
#include "Engine/Quaternion.h"
using namespace TempestMath;

Quaternion::Quaternion(void)
    :
    _data(0.0f, 0.0f, 0.0f, 0.0f)
{  }

Quaternion::Quaternion(real value)
    :
    _data(value, value, value, value)
{  }

Quaternion::Quaternion(real wVal, real xVal, real yVal, real zVal)
    :
    _data(wVal, xVal, yVal, zVal)
{  }

Quaternion::Quaternion(const Quaternion& q)
    :
    _data(q.GetW(), q.GetX(), q.GetY(), q.GetZ())
{  }

Quaternion::Quaternion(glm::quat other)
    :
    _data(other)
{  }

Quaternion::~Quaternion(void)
{  }

glm::quat Quaternion::GetRawData(void) const
{
    return _data;
}

Quaternion Quaternion::operator/ (real d)
{
    return Quaternion(_data / d);
}

Quaternion& Quaternion::operator/=(real d)
{
    _data /= d;

    return *this;
}

Quaternion Quaternion::operator*(real m)
{
    return Quaternion(_data * m);
}

Quaternion Quaternion::operator*(const Quaternion& otherQuat)
{
    return Quaternion(_data * otherQuat.GetRawData());
}

Quaternion& Quaternion::operator*=(real m)
{
    _data *= m;

    return *this;
}

Quaternion& Quaternion::operator*=(const Quaternion& otherQuat)
{
    _data *= otherQuat.GetRawData();

    return *this;
}

real Quaternion::Magnitude(void) const
{
    return glm::length(_data);
}

Quaternion Quaternion::Conjugate(void)
{
    return Quaternion(glm::conjugate(_data));
}

Quaternion Quaternion::Inverse(void)
{
    Quaternion conjugate = Conjugate();
    real mag = Magnitude();

    return conjugate / mag;
}

Quaternion Quaternion::Difference(Quaternion& otherQuat)
{
    return otherQuat * Inverse();
}

real Quaternion::Dot(Quaternion& otherQuat)
{
    return glm::dot(_data, otherQuat.GetRawData());
}

void Quaternion::Negate(void)
{
    _data = -_data;
}

Quaternion Quaternion::Opposite(void)
{
    return Quaternion(-_data);
}

void Quaternion::Normalize(void)
{
    _data = glm::normalize(_data);
}

void Quaternion::RotateByEuler(const Vector3& vec)
{
    _data = glm::quat(vec.GetRawData());
}

void Quaternion::RotateByEuler(real yaw, real pitch, real roll)
{
    _data = glm::quat(glm::vec3(yaw, pitch, roll));
}

void Quaternion::AddEuler(const Vector3& vec)
{
    _data += glm::quat(vec.GetRawData());
}

void Quaternion::AddEuler(real yaw, real pitch, real roll)
{
    _data += glm::quat(glm::vec3(yaw, pitch, roll));
}

real Quaternion::GetW(void) const
{
    return _data.w;
}
        
real Quaternion::GetX(void) const
{
    return _data.x;
}
        
real Quaternion::GetY(void) const
{
    return _data.y;
}
        
real Quaternion::GetZ(void) const
{
    return _data.z;
}

void Quaternion::SetW(F32 val)
{
    _data.w = val;
}
        
void Quaternion::SetX(F32 val)
{
    _data.x = val;
}
        
void Quaternion::SetY(F32 val)
{
    _data.y = val;
}
        
void Quaternion::SetZ(F32 val)
{
    _data.z = val;
}