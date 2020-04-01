#include <Engine/Quaternion.h>

using namespace TempestMath;

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Quaternion::Quaternion(void)
:
_data{0.0f, 0.0f, 0.0f, 0.0f}
{  }

Quaternion::Quaternion(real value)
:
_data{value, value, value, value}
{  }

Quaternion::Quaternion(real xVal, real yVal, real zVal, real wVal)
:
_data{xVal, yVal, zVal, wVal}
{  }

Quaternion::Quaternion(const Quaternion& q)
:
_data{q[x], q[y], q[z], q[w]}
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

    return Quaternion(_data[x] / d, _data[y] / d, _data[z] / d, _data[w] / d);
}

Quaternion& Quaternion::operator/=(real d)
{
    assert(d != 0);

    _data[x] /= d; 
    _data[y] /= d;
    _data[z] /= d; 
    _data[w] /= d;

    return *this;
}

Quaternion Quaternion::operator*(real m)
{
    return Quaternion(_data[x] *= m, _data[y] *= m, _data[z] *= m, _data[w] *= m);
}

Quaternion Quaternion::operator*(const Quaternion& q2)
{
    real x2 = q2[x];
    real y2 = q2[y];
    real z2 = q2[z];
    real w2 = q2[w];

    return Quaternion(_data[w] * x2 + _data[x] * w2 + _data[y] * z2 - _data[z] * y2,  //x
                      _data[w] * y2 + _data[y] * w2 + _data[z] * x2 - _data[x] * z2,  //y
                      _data[w] * z2 + _data[z] * w2 + _data[x] * y2 - _data[y] * x2,  //z
                      _data[w] * w2 - _data[x] * x2 - _data[y] * y2 - _data[z] * z2); //w
}

Quaternion& Quaternion::operator*=(real m)
{
    _data[x] *= m; 
    _data[y] *= m;
    _data[z] *= m; 
    _data[w] *= m;

    return *this;
}

Quaternion& Quaternion::operator*=(const Quaternion& q2)
{
    real x1 = _data[x];
    real y1 = _data[y];
    real z1 = _data[z];
    real w1 = _data[w];

    real x2 = q2[x];
    real y2 = q2[y];
    real z2 = q2[z];
    real w2 = q2[w];

    _data[x] = w1 * x2 + x1 * w2 + y1 * z2 - z1 * y2;  //x
    _data[y] = w1 * y2 + y1 * w2 + z1 * x2 - x1 * z2;  //y
    _data[z] = w1 * z2 + z1 * w2 + x1 * y2 - y1 * x2;  //z
    _data[w] = w1 * w2 - x1 * x2 - y1 * y2 - z1 * z2;  //w

    return *this;
}

//==========================================================================================================================
//
//Quaternion Functions
//
//==========================================================================================================================	
real Quaternion::Magnitude(void)
{
    return real_sqrt(_data[w] * _data[w] + _data[x] * _data[x] + _data[y] * _data[y] + _data[z] * _data[z]);
}

Quaternion Quaternion::Conjugate(void)
{
    Quaternion Q{_data[x] * -1.0f, _data[y] * -1.0f, _data[z] * -1.0f, _data[w]};

    return Q;
}

Quaternion Quaternion::Inverse(void)
{
    Quaternion conjugate = Conjugate();
    real mag = Magnitude();

    return conjugate / mag;
}

Quaternion Quaternion::Difference(Quaternion& Q)
{
    return Q * Inverse();
}

real Quaternion::Dot(Quaternion& Q)
{
    return _data[w] * Q[w] + _data[x] * Q[x] + _data[y] * Q[y] + _data[z] * Q[z];
}

void Quaternion::Negate(void)
{
    _data[x] *= -1;
    _data[y] *= -1;
    _data[z] *= -1;
    _data[w] *= -1;
}

Quaternion Quaternion::Opposite(void)
{
    return Quaternion(_data[x] * -1.0f, _data[y] * -1.0f, _data[z] * -1.0f, _data[w] * -1.0f);
}

void Quaternion::Normalize(void)
{
    *this /= Magnitude();
}

void Quaternion::RotateByEuler(const Vector3& vec)
{
    // c = cos, s = sin, y = yaw, p = pitch, r = roll
    real cy = real_cos(vec[x] / 2.0f);
    real sy = real_sin(vec[x] / 2.0f);
    real cp = real_cos(vec[y] / 2.0f);
    real sp = real_sin(vec[y] / 2.0f);
    real cr = real_cos(vec[z] / 2.0f);
    real sr = real_sin(vec[z] / 2.0f);

    _data[x] = cy * cp * sr - sy * sp * cr;
    _data[y] = sy * cp * sr + cy * sp * cr;
    _data[z] = sy * cp * cr - cy * sp * sr;
    _data[w] = cy * cp * cr + sy * sp * sr;
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

    _data[x] = cy * cp * sr - sy * sp * cr;
    _data[y] = sy * cp * sr + cy * sp * cr;
    _data[z] = sy * cp * cr - cy * sp * sr;
    _data[w] = cy * cp * cr + sy * sp * sr;
}

void Quaternion::AddEuler(const Vector3& vec)
{
    // If this quaternion is at 0, and we want to add a rotation,
    // just add it.
    if(_data[x] == 0.0f && _data[y] == 0.0f &&
       _data[z] == 0.0f && _data[w] == 0.0f)
    {
        RotateByEuler(vec);
        return;
    }
        
    real cy = real_cos(vec[x] / 2.0f);
    real sy = real_sin(vec[x] / 2.0f);
    real cp = real_cos(vec[y] / 2.0f);
    real sp = real_sin(vec[y] / 2.0f);
    real cr = real_cos(vec[z] / 2.0f);
    real sr = real_sin(vec[z] / 2.0f);
    
    real qx = cy * cp * sr - sy * sp * cr;
    real qy = sy * cp * sr + cy * sp * cr;
    real qz = sy * cp * cr - cy * sp * sr;
    real qw = cy * cp * cr + sy * sp * sr;

    Quaternion q {qx, qy, qz, qw};

    (*this) *= q;
}

void Quaternion::AddEuler(real yaw, real pitch, real roll)
{
// If this quaternion is at 0, and we want to add a rotation,
    // just add it.
    if(_data[x] == 0.0f && _data[y] == 0.0f &&
       _data[z] == 0.0f && _data[w] == 0.0f)
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

    Quaternion q{qx, qy, qz, qw};

    (*this) *= q;
}