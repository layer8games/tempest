#pragma once

//===== Killer Includes =====
#include <Engine/Atom.h>


//===== Stnadard inlcudes =====
#include <cassert>

namespace KillerMath
{
	class Vector
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		Vector(void);

		explicit Vector(F32 val);

		Vector(F32 x, F32 y);

		Vector(F32 x, F32 y, F32 z);

		Vector(F32 x, F32 y, F32 z, F32 w);

		Vector(const Vector& v);

		~Vector(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
//===== 2D checks =====		
		inline void Make2D(void)
		{
			_2D = true;
		}

		inline void Make3D(void)
		{
			_2D = false;
		}

		inline bool Is2D(void) const
		{
			return _2D;
		}

		inline const F32* GetElems(void) const
		{
			return _data;
		}

//===== Vector Special functions =====
		F32 DotProduct(const Vector& vec);

		Vector CrossProduct(const Vector& vec);

		F32 Magnitude(void);

		F32 SqrMagnitude(void);

		void Normalize(void);

		void Reset(F32 val=0.0f);

//===== Math Helper Functions =====
		void AddScaledVector(const Vector& vec, F32 scale);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		inline F32* GetPointer(void)
		{
			return _data;
		}

		inline void Set(F32 xVal, F32 yVal, F32 zVal)
		{
			_data[x] = xVal;
			_data[y] = yVal;
			_data[z] = zVal;
		}

//==========================================================================================================================
//
//operator Overloads
//
//==========================================================================================================================
		inline const F32& operator[](int i) const
		{
			return _data[i];
		}

		inline F32& operator[](int i)
		{
			return _data[i];
		}

//===== Copy Assignment =====		
		Vector& operator=(const Vector& vec);

		Vector& operator=(F32 val);

//===== Add by Vector =====
		Vector operator+(const Vector& vec) const;

		Vector& operator+=(const Vector& vec);

//===== Add by scalar =====
		Vector operator+(F32 val) const;

		Vector& operator+=(F32 val);

		Vector operator+(shared_ptr<Vector> vec) const;

//===== Subtract by Vector =====
		Vector operator-(const Vector& vec) const;

		Vector& operator-=(const Vector& vec);

//===== Subtract by scalar =====
		Vector operator-(F32 val) const;

		Vector& operator-=(F32 val);

//===== Component-wise multiply by vector =====
		Vector operator*(const Vector vec) const;

		Vector& operator*=(const Vector vec);

//===== Mutliply by Scalar =====
		Vector operator*(F32 val) const;

		Vector& operator*=(F32 val);

//===== Component-wise divide by vector =====
		Vector operator/(const Vector vec) const;

		Vector& operator/=(const Vector vec);

//===== Divide by scalar =====
		Vector operator/(F32 val) const;

		Vector& operator/=(F32 val);

//===== Comparison =====
		bool operator>(const Vector& vec) const;

		bool operator<(const Vector& vec) const;

		bool operator>=(const Vector& vec) const;

		bool operator<=(const Vector& vec) const;

		bool operator==(const Vector& vec) const;

		bool operator!=(const Vector& vec) const;


	private:
		enum {
			x = 0,
			y = 1,
			z = 2,
			w = 3
		};

		bool _2D;
		F32  _data[4];
	};
}