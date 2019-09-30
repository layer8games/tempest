#include <Engine/Matrix3.h>

using namespace KillerMath;

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Matrix3::Matrix3(void)
:
_data{ Vector3(1.0f, 0.0f, 0.0f),
	   Vector3(0.0f, 1.0f, 0.0f),
	   Vector3(0.0f, 0.0f, 1.0f) }
{  }

Matrix3::Matrix3(const Vector3& x, const Vector3& y, const Vector3& z)
:
_data{x, y, z}
{  }

Matrix3::Matrix3(const Vector4& x, const Vector4& y, const Vector4& z)
:
_data{Vector3(x), Vector3(y), Vector3(z)}
{  }


Matrix3::Matrix3(const F32 val)
:
_data{ Vector3(val, 0.0f, 0.0f),
	   Vector3(0.0f, val, 0.0f),
 	   Vector3(0.0f, 0.0f, val) }
{  }

Matrix3::Matrix3( F32 m00, F32 m01, F32 m02,
				  F32 m10, F32 m11, F32 m12,
				  F32 m20, F32 m21, F32 m22 )
:
_data{Vector3(m00, m01, m02),
	  Vector3(m10, m11, m12),
	  Vector3(m20, m21, m22) }
{  }

Matrix3::Matrix3(const Matrix3& M)
:
_data{M[0], M[1], M[2]}
{  }

//==========================================================================================================================
//
//Matrix3 functions
//
//==========================================================================================================================
const std::vector<F32> Matrix3::GetElems(void) const
{
	std::vector<F32> elems;
	
	elems.push_back(_data[0][x]);
	elems.push_back(_data[0][y]);
	elems.push_back(_data[0][z]);
	elems.push_back(_data[1][x]);
	elems.push_back(_data[1][y]);
	elems.push_back(_data[1][z]);
	elems.push_back(_data[2][x]);
	elems.push_back(_data[2][y]);
	elems.push_back(_data[2][z]);

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

Matrix3 Matrix3::Scale(const Vector3& vec)
{
	Matrix3 mat{1.0f};

	mat[0][x] = vec[x];
	mat[1][y] = vec[y];
	mat[2][z] = vec[z];

	return mat;
}

Matrix3 Matrix3::Scale(const Vector4& vec)
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

	_data[0][x] = xVal;
	_data[1][y] = yVal;
}

void Matrix3::SetScale(F32 xVal, F32 yVal, F32 zVal)
{
	MakeIdentity();

	_data[0][x] = xVal;
	_data[1][y] = yVal;
	_data[2][z] = zVal;
}

void Matrix3::SetScale(const Vector3& vec)
{
	MakeIdentity();

	_data[0][x] = vec[x];
	_data[1][y] = vec[y];
	
	if(!vec.Is2D()) 
	{
		_data[2][z] = vec[z];
	}
}

void Matrix3::SetScale(const Vector4& vec)
{
	MakeIdentity();

	_data[0][x] = vec[x];
	_data[1][y] = vec[y];
	
	if(!vec.Is2D()) 
	{
		_data[2][z] = vec[z];
	}
}

void Matrix3::AddScale(F32 xVal, F32 yVal)
{
	_data[0][x] += xVal;
	_data[1][y] += yVal;
}

void Matrix3::AddScale(F32 xVal, F32 yVal, F32 zVal)
{
	_data[0][x] += xVal;
	_data[1][y] += yVal;
	_data[2][z] += zVal;
}

void Matrix3::AddScale(const Vector3& vec)
{
	_data[0][x] += vec[x];
	_data[1][y] += vec[y];
	
	if(!vec.Is2D()) 
	{
		_data[2][z] += vec[z];
	}
}

void Matrix3::AddScale(const Vector4& vec)
{
	_data[0][x] += vec[x];
	_data[1][y] += vec[y];
	
	if(!vec.Is2D()) 
	{
		_data[2][z] += vec[z];
	}
}

//==========================================================================================================================
//Rotations
//==========================================================================================================================
Matrix3 Matrix3::RotateX(F32 val)
{
	val = RADIAN(val);
	Matrix3 mat{1.0f};

	mat[1][y] = static_cast<F32>(cos(val));
	mat[1][z] = static_cast<F32>(-sin(val));
	mat[2][y] = static_cast<F32>(sin(val));
	mat[2][z] = static_cast<F32>(cos(val));

	return mat;
}

Matrix3 Matrix3::RotateY(F32 val)
{
	val = RADIAN(val);
	Matrix3 mat{1.0f};

	mat[0][x] = static_cast<F32>(cos(val));
	mat[0][z] = static_cast<F32>(sin(val));
	mat[2][x] = static_cast<F32>(-sin(val));
	mat[2][z] = static_cast<F32>(cos(val));

	return mat;
}

Matrix3 Matrix3::RotateZ(F32 val)
{
	val = RADIAN(val);
	Matrix3 mat{1.0f};

	mat[0][x] = static_cast<F32>(cos(val));
	mat[0][y] = static_cast<F32>(-sin(val));
	mat[1][x] = static_cast<F32>(sin(val));
	mat[1][y] = static_cast<F32>(cos(val));

	return mat;
}

void Matrix3::SetRotateX(F32 val)
{
	val = RADIAN(val);

	MakeIdentity();

	_data[1][y] = static_cast<F32>(cos(val));
	_data[1][z] = static_cast<F32>(-sin(val));
	_data[2][y] = static_cast<F32>(sin(val));
	_data[2][z] = static_cast<F32>(cos(val));
}

void Matrix3::AddRotateX(F32 val)
{
	val = RADIAN(val);

	_data[1][y] += static_cast<F32>(cos(val));
	_data[1][z] += static_cast<F32>(-sin(val));
	_data[2][y] += static_cast<F32>(sin(val));
	_data[2][z] += static_cast<F32>(cos(val));
}

void Matrix3::SetRotateY(F32 val)
{
	val = RADIAN(val);

	MakeIdentity();

	_data[0][x] = static_cast<F32>(cos(val));
	_data[0][z] = static_cast<F32>(sin(val));
	_data[2][x] = static_cast<F32>(-sin(val));
	_data[2][z] = static_cast<F32>(cos(val));
}

void Matrix3::AddRotateY(F32 val)
{
	val = RADIAN(val);

	_data[0][x] += static_cast<F32>(cos(val));
	_data[0][y] += static_cast<F32>(sin(val));
	_data[2][x] += static_cast<F32>(-sin(val));
	_data[2][y] += static_cast<F32>(cos(val));
}

void Matrix3::SetRotateZ(F32 val)
{
	val = RADIAN(val);

	MakeIdentity();

	_data[0][x] = static_cast<F32>(cos(val));
	_data[0][y] = static_cast<F32>(-sin(val));
	_data[1][x] = static_cast<F32>(sin(val));
	_data[1][y] = static_cast<F32>(cos(val));
}

void Matrix3::AddRotateZ(F32 val)
{
	val = RADIAN(val);

	_data[0][x] += static_cast<F32>(cos(val));
	_data[0][y] += static_cast<F32>(-sin(val));
	_data[1][x] += static_cast<F32>(sin(val));
	_data[1][y] += static_cast<F32>(cos(val));
}

void Matrix3::SetRotate(F32 xVal, F32 yVal, F32 zVal)
{
	xVal = RADIAN(xVal);
	yVal = RADIAN(yVal);
	zVal = RADIAN(zVal);

	MakeIdentity();

	_data[0][x] = static_cast<F32>(cos(yVal) * cos(zVal));
	_data[0][y] = static_cast<F32>(-cos(yVal) * sin(zVal));
	_data[0][z] = static_cast<F32>(sin(yVal));
	_data[1][x] = static_cast<F32>(cos(xVal) * sin(zVal) + sin(xVal) * sin(yVal) * cos(zVal));
	_data[1][y] = static_cast<F32>(cos(xVal) * cos(zVal) - sin(xVal) * sin(yVal) * sin(zVal));
	_data[1][z] = static_cast<F32>(-sin(xVal) * cos(yVal));
	_data[2][x] = static_cast<F32>(sin(xVal) * sin(zVal) - cos(xVal) * sin(yVal) * cos(zVal));
	_data[2][y] = static_cast<F32>(sin(xVal) * cos(zVal) + cos(xVal) * sin(yVal) * sin(zVal));
	_data[2][z] = static_cast<F32>(cos(xVal) * cos(yVal));
}

void Matrix3::AddRotation(F32 xVal, F32 yVal, F32 zVal)
{
	xVal = RADIAN(xVal);
	yVal = RADIAN(yVal);
	zVal = RADIAN(zVal);

	_data[0][x] += static_cast<F32>(cos(yVal) * cos(zVal));
	_data[0][y] += static_cast<F32>(-cos(yVal) * sin(zVal));
	_data[0][z] += static_cast<F32>(sin(yVal));
	_data[1][x] += static_cast<F32>(cos(xVal) * sin(zVal) + sin(xVal) * sin(yVal) * cos(zVal));
	_data[1][y] += static_cast<F32>(cos(xVal) * cos(zVal) - sin(xVal) * sin(yVal) * sin(zVal));
	_data[1][z] += static_cast<F32>(-sin(xVal) * cos(yVal));
	_data[2][x] += static_cast<F32>(sin(xVal) * sin(zVal) - cos(xVal) * sin(yVal) * cos(zVal));
	_data[2][y] += static_cast<F32>(sin(xVal) * cos(zVal) + cos(xVal) * sin(yVal) * sin(zVal));
	_data[2][z] += static_cast<F32>(cos(xVal) * cos(yVal));
}

void Matrix3::SetOrientation(const Quaternion& q)
{
	F32 q_w = q[0];
	F32 q_x = q[1];
	F32 q_y = q[2];
	F32 q_z = q[3];

	_data[0][x] = 1.0f - (2.0f * q_y * q_y + q_z * q_z);
	_data[0][y] = 2.0f * q_x * q_y - 2.0f * q_z * q_w;
	_data[0][z] = 2.0f * q_x * q_z + 2.0f * q_y * q_w;

	_data[1][x] = 2.0f * q_w * q_y + 2.0f * q_z * q_w;
	_data[1][y] = 1.0f - (2.0f * q_x * q_x + 2.0f * q_z * q_z);
	_data[1][z] = 2.0f * q_y * q_z - 2.0f * q_x * q_w;

	_data[2][x] = 2.0f * q_x * q_z - 2.0f * q_y * q_w;
	_data[2][y] = 2.0f * q_y * q_z + 2.0f * q_x * q_w;
	_data[2][z] = 1 - (2.0f * q_x * q_x + 2.0f * q_y * q_y);
}

//==========================================================================================================================
//Inverse
//==========================================================================================================================
void Matrix3::SetInverse(void)
{
	F32 det = Determinate();

	if(det == 0.0f) return;

	// Find the minors based on the cofactors
	F32 c0x = _Cofactor(_data[1][y], _data[1][z], _data[2][y], _data[2][z]);

	F32 c0y = _Cofactor(_data[1][x], _data[1][z], _data[2][x], _data[2][z]);

	F32 c0z = _Cofactor(_data[1][x], _data[1][y], _data[2][x], _data[2][y]);

	Vector3 colx {c0x, -c0y, c0z};

	F32 c1x = _Cofactor(_data[0][y], _data[0][z], _data[2][y], _data[2][z]);

	F32 c1y = _Cofactor(_data[0][x], _data[0][z], _data[2][x], _data[2][z]);

	F32 c1z = _Cofactor(_data[0][x], _data[0][y], _data[2][x], _data[2][y]);

	Vector3 coly {-c1x, c1y, -c1z};

	F32 c2x = _Cofactor(_data[0][y], _data[0][z], _data[1][y], _data[1][z]);

	F32 c2y = _Cofactor(_data[0][x], _data[0][z], _data[1][x], _data[1][z]);

	F32 c2z = _Cofactor(_data[0][x], _data[0][y], _data[1][x], _data[1][y]);

	Vector3 colz {c2x, -c2y, c2z};

	//Create the new Matrix
	Matrix3 adj {colx, coly, colz};

	//Transpose and divide.
	adj.Transpose();	

	adj	/= det;

	*this = adj;
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
	return _data[0][x] * (_data[1][y] * _data[2][z] - _data[2][y] * _data[1][z])
		 + _data[1][x] * (_data[2][y] * _data[0][z] - _data[0][y] * _data[2][z])
		 + _data[2][x] * (_data[0][y] * _data[1][z] - _data[1][y] * _data[0][z]);
}

//==========================================================================================================================
//Resettings
//==========================================================================================================================
void Matrix3::Reset(F32 val)
{
	//Reset Matrix3
	_data[0] = Vector3(val, 0.0f, 0.0f);
	_data[1] = Vector3(0.0f, val, 0.0f);
	_data[2] = Vector3(0.0f, 0.0f, val);
}

//==========================================================================================================================
//Misc
//==========================================================================================================================
void Matrix3::Transpose(void)
{
	Vector3 newCol0 {_data[0][x], _data[1][x], _data[2][x]};
	Vector3 newCol1 {_data[0][y], _data[1][y], _data[2][y]};
	Vector3 newCol2 {_data[0][z], _data[1][z], _data[2][z]};

	_data[0] = newCol0;
	_data[1] = newCol1;
	_data[2] = newCol2;
}

void Matrix3::ComponentMulti(const Matrix3& mat)
{
	_data[0][x] *= mat[0][x];
	_data[0][y] *= mat[0][y];
	_data[0][z] *= mat[0][z];

	_data[1][x] *= mat[1][x];
	_data[1][y] *= mat[1][y];
	_data[1][z] *= mat[1][z];

	_data[2][x] *= mat[2][x];
	_data[2][y] *= mat[2][y];
	_data[2][z] *= mat[2][z];
}

Matrix3 Matrix3::Transform(const Matrix3& mat) const
{
	Vector3 xCol 
	{
		_data[0][x] * mat[0][x] + _data[1][x] * mat[0][y] + _data[2][x] * mat[0][z],
		_data[0][y] * mat[0][x] + _data[1][y] * mat[0][y] + _data[2][y] * mat[0][z],
		_data[0][z] * mat[0][x] + _data[1][z] * mat[0][y] + _data[2][z] * mat[0][z]
	};

	Vector3 yCol
	{
		_data[0][x] * mat[1][x] + _data[1][x] * mat[1][y] + _data[2][x] * mat[1][z],
		_data[0][y] * mat[1][x] + _data[1][y] * mat[1][y] + _data[2][y] * mat[1][z],
		_data[0][z] * mat[1][x] + _data[1][z] * mat[1][y] + _data[2][z] * mat[1][z]
	};

	Vector3 zCol
	{
		_data[0][x] * mat[2][x] + _data[1][x] * mat[2][y] + _data[2][x] * mat[2][z],
		_data[0][y] * mat[2][x] + _data[1][y] * mat[2][y] + _data[2][y] * mat[2][z],
		_data[0][z] * mat[2][x] + _data[1][z] * mat[2][y] + _data[2][z] * mat[2][z]
	};

	return Matrix3(xCol, yCol, zCol);
}

Vector4 Matrix3::Transform(const Vector4& vec) const
{
	return Vector4( _data[0][x] * vec[x] + _data[1][x] * vec[y] + _data[2][x] * vec[z],
				   _data[0][y] * vec[x] + _data[1][y] * vec[y] + _data[2][y] * vec[z],
				   _data[0][z] * vec[x] + _data[1][z] + vec[y] + _data[2][z] * vec[z] );
}

//==========================================================================================================================
//
//Operator Overloads
//
//==========================================================================================================================
Matrix3& Matrix3::operator=(const Matrix3& mat) 
{
	_data[0][x] = mat[0][x];
	_data[0][y] = mat[0][y];
	_data[0][z] = mat[0][z];

	_data[1][x] = mat[1][x];
	_data[1][y] = mat[1][y];
	_data[1][z] = mat[1][z];

	_data[2][x] = mat[2][x];
	_data[2][y] = mat[2][y];
	_data[2][z] = mat[2][z];

	return *this;
}

Matrix3 Matrix3::operator*(const Matrix3& mat) const
{
	Vector3 xCol 
	{
		_data[0][x] * mat[0][x] + _data[1][x] * mat[0][y] + _data[2][x] * mat[0][z],
		_data[0][y] * mat[0][x] + _data[1][y] * mat[0][y] + _data[2][y] * mat[0][z],
		_data[0][z] * mat[0][x] + _data[1][z] * mat[0][y] + _data[2][z] * mat[0][z] 

	};

	Vector3 yCol
	{
		_data[0][x] * mat[1][x] + _data[1][x] * mat[1][y] + _data[2][x] * mat[1][z],
		_data[0][y] * mat[1][x] + _data[1][y] * mat[1][y] + _data[2][y] * mat[1][z],
		_data[0][z] * mat[1][x] + _data[1][z] * mat[1][y] + _data[2][z] * mat[1][z]
	};

	Vector3 zCol
	{
		_data[0][x] * mat[2][x] + _data[1][x] * mat[2][y] + _data[2][x] * mat[2][z],
		_data[0][y] * mat[2][x] + _data[1][y] * mat[2][y] + _data[2][y] * mat[2][z],
		_data[0][z] * mat[2][x] + _data[1][z] * mat[2][y] + _data[2][z] * mat[2][z]
	};


	return Matrix3(xCol, yCol, zCol);
}

Vector4 Matrix3::operator*(const Vector4& vec) const
{
	return Vector4( _data[0][x] * vec[x] + _data[1][x] * vec[y] + _data[2][x] * vec[z],
				    _data[0][y] * vec[x] + _data[1][y] * vec[y] + _data[2][y] * vec[z],
				    _data[0][z] * vec[x] + _data[1][z] + vec[y] + _data[2][z] * vec[z] );
}

Matrix3& Matrix3::operator/=(F32 val)
{
	_data[x][x] /= val;
	_data[x][y] /= val;
	_data[x][z] /= val;
	
	_data[y][x] /= val;
	_data[y][y] /= val;
	_data[y][z] /= val;

	_data[z][x] /= val;
	_data[z][y] /= val;
	_data[z][z] /= val;

	return *this;
}

F32 Matrix3::_Cofactor(F32 c00, F32 c01, F32 c10, F32 c11) const
{
	return c00 * c11 - c10 * c01;
}