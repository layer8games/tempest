#include <Engine/Matrix.h>
#include <iostream>

using namespace KillerMath;

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Matrix::Matrix(void)
:
_columns{Vector(1.0f, 0.0f, 0.0f, 0.0f),
		 Vector(0.0f, 1.0f, 0.0f, 0.0f),
		 Vector(0.0f, 0.0f, 1.0f, 0.0f),
		 Vector(0.0f, 0.0f, 0.0f, 1.0f)}
{  }

Matrix::Matrix(const Vector& x, const Vector& y, const Vector& z)
:
_columns{x, y, z, Vector(0.0f, 0.0f, 0.0f, 1.0f)}
{  }

Matrix::Matrix(const F32 mSrc[16])
:
_columns{Vector(mSrc[0], mSrc[1], mSrc[2], mSrc[3]),
		 Vector(mSrc[4], mSrc[5], mSrc[6], mSrc[7]),
		 Vector(mSrc[8], mSrc[9], mSrc[10], mSrc[11]),
		 Vector(mSrc[12], mSrc[13], mSrc[14], mSrc[15])}
{  }

Matrix::Matrix( F32 m00, F32 m01, F32 m02, F32 m03,
				F32 m10, F32 m11, F32 m12, F32 m13,
				F32 m20, F32 m21, F32 m22, F32 m23,
				F32 m30, F32 m31, F32 m32, F32 m33)
:
_columns{Vector(m00, m01, m02, m03),
		 Vector(m10, m11, m12, m13),
		 Vector(m20, m21, m22, m23),
		 Vector(m30, m31, m32, m33)}
{  }

Matrix::Matrix(const Matrix& M)
:
_columns{M[0], M[1], M[2], M[3]}
{  }

//==========================================================================================================================
//
//Matrix functions
//
//==========================================================================================================================
//==========================================================================================================================
//Projections
//==========================================================================================================================
void Matrix::MakeOrthographic(F32 width, F32 height, F32 depth, bool center) 
{
	F32 right; 
	F32 left; 
	F32 top;
	F32 bottom;
	F32 farPlane; 
	F32 nearPlane;
	
	if(center)
	{
		right     = width / 2.0f; 
		left      = -width / 2.0f; 
		top       = height / 2.0f;
		bottom    = -height / 2.0f;
		farPlane  = depth / 2.0f; 
		nearPlane = 0.0f;
	}
	else
	{
		right 	  = width;
	  	left 	  = 0.0f;
		top 	  = height;
		bottom 	  = 0.0f;
		farPlane  = depth;
		nearPlane = 0.0f;
	}

  	//Reset Matrix
	MakeIdentity();

	assert(right - left != 0.0f);
	assert(bottom - top != 0.0f);
	assert(nearPlane - farPlane != 0.0f);

	//Diagnal
	_columns[0][x]  = 2.0f / (right - left);
	_columns[1][y]  = 2.0f / (top - bottom);
	_columns[2][z] = 2.0f / (nearPlane - farPlane);
	_columns[3][w] = 1.0f;

	//Transform "Vector"
	_columns[3][x] = (left + right) / (left - right);
	_columns[3][y] = (bottom + top) / (bottom - top);
	_columns[3][z] = (nearPlane + farPlane)   / (farPlane - nearPlane);
}

void Matrix::MakePerspective(F32 width, F32 height, F32 depth, bool center)
{

	F32 right; 
	F32 left; 
	F32 top;
	F32 bottom;
	F32 farPlane; 
	F32 nearPlane;
	

	if(center)
	{
		right     = width / 2.0f; 
		left      = -width / 2.0f; 
		top       = height / 2.0f;
		bottom    = -height / 2.0f;
		farPlane  = depth / 2.0f; 
		nearPlane = 0.0f;
	}
	else
	{
		right 	  = width;
	  	left 	  = 0.0f;
		top 	  = height;
		bottom 	  = 0.0f;
		farPlane  = depth;
		nearPlane = 0.0f;
	}

	//Reset Matrix 
	MakeIdentity();

	assert(right - left != 0.0f);
	assert(top - bottom != 0.0f);
	assert(nearPlane - farPlane != 0.0f);

	
	_columns[0][x]  = (2.0f * nearPlane) / (right - left);
	_columns[1][y]  = (2.0f * nearPlane) / (top - bottom);
	_columns[2][x]  = (right + left) / (right - left);
	_columns[2][y]  = (top + bottom) / (top - bottom);
	_columns[2][z] = (nearPlane + farPlane) / (nearPlane - farPlane);
	_columns[2][w] = -1.0f;
	_columns[3][z] = (2.0f * nearPlane * farPlane) / (nearPlane - farPlane);
}

void Matrix::MakePerspective(F32 fieldOfView, F32 aspectRatio, F32 nearPlane, F32 farPlane)
{
	assert(nearPlane - farPlane != 0.0f);

	F32 S = 1.0f / tan(DegreeToRadian(0.5f * fieldOfView));

	//Reset Matrix 
	MakeIdentity();

	_columns[0][x] = S / aspectRatio;
	_columns[1][y] = S;
	_columns[2][z] = (nearPlane + farPlane) / (nearPlane - farPlane);
	_columns[2][w] = -1.0f;
	_columns[3][z] = (2.0f * nearPlane * farPlane) / (nearPlane - farPlane);
}

//==========================================================================================================================
//Translations
//==========================================================================================================================
void Matrix::Translate(F32 xVal, F32 yVal)
{
	MakeIdentity();

	_columns[3][x] = xVal;
	_columns[3][y] = yVal;
}

void Matrix::Translate(F32 x, F32 y, F32 z)
{
	MakeIdentity();			

	_columns[3][x] = xVal;
	_columns[3][y] = yVal;
	_columns[3][z] = zVal;
}

void Matrix::Translate2D(const Vector& vec)
{
	MakeIdentity(); 

	_columns[3][x] = vec[x];
	_columns[3][y] = vec[y];
}

void Matrix::Translate(const Vector& vec)
{
	MakeIdentity();

	_columns[3][x] = vec[x];
	_columns[3][y] = vec[y];
	_columns[3][z] = vec[z];
}

void Matrix::AddTranslate(F32 xVal, F32 yVal)
{
	_columns[3][x] += xVal;
	_columns[3][y] += yVal;
}

void Matrix::AddTranslate(F32 xVal, F32 yVal, F32 zVal)
{
	_columns[3][x] += xVal; 
	_columns[3][y] += yVal; 
	_columns[3][z] += zVal;
}

void Matrix::AddTranslate2D(const Vector& vec)
{
	_columns[3][x] += vec[x];
	_columns[3][y] += vec[y];
}

void Matrix::AddTranslate(const Vector& vec)
{
	_columns[3][x] += vec[x];
	_columns[3][y] += vec[y];
	_columns[3][z] += vec[z];
}

//==========================================================================================================================
//Scaling
//==========================================================================================================================
void Matrix::Scale(F32 xVal, F32 yVal)
{
	MakeIdentity();

	_columns[0][x] = xVal;
	_columns[1][y] = yVal;
}

void Matrix::Scale(F32 xVal, F32 yVal, F32 zVal)
{
	MakeIdentity();

	_columns[0][x] = xVal;
	_columns[1][y] = yVal;
	_columns[2][z] = zVal;
}

void Matrix::Scale2D(const Vector& vec)
{
	MakeIdentity();

	_columns[0][x] = vec[x];
	_columns[1][y] = vec[y];
}

void Matrix::Scale(const Vector& vec)
{
	MakeIdentity();

	_columns[0][x] = vec[x];
	_columns[1][y] = vec[y];
	_columns[2][z] = vec[z];
}

void Matrix::AddScale(F32 xVal, F32 yVal)
{
	_columns[0][x] += xVal;
	_columns[1][y] += yVal;
}

void Matrix::AddScale(F32 xVal, F32 yVal, F32 zVal)
{
	_columns[0][x] += xVal;
	_columns[1][y] += yVal;
	_columns[2][z] += zVal;
}

void Matrix::AddScale2D(const Vector& vec)
{
	_columns[0][x] += vec[x];
	_columns[1][y] += vec[y];
}

void Matrix::AddScale(const Vector& vec)
{
	_columns[0][x] += vec[x];
	_columns[1][y] += vec[y];
	_columns[2][z] += vec[z];
}

//==========================================================================================================================
//Rotations
//==========================================================================================================================
void Matrix::RotateX(F32 val)
{
	val = DegreeToRadian(val);

	MakeIdentity();

	_columns[1][y] = cos(val);
	_columns[1][z] = -sin(val);
	_columns[2][y] = sin(val);
	_columns[2][z] = cos(val);
}

void Matrix::AddRotateX(F32 val)
{
	val = DegreeToRadian(val);

	_columns[1][y] += cos(val);
	_columns[1][z] += -sin(val);
	_columns[2][y] += sin(val);
	_columns[2][z] += cos(val);
}

void Matrix::RotateY(F32 val)
{
	val = DegreeToRadian(val);

	MakeIdentity();

	_columns[0][x] = cos(val);
	_columns[0][y] = sin(val);
	_columns[2][x] = -sin(val);
	_columns[2][y] = cos(val);
}

void Matrix::AddRotateY(F32 val)
{
	val = DegreeToRadian(val);

	_columns[0][x] += cos(val);
	_columns[0][y] += sin(val);
	_columns[2][x] += -sin(val);
	_columns[2][y] += cos(val);	
}

void Matrix::RotateZ(F32 val)
{
	val = DegreeToRadian(val);

	MakeIdentity();

	_columns[0][x] = cos(val);
	_columns[0][y] = -sin(val);
	_columns[1][x] = sin(val);
	_columns[1][y] = cos(val);
}

void Matrix::AddRotateZ(F32 val)
{
	val = DegreeToRadian(val);

	_columns[0][x] += cos(val);
	_columns[0][y] += -sin(val);
	_columns[1][x] += sin(val);
	_columns[1][y] += cos(val);
}

void Matrix::Rotate(F32 xVal, F32 yVal, F32 zVal)
{
	xVal = DegreeToRadian(xVal);
	yVal = DegreeToRadian(yVal);
	zVal = DegreeToRadian(zVal);

	MakeIdentity();

	_columns[0][x] = cos(yVal) * cos(zVal);
	_columns[0][y] = -cos(yVal) * sin(zVal);
	_columns[0][z] = sin(yVal);
	_columns[1][x] = cos(xVal) * sin(zVal) + sin(xVal) * sin(yVal) * cos(zVal);
	_columns[1][y] = cos(xVal) * cos(zVal) - sin(xVal) * sin(yVal) * sin(zVal);
	_columns[1][z] = -sin(xVal) * cos(yVal);
	_columns[2][x] = sin(xVal) * sin(zVal) - cos(xVal) * sin(yVal) * cos(zVal);
	_columns[2][y] = sin(xVal) * cos(zVal) + cos(xVal) * sin(yVal) * sin(zVal);
	_columns[2][z] = cos(xVal) * cos(yVal);
}

void Matrix::AddRotation(F32 xVal, F32 yVal, F32 zVal)
{
	xVal = DegreeToRadian(xVal);
	yVal = DegreeToRadian(yVal);
	zVal = DegreeToRadian(zVal);

	_columns[0][x] += cos(yVal) * cos(zVal);
	_columns[0][y] += -cos(yVal) * sin(zVal);
	_columns[0][z] += sin(yVal);
	_columns[1][x] += cos(xVal) * sin(zVal) + sin(xVal) * sin(yVal) * cos(zVal);
	_columns[1][y] += cos(xVal) * cos(zVal) - sin(xVal) * sin(yVal) * sin(zVal);
	_columns[1][z] += -sin(xVal) * cos(yVal);
	_columns[2][x] += sin(xVal) * sin(zVal) - cos(xVal) * sin(yVal) * cos(zVal);
	_columns[2][y] += sin(xVal) * cos(zVal) + cos(xVal) * sin(yVal) * sin(zVal);
	_columns[2][z] += cos(xVal) * cos(yVal);
}

//==========================================================================================================================
//Resettings
//==========================================================================================================================
void Matrix::ResetMatrix(F32 val)
{
	//Reset Matrix
	_columns[0] = Vector(val, 0.0f, 0.0f, 0.0f);
	_columns[1] = Vector(0.0f, val, 0.0f, 0.0f);
	_columns[2] = Vector(0.0f, 0.0f, val, 0.0f);
	_columns[3] = Vector(0.0f, 0.0f, 0.0f, val);
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