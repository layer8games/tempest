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

Matrix::Matrix(const Vector& x, const Vector& y, const Vector& z, const Vector& w)
:
_columns{x, y, z, w}
{  }

Matrix::Matrix(const F32 val)
:
_columns{Vector(val, 0.0f, 0.0f, 0.0f),
		 Vector(0.0f, val, 0.0f, 0.0f),
		 Vector(0.0f, 0.0f, val, 0.0f),
		 Vector(0.0f, 0.0f, 0.0f, 1.0f)}
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
const std::vector<F32> Matrix::GetElems(void) const
{
	std::vector<F32> elems;
	
	elems.push_back(_columns[0][x]);
	elems.push_back(_columns[0][y]);
	elems.push_back(_columns[0][z]);
	elems.push_back(_columns[0][w]);
	elems.push_back(_columns[1][x]);
	elems.push_back(_columns[1][y]);
	elems.push_back(_columns[1][z]);
	elems.push_back(_columns[1][w]);
	elems.push_back(_columns[2][x]);
	elems.push_back(_columns[2][y]);
	elems.push_back(_columns[2][z]);
	elems.push_back(_columns[2][w]);
	elems.push_back(_columns[3][x]);
	elems.push_back(_columns[3][y]);
	elems.push_back(_columns[3][z]);
	elems.push_back(_columns[3][w]);

	return elems;
}

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

void Matrix::Translate(F32 xVal, F32 yVal, F32 zVal)
{
	MakeIdentity();			

	_columns[3][x] = xVal;
	_columns[3][y] = yVal;
	_columns[3][z] = zVal;
}

void Matrix::Translate(const Vector& vec)
{
	MakeIdentity(); 

	_columns[3][x] = vec[x];
	_columns[3][y] = vec[y];

	if(!vec.Is2D())
	{
		_columns[3][z] = vec[z];
	}
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

void Matrix::AddTranslate(const Vector& vec)
{
	_columns[3][x] += vec[x];
	_columns[3][y] += vec[y];
	
	if(!vec.Is2D()) 
	{
		_columns[3][z] += vec[z];
	}
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

void Matrix::Scale(const Vector& vec)
{
	MakeIdentity();

	_columns[0][x] = vec[x];
	_columns[1][y] = vec[y];
	
	if(!vec.Is2D()) 
	{
		_columns[2][z] = vec[z];
	}
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

void Matrix::AddScale(const Vector& vec)
{
	_columns[0][x] += vec[x];
	_columns[1][y] += vec[y];
	
	if(!vec.Is2D()) 
	{
		_columns[2][z] += vec[z];
	}
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
	_columns[0][z] = sin(val);
	_columns[2][x] = -sin(val);
	_columns[2][z] = cos(val);
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
void Matrix::Reset(F32 val)
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
	Vector newCol0 {_columns[0][x], _columns[1][x], _columns[2][x], _columns[3][x]};
	Vector newCol1 {_columns[0][y], _columns[1][y], _columns[2][y], _columns[3][y]};
	Vector newCol2 {_columns[0][z], _columns[1][z], _columns[2][z], _columns[3][z]};
	Vector newCol3 {_columns[0][w], _columns[1][w], _columns[2][w], _columns[3][w]};

	_columns[0] = newCol0;
	_columns[1] = newCol1;
	_columns[2] = newCol2;
	_columns[3] = newCol3;
}

void Matrix::ComponentMulti(const Matrix& mat)
{
	_columns[0][x] *= mat[0][x];
	_columns[0][y] *= mat[0][y];
	_columns[0][z] *= mat[0][z];
	_columns[0][w] *= mat[0][w];

	_columns[1][x] *= mat[1][x];
	_columns[1][y] *= mat[1][y];
	_columns[1][z] *= mat[1][z];
	_columns[1][w] *= mat[1][w];

	_columns[2][x] *= mat[2][x];
	_columns[2][y] *= mat[2][y];
	_columns[2][z] *= mat[2][z];
	_columns[2][w] *= mat[2][w];

	_columns[3][x] *= mat[3][x];
	_columns[3][y] *= mat[3][y];
	_columns[3][z] *= mat[3][z];
	_columns[3][w] *= mat[3][w];
}

//==========================================================================================================================
//
//Operator Overloads
//
//==========================================================================================================================
Matrix& Matrix::operator=(const Matrix& mat) 
{
	_columns[0][x] = mat[0][x];
	_columns[0][y] = mat[0][y];
	_columns[0][z] = mat[0][z];
	_columns[0][w] = mat[0][w];

	_columns[1][x] = mat[1][x];
	_columns[1][y] = mat[1][y];
	_columns[1][z] = mat[1][z];
	_columns[1][w] = mat[1][w];

	_columns[2][x] = mat[2][x];
	_columns[2][y] = mat[2][y];
	_columns[2][z] = mat[2][z];
	_columns[2][w] = mat[2][w];

	_columns[3][x] = mat[3][x];
	_columns[3][y] = mat[3][y];
	_columns[3][z] = mat[3][z];
	_columns[3][w] = mat[3][w];

	return *this;
}

Matrix Matrix::operator*(const Matrix& mat) 
{
	Vector xCol 
	{
		_columns[0][x] * mat[0][x] + _columns[1][x] * mat[0][y] + _columns[2][x] * mat[0][z] + _columns[3][x] * mat[0][w],
		_columns[0][y] * mat[0][x] + _columns[1][y] * mat[0][y] + _columns[2][y] * mat[0][z] + _columns[3][y] * mat[0][w],
		_columns[0][z] * mat[0][x] + _columns[1][z] * mat[0][y] + _columns[2][z] * mat[0][z] + _columns[3][z] * mat[0][w],
		_columns[0][w] * mat[0][x] + _columns[1][w] * mat[0][y] + _columns[2][w] * mat[0][z] + _columns[3][w] * mat[0][w],

	};

	Vector yCol
	{
		_columns[0][x] * mat[1][x] + _columns[1][x] * mat[1][y] + _columns[2][x] * mat[1][z] + _columns[3][x] * mat[1][w],
		_columns[0][y] * mat[1][x] + _columns[1][y] * mat[1][y] + _columns[2][y] * mat[1][z] + _columns[3][y] * mat[1][w],
		_columns[0][z] * mat[1][x] + _columns[1][z] * mat[1][y] + _columns[2][z] * mat[1][z] + _columns[3][z] * mat[1][w],
		_columns[0][w] * mat[1][x] + _columns[1][w] * mat[1][y] + _columns[2][w] * mat[1][z] + _columns[3][w] * mat[1][w],
	};

	Vector zCol
	{
		_columns[0][x] * mat[2][x] + _columns[1][x] * mat[2][y] + _columns[2][x] * mat[2][z] + _columns[3][x] * mat[2][w],
		_columns[0][y] * mat[2][x] + _columns[1][y] * mat[2][y] + _columns[2][y] * mat[2][z] + _columns[3][y] * mat[2][w],
		_columns[0][z] * mat[2][x] + _columns[1][z] * mat[2][y] + _columns[2][z] * mat[2][z] + _columns[3][z] * mat[2][w],
		_columns[0][w] * mat[2][x] + _columns[1][w] * mat[2][y] + _columns[2][w] * mat[2][z] + _columns[3][w] * mat[2][w],
	};

	Vector wCol
	{
		_columns[0][x] * mat[3][x] + _columns[1][x] * mat[3][y] + _columns[2][x] * mat[3][z] + _columns[3][x] * mat[3][w],
		_columns[0][y] * mat[3][x] + _columns[1][y] * mat[3][y] + _columns[2][y] * mat[3][z] + _columns[3][y] * mat[3][w],
		_columns[0][z] * mat[3][x] + _columns[1][z] * mat[3][y] + _columns[2][z] * mat[3][z] + _columns[3][z] * mat[3][w],
		_columns[0][w] * mat[3][x] + _columns[1][w] * mat[3][y] + _columns[2][w] * mat[3][z] + _columns[3][w] * mat[3][w],
	};

	return Matrix(xCol, yCol, zCol, wCol);
}

Vector Matrix::operator*(const Vector& vec)
{
	return Vector( _columns[0][x] * vec[x] + _columns[1][x] * vec[y] + _columns[2][x] * vec[z] + _columns[3][x] * vec[w],
				   _columns[0][y] * vec[x] + _columns[1][y] * vec[y] + _columns[2][y] * vec[z] + _columns[3][y] * vec[w],
				   _columns[0][z] * vec[x] + _columns[1][z] + vec[y] + _columns[2][z] * vec[z] + _columns[3][z] * vec[w],
				   _columns[0][w] * vec[x] + _columns[1][w] + vec[y] + _columns[2][w] + vec[z] + _columns[3][w] * vec[w] );
}