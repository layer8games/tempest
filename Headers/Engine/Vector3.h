/*========================================================================


This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Vector2.h>

//=====Other includes=====
#include <cassert>

namespace KillerMath
{
	//=====Declaration=====
	class Vector2;

	class Vector3
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		Vector3(void);

		explicit Vector3(F32 val);

		Vector3(F32 x, F32 y);

		Vector3(F32 x, F32 y, F32 z);

		Vector3(F32 x, F32 y, F32 z, F32 w);

		Vector3(const Vector3& V);

	 	explicit Vector3(const Vector2& V);

		~Vector3(void);
//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
	F32 GetX(void) const
	{
		return _x;
	}
	
	void SetX(F32 val)
	{
		_x = val;
	}

	F32 GetY(void) const
	{
		return _y;
	}

	void SetY(F32 val)
	{
		_y = val;
	}

	F32 GetZ(void) const
	{
		return _z; 
	}

	void SetZ(F32 val)
	{
		_z = val; 
	}

	F32 GetW(void) const
	{
		return _w;
	}

	void SetW(F32 val)
	{
		_w = val; 
	}
//==========================================================================================================================
//
//Operator Overloads
//
//==========================================================================================================================
//=====Copy Assignment=====
	Vector3& operator=(const Vector3& V);

	Vector3& operator=(const Vector2& V);

	Vector3& operator=(F32 val);

//=====Add by vector=====	
	Vector3 operator+(const Vector3& V) const;

	Vector3 operator+(shared_ptr<Vector3> v) const;

	Vector3& operator+=(const Vector3& V);

//=====Add by scalar=====
	Vector3 operator+(F32 val) const;

	Vector3& operator+=(F32 val);

//=====Subtract by vector=====
	Vector3 operator-(const Vector3& V);

	Vector3& operator-=(const Vector3& V);

//=====Subtract by scalar=====
	Vector3 operator-(F32 val);

	Vector3& operator-=(F32 val);

//=====Component-wise multiplication=====
	Vector3 operator*(const Vector3& V);

	Vector3& operator*=(const Vector3& V);

//=====Multiply by scalar=====
	Vector3 operator*(F32 val);

	Vector3& operator*=(F32 val);

//=====Component-wise division=====
	Vector3 operator/(const Vector3& V);

	Vector3& operator/=(const Vector3& V);

//=====Divide by scalar=====
	Vector3 operator/(F32 val);

	Vector3& operator/=(F32 val);

//===== Comparison =====
	bool operator>(Vector3& vec);

	bool operator<(Vector3& vec);

	bool operator>=(Vector3& vec);

	bool operator<=(Vector3& vec);

	bool operator==(Vector3& vec);

	bool operator!=(Vector3& vec);

//==========================================================================================================================
//
//Math Helper functions
//
//==========================================================================================================================
	void AddScaledVector(const Vector3& V, F32 scale);

	void AddScaledVector(const Vector2& V, F32 scale);

//==========================================================================================================================
//
//Vector Functions
//
//==========================================================================================================================
	F32 DotProduct(const Vector3& V);

	Vector3 CrossProduct(const Vector3& V);

	F32 Magnitude(void);

	F32 SqrMagnitude(void);

	void Normalize(void);

	//Need to rethink the purpose of this function
	//void MakeBasis(const Vector3& A, const Vector3& B, const Vector3& C);

	void Reset(void);

	void Set(F32 x, F32 y, F32 z);

	private:
		F32 _x; 
		F32 _y;
		F32 _z;
		F32 _w;
		
	};//end Class
}//end Namespace