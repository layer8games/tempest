#pragma once

//=====Killer1 includes=====
#include <Engine/Atom.h>
#include <Engine/Vector3.h>
#include <Engine/Vector4.h>
#include <Engine/Quaternion.h>

#include <vector>
#include <cassert>

namespace KillerMath 
{
//==========================================================================================================================
//Documentation
//==========================================================================================================================
/*! The Matrix3 is meant to be mathematically sound. The functions found here have been tested and are built according to 
	linear algebra rules. The 

	Matrices will be column major to ahdere to the format used within opengl, and only 4x4 Matrices will be supported. This 
	is because I cannot find any useful reason to suport a dynamic type at this time. In the future if other Matrices appear 
	to be useful, this class will basically be copied and will be turned into whatever other type of Matrix3 is needed, be it 
	a 3x3 or 2x2 or whatever. This class will only be a 4x4. 

	All of the values in the Matrix3 are stores as a 16 length array of F32. This is a single dimensional array.

	This is the way that the array mapping looks, for a quick reference. */	
	class Matrix3
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
/*! Default constructor. Sets all values to 0, except for the last in the Matrix3. */
		Matrix3(void);

		Matrix3(const Vector3& x, const Vector3& y, const Vector3& z);

		Matrix3(const Vector4& x, const Vector4& y, const Vector4& z);

		explicit Matrix3(const F32 val);
		
/*! 
	All value constructor. Takes a list of values and turns them into a Matrix3 of the same mapping. 
	\param m00 F32. Value 0,0.
	\param m01 F32. Value 0,1.
	\param m02 F32. Value 0,2
	\param m03 F32. Value 0,3.
	\param m10 F32. Value 1,0.
	\param m11 F32. Value 1,1.
	\param m12 F32. Value 1,2
	\param m13 F32. Value 1,3.
	\param m20 F32. Value 2,0.
	\param m21 F32. Value 2,1.
	\param m22 F32. Value 2,2
	\param m23 F32. Value 2,3.
*/
		Matrix3( F32 m00, F32 m01, F32 m02,
				 F32 m10, F32 m11, F32 m12,
				 F32 m20, F32 m21, F32 m22 );

/*! Copy Constructor. Calls GetElems(), then sets the values accordingly. */		
		Matrix3(const Matrix3& M);

//==========================================================================================================================
//
//Matrix3 functions
//
//==========================================================================================================================
/*! Return the array containing all the elements. */
		const std::vector<F32> GetElems(void) const;

//==========================================================================================================================
//Scaling
//==========================================================================================================================
		static Matrix3 Scale(F32 xVal, F32 yVal);

		static Matrix3 Scale(F32 xVal, F32 yVal, F32 zVal);

		static Matrix3 Scale(const Vector3& vec);

		static Matrix3 Scale(const Vector4& vec);

/*! Resets the Matrix3 and creates a scaling Matrix3 on the x and y axes. Calls MakeIndentity()
	\param x F32. Length to scale on x axis.
	\param y F32. Length to scale on y axis. */
		void SetScale(F32 xVal, F32 yVal);

/*! Resets the Matrix3 and creates a scaling Matrix3 on the x, y and z axes. MakeIndentity()
	\param x F32. Length to scale on the x axis.
	\param y F32. Length to scale on the y axis.
	\param z F32. Length to scale on the z axis. */
		void SetScale(F32 xVal, F32 yVal, F32 zVal);

		void SetScale(const Vector3& vec);

/*! 
	Resets the Matrix3 and creates a scaling Matrix3 on the x and y axes. Calls MakeIndentity().
*/
		void SetScale(const Vector4& vec);

/*! Creates a scaling Matrix3 on the x and y axes without resetting the other values.
	\param x F32. Value of scale on x axis.
	\param y F32. Value of scale on y axis. */
		void AddScale(F32 xVal, F32 yVal);

/*! Creates a scaling Matrix3 on the x, y and z axes without resetting the other values.
	\param x F32. Value of scale on x axis.
	\param y F32. Value of scale on y axis.
	\param z F32. Value of scale on z axis. */
		void AddScale(F32 xVal, F32 yVal, F32 zVal);

		void AddScale(const Vector3& vec);

/*! 
	Creates a scaling Matrix3 on the x, y and z axes without resetting the other values.
*/
		void AddScale(const Vector4& vec);

//==========================================================================================================================
//Rotations
//==========================================================================================================================
		static Matrix3 RotateX(F32 val);

		static Matrix3 RotateY(F32 val);

		static Matrix3 RotateZ(F32 val);

/*! Resets Matrix3 and creates rotation around the x axis. Call MakeIdentiy().
	\bug This is not working at all. 
	\param x F32. Degree of rotation around x axis. Calls RADIAN() */
		void SetRotateX(F32 val);

/*! Creates rotation around the x axis without resetting other values. 
	\bug Completely untested and probably not working at all. 
	\param x F32. Degree of rotation around x axis. Calls RADIAN() */
		void AddRotateX(F32 val);

/*! Resets Matrix3 and creates rotation around the y axis. Call MakeIdentiy().
	\bug This is not working at all. 
	\param y F32. Degree of rotation around y axis. Calls RADIAN() */
		void SetRotateY(F32 val);

/*! Creates rotation around the y axis without resetting other values. 
	\bug Completely untested and probably not working at all. 
	\param y F32. Degree of rotation around y axis. Calls RADIAN() */
		void AddRotateY(F32 val);

/*! Resets Matrix3 and creates rotation around the z axis. Call MakeIdentiy().
	\bug This is not working at all. 
	\param z F32. Degree of rotation around z axis. Calls RADIAN() */
		void SetRotateZ(F32 val);

/*! Creates rotation around the z axis without resetting other values. 
	\bug Completely untested and probably not working at all. 
	\param z F32. Degree of rotation around z axis. Calls RADIAN() */
		void AddRotateZ(F32 val);

/*! Resets the Matrix3 and creates an Matrix3 which will perform a rotation around the x, y and z axis in that order. 
	Calls MakeIdentity() 
	\bug Not working at all. The math is wrong, and rotations are not working in general.
	\param x F32. Degree of rotation around the x axis. Calls RADIAN()
	\param y F32. Degree of rotation around the y axis. Calls RADIAN()
	\param z F32. Degree of rotation around the z axis. Calls RADIAN() */
		void SetRotate(F32 xVal, F32 yVal, F32 zVal);

/*! Creates rotation around the x, y and z axis, in that order, without resetting other values.
	\bug Not working at all. The math is wrong, and rotations are not working in general.
	\param x F32. Degree of rotation around the x axis. Calls RADIAN()
	\param y F32. Degree of rotation around the y axis. Calls RADIAN()
	\param z F32. Degree of rotation around the z axis. Calls RADIAN() */
		void AddRotation(F32 xVal, F32 yVal, F32 zVal);

		void SetOrientation(const Quaternion& q);

//==========================================================================================================================
//Inverse
//==========================================================================================================================		
		void SetInverse(void);

		void SetAsInverse(const Matrix3& mat);

		Matrix3 GetInverse(void) const;

		F32 Determinate(void) const;
//==========================================================================================================================
//Resettings
//==========================================================================================================================
/*! Wrapper for Reset(). Sets all values of the Matrix3 to 0, with the diagnal set to 1. */
		void MakeIdentity(void)
		{
			Reset(1.0f);
		}	

/*! Sets all the values of the Matrix3 to 0, with the diagnal set to val.
	\param val F32. Value of the diagnal of the Matrix3. */		
		void Reset(F32 val=0.0f);

//==========================================================================================================================
//Misc
//==========================================================================================================================		
/*! Reverses the Column/Row order of the Matrix3. */
		void Transpose(void);

/*! Also known as a straight multiplication. Multiplies each value of this Matrix3 by the matching value of M.
	\param M Matrix3&. Right hand value to multiply by. */		
		void ComponentMulti(const Matrix3& M);

		Matrix3 Matrix3::Transform(const Matrix3& mat) const;

		Vector4 Matrix3::Transform(const Vector4& vec) const;

//==========================================================================================================================
//
//Operator Overloads
//
//==========================================================================================================================
/*! Used to access the ith column of the Matrix3.
	\param i int. Cannot be greater than 3. There are only 4 columns. */
		const Vector3& operator[](int i) const
		{
			return _data[i];
		}

/*! Used to access the ith column of the Matrix3. This version allows you to edit the values in the column.
	\param i int. Cannot be greater than 3. There are only 4 columns. */
		Vector3& operator[](int i)
		{
			return _data[i];
		}

/*! Sets all the values of object to values of M. Call GetElems().
	\param M Matrix3& */
		Matrix3& operator=(const Matrix3& mat);
		
/*! Performs a Matrix3 style multiplication.
	\param RightMatrix3 Matrix3&. Right hand value for multiplication. */
		Matrix3 operator*(const Matrix3& mat) const;

/*! Performs Matrix3 multiplication with Vector4.
*/
		Vector4 operator*(const Vector4& vec) const;

		Matrix3& operator/=(F32 val);

	private:
//==========================================================================================================================
//
//Private functions
//
//==========================================================================================================================
		F32 _Cofactor(F32 c00, F32 c01, F32 c10, F32 c11) const;

//==========================================================================================================================
//
//Data
//
//==========================================================================================================================
		Vector3 _data[3];
	};

}//End namespace
