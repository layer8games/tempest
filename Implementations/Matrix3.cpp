#include <Engine/Matrix3.h>

using namespace KillerMath;

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Matrix3::Matrix3(void)
:
_columns{ Column3(1.0f, 0.0f, 0.0f),
		  Column3(0.0f, 1.0f, 0.0f),
		  Column3(0.0f, 0.0f, 1.0f) }
{  }

Matrix3::Matrix3(const Column3& x, const Column3& y, const Column3& z)
:
_columns{x, y, z}
{  }

Matrix3::Matrix3(const Vector& x, const Vector& y, const Vector& z)
:
_columns{x, y, z}
{  }


Matrix3::Matrix3(const F32 val)
:
_columns{ Column3(val, 0.0f, 0.0f),
		  Column3(0.0f, val, 0.0f),
		  Column3(0.0f, 0.0f, val) }
{  }

Matrix3::Matrix3( F32 m00, F32 m01, F32 m02,
				  F32 m10, F32 m11, F32 m12,
				  F32 m20, F32 m21, F32 m22 )
:
_columns{Column3(m00, m01, m02),
		 Column3(m10, m11, m12),
		 Column3(m20, m21, m22) }
{  }

Matrix3::Matrix3(const Matrix3& M)
:
_columns{M[0], M[1], M[2]}
{  }

//==========================================================================================================================
//
//Matrix3 functions
//
//==========================================================================================================================
const std::vector<F32> Matrix3::GetElems(void) const
{
	std::vector<F32> elems;
	
	elems.push_back(_columns[0][x]);
	elems.push_back(_columns[0][y]);
	elems.push_back(_columns[0][z]);
	elems.push_back(_columns[1][x]);
	elems.push_back(_columns[1][y]);
	elems.push_back(_columns[1][z]);
	elems.push_back(_columns[2][x]);
	elems.push_back(_columns[2][y]);
	elems.push_back(_columns[2][z]);

	return elems;
}


//==========================================================================================================================
//Scaling
//==========================================================================================================================
Matrix3 Matrix3::Scale(F32 xVal, F32 yVal)
{
	Matrix3 mat{1.0f};

	mat[0][x] = xVal;
	mat[1][y] = yVal;

	return mat;
}

Matrix3 Matrix3::Scale(F32 xVal, F32 yVal, F32 zVal)
{
	Matrix3 mat{1.0f};

	mat[0][x] = xVal;
	mat[1][y] = yVal;
	mat[2][z] = zVal;

	return mat;
}

Matrix3 Matrix3::Scale(const Vector& vec)
{
	Matrix3 mat{1.0f};

	mat[0][x] = vec[x];
	mat[1][y] = vec[y];
	mat[2][z] = vec[z];

	return mat;
}

void Matrix3::SetScale(F32 xVal, F32 yVal)
{
	MakeIdentity();

	_columns[0][x] = xVal;
	_columns[1][y] = yVal;
}

void Matrix3::SetScale(F32 xVal, F32 yVal, F32 zVal)
{
	MakeIdentity();

	_columns[0][x] = xVal;
	_columns[1][y] = yVal;
	_columns[2][z] = zVal;
}

void Matrix3::SetScale(const Vector& vec)
{
	MakeIdentity();

	_columns[0][x] = vec[x];
	_columns[1][y] = vec[y];
	
	if(!vec.Is2D()) 
	{
		_columns[2][z] = vec[z];
	}
}

void Matrix3::AddScale(F32 xVal, F32 yVal)
{
	_columns[0][x] += xVal;
	_columns[1][y] += yVal;
}

void Matrix3::AddScale(F32 xVal, F32 yVal, F32 zVal)
{
	_columns[0][x] += xVal;
	_columns[1][y] += yVal;
	_columns[2][z] += zVal;
}

void Matrix3::AddScale(const Vector& vec)
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
Matrix3 Matrix3::RotateX(F32 val)
{
	val = RADIAN(val);
	Matrix3 mat{1.0f};

	mat[1][y] = cos(val);
	mat[1][z] = -sin(val);
	mat[2][y] = sin(val);
	mat[2][z] = cos(val);

	return mat;
}

Matrix3 Matrix3::RotateY(F32 val)
{
	val = RADIAN(val);
	Matrix3 mat{1.0f};

	mat[0][x] = cos(val);
	mat[0][z] = sin(val);
	mat[2][x] = -sin(val);
	mat[2][z] = cos(val);

	return mat;
}

Matrix3 Matrix3::RotateZ(F32 val)
{
	val = RADIAN(val);
	Matrix3 mat{1.0f};

	mat[0][x] = cos(val);
	mat[0][y] = -sin(val);
	mat[1][x] = sin(val);
	mat[1][y] = cos(val);

	return mat;
}

void Matrix3::SetRotateX(F32 val)
{
	val = RADIAN(val);

	MakeIdentity();

	_columns[1][y] = cos(val);
	_columns[1][z] = -sin(val);
	_columns[2][y] = sin(val);
	_columns[2][z] = cos(val);
}

void Matrix3::AddRotateX(F32 val)
{
	val = RADIAN(val);

	_columns[1][y] += cos(val);
	_columns[1][z] += -sin(val);
	_columns[2][y] += sin(val);
	_columns[2][z] += cos(val);
}

void Matrix3::SetRotateY(F32 val)
{
	val = RADIAN(val);

	MakeIdentity();

	_columns[0][x] = cos(val);
	_columns[0][z] = sin(val);
	_columns[2][x] = -sin(val);
	_columns[2][z] = cos(val);
}

void Matrix3::AddRotateY(F32 val)
{
	val = RADIAN(val);

	_columns[0][x] += cos(val);
	_columns[0][y] += sin(val);
	_columns[2][x] += -sin(val);
	_columns[2][y] += cos(val);	
}

void Matrix3::SetRotateZ(F32 val)
{
	val = RADIAN(val);

	MakeIdentity();

	_columns[0][x] = cos(val);
	_columns[0][y] = -sin(val);
	_columns[1][x] = sin(val);
	_columns[1][y] = cos(val);
}

void Matrix3::AddRotateZ(F32 val)
{
	val = RADIAN(val);

	_columns[0][x] += cos(val);
	_columns[0][y] += -sin(val);
	_columns[1][x] += sin(val);
	_columns[1][y] += cos(val);
}

void Matrix3::SetRotate(F32 xVal, F32 yVal, F32 zVal)
{
	xVal = RADIAN(xVal);
	yVal = RADIAN(yVal);
	zVal = RADIAN(zVal);

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

void Matrix3::AddRotation(F32 xVal, F32 yVal, F32 zVal)
{
	xVal = RADIAN(xVal);
	yVal = RADIAN(yVal);
	zVal = RADIAN(zVal);

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

void Matrix3::SetOrientation(const Quaternion& q)
{
	F32 q_w = q[0];
	F32 q_x = q[1];
	F32 q_y = q[2];
	F32 q_z = q[3];

	_columns[0][x] = 1.0f - (2.0f * q_y * q_y + q_z * q_z);
	_columns[0][y] = 2.0f * q_x * q_y - 2.0f * q_z * q_w;
	_columns[0][z] = 2.0f * q_x * q_z + 2.0f * q_y * q_w;

	_columns[1][x] = 2.0f * q_w * q_y + 2.0f * q_z * q_w;
	_columns[1][y] = 1.0f - (2.0f * q_x * q_x + 2.0f * q_z * q_z);
	_columns[1][z] = 2.0f * q_y * q_z - 2.0f * q_x * q_w;

	_columns[2][x] = 2.0f * q_x * q_z - 2.0f * q_y * q_w;
	_columns[2][y] = 2.0f * q_y * q_z + 2.0f * q_x * q_w;
	_columns[2][z] = 1 - (2.0f * q_x * q_x + 2.0f * q_y * q_y);
}

void Matrix3::SetOrientationAndPosition(const Quaternion& q, const Vector& v)
{
	SetOrientation(q);
	
	_columns[3][x] = v[x];
	_columns[3][y] = v[y];
	_columns[3][z] = v[z];
}

//==========================================================================================================================
//Inverse
//==========================================================================================================================

void Matrix3::SetInverse(void)
{
	
}

void Matrix3::SetAsInverse(const Matrix3& mat)
{
	*this = mat;
	SetInverse();
}

Matrix3 Matrix3::GetInverse(void) const
{
	Matrix3 ret = *this;

	ret.SetInverse();

	return ret;
}

F32 Matrix3::Determinate(void) const
{
	//Implement later
	return 1.0f;
}

F32 Matrix3::Determinate3x3(Vector& col1, Vector& col2, Vector& col3)
{
	//Implement later
	return 1.0f;
}

//==========================================================================================================================
//Resettings
//==========================================================================================================================
void Matrix3::Reset(F32 val)
{
	//Reset Matrix3
	_columns[0] = Column3(val, 0.0f, 0.0f);
	_columns[1] = Column3(0.0f, val, 0.0f);
	_columns[2] = Column3(0.0f, 0.0f, val);
}

//==========================================================================================================================
//Misc
//==========================================================================================================================
void Matrix3::Transpose(void)
{
	Column3 newCol0 {_columns[0][x], _columns[1][x], _columns[2][x]};
	Column3 newCol1 {_columns[0][y], _columns[1][y], _columns[2][y]};
	Column3 newCol2 {_columns[0][z], _columns[1][z], _columns[2][z]};

	_columns[0] = newCol0;
	_columns[1] = newCol1;
	_columns[2] = newCol2;
}

void Matrix3::ComponentMulti(const Matrix3& mat)
{
	_columns[0][x] *= mat[0][x];
	_columns[0][y] *= mat[0][y];
	_columns[0][z] *= mat[0][z];

	_columns[1][x] *= mat[1][x];
	_columns[1][y] *= mat[1][y];
	_columns[1][z] *= mat[1][z];

	_columns[2][x] *= mat[2][x];
	_columns[2][y] *= mat[2][y];
	_columns[2][z] *= mat[2][z];
}

Matrix3 Matrix3::Transform(const Matrix3& mat) const
{
	Column3 xCol 
	{
		_columns[0][x] * mat[0][x] + _columns[1][x] * mat[0][y] + _columns[2][x] * mat[0][z],
		_columns[0][y] * mat[0][x] + _columns[1][y] * mat[0][y] + _columns[2][y] * mat[0][z],
		_columns[0][z] * mat[0][x] + _columns[1][z] * mat[0][y] + _columns[2][z] * mat[0][z]
	};

	Column3 yCol
	{
		_columns[0][x] * mat[1][x] + _columns[1][x] * mat[1][y] + _columns[2][x] * mat[1][z],
		_columns[0][y] * mat[1][x] + _columns[1][y] * mat[1][y] + _columns[2][y] * mat[1][z],
		_columns[0][z] * mat[1][x] + _columns[1][z] * mat[1][y] + _columns[2][z] * mat[1][z]
	};

	Column3 zCol
	{
		_columns[0][x] * mat[2][x] + _columns[1][x] * mat[2][y] + _columns[2][x] * mat[2][z],
		_columns[0][y] * mat[2][x] + _columns[1][y] * mat[2][y] + _columns[2][y] * mat[2][z],
		_columns[0][z] * mat[2][x] + _columns[1][z] * mat[2][y] + _columns[2][z] * mat[2][z]
	};

	return Matrix3(xCol, yCol, zCol);
}

Vector Matrix3::Transform(const Vector& vec) const
{
	return Vector( _columns[0][x] * vec[x] + _columns[1][x] * vec[y] + _columns[2][x] * vec[z],
				   _columns[0][y] * vec[x] + _columns[1][y] * vec[y] + _columns[2][y] * vec[z],
				   _columns[0][z] * vec[x] + _columns[1][z] + vec[y] + _columns[2][z] * vec[z] );
}

//==========================================================================================================================
//
//Operator Overloads
//
//==========================================================================================================================
Matrix3& Matrix3::operator=(const Matrix3& mat) 
{
	_columns[0][x] = mat[0][x];
	_columns[0][y] = mat[0][y];
	_columns[0][z] = mat[0][z];

	_columns[1][x] = mat[1][x];
	_columns[1][y] = mat[1][y];
	_columns[1][z] = mat[1][z];

	_columns[2][x] = mat[2][x];
	_columns[2][y] = mat[2][y];
	_columns[2][z] = mat[2][z];

	return *this;
}

Matrix3 Matrix3::operator*(const Matrix3& mat) const
{
	Column3 xCol 
	{
		_columns[0][x] * mat[0][x] + _columns[1][x] * mat[0][y] + _columns[2][x] * mat[0][z],
		_columns[0][y] * mat[0][x] + _columns[1][y] * mat[0][y] + _columns[2][y] * mat[0][z],
		_columns[0][z] * mat[0][x] + _columns[1][z] * mat[0][y] + _columns[2][z] * mat[0][z] 

	};

	Column3 yCol
	{
		_columns[0][x] * mat[1][x] + _columns[1][x] * mat[1][y] + _columns[2][x] * mat[1][z],
		_columns[0][y] * mat[1][x] + _columns[1][y] * mat[1][y] + _columns[2][y] * mat[1][z],
		_columns[0][z] * mat[1][x] + _columns[1][z] * mat[1][y] + _columns[2][z] * mat[1][z]
	};

	Column3 zCol
	{
		_columns[0][x] * mat[2][x] + _columns[1][x] * mat[2][y] + _columns[2][x] * mat[2][z],
		_columns[0][y] * mat[2][x] + _columns[1][y] * mat[2][y] + _columns[2][y] * mat[2][z],
		_columns[0][z] * mat[2][x] + _columns[1][z] * mat[2][y] + _columns[2][z] * mat[2][z]
	};


	return Matrix3(xCol, yCol, zCol);
}

Vector Matrix3::operator*(const Vector& vec) const
{
	return Vector( _columns[0][x] * vec[x] + _columns[1][x] * vec[y] + _columns[2][x] * vec[z],
				   _columns[0][y] * vec[x] + _columns[1][y] * vec[y] + _columns[2][y] * vec[z],
				   _columns[0][z] * vec[x] + _columns[1][z] + vec[y] + _columns[2][z] * vec[z] );
}

Matrix3& Matrix3::operator/=(F32 val)
{
	_columns[x][x] /= val;
	_columns[x][y] /= val;
	_columns[x][z] /= val;
	
	_columns[y][x] /= val;
	_columns[y][y] /= val;
	_columns[y][z] /= val;

	_columns[z][x] /= val;
	_columns[z][y] /= val;
	_columns[z][z] /= val;

	return *this;
}