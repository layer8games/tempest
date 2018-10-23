#pragma once

//=====Killer1 includes=====
#include <Engine/Atom.h>
#include <Engine/Vector.h>

#include <vector>
#include <cassert>

namespace KillerMath 
{
//==========================================================================================================================
//Documentation
//==========================================================================================================================
/*! The Matrix is meant to be mathematically sound. The functions found here have been tested and are built according to 
	linear algebra rules. The 

	Matrices will be column major to ahdere to the format used within opengl, and only 4x4 Matrices will be supported. This 
	is because I cannot find any useful reason to suport a dynamic type at this time. In the future if other Matrices appear 
	to be useful, this class will basically be copied and will be turned into whatever other type of Matrix is needed, be it 
	a 3x3 or 2x2 or whatever. This class will only be a 4x4. 

	All of the values in the Matrix are stores as a 16 length array of F32. This is a single dimensional array.

	This is the way that the array mapping looks, for a quick reference. */	
	class Matrix
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
/*! Default constructor. Sets all values to 0, except for the last in the Matrix. */
		Matrix(void);

		Matrix(const Vector& x, const Vector& y, const Vector& z);

		Matrix(const Vector& x, const Vector& y, const Vector& z, const Vector& w);

		explicit Matrix(const F32 val);
		
/*! All value constructor. Takes a list of values and turns them into a matrix of the same mapping. 
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
	\param m30 F32. Value 3,0.
	\param m31 F32. Value 3,1.
	\param m32 F32. Value 3,2
	\param m33 F32. Value 3,3. */
		Matrix( F32 m00, F32 m01, F32 m02, F32 m03,
				F32 m10, F32 m11, F32 m12, F32 m13,
				F32 m20, F32 m21, F32 m22, F32 m23,
				F32 m30, F32 m31, F32 m32, F32 m33);

/*! Copy Constructor. Calls GetElems(), then sets the values accordingly. */		
		Matrix(const Matrix& M);

//==========================================================================================================================
//
//Matrix functions
//
//==========================================================================================================================
/*! Return the array containing all the elements. */
		const std::vector<F32> GetElems(void) const;

//==========================================================================================================================
//Projections
//==========================================================================================================================		
/*! Resets the Matrix, then sets the values up as an Orthographic projection. Calls MakeIdentiy(). The viewport values are 
	usually based on the dimensions of the window, but could be made smaller.
	\param width F32. Width of viewport.
	\param height F32. Height of viewport.
	\param depth F32. Depth of the viewport. 
	\param center bool. Set to true by default. If true, the origin of the view port will be the middle of the screen. 
		   Otherwise it will be the bottom left corner of the screen. */
		void MakeOrthographic(F32 left, F32 right, F32 bottom, F32 top, F32 nearPlane, F32 farPlane);

/*! Resets the Matrix, then sets the values up as a Perspective projection, using the more standard equation. Calls MakeIdenity().
	The viewport values are usually based on the dimensions of the window, but could be made smaller.
	\bug I cannot get this to work for the life of me. I am not sure why, the math all looks right but the function wont work.
	\param width F32. Width of viewport. 
	\param height F32. Height of viewport.
	\param depth F32. Depfth of viewport.
	\param center bool. True by default. If true, the origin of the view port will be the middle of the screen. 
		   Otherwise it will be the bottom left corner of the screen. */
		void MakePerspective(F32 width, F32 height, F32 depth, bool center=true);

/*! Resets the Matrix, then sets the values up as a Perspective Matrix. Instead of using the dimensions of the viewport, 
	this version uses slightly differently ideas. 
	\param fieldOfview F32. Angle of the view fields of view. Good values include 90 or 120. Will change the skew of the view.
	\param aspectration F32. Width/height of the screen, but can be set to more specifici values like 4:3 or 16:9.
	\param nearPlane F32. Near rendering plane of viewport. Must be at least 1.0f.
	\param farPlane F32. Similar to depth, this is the point at which culling will happen. Should be greater than nearPlane. */
		void MakePerspective(F32 fieldOfView, F32 aspectRatio, F32 nearPlane, F32 farPlane);

//==========================================================================================================================
//Translations
//==========================================================================================================================
		static Matrix Translate(F32 xVal, F32 yVal);

		static Matrix Translate(F32 xVal, F32 yVal, F32 zVal);

		static Matrix Translate(const Vector& vec);

/*! Resets Matrix, then creates a Translation on the x and y axes. Calls MakeIdentiy().
	\param x F32. Value of x axis translation.
	\param y F32. Value of y axis translation. */
		void SetTranslate(F32 xVal, F32 yVal);

/*! Resets Matrix, thn creates a Translation on the x, y and z axes. Calls MakeIdentiy().
	\param x F32. Value of x axis translation.
	\param y F32. Value of y axis translation.
	\param z F32. Value of z axis translation. */		
		void SetTranslate(F32 xVal, F32 yVal, F32 zVal);

/*! Resets Matrix, then creates translation based on the x, y and z values found in vec. Calls MakeIdentiy().
*/	
		void SetTranslate(const Vector& vec);

/*! Creates a translation on the x and y axes without reseting the other values. 
	\param x F32. Value of x axis translation.
	\param y F32. Value of y axis translation. */		
		void AddTranslate(F32 xVal, F32 yVal);

/*! Creates a translation on the x, y and z axes without resetting the other values.
	\param x F32. Value of x axis translation.
	\param y F32. Value of y axis translation.
	\param z F32. Value of z axis translation. */
		void AddTranslate(F32 xVal, F32 yVal, F32 zVal);

/*! Creates a translation on the x, y and z axes without reseting the other values. 
*/	
		void AddTranslate(const Vector& vec);

//==========================================================================================================================
//Scaling
//==========================================================================================================================
		static Matrix Scale(F32 xVal, F32 yVal);

		static Matrix Scale(F32 xVal, F32 yVal, F32 zVal);

		static Matrix Scale(const Vector& vec);

/*! Resets the Matrix and creates a scaling Matrix on the x and y axes. Calls MakeIndentity()
	\param x F32. Length to scale on x axis.
	\param y F32. Length to scale on y axis. */
		void SetScale(F32 xVal, F32 yVal);

/*! Resets the Matrix and creates a scaling Matrix on the x, y and z axes. MakeIndentity()
	\param x F32. Length to scale on the x axis.
	\param y F32. Length to scale on the y axis.
	\param z F32. Length to scale on the z axis. */
		void SetScale(F32 xVal, F32 yVal, F32 zVal);

/*! Resets the Matrix and creates a scaling Matrix on the x and y axes. Calls MakeIndentity().
*/
		void SetScale(const Vector& vec);

/*! Creates a scaling Matrix on the x and y axes without resetting the other values.
	\param x F32. Value of scale on x axis.
	\param y F32. Value of scale on y axis. */
		void AddScale(F32 xVal, F32 yVal);

/*! Creates a scaling Matrix on the x, y and z axes without resetting the other values.
	\param x F32. Value of scale on x axis.
	\param y F32. Value of scale on y axis.
	\param z F32. Value of scale on z axis. */
		void AddScale(F32 xVal, F32 yVal, F32 zVal);

/*! Creates a scaling Matrix on the x, y and z axes without resetting the other values.
*/
		void AddScale(const Vector& vec);

//==========================================================================================================================
//Rotations
//==========================================================================================================================
		static Matrix RotateX(F32 val);

		static Matrix RotateY(F32 val);

		static Matrix RotateZ(F32 val);

/*! Resets Matrix and creates rotation around the x axis. Call MakeIdentiy().
	\bug This is not working at all. 
	\param x F32. Degree of rotation around x axis. Calls RADIAN() */
		void SetRotateX(F32 val);

/*! Creates rotation around the x axis without resetting other values. 
	\bug Completely untested and probably not working at all. 
	\param x F32. Degree of rotation around x axis. Calls RADIAN() */
		void AddRotateX(F32 val);

/*! Resets Matrix and creates rotation around the y axis. Call MakeIdentiy().
	\bug This is not working at all. 
	\param y F32. Degree of rotation around y axis. Calls RADIAN() */
		void SetRotateY(F32 val);

/*! Creates rotation around the y axis without resetting other values. 
	\bug Completely untested and probably not working at all. 
	\param y F32. Degree of rotation around y axis. Calls RADIAN() */
		void AddRotateY(F32 val);

/*! Resets Matrix and creates rotation around the z axis. Call MakeIdentiy().
	\bug This is not working at all. 
	\param z F32. Degree of rotation around z axis. Calls RADIAN() */
		void SetRotateZ(F32 val);

/*! Creates rotation around the z axis without resetting other values. 
	\bug Completely untested and probably not working at all. 
	\param z F32. Degree of rotation around z axis. Calls RADIAN() */
		void AddRotateZ(F32 val);

/*! Resets the Matrix and creates an Matrix which will perform a rotation around the x, y and z axis in that order. 
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
		
//==========================================================================================================================
//Resettings
//==========================================================================================================================
/*! Wrapper for Reset(). Sets all values of the Matrix to 0, with the diagnal set to 1. */
		void MakeIdentity(void)
		{
			Reset(1.0f);
		}	

/*! Sets all the values of the Matrix to 0, with the diagnal set to val.
	\param val F32. Value of the diagnal of the Matrix. */		
		void Reset(F32 val=0.0f);

//==========================================================================================================================
//Misc
//==========================================================================================================================		
/*! Reverses the Column/Row order of the Matrix. */
		void Transpose(void);

/*! Also known as a straight multiplication. Multiplies each value of this Matrix by the matching value of M.
	\param M Matrix&. Right hand value to multiply by. */		
		void ComponentMulti(const Matrix& M);

		static Matrix LookAt(const Vector& cameraPos, const Vector& target, const Vector& up);

/*! Creates a view matrix from the world position. Will set the view to "look at" the specified point. This assumes a Right
	Handed Coordinate system. This means that the camera, by default at 0.0 is looking down the -z axis.
	\param cameraPos Vector&. The world position of the camera. Can be thought of as the eye.
	\param target Vector&. The target point to "look at".
	\param up Vector&. The direction of UP space in the coordinate scheme. could be +y, for example. */
		void SetLookAt(const Vector& cameraPos, const Vector& target, const Vector& up);

		static Matrix FPSView(const Vector& cameraPos, F32 pitch, F32 yaw);

/*! Uses Euler angles to compute a view matrix from the world position. This assumes a Right Handed Coordinate system. This 
	means that the camera, by default at 0.0 is looking down the -z axis.
	\param cameraPos Vector&. The position of the camera in world space. Can be thought of as the eye. 
	\param pitch F32. Must be between -90 and 90. An assert checks for this.
	\param yaw F32. Must be between 0 and 360. An assert checks for thisl */		
		void SetFPSView(const Vector& cameraPos, F32 pitch, F32 yaw);

//==========================================================================================================================
//
//Operator Overloads
//
//==========================================================================================================================
/*! Used to access the ith column of the matrix.
	\param i int. Cannot be greater than 3. There are only 4 columns. */
		const Vector& operator[](int i) const
		{
			return _columns[i];
		}

/*! Used to access the ith column of the matrix. This version allows you to edit the values in the column.
	\param i int. Cannot be greater than 3. There are only 4 columns. */
		Vector& operator[](int i)
		{
			return _columns[i];
		}

/*! Sets all the values of object to values of M. Call GetElems().
	\param M Matrix& */
		Matrix& operator=(const Matrix& mat);
		
/*! Performs a Matrix style multiplication.
	\param RightMatrix Matrix&. Right hand value for multiplication. */
		Matrix operator*(const Matrix& mat);

/*! Performs Matrix multiplication with Vector.
*/
		Vector operator*(const Vector& vec);

	private:
		enum {
			x=0,
			y=1,
			z=2,
			w=3
		};

//==========================================================================================================================
//
//Data
//
//==========================================================================================================================
		Vector _columns[4];
	};

}//End namespace
