#include <Engine/Vector2.h>

namespace KillerMath
{
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
	Vector2::Vector2(void) : _x(0.0f), _y(0.0f), _z(0.0f), _w(1.0f)
	{  }

	Vector2::Vector2(F32 val) : _x(val), _y(val), _z(0.0f), _w(1.0f)
	{  }

	Vector2::Vector2(F32 x, F32 y) : _x(x), _y(y), _z(0.0f), _w(1.0f)
	{  }

	Vector2::Vector2(const Vector2& V) : _x(0.0f), _y(0.0f), _z(0.0f), _w(1.0f)
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

//=====Add by vector=====
	Vector2 Vector2::operator+(const Vector2& V)
	{
		return Vector2(_x + V.GetX(), _y + V.GetY());
	}

	Vector2& Vector2::operator+=(const Vector2& V)
	{
		_x += V.GetX();
		_y += V.GetY();

		return *this; 
	}

}//end namespace