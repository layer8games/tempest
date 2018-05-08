#include <Engine/Matrix.h>

using namespace KillerMath;

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Matrix::Matrix(void)
{
	_m[0]  = _m[1]  = _m[2]  = _m[3]  = 0;
	_m[4]  = _m[5]  = _m[6]  = _m[7]  = 0;
	_m[8]  = _m[9]  = _m[10] = _m[11] = 0;
	_m[12] = _m[13] = _m[14] = 0;
	_m[15] = 1;
}

Matrix::Matrix(F32 val)
{
	_m[0] = _m[5] = _m[10] = _m[15] = val;

	_m[1]  = _m[2]  = _m[3]  = 0;
	_m[4]  = _m[6]  = _m[7]  = 0; 
	_m[8]  = _m[9]  = _m[11] = 0;
	_m[12] = _m[13] = _m[14] = 0;
}

Matrix::Matrix(const F32 mSrc[16])
{
	_m[0]  = mSrc[0];  _m[1] = mSrc[1];   _m[2]  = mSrc[2];  _m[3]  = mSrc[3];
	_m[4]  = mSrc[4];  _m[5] = mSrc[5];   _m[6]  = mSrc[6];  _m[7]  = mSrc[7];
	_m[8]  = mSrc[8];  _m[9] = mSrc[9];   _m[10] = mSrc[10]; _m[11] = mSrc[11];
	_m[12] = mSrc[12]; _m[13] = mSrc[13]; _m[14] = mSrc[14]; _m[15] = mSrc[15];
}

Matrix::Matrix( F32 m00, F32 m01, F32 m02, F32 m03,
				 F32 m10, F32 m11, F32 m12, F32 m13,
				 F32 m20, F32 m21, F32 m22, F32 m23,
				 F32 m30, F32 m31, F32 m32, F32 m33)
{
	_m[0] = m00;  
	_m[1] = m01;  
	_m[2] = m02;  
	_m[3] = m03;
	_m[4] = m10;  
	_m[5] = m11;   
	_m[6] = m12;  
	_m[7] = m13;
	_m[8] = m20;  
	_m[9] = m21;   
	_m[10] = m22; 
	_m[11] = m23;		
	_m[12] = m30; 
	_m[13] = m31;   
	_m[14] = m32; 
	_m[15] = m33;
}

Matrix::Matrix(const Matrix& M)
{
	const F32* m = M.GetElems();

	_m[0] = m[0];  
	_m[1] = m[1];   
	_m[2] = m[2];  
	_m[3] = m[3];
	_m[4] = m[4]; 
	_m[5] = m[5];   
	_m[6] = m[6];  
	_m[7] = m[7];
	_m[8] = m[8];  
	_m[9] = m[9];  
	_m[10] = m[10]; 
	_m[11] = m[11];
	_m[12] = m[12];
	_m[13] = m[13];   
	_m[14] = m[14]; 
	_m[15] = m[15];
}

//==========================================================================================================================
//
//Matrix functions
//
//==========================================================================================================================
//==========================================================================================================================
//Projections
//==========================================================================================================================
void Matrix::MakeOrthographic(F32 width, F32 height, F32 depth) 
{
  	F32 right = width;
  	F32 left = 0.0f;
	F32 top = height;
	F32 bottom = 0.0f;
	F32 farPlane = depth;
	F32 nearPlane = 0.0f;

  	//Reset Matrix
	_m[0]  =  _m[1]  =  _m[2]  =  _m[3]  = 0.0f;

	_m[4]  =  _m[5]  =  _m[6]  =  _m[7]  = 0.0f;

	_m[8]  =  _m[9]  =  _m[10] =  _m[11] = 0.0f;

	_m[12] =  _m[13] =  _m[14] =  _m[15] = 0.0f;

	assert(right - left != 0.0f);
	assert(bottom - top != 0.0f);
	assert(nearPlane - farPlane != 0.0f);

	//Diagnal
	_m[0]  = 2.0f / (right - left);
	_m[5]  = 2.0f / (top - bottom);
	_m[10] = 2.0f / (nearPlane - farPlane);
	_m[15] = 1.0f;

	//Transform "Vector"
	_m[12] = (left + right) / (left - right);
	_m[13] = (bottom + top) / (bottom - top);
	_m[14] = (nearPlane + farPlane)   / (farPlane - nearPlane);

}

void Matrix::MakePerspective(F32 width, F32 height, F32 depth)
{
	F32 right   = width; 
	F32 left    = 0.0f; 
	F32 top     = height;
	F32 bottom  = 0.0f; 
	F32 farPlane     = depth; 
	//===== I don't know why this works. 0.0f will not... =====
	F32 nearPlane    = 100.0f;

	//Reset Matrix 
	_m[0]  =  _m[1]  =  _m[2]  =  _m[3]  = 0.0f;

	_m[4]  =  _m[5]  =  _m[6]  =  _m[7]  = 0.0f;

	_m[8]  =  _m[9]  =  _m[10] =  _m[11] = 0.0f;

	_m[12] =  _m[13] =  _m[14] =  _m[15] = 0.0f;

	assert(right - left != 0.0f);
	assert(top - bottom != 0.0f);
	assert(nearPlane - farPlane != 0.0f);

	//Diagnal
	_m[0]  = (2.0f * nearPlane) / (right - left);
	_m[5]  = (2.0f * nearPlane) / (top - bottom);
	_m[15] = 0.0f;

	//Transform "Vector"
	_m[8] = (right + left) / (right - left);
	_m[9] = (top + bottom) / (top - bottom);
	_m[10] = (nearPlane + farPlane) / (nearPlane - farPlane);
	
	_m[11] = -1.0f;
	_m[14] = (2.0f * nearPlane * farPlane) / (nearPlane - farPlane);
}

//==========================================================================================================================
//Translations
//==========================================================================================================================
void Matrix::Translate(F32 x, F32 y)
{
	MakeIdentity();

	_m[12] = x;
	_m[13] = y;
}

void Matrix::Translate(F32 x, F32 y, F32 z)
{
	MakeIdentity();			

	_m[12] = x;
	_m[13] = y;
	_m[14] = z;
}

void Matrix::Translate(const Vector2& vec)
{
	MakeIdentity(); 

	_m[12] = vec.GetX();
	_m[13] = vec.GetY();
}

void Matrix::Translate(const Vector3& vec)
{
	MakeIdentity();

	_m[12] = vec.GetX();
	_m[13] = vec.GetY();
	_m[14] = vec.GetZ();
}

void Matrix::AddTranslate(F32 x, F32 y)
{
	_m[12] = x;
	_m[13] = y;
}

void Matrix::AddTranslate(F32 x, F32 y, F32 z)
{
	_m[12] = x; 
	_m[13] = y; 
	_m[14] = z;
}

void Matrix::AddTranslate(const Vector2& vec)
{
	_m[12] = vec.GetX();
	_m[13] = vec.GetY();
}

void Matrix::AddTranslate(const Vector3& vec)
{
	_m[12] = vec.GetX();
	_m[13] = vec.GetY();
	_m[14] = vec.GetZ();
}

//==========================================================================================================================
//Scaling
//==========================================================================================================================
void Matrix::Scale(F32 x, F32 y)
{
	MakeIdentity();

	_m[0] = x;
	_m[5] = y;
}

void Matrix::Scale(F32 x, F32 y, F32 z)
{
	MakeIdentity();

	_m[0] = x;
	_m[5] = y;
	_m[10] = z;
}

void Matrix::Scale(const Vector2& vec)
{
	MakeIdentity();

	_m[0] = vec.GetX();
	_m[5] = vec.GetY();
}

void Matrix::Scale(const Vector3& vec)
{
	MakeIdentity();

	_m[0] = vec.GetX();
	_m[5] = vec.GetY();
	_m[10] = vec.GetZ();
}

void Matrix::AddScale(F32 x, F32 y)
{
	_m[0] = x;
	_m[5] = y;
}

void Matrix::AddScale(F32 x, F32 y, F32 z)
{
	_m[0] = x;
	_m[5] = y;
	_m[10] = z;
}

void Matrix::AddScale(const Vector2& vec)
{
	_m[0] = vec.GetX();
	_m[5] = vec.GetY();
}

void Matrix::AddScale(const Vector3& vec)
{
	_m[0] = vec.GetX();
	_m[5] = vec.GetY();
	_m[10] = vec.GetZ();
}

//==========================================================================================================================
//Rotations
//==========================================================================================================================
void Matrix::RotateX(F32 x)
{
	x = DegreeToRadian(x);

	MakeIdentity();

	_m[5] = cos(x);
	_m[6] = -sin(x);
	_m[9] = sin(x);
	_m[10] = cos(x);
}

void Matrix::RotateY(F32 y)
{
	y = DegreeToRadian(y);

	MakeIdentity();

	_m[0] = cos(y);
	_m[2] = sin(y);
	_m[8] = -sin(y);
	_m[10] = cos(y);
}

void Matrix::RotateZ(F32 z)
{
	z = DegreeToRadian(z);

	MakeIdentity();

	_m[0] = cos(z);
	_m[1] = -sin(z);
	_m[4] = sin(z);
	_m[5] = cos(z);
}

void Matrix::Rotate(F32 x, F32 y, F32 z)
{
	x = DegreeToRadian(x);
	y = DegreeToRadian(y);
	z = DegreeToRadian(z);

	MakeIdentity();

	_m[0] = cos(y) * cos(z);
	_m[1] = -cos(y) * sin(z);
	_m[2] = sin(y);
	_m[4] = cos(x) * sin(z) + sin(x) * sin(y) * cos(z);
	_m[5] = cos(x) * cos(z) - sin(x) * sin(y) * sin(z);
	_m[6] = -sin(x) * cos(y);
	_m[8] = sin(x) * sin(z) - cos(x) * sin(y) * cos(z);
	_m[9] = sin(x) * cos(z) + cos(x) * sin(y) * sin(z);
	_m[10] = cos(x) * cos(y);
}

//==========================================================================================================================
//Resettings
//==========================================================================================================================
void Matrix::ResetMatrix(F32 val)
{
	//Reset Matrix
	_m[0]  =  _m[1]  =  _m[2]  =  _m[3]  = 0;

	_m[4]  =  _m[5]  =  _m[6]  =  _m[7]  = 0;

	_m[8]  =  _m[9]  =  _m[10] =  _m[11] = 0;

	_m[12] =  _m[13] =  _m[14] =  _m[15] = 0;

	_m[0] = val;
	_m[5] = val;
	_m[10] = val;
	_m[15] = val;

}

//==========================================================================================================================
//Misc
//==========================================================================================================================
void Matrix::Transpose(void)
{
	F32 newMatrix[16];

	
	newMatrix[0] = _m[0];
	newMatrix[1] = _m[4];
	newMatrix[2] = _m[8];
	newMatrix[3] = _m[12];

	newMatrix[4] = _m[1];
	newMatrix[5] = _m[5];
	newMatrix[6] = _m[9];
	newMatrix[7] = _m[13];

	newMatrix[8] = _m[2];
	newMatrix[9] = _m[6];
	newMatrix[10] = _m[10];
	newMatrix[11] = _m[14];

	newMatrix[12] = _m[3];
	newMatrix[13] = _m[7];
	newMatrix[14] = _m[11];
	newMatrix[15] = _m[15];


	_m[0] = newMatrix[0];
	_m[1] = newMatrix[1];
	_m[2] = newMatrix[2];
	_m[3] = newMatrix[3];

	_m[4] = newMatrix[4];
	_m[5] = newMatrix[5];
	_m[6] = newMatrix[6];
	_m[7] = newMatrix[7];

	_m[8] = newMatrix[8];
	_m[9] = newMatrix[9];
	_m[10] = newMatrix[10];
	_m[11] = newMatrix[11];

	_m[12] = newMatrix[12];
	_m[13] = newMatrix[13];
	_m[14] = newMatrix[14];
	_m[15] = newMatrix[15];
}

void Matrix::ComponentMulti(const Matrix& M)
{
	const F32* elems = M.GetElems();

	_m[0] *= elems[0];
	_m[1] *= elems[1];
	_m[2] *= elems[2];
	_m[3] *= elems[3];
	_m[4] *= elems[4];
	_m[5] *= elems[5];
	_m[6] *= elems[6];
	_m[7] *= elems[7];
	_m[8] *= elems[8];
	_m[9] *= elems[9];
	_m[10] *= elems[10];
	_m[11] *= elems[11];
	_m[12] *= elems[12];
	_m[13] *= elems[13];
	_m[14] *= elems[14];
	_m[15] *= elems[15];

}

//==========================================================================================================================
//
//Operator Overloads
//
//==========================================================================================================================
Matrix& Matrix::operator=(const Matrix& M) 
{
	const F32* elems = M.GetElems();

	_m[0] = elems[0];
	_m[1] = elems[1];
	_m[2] = elems[2];
	_m[3] = elems[3];

	_m[4] = elems[4];
	_m[5] = elems[5];
	_m[6] = elems[6];
	_m[7] = elems[7];


	_m[8]  = elems[8];
	_m[9]  = elems[9];
	_m[10] = elems[10];
	_m[11] = elems[11];

	_m[12] = elems[12];
	_m[13] = elems[13];
	_m[14] = elems[14];
	_m[15] = elems[15];

	return *this;
}

Matrix& Matrix::operator*(const Matrix& RightMatrix) 
{
	const F32* left = this->GetElems();
	const F32* right = RightMatrix.GetElems();

	Matrix newMatrix
	(
		left[0] * right[0] + left[4] * right[1] + left[8]  * right[2] + left[12] * right[3], //m00
		left[1] * right[0] + left[5] * right[1] + left[9]  * right[2] + left[13] * right[3], //m01
		left[2] * right[0] + left[6] * right[1] + left[10] * right[2] + left[14] * right[3], //m02
		left[3] * right[0] + left[7] * right[1] + left[11] * right[2] + left[15] * right[3], //m03

		left[0] * right[4] + left[4] * right[5] + left[8]  * right[6] + left[12] * right[7], //m10
		left[1] * right[4] + left[5] * right[5] + left[9]  * right[6] + left[13] * right[7], //m11
		left[2] * right[4] + left[6] * right[5] + left[10] * right[6] + left[14] * right[7], //m12
		left[3] * right[4] + left[7] * right[5] + left[11] * right[6] + left[15] * right[7], //m13

		left[0] * right[8] + left[4] * right[9] + left[8]  * right[10] + left[12] * right[11], //m20
		left[1] * right[8] + left[5] * right[9] + left[9]  * right[10] + left[13] * right[11], //m21
		left[2] * right[8] + left[6] * right[9] + left[10] * right[10] + left[14] * right[11], //m22
		left[3] * right[8] + left[7] * right[9] + left[11] * right[10] + left[15] * right[11], //m23

		left[0] * right[12] + left[4] * right[13] + left[8]  * right[14] + left[12] * right[15], //m30
		left[1] * right[12] + left[5] * right[13] + left[9]  * right[14] + left[13] * right[15], //m31
		left[2] * right[12] + left[6] * right[13] + left[10] * right[14] + left[14] * right[15], //m32
		left[3] * right[12] + left[7] * right[13] + left[11] * right[14] + left[15] * right[15]  //m33
	);

	*this = newMatrix;
	return *this;
}

Matrix& Matrix::operator*=(Matrix& RHM) 
{
	*this = RHM * *this;
	return *this;
}

Vector2 Matrix::operator*(const Vector2& RHV)
{
	F32 x = RHV.GetX();
	F32 y = RHV.GetY();
	F32 z = RHV. GetZ();
	F32 w = RHV.GetW();

	return Vector2
	(
		x * _m[0] + y * _m[4] + z * _m[8] + w * _m[12],
		x * _m[1] + y * _m[5] + z * _m[9] + w * _m[13]
	);
}

Vector3 Matrix::operator*(const Vector3& RHV)
{
	F32 x = RHV.GetX();
	F32 y = RHV.GetY();
	F32 z = RHV. GetZ();
	F32 w = RHV.GetW();

	return Vector3
	(
		x * _m[0] + y * _m[4] + z * _m[8] + w * _m[12],
		x * _m[1] + y * _m[5] + z * _m[9] + w * _m[13],
		x * _m[2] + y * _m[6] + z * _m[10] + w * _m[14]

	);
}