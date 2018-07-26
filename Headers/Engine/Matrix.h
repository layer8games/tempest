#pragma once

//=====Killer1 includes=====
#include <Engine/Atom.h>
#include <Engine/Vector2.h>
#include <Engine/Vector3.h>

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

	Since the matrix is column major, it is mapped as such: 

	- | m00 | m10 | m20 | m30 |
	- | m01 | m11 | m21 | m31 |
	- | m03 | m12 | m22 | m32 |
	- | m04 | m13 | m23 | m33 |

	This means that _m[0] -> _m[3] == m00 -> m04

	What this looks like is this:

	- | _m[0] | _m[4] | _m[8]  | _m[12] |
	- | _m[1] | _m[5] | _m[9]  | _m[13] |
	- | _m[2] | _m[6] | _m[10] | _m[14] |
	- | _m[3] | _m[7] | _m[11] | _m[15] |

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
		
/*! Single value constructor. Set's the diagnal of the Matrix to value.
	\param val F32. Value for elements 0, 5, 10 and 15. */		
		explicit Matrix(F32 val);
		
/*! Array constructor. Set's all values of the Matrix to the cooresponding values in the array.
	\param mSrc F32[16]. Array of 16 values, basically a raw Matrix. */		
		explicit Matrix(const F32 mSrc[16]);
		
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
		void MakeOrthographic(F32 width, F32 height, F32 depth, bool center=true);

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
/*! Resets Matrix, then creates a Translation on the x and y axes. Calls MakeIdentiy().
	\param x F32. Value of x axis translation.
	\param y F32. Value of y axis translation. */
		void Translate(F32 x, F32 y);

/*! Resets Matrix, thn creates a Translation on the x, y and z axes. Calls MakeIdentiy().
	\param x F32. Value of x axis translation.
	\param y F32. Value of y axis translation.
	\param z F32. Value of z axis translation. */		
		void Translate(F32 x, F32 y, F32 z);

/*! Resets Matrix, then creates translation based on the x and y values found in vec. Calls MakeIdentiy().
	\param vec Vector2&. Calls Vector2::GetX and Vector::GetY to get values for translation. */
		void Translate(const Vector2& vec);

/*! Resets Matrix, then creates translation based on the x, y and z values found in vec. Calls MakeIdentiy().
	\param vec Vector3&. Calls Vector3::GetX, Vector3::GetY and Vector3::GetZ to get values for translation. */	
		void Translate(const Vector3& vec);

/*! Creates a translation on the x and y axes without reseting the other values. 
	\param x F32. Value of x axis translation.
	\param y F32. Value of y axis translation. */		
		void AddTranslate(F32 x, F32 y);

/*! Creates a translation on the x, y and z axes without resetting the other values.
	\param x F32. Value of x axis translation.
	\param y F32. Value of y axis translation.
	\param z F32. Value of z axis translation. */
		void AddTranslate(F32 x, F32 y, F32 z);

/*! Creates a translation on the x and y axes without reseting the other values. 
	\param vec Vector3&. Calls Vector2::GetX and Vector2::GetY to get values for translation. */	
		void AddTranslate(const Vector2& vec);

/*! Creates a translation on the x, y and z axes without reseting the other values. 
	\param vec Vector3&. Calls Vector3::GetX, Vector3::GetY and Vector3::GetZ to get values for translation. */	
		void AddTranslate(const Vector3& vec);

//==========================================================================================================================
//Scaling
//==========================================================================================================================
/*! Resets the Matrix and creates a scaling Matrix on the x and y axes. Calls MakeIndentity()
	\param x F32. Length to scale on x axis.
	\param y F32. Length to scale on y axis. */
		void Scale(F32 x, F32 y);

/*! Resets the Matrix and creates a scaling Matrix on the x, y and z axes. MakeIndentity()
	\param x F32. Length to scale on the x axis.
	\param y F32. Length to scale on the y axis.
	\param z F32. Length to scale on the z axis. */
		void Scale(F32 x, F32 y, F32 z);

/*! Resets the Matrix and creates a scaling Matrix on the x and y axes. Calls MakeIndentity().
	\param vec Vector2&. Calls Vector2::GetX and Vector2::GetY as values for scale on x and y axes. */
		void Scale(const Vector2& vec);

/*! Resets the Matrix and creates a scaling Matrix on the x and y axes. Calls MakeIndentity().
	\param vec Vector3&. Calls Vector3::GetX, Vector3::GetY and Vector3::GetZ as values for scale on x, y and z axes. */
		void Scale(const Vector3& vec);

/*! Creates a scaling Matrix on the x and y axes without resetting the other values.
	\param x F32. Value of scale on x axis.
	\param y F32. Value of scale on y axis. */
		void AddScale(F32 x, F32 y);

/*! Creates a scaling Matrix on the x, y and z axes without resetting the other values.
	\param x F32. Value of scale on x axis.
	\param y F32. Value of scale on y axis.
	\param z F32. Value of scale on z axis. */
		void AddScale(F32 x, F32 y, F32 z);

/*! Creates a scaling Matrix on the x and y axes without resetting the other values.
	\param vec Vector2&. Calls Vector2::GetX and Vector2::GetY as values for scale on x and y axes. */
		void AddScale(const Vector2& vec);

/*! Creates a scaling Matrix on the x, y and z axes without resetting the other values.
	\param vec Vector2&. Calls Vector3::GetX, Vector3::GetY and Vector3::GetZ as values for scale on x, y and z axes. */
		void AddScale(const Vector3& vec);

//==========================================================================================================================
//Rotations
//==========================================================================================================================
/*! Resets Matrix and creates rotation around the x axis. Call MakeIdentiy().
	\bug This is not working at all. 
	\param x F32. Degree of rotation around x axis. Calls DegreeToRadian() */
		void RotateX(F32 x);

/*! Creates rotation around the x axis without resetting other values. 
	\bug Completely untested and probably not working at all. 
	\param x F32. Degree of rotation around x axis. Calls DegreeToRadian() */
		void AddRotateX(F32 x);

/*! Resets Matrix and creates rotation around the y axis. Call MakeIdentiy().
	\bug This is not working at all. 
	\param y F32. Degree of rotation around y axis. Calls DegreeToRadian() */
		void RotateY(F32 y);

/*! Creates rotation around the y axis without resetting other values. 
	\bug Completely untested and probably not working at all. 
	\param y F32. Degree of rotation around y axis. Calls DegreeToRadian() */
		void AddRotateY(F32 y);

/*! Resets Matrix and creates rotation around the z axis. Call MakeIdentiy().
	\bug This is not working at all. 
	\param z F32. Degree of rotation around z axis. Calls DegreeToRadian() */
		void RotateZ(F32 z);

/*! Creates rotation around the z axis without resetting other values. 
	\bug Completely untested and probably not working at all. 
	\param z F32. Degree of rotation around z axis. Calls DegreeToRadian() */
		void AddRotateZ(F32 z);

/*! Resets the Matrix and creates an Matrix which will perform a rotation around the x, y and z axis in that order. 
	Calls MakeIdentity() 
	\bug Not working at all. The math is wrong, and rotations are not working in general.
	\param x F32. Degree of rotation around the x axis. Calls DegreeToRadian()
	\param y F32. Degree of rotation around the y axis. Calls DegreeToRadian()
	\param z F32. Degree of rotation around the z axis. Calls DegreeToRadian() */
		void Rotate(F32 x, F32 y, F32 z);

/*! Creates rotation around the x, y and z axis, in that order, without resetting other values.
	\bug Not working at all. The math is wrong, and rotations are not working in general.
	\param x F32. Degree of rotation around the x axis. Calls DegreeToRadian()
	\param y F32. Degree of rotation around the y axis. Calls DegreeToRadian()
	\param z F32. Degree of rotation around the z axis. Calls DegreeToRadian() */
		void AddRotation(F32 x, F32 y, F32 z);
		
//==========================================================================================================================
//Resettings
//==========================================================================================================================
/*! Wrapper for ResetMatrix(). Sets all values of the Matrix to 0, with the diagnal set to 1. */
		void MakeIdentity(void)
		{
			ResetMatrix(1);
		}	

/*! Sets all the values of the Matrix to 0, with the diagnal set to val.
	\param val F32. Value of the diagnal of the Matrix. */		
		void ResetMatrix(F32 val);

//==========================================================================================================================
//Misc
//==========================================================================================================================		
/*! Reverses the Column/Row order of the Matrix. */
		void Transpose(void);

/*! Also known as a straight multiplication. Multiplies each value of this Matrix by the matching value of M.
	\param M Matrix&. Right hand value to multiply by. */		
		void ComponentMulti(const Matrix& M);

//==========================================================================================================================
//
//Accessor
//
//==========================================================================================================================
/*! Return the array containing all the elements. */
		const F32* GetElems(void) const 
		{ 
			return _m; 
		}

//=====Return each element===== 
/*! Returns 0,0 */
		F32 Get11(void) const 
		{ 
			return _m[0];  
		}

/*! Returns 0,1 */		
		F32 Get12(void) const 
		{ 
			return _m[1];  
		}

/*! Returns 0,2 */		
		F32 Get13(void) const 
		{ 
			return _m[2];  
		}

/*! Returns 0,3 */		
		F32 Get14(void) const 
		{ 
			return _m[3];  
		}

/*! Returns 1,0 */
		F32 Get21(void) const 
		{ 
			return _m[4];  
		}

/*! Returns 1,1 */
		F32 Get22(void) const 
		{ 
			return _m[5];  
		}

/*! Returns 1,2 */
		F32 Get23(void) const 
		{ 
			return _m[6];  
		}
		
/*! Returns 1,3 */
		F32 Get24(void) const 
		{ 
			return _m[7];  
		}

/*! Returns 2,0 */
		F32 Get31(void) const 
		{ 
			return _m[8];  
		}
		
/*! Returns 2,1 */	
		F32 Get32(void) const 
		{ 
			return _m[9];  
		}
		
/*! Returns 2,2 */	
		F32 Get33(void) const 
		{ 
			return _m[10]; 
		}
		
/*! Returns 2,3 */
		F32 Get34(void) const 
		{ 
			return _m[11]; 
		}

/*! Returns 3,0 */
		F32 Get41(void) const 
		{ 
			return _m[12]; 
		}
		
/*! Returns 3,1 */
		F32 Get42(void) const 
		{ 
			return _m[13]; 
		}

/*! Returns 3,2 */
		F32 Get43(void) const 
		{ 
			return _m[14]; 
		}

/*! Returns 3,3 */
		F32 Get44(void) const 
		{ 
			return _m[15]; 
		}

//==========================================================================================================================
//
//Operator Overloads
//
//==========================================================================================================================
/*! Sets all the values of object to values of M. Call GetElems().
	\param M Matrix& */
		Matrix& operator=(const Matrix& M);
		
/*! Performs a Matrix style multiplication.
	\param RightMatrix Matrix&. Right hand value for multiplication. */
		Matrix& operator*(const Matrix& RightMatrix);
		
/*! Performs a Matrix sytle multiplication. Changes object after multiplication.
	\param RHM Matrix&. Right hand value for multiplication. */
		Matrix& operator*=(Matrix& RHM);

/*! Performs Matrix multiplication with Vector.
	\param RHV Vector2&. Right hand vector for multiplication. */
		Vector2 operator*(const Vector2& RHV);

/*! Performs Matrix multiplication with Vector.
	\param RHV Vector3&. Right hand vector for multiplication. */
		Vector3 operator*(const Vector3& RHV);

	private:
	struct vec4
	{

	};

//==========================================================================================================================
//
//Data
//
//==========================================================================================================================
		F32 _m[16]; ///< Array of values that represent the matrix.
		Vector3 _columns[4];
	};

}//End namespace
