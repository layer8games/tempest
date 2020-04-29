#pragma once

//=====Killer1 includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/Vector2.h>
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
    class Matrix3
    {
    public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
        ///	Default constructor. Sets all values to 0.
        TEMPEST_API Matrix3(void);

        TEMPEST_API Matrix3(const Vector3& x, const Vector3& y, const Vector3& z);

        TEMPEST_API Matrix3(const Vector4& x, const Vector4& y, const Vector4& z);

        TEMPEST_API explicit Matrix3(const real val);

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
        TEMPEST_API Matrix3( real m00, real m01, real m02,
                             real m10, real m11, real m12,
                             real m20, real m21, real m22 );
 
        ///	Copy Constructor. Calls Matrix3::[] to, which will copy the Vector4 from each colume of M into this Matrix.
        ///	\param M is the matrix to copy into this one.	
        TEMPEST_API Matrix3(const Matrix3& otherMatrix);

//==========================================================================================================================
//
//Matrix3 functions
//
//========================================================================================================================== 
        ///	Return the array containing all the elements. 
        TEMPEST_API const std::vector<real> GetElems(void) const;

//==========================================================================================================================
//Scaling
//==========================================================================================================================
        ///	Creates a matrix that will perform a scaling transformation in 2D.
        ///	\param xVal is the amount to scale in the x axis. 
        ///	\param yVal is the amount to scale in the y axis.
        TEMPEST_API static Matrix3 Scale(real xVal, real yVal);

        ///	Creates a matrix that will perform a scaling transformation in 3D.
        ///	\param xVal is the amount to scale in the x axis. 
        ///	\param yVal is the amount to scale in the y axis.
        ///	\param zVal is the amount to scale in the z axis. 
        TEMPEST_API static Matrix3 Scale(real xVal, real yVal, real zVal);

        ///	Creates a matrix that will perform a scaling translation equal to the x y and z values in a Vector3.
        ///	\param vec contains the values used in the scaling. 
        TEMPEST_API static Matrix3 Scale(const Vector3& vec);

        ///	Creates a matrix that will perform a scaling translation equal to the x y and z values in a Vector4.
        ///	\param vec contains the values used in the scaling. 
        TEMPEST_API static Matrix3 Scale(const Vector4& vec);

        ///	Sets this matrix to perform a scaling transformation in 2D.
        ///	\param xVal is the amount to scale in the x axis. 
        ///	\param yVal is the amount to scale in the y axis.
        TEMPEST_API void SetScale(real xVal, real yVal);

        ///	Sets this matrix to perform a scaling transformation in 3D.
        ///	\param xVal is the amount to scale in the x axis. 
        ///	\param yVal is the amount to scale in the y axis.
        ///	\param zVal is the amount to scale in the z axis. 		
        TEMPEST_API void SetScale(real xVal, real yVal, real zVal);

        ///	Sets this matrix to perform a scaling translation equal to the x y and z values in a Vector3.
        ///	\param vec contains the values used in the scaling.  
        ///	\param vec contains the values used in the scaling.  
        TEMPEST_API void SetScale(const Vector2& vec);
        
        ///	Sets this matrix to perform a scaling translation equal to the x y and z values in a Vector3.
        ///	\param vec contains the values used in the scaling.  
        TEMPEST_API void SetScale(const Vector3& vec);

        ///	Sets this matrix to perform a scaling translation equal to the x y and z values in a Vector4.
        ///	\param vec contains the values used in the scaling. 
        TEMPEST_API void SetScale(const Vector4& vec);

//==========================================================================================================================
//Rotations
//==========================================================================================================================
        ///	Creates a matrix that will perform a rotation around the x axis.
        ///	\param val is the angle to rotate in degrees. 
        TEMPEST_API static Matrix3 RotateX(real val);

        ///	Creates a matrix that will perform a rotation around the y axis.
        ///	\param val is the angle to rotate in degrees. 
        TEMPEST_API static Matrix3 RotateY(real val);

        ///	Creates a matrix that will perform a rotation around the z axis.
        ///	\param val is the angle to rotate in degrees. 
        TEMPEST_API static Matrix3 RotateZ(real val);

        ///	Resets Matrix3 and creates rotation around the x axis. Call MakeIdentiy().
        ///	\bug This is not working at all. 
        ///	\param x real. Degree of rotation around x axis. Calls RADIAN() 
        TEMPEST_API void SetRotateX(real val);
 
        ///	Creates rotation around the x axis without resetting other values. 
        ///	\bug Completely untested and probably not working at all. 
        ///	\param x Degree of rotation around x axis. Calls RADIAN() 
        TEMPEST_API void AddRotateX(real val);

        ///	Resets Matrix4 and creates rotation around the y axis. Call MakeIdentiy().
        ///	\bug This is not working at all. 
        ///	\param x Degree of rotation around x axis. Calls RADIAN() 
        TEMPEST_API void SetRotateY(real val);

        ///	Creates rotation around the x axis without resetting other values. 
        ///	\bug Completely untested and probably not working at all. 
        ///	\param x Degree of rotation around x axis. Calls RADIAN() 
        TEMPEST_API void AddRotateY(real val);

        ///	Resets Matrix3 and creates rotation around the z axis. Call MakeIdentiy().
        ///	\bug This is not working at all. 
        ///	\param z real. Degree of rotation around z axis. Calls RADIAN() 
        TEMPEST_API void SetRotateZ(real val);

        ///	Creates rotation around the z axis without resetting other values. 
        ///	\bug Completely untested and probably not working at all. 
        ///	\param z real. Degree of rotation around z axis. Calls RADIAN() 
        TEMPEST_API void AddRotateZ(real val);

        ///	Resets the Matrix3 and creates an Matrix3 which will perform a rotation around the x, y and z axis in that order. 
        ///	Calls MakeIdentity() 
        ///	\bug Not working at all. The math is wrong, and rotations are not working in general.
        ///	\param x real. Degree of rotation around the x axis. Calls RADIAN()
        ///	\param y real. Degree of rotation around the y axis. Calls RADIAN()
        ///	\param z real. Degree of rotation around the z axis. Calls RADIAN() 
        TEMPEST_API void SetRotate(real xVal, real yVal, real zVal);

        ///	Creates rotation around the x, y and z axis, in that order, without resetting other values.
        ///	\bug Not working at all. The math is wrong, and rotations are not working in general.
        ///	\param x real. Degree of rotation around the x axis. Calls RADIAN()
        ///	\param y real. Degree of rotation around the y axis. Calls RADIAN()
        ///	\param z real. Degree of rotation around the z axis. Calls RADIAN()
        TEMPEST_API void AddRotation(real xVal, real yVal, real zVal);

        ///	Sets the rotational transform of the matrix equal to the orientation contained in teh Quaternion. This is currently untested.
        ///	\param q conatins the orientation to set. 
        TEMPEST_API void SetOrientation(const Quaternion& q);

//==========================================================================================================================
//Inverse
//==========================================================================================================================		
        ///	Changes this matrix to equal its inverse. Warning, this is a very expensive function to call. 
        TEMPEST_API void SetInverse(void);

        ///	Changes this matrix to equal the inverse of another. Warning, very expsenive function to call. 
        ///	\param mat inverse will be set to this matrix. 
        TEMPEST_API void SetAsInverse(const Matrix3& mat);

        ///	Returns a matrix that is the inverse of this one. Warning, very expensive function to call. 
        TEMPEST_API Matrix3 GetInverse(void) const;

        ///	Returns the determinate of this matrix. This has many uses, and if you are not sure what a determinate is, I have a lot
        ///	of books you can read...
        TEMPEST_API real Determinate(void) const;
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
        TEMPEST_API void Reset(real val=0.0f);

//==========================================================================================================================
//Misc
//==========================================================================================================================		 
        ///	Reverses the Column/Row order of the Matrix3. 
        TEMPEST_API void Transpose(void);

        ///	Also known as a straight multiplication. Multiplies each value of this Matrix4 by the matching value of M.
        ///	\param M Matrix4&. Right hand value to multiply by. 	
        TEMPEST_API void ComponentMulti(const Matrix3& M);

        ///	Helper function that will return the transformed version of a matrix.
        ///	\param mat is transformed.
        TEMPEST_API Matrix3 Transform(const Matrix3& mat) const;

        ///	Helper function that will return the transformed version of a vector. 
        ///	\param vec is transformed. 
        TEMPEST_API Vector4 Transform(const Vector4& vec) const;

//==========================================================================================================================
//
//Operator Overloads
//
//==========================================================================================================================
        ///	Assigns this matrix to be equal to the values of another.
        ///	\param mat is the matrix that is copied. 
        TEMPEST_API Matrix3& operator=(const Matrix3& mat);
        
        ///	Performs a Matrix4 style multiplication.
        ///	\param mat is the matrix that is multiplied by this matrix. 
        TEMPEST_API Matrix3 operator*(const Matrix3& mat) const;

        ///	Performs Matrix4 multiplication with Vector4.
        ///	\param vec is the vector that is multiplied by this matrix. 
        TEMPEST_API Vector4 operator*(const Vector4& vec) const;

        ///	Divides each element of this matrix, setting it to the results. 
        ///	\param val is the value that this matrix is divided by. 
        TEMPEST_API Matrix3& operator/=(real val);
//==========================================================================================================================
//
//Data
//
//==========================================================================================================================
        Vector3 column1;
        Vector3 column2;
        Vector3 column3;

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
        real _Cofactor(real c00, real c01, real c10, real c11) const;

    };
    typedef shared_ptr<Matrix3> p_Matrix3;
}//End namespace
