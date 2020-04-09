#include <Engine/Quaternion.h>

using namespace TempestMath;

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Quaternion::Quaternion(void)
    :
    w(0.0f),
    x(0.0f),
    y(0.0f),
    z(0.0f)
{  }

Quaternion::Quaternion(real value)
    :
    w(value),
    x(value),
    y(value),
    z(value)
{  }

Quaternion::Quaternion(real wVal, real xVal, real yVal, real zVal)
    :
    w(wVal),
    x(xVal),
    y(yVal),
    z(zVal)
{  }

Quaternion::Quaternion(const Quaternion& q)
    :
    w(q.w),
    x(q.x),
    y(q.y),
    z(q.z)
{  }

Quaternion::~Quaternion(void)
{  }
//==========================================================================================================================
//
//Opperators
//
//==========================================================================================================================
Quaternion Quaternion::operator/ (real d)
{
    assert(d != 0);

    return Quaternion(w / d, x / d, y / d, z / d);
}

Quaternion& Quaternion::operator/=(real d)
{
    assert(d != 0);

    w /= d;
    x /= d; 
    y /= d;
    z /= d; 

    return *this;
}

Quaternion Quaternion::operator*(real m)
{
    return Quaternion(w *= m, x *= m, y *= m, z *= m);
}

Quaternion Quaternion::operator*(const Quaternion& otherQuat)
{
    return Quaternion(w * otherQuat.w - x * otherQuat.x - y * otherQuat.y - z * otherQuat.z,  //w
                      w * otherQuat.x + x * otherQuat.w + y * otherQuat.z - z * otherQuat.y,  //x
                      w * otherQuat.y + y * otherQuat.w + z * otherQuat.x - x * otherQuat.z,  //y
                      w * otherQuat.z + z * otherQuat.w + x * otherQuat.y - y * otherQuat.x); //z
}

Quaternion& Quaternion::operator*=(real m)
{
    w *= m;
    x *= m; 
    y *= m;
    z *= m; 

    return *this;
}

Quaternion& Quaternion::operator*=(const Quaternion& otherQuat)
{
    // Can't change the values mid operation.
    real newWVal = w * otherQuat.w - x * otherQuat.x - y * otherQuat.y - z * otherQuat.z;
    real newXVal = w * otherQuat.x + x * otherQuat.w + y * otherQuat.z - z * otherQuat.y;
    real newYVal = w * otherQuat.y + y * otherQuat.w + z * otherQuat.x - x * otherQuat.z;
    real newZVal = w * otherQuat.z + z * otherQuat.w + x * otherQuat.y - y * otherQuat.x;

    w = newWVal;
    x = newXVal;
    y = newYVal;
    z = newZVal;

    return *this;
}

//==========================================================================================================================
//
//Quaternion Functions
//
//==========================================================================================================================	
real Quaternion::Magnitude(void)
{
    return real_sqrt(w * w + x * x + y * y + z * z);
}

Quaternion Quaternion::Conjugate(void)
{
    Quaternion quaternion{w, x * -1.0f, y * -1.0f, z * -1.0f};

    return quaternion;
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
    return w * otherQuat.w + x * otherQuat.x + y * otherQuat.y + z * otherQuat.z;
}

void Quaternion::Negate(void)
{
    w *= -1;
    x *= -1;
    y *= -1;
    z *= -1;
}

Quaternion Quaternion::Opposite(void)
{
    return Quaternion(w * -1.0f, x * -1.0f, y * -1.0f, z * -1.0f);
}

void Quaternion::Normalize(void)
{
    *this /= Magnitude();
}

void Quaternion::RotateByEuler(const Vector3& vec)
{
    // c = cos, s = sin, y = yaw, p = pitch, r = roll
    real cy = real_cos(vec.x / 2.0f);
    real sy = real_sin(vec.x / 2.0f);
    real cp = real_cos(vec.y / 2.0f);
    real sp = real_sin(vec.y / 2.0f);
    real cr = real_cos(vec.z / 2.0f);
    real sr = real_sin(vec.z / 2.0f);

    x = cy * cp * sr - sy * sp * cr;
    y = sy * cp * sr + cy * sp * cr;
    z = sy * cp * cr - cy * sp * sr;
    w = cy * cp * cr + sy * sp * sr;
}

void Quaternion::RotateByEuler(real yaw, real pitch, real roll)
{
    // c = cos, s = sin, y = yaw, p = pitch, r = roll
    real cy = real_cos(yaw / 2.0f);
    real sy = real_sin(yaw / 2.0f);
    real cp = real_cos(pitch / 2.0f);
    real sp = real_sin(pitch / 2.0f);
    real cr = real_cos(roll / 2.0f);
    real sr = real_sin(roll / 2.0f);

    x = cy * cp * sr - sy * sp * cr;
    y = sy * cp * sr + cy * sp * cr;
    z = sy * cp * cr - cy * sp * sr;
    w = cy * cp * cr + sy * sp * sr;
}

void Quaternion::AddEuler(const Vector3& vec)
{
    // If this quaternion is at 0, and we want to add a rotation,
    // just add it.
    if(w == 0.0f, x == 0.0f && y == 0.0f && z == 0.0f)
    {
        RotateByEuler(vec);
        return;
    }
        
    real cy = real_cos(vec.x / 2.0f);
    real sy = real_sin(vec.x / 2.0f);
    real cp = real_cos(vec.y / 2.0f);
    real sp = real_sin(vec.y / 2.0f);
    real cr = real_cos(vec.z / 2.0f);
    real sr = real_sin(vec.z / 2.0f);
    
    real qx = cy * cp * sr - sy * sp * cr;
    real qy = sy * cp * sr + cy * sp * cr;
    real qz = sy * cp * cr - cy * sp * sr;
    real qw = cy * cp * cr + sy * sp * sr;

    Quaternion q {qw, qx, qy, qz};

    (*this) *= q;
}

void Quaternion::AddEuler(real yaw, real pitch, real roll)
{
// If this quaternion is at 0, and we want to add a rotation,
    // just add it.
    if(w == 0.0f && x == 0.0f && y == 0.0f && z == 0.0f)
    {
        RotateByEuler(yaw, pitch, roll);
        return;
    }

    real cy = real_cos(yaw / 2.0f);
    real sy = real_sin(yaw / 2.0f);
    real cp = real_cos(pitch / 2.0f);
    real sp = real_sin(pitch / 2.0f);
    real cr = real_cos(roll / 2.0f);
    real sr = real_sin(roll / 2.0f);

    real qx = cy * cp * sr - sy * sp * cr;
    real qy = sy * cp * sr + cy * sp * cr;
    real qz = sy * cp * cr - cy * sp * sr;
    real qw = cy * cp * cr + sy * sp * sr;

    Quaternion q{qw, qx, qy, qz};

    (*this) *= q;
}