#include <Engine/Vector2.h>

using namespace KillerMath;

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Vector2::Vector2(void) 
: 
_x(0.0f), 
_y(0.0f), 
_z(0.0f), 
_w(1.0f)
{  }

Vector2::Vector2(F32 val)
: 
_x(val), 
_y(val), 
_z(0.0f), 
_w(1.0f)
{  }

Vector2::Vector2(F32 x, F32 y)
: 
_x(x), 
_y(y), 
_z(0.0f), 
_w(1.0f)
{  }

Vector2::Vector2(const Vector2& V)
: 
_x(V.GetX()), 
_y(V.GetY()),
 _z(0.0f), 
 _w(1.0f)
{  }

Vector2::Vector2(const Vector3& V)
: 
_x(V.GetX()), 
_y(V.GetY()), 
_z(0.0f), 
_w(1.0f)
{  }

Vector2::~Vector2(void)
{  }

//==========================================================================================================================
//
//Operator Overloads
//
//==========================================================================================================================
//=====Copy assignment=====
Vector2& Vector2::operator=(const Vector2& V)
{
	_x = V.GetX();
	_y = V.GetY();
	_z = V.GetZ();
	_w = V.GetW();

	return *this; 
}

Vector2& Vector2::operator=(const Vector3& V)
{
	_x = V.GetX();
	_y = V.GetY();
	_z = 0.0f;
	_w = 1.0f;

	return *this; 
}

Vector2& Vector2::operator=(F32 val)
{
	_x = val; 
	_y = val;

	return *this;
}

//=====Add by vector=====
Vector2 Vector2::operator+(const Vector2& V) const
{
	return Vector2(_x + V.GetX(), _y + V.GetY());
}

Vector2& Vector2::operator+=(const Vector2& V)
{
	_x += V.GetX();
	_y += V.GetY();

	return *this; 
}

//=====Add by scalar=====
Vector2 Vector2::operator+(F32 val)
{
	return Vector2(_x + val, _y + val);
}

Vector2& Vector2::operator+=(F32 val)
{
	_x += val; 
	_y += val; 

	return *this; 
}

//=====Subtract by vector=====
Vector2 Vector2::operator-(const Vector2& V)
{
	return Vector2(_x - V.GetX(), _y - V.GetY());
}

Vector2& Vector2::operator-=(const Vector2& V)
{
	_x -= V.GetX();
	_y -= V.GetY();

	return *this; 
}

//=====Subtract by scalar=====
Vector2 Vector2::operator-(F32 val)
{
	return Vector2(_x - val, _y - val);
}

Vector2& Vector2::operator-=(F32 val)
{
	_x -= val; 
	_y -= val; 

	return *this; 
}

//=====Component-wise multiply by vector=====
Vector2 Vector2::operator*(const Vector2& V)
{
	return Vector2(_x * V.GetX(), _y * V.GetY());
}

Vector2& Vector2::operator*=(const Vector2& V)
{
	_x *= V.GetX();
	_y *= V.GetY();

	return *this; 
}

//=====Multiply by scalar=====
Vector2 Vector2::operator*(F32 val)
{
	return Vector2(_x * val, _y * val);
}

Vector2& Vector2::operator*=(F32 val)
{
	_x *= val; 
	_y *= val; 

	return *this; 
}

//=====Component-wise Divide by vector=====	
Vector2 Vector2::operator/(const Vector2& V)
{
	F32 vecX = V.GetX();
	F32 vecY = V.GetY();

	assert(vecX != 0.0f || vecY != 0.0f);

	return Vector2(_x / vecX, _y / vecY);
}

Vector2& Vector2::operator/=(const Vector2& V)
{
	F32 vecX = V.GetX();
	F32 vecY = V.GetY();

	assert(vecX != 0.0f || vecY != 0.0f);

	_x /= vecX;
	_y /= vecY;

	return *this; 
}

//=====Divide by scalar=====
Vector2 Vector2::operator/(F32 val)
{
	assert(val != 0.0f);
	
	return Vector2(_x / val, _y / val);
}

Vector2& Vector2::operator/=(F32 val)
{
	assert(val != 0.0f);

	_x /= val; 
	_y /= val; 

	return *this; 
}

//===== Comparison =====
bool Vector2::operator>(Vector2& vec)
{
	return 	_x > vec.GetX() &&
			_y > vec.GetY();
}

bool Vector2::operator<(Vector2& vec)
{
	return 	_x < vec.GetX() &&
			_y < vec.GetY();
}

bool Vector2::operator>=(Vector2& vec)
{
	return 	_x >= vec.GetX() &&
			_y >= vec.GetY();
}

bool Vector2::operator<=(Vector2& vec)
{
	return 	_x <= vec.GetX() &&
			_y <= vec.GetY();
}

bool Vector2::operator==(Vector2& vec)
{
	return 	_x == vec.GetX() &&
			_y == vec.GetY();
}

bool Vector2::operator!=(Vector2& vec)
{
	return 	_x != vec.GetX() &&
			_y != vec.GetY();
}

//==========================================================================================================================
//
//Vector Functions
//
//==========================================================================================================================	
F32 Vector2::DotProduct(const Vector2& V)
{
	return _x * V.GetX() + _y * V.GetY();
}

F32 Vector2::Magnitude(void)
{
	return sqrt(_x * _x + _y * _y);
}

F32 Vector2::SqrMagnitude(void)
{
	return _x * _x + _y * _y;
}

void Vector2::Normalize(void)
{
	F32 mag = Magnitude();

	if(mag > 0.0f)
	{
		(*this) *= 1.0f / mag;
	}
}

void Vector2::Reset(void)
{
	_x = 0.0f; 
	_y = 0.0f;
}

void Vector2::Set(F32 x, F32 y)
{
	_x = x;
	_y = y;
}

//==========================================================================================================================
//
//Misc Math Helpers
//
//==========================================================================================================================
void Vector2::AddScaledVector(const Vector2& V, F32 scale)
{
	_x += V.GetX() * scale; 
	_y += V.GetY() * scale; 
}

void Vector2::AddScaledVector(const Vector3& V, F32 scale)
{
	_x += V.GetX() * scale; 
	_y += V.GetY() * scale; 
}