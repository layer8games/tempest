#include <Engine/Vector3.h>

using namespace KillerMath;

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Vector3::Vector3(void)
: 
_x(0.0f), 
_y(0.0f), 
_z(0.0f), 
_w(1.0f)
{  }

Vector3::Vector3(F32 val)
: 
_x(val), 
_y(val), 
_z(val), 
_w(1.0f)
{  }

Vector3::Vector3(F32 x, F32 y)
: 
_x(x), 
_y(y), 
_z(0.0f), 
_w(1.0f)
{  }

Vector3::Vector3(F32 x, F32 y, F32 z)
: 
_x(x), 
_y(y), 
_z(z), 
_w(1.0f)
{  }

Vector3::Vector3(F32 x, F32 y, F32 z, F32 w) 
: 
_x(x), 
_y(y), 
_z(z), 
_w(w)
{  }

Vector3::Vector3(const Vector3& V) 
: 
_x(V.GetX()), 
_y(V.GetY()), 
_z(V.GetZ()), 
_w(V.GetW())
{  }

Vector3::Vector3(const Vector2& V) 
: 
_x(V.GetX()), 
_y(V.GetY()), 
_z(0.0f), 
_w(1.0f)
{  }

Vector3::~Vector3(void)
{  }

//==========================================================================================================================
//
//Operator Overloads
//
//==========================================================================================================================
//=====Copy Assignment=====
Vector3& Vector3::operator=(const Vector3& V)
{
	_x = V.GetX();
	_y = V.GetY();
	_z = V.GetZ();
	_w = V.GetW();

	return *this; 
}

Vector3& Vector3::operator=(const Vector2& V)
{
	_x = V.GetX();
	_y = V.GetY();
	_z = 0.0f;
	_w = 1.0f;

	return *this;
}

Vector3& Vector3::operator=(F32 val)
{
	_x = val; 
	_y = val; 
	_z = val; 

	return *this; 
}

//=====Add by vector=====
Vector3 Vector3::operator+(const Vector3& V)
{
	return Vector3(_x + V.GetX(), _y + V.GetY(), _z + V.GetZ());
}

Vector3& Vector3::operator+=(const Vector3& V)
{
	_x += V.GetX();
	_y += V.GetY();
	_z += V.GetZ();

	return *this; 
}

//=====Add by scalar===== 
Vector3 Vector3::operator+(F32 val)
{
	return Vector3(_x + val, _y + val, _z + val);
}

Vector3& Vector3::operator+=(F32 val)
{
	_x += val; 
	_y += val; 
	_z += val; 

	return *this; 
}

//=====Subtract by vector=====
Vector3 Vector3::operator-(const Vector3& V)
{
	return Vector3(_x - V.GetX(), _y - V.GetY(), _z - V.GetZ());
}

Vector3& Vector3::operator-=(const Vector3& V)
{
	_x -= V.GetX();
	_y -= V.GetY();
	_z -= V.GetZ();

	return *this; 
}

//=====Component-wise multiplication=====
Vector3 Vector3::operator*(const Vector3& V)
{
	return Vector3(_x * V.GetX(), _y * V.GetY(), _z * V.GetZ());
}

Vector3& Vector3::operator*=(const Vector3& V)
{
	_x *= V.GetX();
	_y *= V.GetY();
	_z *= V.GetZ();

	return *this; 
}

//=====Multiply by scalar=====
Vector3 Vector3::operator*(F32 val)
{
	return Vector3(_x * val, _y * val, _z * val);
}

Vector3& Vector3::operator*=(F32 val)
{
	_x *= val; 
	_y *= val; 
	_z *= val; 

	return *this; 
}

//=====Component-wise division=====
Vector3 Vector3::operator/(const Vector3& V)
{
	F32 vecX = V.GetX();
	F32 vecY = V.GetY();
	F32 vecZ = V.GetZ();

	assert(vecX != 0.0f || vecY != 0.0f || vecZ != 0.0f);

	return Vector3(_x / vecX, _y / vecY, _z / vecZ);
}

Vector3& Vector3::operator/=(const Vector3& V)
{
	F32 vecX = V.GetX();
	F32 vecY = V.GetY();
	F32 vecZ = V.GetZ();

	assert(vecX != 0.0f || vecY != 0.0f || vecZ != 0.0f);

	_x /= vecX;
	_y /= vecY;
	_z /= vecZ;

	return *this; 
}

//=====Divide by scalar=====
Vector3 Vector3::operator/(F32 val)
{
	assert(val != 0.0f);

	return Vector3(_x / val, _y / val, _z / val);
}

Vector3& Vector3::operator/=(F32 val)
{
	assert(val != 0.0f);

	_x /= val;
	_y /= val; 
	_z /= val; 

	return *this; 
}

//===== Comparison =====
bool Vector3::operator>(Vector3& vec)
{
	return 	_x > vec.GetX() &&
			_y > vec.GetY() &&
			_z > vec.GetZ();
}

bool Vector3::operator<(Vector3& vec)
{
	return 	_x < vec.GetX() &&
			_y < vec.GetY() &&
			_z < vec.GetZ();
}

bool Vector3::operator>=(Vector3& vec)
{
	return 	_x >= vec.GetX() &&
			_y >= vec.GetY() &&
			_z >= vec.GetZ();
}

bool Vector3::operator<=(Vector3& vec)
{
	return	_x <= vec.GetX() &&
			_y <= vec.GetY() &&
			_z <= vec.GetZ();
}

bool Vector3::operator==(Vector3& vec)
{
	return	_x == vec.GetX() &&
			_y == vec.GetY() &&
			_z == vec.GetZ();
}

bool Vector3::operator!=(Vector3& vec)
{
	return	_x != vec.GetX() &&
			_y != vec.GetY() &&
			_z != vec.GetZ();
}

//==========================================================================================================================
//
//Math Helper functions
//
//==========================================================================================================================
void Vector3::AddScaledVector(const Vector3& V, F32 scale)
{
	_x += V.GetX() * scale; 
	_y += V.GetY() * scale; 
	_z += V.GetZ() * scale; 
}

void Vector3::AddScaledVector(const Vector2& V, F32 scale)
{
	_x += V.GetX() * scale;
	_y += V.GetY() * scale;
}

//==========================================================================================================================
//
//Vector Functions
//
//==========================================================================================================================
F32 Vector3::DotProduct(const Vector3& V)
{
	return _x * V.GetX() + _y * V.GetY() + _z * V.GetZ();
}

Vector3 Vector3::CrossProduct(const Vector3& V)
{
	return Vector3(_y * V.GetZ() - _z * V.GetY(),
				   _z * V.GetX() - _x * V.GetZ(),
				   _x * V.GetY() - _y * V.GetX());
}

F32 Vector3::Magnitude(void)
{
	return sqrt(_x * _x + _y * _y  + _z * _z);
}

F32 Vector3::SqrMagnitude(void)
{
	return _x * _x + _y * _y + _z * _z;
}

void Vector3::Normalise(void)
{
	F32 mag = Magnitude();

	if(mag > 0)
	{
		(*this) *= 1 / mag;
	}
}
/*
void Vector3::MakeBasis(const Vector3& A, const Vector3& B, const Vector3& C)
{
	C = A.CrossProduct(B);

	if(C.SqrMagnitude() == 0.0) 
		return;

	C.Normalise();

	B = C.CrossProduct(A);
}
*/

void Vector3::Reset(void)
{
	_x = 0.0f; 
	_y = 0.0f; 
	_z = 0.0f; 
	_w = 1.0f; 
}

void Vector3::Set(F32 x, F32 y, F32 z)
{
	_x = x;
	_y = y;
	_z = z;
}