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
	according to linear algebra rules. The Matrices are column major to ahdere to the format used within OpenGL. 

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
	\param  nearPlane represents the number of pixels from the center to the nearest boundary of the view frustum.
	\param farPlane represents the number of pixels from the center to the furthest boundary of the view furstum. 
*/
		void MakeOrthographic(F32 left, F32 right, F32 bottom, F32 top, F32 nearPlane, F32 farPlane);

/*! 
	Resets the Matrix4, then sets the values up as a Perspective Matrix4. Instead of using the dimensions of the viewport, 
	this version uses slightly differently ideas. 
	\param fieldOfview F32. Angle of the view fields of view. Good values include 90 or 120. Will change the skew of the view.
	\param aspectration F32. Width/height of the screen, but can be set to more specifici values like 4:3 or 16:9.
	\param nearPlane F32. Near rendering plane of viewport. Must be at least 1.0f.
	\param farPlane F32. Similar to depth, this is the point at which culling will happen. Should be greater than nearPlane. 
*/
		void MakePerspective(F32 fieldOfView, F32 aspectRatio, F32 nearPlane, F32 farPlane);

//==========================================================================================================================
//Translations
//==========================================================================================================================
		static Matrix4 Translate(F32 xVal, F32 yVal);

		static Matrix4 Translate(F32 xVal, F32 yVal, F32 zVal);

		static Matrix4 Translate(const Vector4& vec);

/*! 
	Resets Matrix4, then creates a Translation on the x and y axes. Calls MakeIdentiy().
	\param x F32. Value of x axis translation.
	\param y F32. Value of y axis translation. 
*/
		void SetTranslate(F32 xVal, F32 yVal);

/*! 
	Resets Matrix4, thn creates a Translation on the x, y and z axes. Calls MakeIdentiy().
	\param x F32. Value of x axis translation.
	\param y F32. Value of y axis translation.
	\param z F32. Value of z axis translation. 
*/		
		void SetTranslate(F32 xVal, F32 yVal, F32 zVal);

/*! 
	Resets Matrix4, then creates translation based on the x, y and z values found in vec. Calls MakeIdentiy().

*/	
		void SetTranslate(const Vector4& vec);

/*! 
	Creates a translation on the x and y axes without reseting the other values. 
	\param x F32. Value of x axis translation.
	\param y F32. Value of y axis translation. 
*/		
		void AddTranslate(F32 xVal, F32 yVal);

/*! 
	Creates a translation on the x, y and z axes without resetting the other values.
	\param x F32. Value of x axis translation.
	\param y F32. Value of y axis translation.
	\param z F32. Value of z axis translation. 
*/
		void AddTranslate(F32 xVal, F32 yVal, F32 zVal);

/*! 
	Creates a translation on the x, y and z axes without reseting the other values. 

*/	
		void AddTranslate(const Vector4& vec);

		Vector4 TransformInverse(const Vector4 vec) const;

		inline static Vector4 LocalToWorld(const Vector4& vec, const Matrix4& mat)
		{
			return mat * vec;
		}

		inline static Vector4 WorldToLocal(const Vector4& vec, const Matrix4& mat)
		{
			return mat.TransformInverse(vec);
		}

		Vector4 TransformDirection(const Vector4& vec) const;

		Vector4 TransformInverseDirection(const Vector4& vec) const;

//==========================================================================================================================
//Scaling
//==========================================================================================================================
		static Matrix4 Scale(F32 xVal, F32 yVal);

		static Matrix4 Scale(F32 xVal, F32 yVal, F32 zVal);

		static Matrix4 Scale(const Vector4& vec);

/*! 
	Resets the Matrix4 and creates a scaling Matrix4 on the x and y axes. Calls MakeIndentity()
	\param x F32. Length to scale on x axis.
	\param y F32. Length to scale on y axis. 
*/
		void SetScale(F32 xVal, F32 yVal);

/*! 
	Resets the Matrix4 and creates a scaling Matrix4 on the x, y and z axes. MakeIndentity()
	\param x F32. Length to scale on the x axis.
	\param y F32. Length to scale on the y axis.
	\param z F32. Length to scale on the z axis. 
*/
		void SetScale(F32 xVal, F32 yVal, F32 zVal);

/*! 
	Resets the Matrix4 and creates a scaling Matrix4 on the x and y axes. Calls MakeIndentity().

*/
		void SetScale(const Vector4& vec);

/*! 
	Creates a scaling Matrix4 on the x and y axes without resetting the other values.
	\param x F32. Value of scale on x axis.
	\param y F32. Value of scale on y axis. 
*/
		void AddScale(F32 xVal, F32 yVal);

/*! 
	Creates a scaling Matrix4 on the x, y and z axes without resetting the other values.
	\param x F32. Value of scale on x axis.
	\param y F32. Value of scale on y axis.
	\param z F32. Value of scale on z axis. 
*/
		void AddScale(F32 xVal, F32 yVal, F32 zVal);

/*! 
	Creates a scaling Matrix4 on the x, y and z axes without resetting the other values.
*/
		void AddScale(const Vector4& vec);

//==========================================================================================================================
//Rotations
//==========================================================================================================================
		static Matrix4 RotateX(F32 val);

		static Matrix4 RotateY(F32 val);

		static Matrix4 RotateZ(F32 val);

/*! 
	Resets Matrix4 and creates rotation around the x axis. Call MakeIdentiy().
	\bug This is not working at all. 
	\param x F32. Degree of rotation around x axis. Calls RADIAN() 
*/
		void SetRotateX(F32 val);

/*! 
	Creates rotation around the x axis without resetting other values. 
	\bug Completely untested and probably not working at all. 
	\param x F32. Degree of rotation around x axis. Calls RADIAN() 
*/
		void AddRotateX(F32 val);

/*! 
	Resets Matrix4 and creates rotation around the y axis. Call MakeIdentiy().
	\bug This is not working at all. 
	\param y F32. Degree of rotation around y axis. Calls RADIAN() 
*/
		void SetRotateY(F32 val);

/*! 
	Creates rotation around the y axis without resetting other values. 
	\bug Completely untested and probably not working at all. 
	\param y F32. Degree of rotation around y axis. Calls RADIAN() 
*/
		void AddRotateY(F32 val);

/*! 
	Resets Matrix4 and creates rotation around the z axis. Call MakeIdentiy().
	\bug This is not working at all. 
	\param z F32. Degree of rotation around z axis. Calls RADIAN() 
*/
		void SetRotateZ(F32 val);

/*! 
	Creates rotation around the z axis without resetting other values. 
	\bug Completely untested and probably not working at all. 
	\param z F32. Degree of rotation around z axis. Calls RADIAN() 
*/
		void AddRotateZ(F32 val);

/*! 
	Resets the Matrix4 and creates an Matrix4 which will perform a rotation around the x, y and z axis in that order. 
	Calls MakeIdentity() 
	\bug Not working at all. The math is wrong, and rotations are not working in general.
	\param x F32. Degree of rotation around the x axis. Calls RADIAN()
	\param y F32. Degree of rotation around the y axis. Calls RADIAN()
	\param z F32. Degree of rotation around the z axis. Calls RADIAN() 
*/
		void SetRotate(F32 xVal, F32 yVal, F32 zVal);

/*! 
	Creates rotation around the x, y and z axis, in that order, without resetting other values.
	\bug Not working at all. The math is wrong, and rotations are not working in general.
	\param x F32. Degree of rotation around the x axis. Calls RADIAN()
	\param y F32. Degree of rotation around the y axis. Calls RADIAN()
	\param z F32. Degree of rotation around the z axis. Calls RADIAN() 
*/
		void AddRotation(F32 xVal, F32 yVal, F32 zVal);

		void SetOrientation(const Quaternion& q);

		void SetOrientationAndPosition(const Quaternion& q, const Vector4& v);

//==========================================================================================================================
//Inverse
//==========================================================================================================================		
		void SetInverse(void);

		void SetAsInverse(const Matrix4& mat);

		Matrix4 GetInverse(void) const;

		F32 Determinate(void) const;
//==========================================================================================================================
//Resettings
//==========================================================================================================================
/*! 
	Wrapper for Reset(). Sets all values of the Matrix4 to 0, with the diagnal set to 1. 
*/
		void MakeIdentity(void)
		{
			Reset(1.0f);
		}	

/*! 
	Sets all the values of the Matrix4 to 0, with the diagnal set to val.
	\param val F32. Value of the diagnal of the Matrix4. 
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

		Matrix4 Transform3x3(const Matrix4& mat) const;

		Vector4 Transform3x3(const Vector4& vec) const;

		static Matrix4 LookAt(const Vector4& cameraPos, const Vector4& target, const Vector4& up);

/*! 
	Creates a view Matrix4 from the world position. Will set the view to "look at" the specified point. This assumes a Right
	Handed Coordinate system. This means that the camera, by default at 0.0 is looking down the -z axis.
	\param cameraPos Vector4&. The world position of the camera. Can be thought of as the eye.
	\param target Vector4&. The target point to "look at".
	\param up Vector4&. The direction of UP space in the coordinate scheme. could be +y, for example. 
*/
		void SetLookAt(const Vector4& cameraPos, const Vector4& target, const Vector4& up);

		static Matrix4 FPSView(const Vector4& cameraPos, F32 pitch, F32 yaw);

/*! 
	Uses Euler angles to compute a view Matrix4 from the world position. This assumes a Right Handed Coordinate system. This 
	means that the camera, by default at 0.0 is looking down the -z axis.
	\param cameraPos Vector4&. The position of the camera in world space. Can be thought of as the eye. 
	\param pitch F32. Must be between -90 and 90. An assert checks for this.
	\param yaw F32. Must be between 0 and 360. An assert checks for this. 
*/		
		void SetFPSView(const Vector4& cameraPos, F32 pitch, F32 yaw);

//==========================================================================================================================
//
//Operator Overloads
//
//==========================================================================================================================
/*! 
	Used to access the ith column of the Matrix4.
	\param i int. Cannot be greater than 3. There are only 4 columns. 
*/
		const Vector4& operator[](int i) const
		{
			return _columns[i];
		}

/*! 
	Used to access the ith column of the Matrix4. This version allows you to edit the values in the column.
	\param i int. Cannot be greater than 3. There are only 4 columns. 
*/
		Vector4& operator[](int i)
		{
			return _columns[i];
		}

/*! 
	Sets all the values of object to values of M. Call GetElems().
	\param M Matrix4& 
*/
		Matrix4& operator=(const Matrix4& mat);
		
/*! 
	Performs a Matrix4 style multiplication.
	\param RightMatrix4 Matrix4&. Right hand value for multiplication. 
*/
		Matrix4 operator*(const Matrix4& mat) const;

/*! 
	Performs Matrix4 multiplication with Vector4.
*/
		Vector4 operator*(const Vector4& vec) const;

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
		Vector4 _columns[4];
	};

}//End namespace
