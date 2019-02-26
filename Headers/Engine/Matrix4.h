#pragma once

//=====Killer1 includes=====
#include <Engine/Atom.h>
#include <Engine/Vector4.h>
#include <Engine/Quaternion.h>

#include <vector>
#include <cassert>

namespace KillerMath 
{
//==========================================================================================================================
//Documentation
//==========================================================================================================================
/*! 
	The Matrix4 is a 4x4 Matrix meant to be mathematically sound. The functions found here have been tested and are built 
	according to linear algebra rules. The Matrices are column major to adhere to the format used within OpenGL. 

	The data for the class is represented by an array of Vector4. This means that you can index into a specific element of
	the Matrix, say, colume 2, row 1 by using [2][1]. In the rest of the this documentation, this type of value will be 
	represented by the term mrowcolumn. For example, colum 2, row 1 will look like m21, read m two one.

*/	
	class Matrix4
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
/*! 
	Default constructor. Sets all values to 0, except for m33. 
*/
		Matrix4(void);

		Matrix4(const Vector4& x, const Vector4& y, const Vector4& z);

		Matrix4(const Vector4& x, const Vector4& y, const Vector4& z, const Vector4& w);

		explicit Matrix4(const F32 val);
		
/*! 
	All value constructor. Takes a list of values and turns them into a Matrix4 of the same mapping. 
	\param m00 is the value for element m00.
	\param m01 is the value for element m01.
	\param m02 is the value for element m02
	\param m03 is the value for element m03.
	\param m10 is the value for element m10.
	\param m11 is the value for element m11.
	\param m12 is the value for element m12
	\param m13 is the value for element m13.
	\param m20 is the value for element m20.
	\param m21 is the value for element m21.
	\param m22 is the value for element m22
	\param m23 is the value for element m23.
	\param m30 is the value for element m30.
	\param m31 is the value for element m31.
	\param m32 is the value for element m32
	\param m33 is the value for element m33. 
*/
		Matrix4( F32 m00, F32 m01, F32 m02, F32 m03,
				 F32 m10, F32 m11, F32 m12, F32 m13,
				 F32 m20, F32 m21, F32 m22, F32 m23,
				 F32 m30, F32 m31, F32 m32, F32 m33);

/*! 
	Copy Constructor. Calls Matrix4::[] to, which will copy the Vector4 from each colume of M into this Matrix.
	\param M is the matrix to copy into this one.
*/		
		Matrix4(const Matrix4& M);

//==========================================================================================================================
//
//Matrix4 functions
//
//==========================================================================================================================
/*! 
	Return the array containing all the elements. 
*/
		const std::vector<F32> GetElems(void) const;

//==========================================================================================================================
//Projections
//==========================================================================================================================		
/*! 
	Resets the Matrix4, then sets the values up as an Orthographic projection. Calls MakeIdentiy(). The viewport values are 
	usually based on the dimensions of the window, but could be made smaller.
	\param left represents the number of pixels from the center to the left boundary of the view frustum.
	\param right represents the number of pixels from the center to the right boundary of the view frustum.
	\param bottom represents the number of pixels from the center to the bottom boundary of the view frustum.
	\param top represents the number of pixels from the center to the top boundary of the view frustum.
	\param nearPlane represents the number of pixels from the center to the nearest boundary of the view frustum.
	\param farPlane represents the number of pixels from the center to the furthest boundary of the view furstum. 
*/
		void MakeOrthographic(F32 left, F32 right, F32 bottom, F32 top, F32 nearPlane, F32 farPlane);

/*! 
	Resets the Matrix4, then sets the values up as a Perspective Matrix4. Instead of using the dimensions of the viewport, 
	this version uses slightly differently ideas. 
	\param fieldOfview is the angle of the fields of view. Good values include 90 or 120. Will change the skew of the view.
	\param aspectration is the Width/height of the screen, but can be set to more specific values like 4:3 or 16:9.
	\param nearPlane represents the number of pixels from the center to the nearest boundary of the view frustum.
	\param farPlane represents the number of pixels from the center to the furthest boundary of the view furstum. 
*/
		void MakePerspective(F32 fieldOfView, F32 aspectRatio, F32 nearPlane, F32 farPlane);

//==========================================================================================================================
//Translations
//==========================================================================================================================
/*!
	Creates a 2D translation matrix.
	\param xVal is the amount to translate on the x axis. 
	\param yVal is the amount to translate on the y axis.
*/
		static Matrix4 Translate(F32 xVal, F32 yVal);

/*!
	Creates a 3D translation Matrix.
	\param xVal is the amount to translate on the x axis. 
	\param yVal is the amount to translate on the y axis.
	\param zVal is the amount to translate on the z axis. 
*/
		static Matrix4 Translate(F32 xVal, F32 yVal, F32 zVal);

/*!
	Creates a translation matrix equal to the x y and z values in the Vector4.
	\param vec contains the values that will be used for the translation. 
*/
		static Matrix4 Translate(const Vector4& vec);

/*! 
	Sets a 2D translation for this matrix.
	\param x is the value of x axis translation.
	\param y is the value of y axis translation. 
*/
		void SetTranslate(F32 xVal, F32 yVal);

/*! 
	Sets a 3D translation for this matrix.
	\param x is the value of x axis translation.
	\param y is the value of y axis translation.
	\param z is the value of z axis translation. 
*/		
		void SetTranslate(F32 xVal, F32 yVal, F32 zVal);

/*! 
	Sets a translation for this matrix equal to the x y and z values in a Vector4.
	\param vec contains the values that will be used for the translation. 
*/	
		void SetTranslate(const Vector4& vec);

/*! 
	Increases the current translation of this matrix.
	\param x is the value of x axis translation.
	\param y is the value of y axis translation. 
*/		
		void AddTranslate(F32 xVal, F32 yVal);

/*! 
	Increases the current translation of this matrix.
	\param x is the value of x axis translation.
	\param y is the value of y axis translation.
	\param z is the value of z axis translation. 
*/
		void AddTranslate(F32 xVal, F32 yVal, F32 zVal);

/*! 
	Increases the current translation of this matrix equal to the x y and z values in a Vector4.
	\param vec contains the values that will be used for the translation.
*/	
		void AddTranslate(const Vector4& vec);

/*!
	Returns a Vector4 transformed by the inverse of this matrix. Warning, this is a costly call. 
	\param vec is the vectored used to performed the transformation.
*/
		Vector4 TransformInverse(const Vector4& vec) const;

//==========================================================================================================================
//Scaling
//==========================================================================================================================
/*!
	Creates a matrix that will perform a scaling transformation in 2D.
	\param xVal is the amount to scale in the x axis. 
	\param yVal is the amount to scale in the y axis.
*/
		static Matrix4 Scale(F32 xVal, F32 yVal);

/*!
	Creates a matrix that will perform a scaling transformation in 3D.
	\param xVal is the amount to scale in the x axis. 
	\param yVal is the amount to scale in the y axis.
	\param zVal is the amount to scale in the z axis. 
*/
		static Matrix4 Scale(F32 xVal, F32 yVal, F32 zVal);

/*!
	Creates a matrix that will perform a scaling translation equal to the x y and z values in a Vector4.
	\param vec contains the values used in the scaling. 
*/
		static Matrix4 Scale(const Vector4& vec);

/*! 
	Sets this matrix to perform a scaling transformation in 2D.
	\param xVal is the amount to scale in the x axis. 
	\param yVal is the amount to scale in the y axis.
*/
		void SetScale(F32 xVal, F32 yVal);

/*! 
	Sets this matrix to perform a scaling transformation in 3D.
	\param xVal is the amount to scale in the x axis. 
	\param yVal is the amount to scale in the y axis.
	\param zVal is the amount to scale in the z axis. 	
*/
		void SetScale(F32 xVal, F32 yVal, F32 zVal);

/*! 
	Sets this matrix to perform a scaling translation equal to the x y and z values in a Vector4.
	\param vec contains the values used in the scaling.  
*/
		void SetScale(const Vector4& vec);

/*! 
	Increases the scaling translation in 2D.
	\param x Value of scale on x axis.
	\param y Value of scale on y axis. 
*/
		void AddScale(F32 xVal, F32 yVal);

/*! 
	Increases the scaling translation in 3D.
	\param x Value of scale on x axis.
	\param y Value of scale on y axis.
	\param z Value of scale on z axis. 
*/
		void AddScale(F32 xVal, F32 yVal, F32 zVal);

/*! 
	Increases the scaling translation equal to the x y and z values in a Vector4.
	\param vec contains the values that will increase the scale.
*/
		void AddScale(const Vector4& vec);

//==========================================================================================================================
//Rotations
//==========================================================================================================================
/*!
	Creates a matrix that will perform a rotation around the x axis.
	\param val is the angle to rotate in degrees. 
*/
		static Matrix4 RotateX(F32 val);

/*!
	Creates a matrix that will perform a rotation around the y axis.
	\param val is the angle to rotate in degrees. 
*/
		static Matrix4 RotateY(F32 val);

/*!
	Creates a matrix that will perform a rotation around the z axis.
	\param val is the angle to rotate in degrees. 
*/
		static Matrix4 RotateZ(F32 val);

/*! 
	Resets Matrix4 and creates rotation around the x axis. Call MakeIdentiy().
	\bug This is not working at all. 
	\param x Degree of rotation around x axis. Calls RADIAN() 
*/
		void SetRotateX(F32 val);

/*! 
	Creates rotation around the x axis without resetting other values. 
	\bug Completely untested and probably not working at all. 
	\param x Degree of rotation around x axis. Calls RADIAN() 
*/
		void AddRotateX(F32 val);

/*! 
	Resets Matrix4 and creates rotation around the y axis. Call MakeIdentiy().
	\bug This is not working at all. 
	\param y Degree of rotation around y axis. Calls RADIAN() 
*/
		void SetRotateY(F32 val);

/*! 
	Creates rotation around the y axis without resetting other values. 
	\bug Completely untested and probably not working at all. 
	\param y Degree of rotation around y axis. Calls RADIAN() 
*/
		void AddRotateY(F32 val);

/*! 
	Resets Matrix4 and creates rotation around the z axis. Call MakeIdentiy().
	\bug This is not working at all. 
	\param z Degree of rotation around z axis. Calls RADIAN() 
*/
		void SetRotateZ(F32 val);

/*! 
	Creates rotation around the z axis without resetting other values. 
	\bug Completely untested and probably not working at all. 
	\param z Degree of rotation around z axis. Calls RADIAN() 
*/
		void AddRotateZ(F32 val);

/*! 
	Resets the Matrix4 and creates an Matrix4 which will perform a rotation around the x, y and z axis in that order. 
	Calls MakeIdentity() 
	\bug Not working at all. The math is wrong, and rotations are not working in general.
	\param x Degree of rotation around the x axis. Calls RADIAN()
	\param y Degree of rotation around the y axis. Calls RADIAN()
	\param z Degree of rotation around the z axis. Calls RADIAN() 
*/
		void SetRotate(F32 xVal, F32 yVal, F32 zVal);

/*! 
	Creates rotation around the x, y and z axis, in that order, without resetting other values.
	\bug Not working at all. The math is wrong, and rotations are not working in general.
	\param x Degree of rotation around the x axis. Calls RADIAN()
	\param y Degree of rotation around the y axis. Calls RADIAN()
	\param z Degree of rotation around the z axis. Calls RADIAN() 
*/
		void AddRotation(F32 xVal, F32 yVal, F32 zVal);

/*!
	Sets the rotational transform of the matrix equal to the orientation contained in teh Quaternion. This is currently untested.
	\param q conatins the orientation to set. 
*/
		void SetOrientation(const Quaternion& q);

/*!
	A helper functions that will set the rotational transform and position at the same time. This is currently untested. 
	\param q contains the orientation to set. 
	\param v contains the position to set, as a translation. 
*/
		void SetOrientationAndPosition(const Quaternion& q, const Vector4& v);

/*!
	A helper functions that will set the rotational transform and position at the same time. This is currently untested. 
	\param q contains the orientation to set. 
	\param p contains the position to set, as a translation. 
*/
		void SetOrientationAndPosition(const Quaternion& q, const Point& p);

//==========================================================================================================================
//Inverse
//==========================================================================================================================		
/*!
	Changes this matrix to equal its inverse. Warning, this is a very expensive function to call. 
*/
		void SetInverse(void);

/*!
	Changes this matrix to equal the inverse of another. Warning, very expsenive function to call. 
	\param mat inverse will be set to this matrix. 
*/
		void SetAsInverse(const Matrix4& mat);

/*!
	Returns a matrix that is the inverse of this one. Warning, very expensive function to call. 
*/
		Matrix4 GetInverse(void) const;

/*!
	Returns the determinate of this matrix. This has many uses, and if you are not sure what a determinate is, I have a lot
	of books you can read...
*/
		F32 Determinate(void) const;
//==========================================================================================================================
//Resettings
//==========================================================================================================================
/*! 
	Sets all values of the Matrix4 to 0, with the diagnal set to 1.
*/
		void MakeIdentity(void)
		{
			Reset(1.0f);
		}	

/*! 
	Sets all the values of the Matrix4 to 0, with the diagnal set to val.
	\param val Value of the diagnal of the Matrix4. 
*/		
		void Reset(F32 val=0.0f);

//==========================================================================================================================
//Misc
//==========================================================================================================================		
/*! 
	Reverses the Column/Row order of the Matrix4. 
*/
		void Transpose(void);

/*! 
	Also known as a straight multiplication. Multiplies each value of this Matrix4 by the matching value of M.
	\param M Matrix4&. Right hand value to multiply by. 
*/		
		void ComponentMulti(const Matrix4& M);

/*!
	Helper function that will return the transformed version of a matrix by the affine transformation of this matrix. This means
	that it will not include any translation.
	\param mat is transformed.
*/
		Matrix4 Transform3x3(const Matrix4& mat) const;

/*!
	Helper function that will return the transformed version of a vector by the affine transformation fo this matrix. This means
	that it will not include any translation. 
	\param vec is transformed. 
*/
		Vector4 Transform3x3(const Vector4& vec) const;

/*!
	Returns a matrix that can translate other entities so that they appear as if they were looking down a target axis from a 
	target position. This is used mostly with the camera. A right handed coordinate system is assumed. 
	\param cameraPos is the position of the camera in world space. This will be the "location" of the camera for the look at. 
	\param target is the axis down which the camera should look. You can also think of this as the target in space the camera should face.
	\param up is the direction considered to be up for the camera. 
*/
		static Matrix4 LookAt(const Vector4& cameraPos, const Vector4& target, const Vector4& up);

/*! 
	Sets this matrix to translate other entities so that they appear as if they were looking down a target axis from a target position. 
	This is used mostly with the camera. A right handed coordinate system is assumed. 
	\param cameraPos is the position of the camera in world space. This will be the "location" of the camera for the look at. 
	\param target is the axis down which the camera should look. You can also think of this as the target in space the camera should face.
	\param up is the direction considered to be up for the camera. 
*/
		void SetLookAt(const Vector4& cameraPos, const Vector4& target, const Vector4& up);

/*!
	Similar to Matrix4::LookAt, this function will create a matrix that can be used to translate entities such that they appear as if 
	to have moved according to a position, pitch and yaw. This is usually cached for the camera to be used in the graphica computations.
	Euler angles are assumed when setting the matrix up.  
	\param cameraPos is the position of the camera in world space. 
	\param pitch is the up/down pitch of the camera in degrees. -90 < pitch < 90.
	\param yas is the right/left yaw of the camera in degress. 0 < yaw < 360.
*/
		static Matrix4 FPSView(const Vector4& cameraPos, F32 pitch, F32 yaw);

/*! 
	Similar to Matrix4::LookAt, this function will set this matrix so that it can be used to translate entities such that they appear as if 
	to have moved according to a position, pitch and yaw. This is usually cached for the camera to be used in the graphica computations.
	Euler angles are assumed when setting the matrix up.  
	\param cameraPos is the position of the camera in world space. 
	\param pitch is the up/down pitch of the camera in degrees. -90 < pitch < 90.
	\param yas is the right/left yaw of the camera in degress. 0 < yaw < 360. 
*/		
		void SetFPSView(const Vector4& cameraPos, F32 pitch, F32 yaw);

//==========================================================================================================================
//
//Operator Overloads
//
//==========================================================================================================================
/*! 
	Used to access the ith column of the Matrix4.
	\param i is the index to return. Cannot be greater than 3. There are only 4 columns. 
*/
		const Vector4& operator[](int i) const
		{
			//could be a bug here...
			//assert(i > 0 && i < 4);
			return _data[i];
		}

/*! 
	Used to access the ith column of the Matrix4. This version allows you to edit the values in the column.
	\param i is the index to return. Cannot be greater than 3. There are only 4 columns. 
*/
		Vector4& operator[](int i)
		{
			//could be a bug here...
			//assert(i > 0 && i < 4);
			return _data[i];
		}

/*! 
	Assigns this matrix to be equal to the values of another.
	\param mat is the matrix that is copied. 
*/
		Matrix4& operator=(const Matrix4& mat);
		
/*! 
	Performs a Matrix4 style multiplication.
	\param mat is the matrix that is multiplied by this matrix. 
*/
		Matrix4 operator*(const Matrix4& mat) const;

/*! 
	Performs Matrix4 multiplication with Vector4.
	\param vec is the vector that is multiplied by this matrix. 
*/
		Vector4 operator*(const Vector4& vec) const;

/*! 
	Performs Matrix4 multiplication with Point.
	\param point is the vector that is multiplied by this matrix. 
*/
		Point operator*(const Point& point) const;

/*!
	Divides each element of this matrix, setting it to the results. 
	\param val is the value that this matrix is divided by. 
*/
		Matrix4& operator/=(F32 val);

	private:
//==========================================================================================================================
//
//Private Fucntions
//
//==========================================================================================================================
/*!
	Returns the cofactor for the sub matrix made up of the 3 Vector4 passed in. This is used in Matrix4::Inverse as part of 
	what is called a Classic Adjoint. 
	\param col1 is the first column of the sub matrix.
	\param col2 is the second column of the sub matrix.
	\param col3 is the fourth column of the sub matrix.
*/
		F32 _Cofactor(const Vector4& col1, const Vector4& col2, const Vector4& col3) const;

//==========================================================================================================================
//
//Data
//
//==========================================================================================================================
		Vector4 _data[4];	///< The matrix itself, represented by 4 Vector4 in an array.
	};

}//End namespace
