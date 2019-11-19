#pragma once

//=====Killer1 includes=====
#include <Engine/Atom.h>
#include <Engine/Vector3.h>
#include <Engine/Vector4.h>
#include <Engine/Quaternion.h>

#include <vector>
#include <cassert>

namespace TempestMath 
{
//==========================================================================================================================
//Documentation
//========================================================================================================================== 
///	The Matrix3 is a 3x3 Matrix meant to be mathematically sound. The functions found here have been tested and are built 
///	according to linear algebra rules. The Matrices are column major to adhere to the format used within OpenGL. 
///	The data for the class is represented by an array of Vector4. This means that you can index into a specific element of
///	the Matrix, say, colume 2, row 1 by using [2][1]. In the rest of the this documentation, this type of value will be 
///	represented by the term mrowcolumn. For example, colum 2, row 1 will look like m21, read m two one.
	class TEMPEST_API Matrix3
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
///	Default constructor. Sets all values to 0.
		Matrix3(void);

		Matrix3(const Vector3& x, const Vector3& y, const Vector3& z);

		Matrix3(const Vector4& x, const Vector4& y, const Vector4& z);

		explicit Matrix3(const F32 val); 

///	All value constructor. Takes a list of values and turns them into a Matrix3 of the same mapping. 
///	\param m00 is the value for element m00.
///	\param m01 is the value for element m01.
///	\param m02 is the value for element m02
///	\param m10 is the value for element m10.
///	\param m11 is the value for element m11.
///	\param m12 is the value for element m12
///	\param m20 is the value for element m20.
///	\param m21 is the value for element m21.
///	\param m22 is the value for element m22
		Matrix3( F32 m00, F32 m01, F32 m02,
				 F32 m10, F32 m11, F32 m12,
				 F32 m20, F32 m21, F32 m22 );
 
///	Copy Constructor. Calls Matrix3::[] to, which will copy the Vector4 from each colume of M into this Matrix.
///	\param M is the matrix to copy into this one.	
		Matrix3(const Matrix3& M);

//==========================================================================================================================
//
//Matrix3 functions
//
//========================================================================================================================== 
///	Return the array containing all the elements. 
		const std::vector<F32> GetElems(void) const;

//==========================================================================================================================
//Scaling
//==========================================================================================================================
///	Creates a matrix that will perform a scaling transformation in 2D.
///	\param xVal is the amount to scale in the x axis. 
///	\param yVal is the amount to scale in the y axis.
		static Matrix3 Scale(F32 xVal, F32 yVal);

///	Creates a matrix that will perform a scaling transformation in 3D.
///	\param xVal is the amount to scale in the x axis. 
///	\param yVal is the amount to scale in the y axis.
///	\param zVal is the amount to scale in the z axis. 
		static Matrix3 Scale(F32 xVal, F32 yVal, F32 zVal);

///	Creates a matrix that will perform a scaling translation equal to the x y and z values in a Vector3.
///	\param vec contains the values used in the scaling. 
		static Matrix3 Scale(const Vector3& vec);

///	Creates a matrix that will perform a scaling translation equal to the x y and z values in a Vector4.
///	\param vec contains the values used in the scaling. 
		static Matrix3 Scale(const Vector4& vec);

///	Sets this matrix to perform a scaling transformation in 2D.
///	\param xVal is the amount to scale in the x axis. 
///	\param yVal is the amount to scale in the y axis.
		void SetScale(F32 xVal, F32 yVal);

///	Sets this matrix to perform a scaling transformation in 3D.
///	\param xVal is the amount to scale in the x axis. 
///	\param yVal is the amount to scale in the y axis.
///	\param zVal is the amount to scale in the z axis. 		
		void SetScale(F32 xVal, F32 yVal, F32 zVal);

///	Sets this matrix to perform a scaling translation equal to the x y and z values in a Vector3.
///	\param vec contains the values used in the scaling.  
		void SetScale(const Vector3& vec);

///	Sets this matrix to perform a scaling translation equal to the x y and z values in a Vector4.
///	\param vec contains the values used in the scaling. 
		void SetScale(const Vector4& vec);

///	Increases the scaling translation in 2D.
///	\param x Value of scale on x axis.
///	\param y Value of scale on y axis. 
		void AddScale(F32 xVal, F32 yVal);
 
///	Increases the scaling translation in 3D.
///	\param x Value of scale on x axis.
///	\param y Value of scale on y axis.
///	\param z Value of scale on z axis. 
		void AddScale(F32 xVal, F32 yVal, F32 zVal);

///	Increases the scaling translation equal to the x y and z values in a Vector3.
///	\param vec contains the values that will increase the scale.
		void AddScale(const Vector3& vec);

///	Increases the scaling translation equal to the x y and z values in a Vector4.
///	\param vec contains the values that will increase the scale.
		void AddScale(const Vector4& vec);

//==========================================================================================================================
//Rotations
//==========================================================================================================================
///	Creates a matrix that will perform a rotation around the x axis.
///	\param val is the angle to rotate in degrees. 
		static Matrix3 RotateX(F32 val);

///	Creates a matrix that will perform a rotation around the y axis.
///	\param val is the angle to rotate in degrees. 
		static Matrix3 RotateY(F32 val);

///	Creates a matrix that will perform a rotation around the z axis.
///	\param val is the angle to rotate in degrees. 
		static Matrix3 RotateZ(F32 val);

///	Resets Matrix3 and creates rotation around the x axis. Call MakeIdentiy().
///	\bug This is not working at all. 
///	\param x F32. Degree of rotation around x axis. Calls RADIAN() 
		void SetRotateX(F32 val);
 
///	Creates rotation around the x axis without resetting other values. 
///	\bug Completely untested and probably not working at all. 
///	\param x Degree of rotation around x axis. Calls RADIAN() 
		void AddRotateX(F32 val);

///	Resets Matrix4 and creates rotation around the y axis. Call MakeIdentiy().
///	\bug This is not working at all. 
///	\param x Degree of rotation around x axis. Calls RADIAN() 
		void SetRotateY(F32 val);

///	Creates rotation around the x axis without resetting other values. 
///	\bug Completely untested and probably not working at all. 
///	\param x Degree of rotation around x axis. Calls RADIAN() 
		void AddRotateY(F32 val);

///	Resets Matrix3 and creates rotation around the z axis. Call MakeIdentiy().
///	\bug This is not working at all. 
///	\param z F32. Degree of rotation around z axis. Calls RADIAN() 
		void SetRotateZ(F32 val);

///	Creates rotation around the z axis without resetting other values. 
///	\bug Completely untested and probably not working at all. 
///	\param z F32. Degree of rotation around z axis. Calls RADIAN() 
		void AddRotateZ(F32 val);

///	Resets the Matrix3 and creates an Matrix3 which will perform a rotation around the x, y and z axis in that order. 
///	Calls MakeIdentity() 
///	\bug Not working at all. The math is wrong, and rotations are not working in general.
///	\param x F32. Degree of rotation around the x axis. Calls RADIAN()
///	\param y F32. Degree of rotation around the y axis. Calls RADIAN()
///	\param z F32. Degree of rotation around the z axis. Calls RADIAN() 
		void SetRotate(F32 xVal, F32 yVal, F32 zVal);

///	Creates rotation around the x, y and z axis, in that order, without resetting other values.
///	\bug Not working at all. The math is wrong, and rotations are not working in general.
///	\param x F32. Degree of rotation around the x axis. Calls RADIAN()
///	\param y F32. Degree of rotation around the y axis. Calls RADIAN()
///	\param z F32. Degree of rotation around the z axis. Calls RADIAN()
		void AddRotation(F32 xVal, F32 yVal, F32 zVal);

///	Sets the rotational transform of the matrix equal to the orientation contained in teh Quaternion. This is currently untested.
///	\param q conatins the orientation to set. 
		void SetOrientation(const Quaternion& q);

//==========================================================================================================================
//Inverse
//==========================================================================================================================		
///	Changes this matrix to equal its inverse. Warning, this is a very expensive function to call. 
		void SetInverse(void);

///	Changes this matrix to equal the inverse of another. Warning, very expsenive function to call. 
///	\param mat inverse will be set to this matrix. 
		void SetAsInverse(const Matrix3& mat);

///	Returns a matrix that is the inverse of this one. Warning, very expensive function to call. 
		Matrix3 GetInverse(void) const;

///	Returns the determinate of this matrix. This has many uses, and if you are not sure what a determinate is, I have a lot
///	of books you can read...
		F32 Determinate(void) const;
//==========================================================================================================================
//Resettings
//==========================================================================================================================
///	Sets all values of the Matrix4 to 0, with the diagnal set to 1.
		void MakeIdentity(void)
		{
			Reset(1.0f);
		}	

///	Sets all the values of the Matrix4 to 0, with the diagnal set to val.
///	\param val Value of the diagnal of the Matrix4. 		
		void Reset(F32 val=0.0f);

//==========================================================================================================================
//Misc
//==========================================================================================================================		 
///	Reverses the Column/Row order of the Matrix3. 
		void Transpose(void);

///	Also known as a straight multiplication. Multiplies each value of this Matrix4 by the matching value of M.
///	\param M Matrix4&. Right hand value to multiply by. 	
		void ComponentMulti(const Matrix3& M);

///	Helper function that will return the transformed version of a matrix.
///	\param mat is transformed.
		Matrix3 Matrix3::Transform(const Matrix3& mat) const;

///	Helper function that will return the transformed version of a vector. 
///	\param vec is transformed. 
		Vector4 Matrix3::Transform(const Vector4& vec) const;

//==========================================================================================================================
//
//Operator Overloads
//
//==========================================================================================================================
///	Used to access the ith column of the Matrix4.
///	\param i is the index to return. Cannot be greater than 3. There are only 4 columns. 
		inline const Vector3& operator[](int i) const
		{
			return _data[i];
		}

///	Used to access the ith column of the Matrix4. This version allows you to edit the values in the column.
///	\param i is the index to return. Cannot be greater than 3. There are only 4 columns. 
		inline Vector3& operator[](int i)
		{
			return _data[i];
		}
 
///	Assigns this matrix to be equal to the values of another.
///	\param mat is the matrix that is copied. 
		Matrix3& operator=(const Matrix3& mat);
		
///	Performs a Matrix4 style multiplication.
///	\param mat is the matrix that is multiplied by this matrix. 
		Matrix3 operator*(const Matrix3& mat) const;

///	Performs Matrix4 multiplication with Vector4.
///	\param vec is the vector that is multiplied by this matrix. 
		Vector4 operator*(const Vector4& vec) const;

///	Divides each element of this matrix, setting it to the results. 
///	\param val is the value that this matrix is divided by. 
		Matrix3& operator/=(F32 val);

	private:
//==========================================================================================================================
//
//Private functions
//
//==========================================================================================================================
///	Returns the cofactor for the sub matrix made up of the 3 Vector4 passed in. This is used in Matrix4::Inverse as part of 
///	what is called a Classic Adjoint. 
///	\param c00 is the first element of the first column of the sub matrix.
///	\param c01 is the second element of the first column of the sub matrix.
///	\param c10 is the first element of the second column of the sub matrix.
///	\param c11 is the second element of the second column of the sub matrix. 
		F32 _Cofactor(F32 c00, F32 c01, F32 c10, F32 c11) const;

//==========================================================================================================================
//
//Data
//
//==========================================================================================================================
		Vector3 _data[3];		///< The matrix itself, represented by 3 Vector43in an array.
	};
	typedef shared_ptr<Matrix3> p_Matrix3;
}//End namespace
