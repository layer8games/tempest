#include <Engine/Quaternion.h>

using namespace KillerMath;

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

Quaternion::Quaternion(real wVal, real xVal, real yVal, real zVal)
:
_data{wVal, xVal, yVal, zVal}
{  }

Quaternion::Quaternion(const Quaternion& q)
:
_data{ q[w], q[x], q[y], q[z] }
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

	return Quaternion(_data[w] / d, _data[x] / d, _data[y] / d, _data[z] / d);
}

Quaternion& Quaternion::operator/=(real d)
{
	assert(d != 0);

	_data[w] /= d;
	_data[x] /= d; 
	_data[y] /= d;
	_data[z] /= d; 

	return *this;
}

Quaternion Quaternion::operator*(real m)
{
	return Quaternion(_data[w] *= m, _data[x] *= m, _data[y] *= m, _data[z] *= m);
}

Quaternion Quaternion::operator*(const Quaternion& q2)
{
	real w2 = q2[w];
	real x2 = q2[x];
	real y2 = q2[y];
	real z2 = q2[z];

	return Quaternion(_data[w] * w2 - _data[x] * x2 - _data[y] * y2 - _data[z] * z2,  //w
					  _data[w] * x2 + _data[x] * w2 + _data[y] * z2 - _data[z] * y2,  //x
					  _data[w] * y2 + _data[y] * w2 + _data[z] * x2 - _data[x] * z2,  //y
					  _data[w] * z2 + _data[z] * w2 + _data[x] * y2 - _data[y] * x2); //z
}

Quaternion& Quaternion::operator*=(real m)
{
	_data[w] *= m;
	_data[x] *= m; 
	_data[y] *= m;
	_data[z] *= m; 

	return *this;
}

Quaternion& Quaternion::operator*=(const Quaternion& q2)
{
	real w1 = _data[w];
	real x1 = _data[x];
	real y1 = _data[y];
	real z1 = _data[z];

	real w2 = q2[w];
	real x2 = q2[x];
	real y2 = q2[y];
	real z2 = q2[z];

	_data[w] = w1 * w2 - x1 * x2 - y1 * y2 - z1 * z2;  //w
	_data[x] = w1 * x2 + x1 * w2 + y1 * z2 - z1 * y2;  //x
	_data[y] = w1 * y2 + y1 * w2 + z1 * x2 - x1 * z2;  //y
	_data[z] = w1 * z2 + z1 * w2 + x1 * y2 - y1 * x2;  //z

	return *this;
}

//==========================================================================================================================
//
//Quaternion Functions
//
//==========================================================================================================================	
real Quaternion::Magnitude(void)
{
	return sqrt(_data[w] * _data[w] + _data[x] * _data[x] + _data[y] * _data[y] + _data[z] * _data[z]);
}

Quaternion Quaternion::Conjugate(void)
{
	Quaternion Q{_data[w], _data[x] * -1.0f, _data[y] * -1.0f, _data[z] * -1.0f};

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
	_data[w] *= -1;
	_data[x] *= -1;
	_data[y] *= -1;
	_data[z] *= -1;
}

Quaternion Quaternion::Opposite(void)
{
	return Quaternion(_data[w] * -1.0f, _data[x] * -1.0f, _data[y] * -1.0f, _data[z] * -1.0f);
}

void Quaternion::Normalize(void)
{
	*this /= Magnitude();
}

void Quaternion::AddScaledVector4(const Vector4& vec, F32 scale)
{
	_data[w] += vec[w] * scale;
	_data[x] += vec[x] * scale;
	_data[y] += vec[y] * scale;
	_data[z] += vec[z] * scale;
}