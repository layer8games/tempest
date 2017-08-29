/*========================================================================
A Vector class that will follow the rules of Mathematics. The equations 
that the Vectors use for each operation were taken from 3D Math Primer 
for Graphics and Game Development by Dunn and Parberry. 

There are two classes that are created in this file. They are the Vector2
and the Vector3. The difference is whether the z can be changed or not. In
a Vector2, once it is created the z will stay the same no matter what, where
in the Vector3, the z will change dynamically as expected. 

Both have 4 elements, but the difference is how the elements are allowed 
to be changed throughout the life of the object. 

w is a special value that is used for computations convience. It is there
so that the vector can be transformed by a 4x4 matrix. As such, it will 
not be changed in any of the operators. Maybe later there will be a reason
to actually change the value of w, but for now I don't see a good reason 
to add this functionality.

Vector2

A 2D vector that is meant to be used in 2D space. It has 4 components still, but this is for easy mulitplication with the matrix class. 
In the operators, Z will never change. This is true for addition. subtraction, mulitplication and divition. When it comes to multiplication, 
it is important to keep in mind how vector multiplication works. For the Dot and Cross product operations, Z is involved and can change, also
in the maginitude it can change, and in unit, but this should be as expected. Z is also updated in the component multiplication update, as that
seems more nature than ignoring it. 

The most important thing to note is the +, +=, -, -= operations. 

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#ifndef VECTOR2_H
#define VECTOR2_H

//=====Engine Includes=====
#include <Engine/Atom.h>

//=====Other Includes=====
#include <cassert>

namespace KillerMath
{
	class Vector2
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		Vector2(void);

		Vector2(F32 val);

		Vector2(F32 x, F32 y);

		Vector2(const Vector2& V);

		~Vector2(void);
//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		F32 GetX(void) const
		{
			return _x;
		}

		void SetX(F32 x)
		{
			_x = x;
		}

		F32 GetY(void) const
		{
			return _y;
		}

		void SetY(F32 y)
		{
			_y = y;
		}

		F32 GetZ(void) const
		{
			return _z;
		}

		F32 GetW(void) const
		{
			return _w;
		}

//==========================================================================================================================
//
//Operator Overloads
//
//==========================================================================================================================
//=====Copy assignment=====
	Vector2& operator=(const Vector2& V);

//=====Add by vector=====
	Vector2 operator+(const Vector2& V);

	Vector2& operator+=(const Vector2& V);		

//=====Add by scalar=====
	Vector2 operator+(F32 val);

	Vector2& operator+=(F32 val);

//=====Subtract from vector=====
	Vector2 operator-(const Vector2& V);

	Vector2& operator-=(const Vector2& V);

//=====Subtract from scalar=====
	Vector2 operator-(F32 val);

	Vector2& operator-=(F32 val);

//=====Component-wise multiply by vector=====
	Vector2 operator*(const Vector2& V);

	Vector2& operator*=(const Vector2& V);

//=====Multiply by scalar=====
	Vector2 operator*(F32 val);

	Vector2& operator*=(F32 val);

//=====Component-wise Divide by vector=====	
	Vector2 operator/(const Vector2& V);

	Vector2& operator/=(const Vector2& V);

//=====Divide by scalar=====
	Vector2 operator/(F32 val);

	Vector2& operator/=(F32 val);

//==========================================================================================================================
//
//Vector Functions
//
//==========================================================================================================================
	F32 DotProduct(const Vector2& V);

	F32 Magnitude(void);

	F32 SqrMagnitude(void);

	void Normalize(void);

	void Reset(void);

	void Reset(F32 val);

//==========================================================================================================================
//
//Misc Math Helpers
//
//==========================================================================================================================
	void AddScaledVector(const Vector2& V, F32 scale);

	private:
		F32 _x;
		F32 _y; 
		F32 _z; 
		F32 _w;

	};//end Class
}//end Namespace
#endif