/*=========================================================================
The Matrix is meant to be mathematically sound. The functions found here
have been tested and are built according to linear algebra rules. The 

Matrices will be column major to ahdere to the format used within opengl, 
and only 4x4 Matrices will be supported. This is because I cannot find any 
useful reason to suport a dynamic type at this time. In the future if other
Matrices appear to be useful, this class will basically be copied and will
be turned into whatever other type of Matrix is needed, be it a 3x3 or 2x2
or whatever. This class will only be a 4x4.

A typedef will be created in the Atom.h that will allow an object of this 
class to be created by just calling "matrix" as a class. 

Constructors: There are several ways to create a Matrix with this class.

matrix(single value) will create a identiy matrix of said value. 

maxtrix(16 values) will create a matrix as intended. It can take an array
or the values themselves. 

Since the matrix is column major, it is mapped as such: 

| m00 | m10 | m20 | m30 |
| m01 | m11 | m21 | m31 |
| m03 | m12 | m22 | m32 |
| m04 | m13 | m23 | m33 |

This means that _m[0] -> _m[3] == m00 -> m04

What this looks like is this:

| _m[0] | _m[4] | _m[8]  | _m[12] |
| _m[1] | _m[5] | _m[9]  | _m[13] |
| _m[2] | _m[6] | _m[10] | _m[14] |
| _m[3] | _m[7] | _m[11] | _m[15] |

This is the way that the array mapping looks, for a quick reference. 

For the construction of the orthographic or persepctive matricies, there
is a funcion that you call to return the specified matrix. 

Matrix::Orthographic(width, height, depth)

Matrix::Perspective(width, height, depth)

Transform and Scale will change the Matrix first into an idenity Matrix, 
then will add the scale or transform to the matrix. This eseentially makes
the matrix onlyi that scale or transform. 

AddScale and AddTransform will add the scale or transform to the matrix while
preserving all other asepcts of the matrix. This will make for faster and more
efficient combination of actions that a matrix and take. 

Transpose. This may be useful later, but now so much now. 

This is not free to use, and cannot be used without the express permission
of KillerWave or Layer8, or whatever I am called now.

Written by Maxwell Miller
=========================================================================*/
#pragma once

//=====Killer1 includes=====
#include <Engine/Atom.h>
#include <Engine/Vector2.h>
#include <Engine/Vector3.h>

namespace KillerMath 
{
	class Matrix
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		Matrix(void) ;
		
		explicit Matrix(F32 val);
		
		explicit Matrix(const F32 mSrc[16]);
		
		Matrix( F32 m00, F32 m01, F32 m02, F32 m03,
				 F32 m10, F32 m11, F32 m12, F32 m13,
				 F32 m20, F32 m21, F32 m22, F32 m23,
				 F32 m30, F32 m31, F32 m32, F32 m33);

		Matrix(const Matrix& M);

//==========================================================================================================================
//
//Matrix functions
//
//==========================================================================================================================
//==========================================================================================================================
//Projections
//==========================================================================================================================		
		void MakeOrthographic(F32 width, F32 height, F32 depth, bool center=true);

		void MakePerspective(F32 width, F32 height, F32 depth, bool center=true);

		void MakePerspective(F32 fieldOfView, F32 aspectRatio, F32 nearPlane, F32 farPlane);

//==========================================================================================================================
//Translations
//==========================================================================================================================
		void Translate(F32 x, F32 y);

		void Translate(F32 x, F32 y, F32 z);

		void Translate(const Vector2& vec);

		void Translate(const Vector3& vec);

		void AddTranslate(F32 x, F32 y);

		void AddTranslate(F32 x, F32 y, F32 z);

		void AddTranslate(const Vector2& vec);

		void AddTranslate(const Vector3& vec);

//==========================================================================================================================
//Scaling
//==========================================================================================================================
		void Scale(F32 x, F32 y);

		void Scale(F32 x, F32 y, F32 z);

		void Scale(const Vector2& vec);

		void Scale(const Vector3& vec);

		void AddScale(F32 x, F32 y);

		void AddScale(F32 x, F32 y, F32 z);

		void AddScale(const Vector2& vec);

		void AddScale(const Vector3& vec);

//==========================================================================================================================
//Rotations
//==========================================================================================================================
		void RotateX(F32 x);

//=====Consider adding an AddRotateX() function here. This would preserve any existing values and add the rotation to it.=====
		void RotateY(F32 y);

		void RotateZ(F32 z);

		void Rotate(F32 x, F32 y, F32 z);		
		
//==========================================================================================================================
//Resettings
//==========================================================================================================================
		void MakeIdentity(void)
		{
			ResetMatrix(1);
		}	

		void ResetMatrix(F32 val);

//==========================================================================================================================
//Misc
//==========================================================================================================================		
		void Transpose(void);

		void ComponentMulti(const Matrix& M);

//==========================================================================================================================
//
//Accessor
//
//==========================================================================================================================
//=====Return the array containing all the elements=====
		const F32* GetElems(void) const 
		{ 
			return _m; 
		}

//=====Return each element===== 
		F32 Get11(void) const 
		{ 
			return _m[0];  
		}
		
		F32 Get12(void) const 
		{ 
			return _m[1];  
		}
		
		F32 Get13(void) const 
		{ 
			return _m[2];  
		}
		
		F32 Get14(void) const 
		{ 
			return _m[3];  
		}

		F32 Get21(void) const 
		{ 
			return _m[4];  
		}
		
		F32 Get22(void) const 
		{ 
			return _m[5];  
		}
		
		F32 Get23(void) const 
		{ 
			return _m[6];  
		}
		
		F32 Get24(void) const 
		{ 
			return _m[7];  
		}

		F32 Get31(void) const 
		{ 
			return _m[8];  
		}
		
		F32 Get32(void) const 
		{ 
			return _m[9];  
		}
		
		F32 Get33(void) const 
		{ 
			return _m[10]; 
		}
		
		F32 Get34(void) const 
		{ 
			return _m[11]; 
		}

		F32 Get41(void) const 
		{ 
			return _m[12]; 
		}
		
		F32 Get42(void) const 
		{ 
			return _m[13]; 
		}
		
		F32 Get43(void) const 
		{ 
			return _m[14]; 
		}
		
		F32 Get44(void) const 
		{ 
			return _m[15]; 
		}

//==========================================================================================================================
//
//Operator Overloads
//
//==========================================================================================================================
		Matrix& operator=(const Matrix& M);
		
		Matrix& operator*(const Matrix& RightMatrix);
		
		Matrix& operator*=(Matrix& RHM);

		Vector2 operator*(const Vector2& RHV);

		Vector3 operator*(const Vector3& RHV);

	private:
		F32 _m[16];
	};

}//End namespace
