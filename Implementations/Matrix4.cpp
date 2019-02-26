#include <Engine/Matrix4.h>

using namespace KillerMath;

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Matrix4::Matrix4(void)
:
_data{Vector4(1.0f, 0.0f, 0.0f, 0.0f),
	  Vector4(0.0f, 1.0f, 0.0f, 0.0f),
	  Vector4(0.0f, 0.0f, 1.0f, 0.0f),
	  Vector4(0.0f, 0.0f, 0.0f, 1.0f)}
{  }

Matrix4::Matrix4(const Vector4& x, const Vector4& y, const Vector4& z)
:
_data{x, y, z, Vector4(0.0f, 0.0f, 0.0f, 1.0f)}
{  }

Matrix4::Matrix4(const Vector4& x, const Vector4& y, const Vector4& z, const Vector4& w)
:
_data{x, y, z, w}
{  }

Matrix4::Matrix4(const F32 val)
:
_data{Vector4(val, 0.0f, 0.0f, 0.0f),
	  Vector4(0.0f, val, 0.0f, 0.0f),
	  Vector4(0.0f, 0.0f, val, 0.0f),
	  Vector4(0.0f, 0.0f, 0.0f, 1.0f)}
{  }

Matrix4::Matrix4( F32 m00, F32 m01, F32 m02, F32 m03,
				  F32 m10, F32 m11, F32 m12, F32 m13,
				  F32 m20, F32 m21, F32 m22, F32 m23,
				  F32 m30, F32 m31, F32 m32, F32 m33)
:
_data{Vector4(m00, m01, m02, m03),
	  Vector4(m10, m11, m12, m13),
	  Vector4(m20, m21, m22, m23),
      Vector4(m30, m31, m32, m33)}
{  }

Matrix4::Matrix4(const Matrix4& M)
:
_data{M[0], M[1], M[2], M[3]}
{  }

//==========================================================================================================================
//
//Matrix4 functions
//
//==========================================================================================================================
const std::vector<F32> Matrix4::GetElems(void) const
{
	std::vector<F32> elems;
	
	elems.push_back(_data[0][x]);
	elems.push_back(_data[0][y]);
	elems.push_back(_data[0][z]);
	elems.push_back(_data[0][w]);
	elems.push_back(_data[1][x]);
	elems.push_back(_data[1][y]);
	elems.push_back(_data[1][z]);
	elems.push_back(_data[1][w]);
	elems.push_back(_data[2][x]);
	elems.push_back(_data[2][y]);
	elems.push_back(_data[2][z]);
	elems.push_back(_data[2][w]);
	elems.push_back(_data[3][x]);
	elems.push_back(_data[3][y]);
	elems.push_back(_data[3][z]);
	elems.push_back(_data[3][w]);

	return elems;
}

//==========================================================================================================================
//Projections
//==========================================================================================================================
void Matrix4::MakeOrthographic(F32 left, F32 right, F32 bottom, F32 top, F32 nearPlane, F32 farPlane)
{
	//Reset Matrix4
	MakeIdentity();

	assert(right - left != 0.0f);
	assert(top - bottom != 0.0f);
	assert(farPlane - nearPlane != 0.0f);

	//Diagnal
	_data[0][x] = 2.0f / (right - left);
	_data[1][y] = 2.0f / (top - bottom);
	_data[2][z] = -2.0f / (farPlane - nearPlane);
	_data[3][w] = 1.0f;

	//Transform "Vector4"
	_data[3][x] = -(right + left) / (right - left);
	_data[3][y] = -(top + bottom) / (top - bottom);
	_data[3][z] = -(farPlane + nearPlane) / (farPlane - nearPlane);
}

void Matrix4::MakePerspective(F32 fieldOfView, F32 aspectRatio, F32 nearPlane, F32 farPlane)
{
	assert(nearPlane - farPlane != 0.0f);

	F32 S = 1.0f / tan(RADIAN(0.5f * fieldOfView));

	//Reset Matrix4 
	MakeIdentity();

	_data[0][x] = S / aspectRatio;
	_data[1][y] = S;
	_data[2][z] = (nearPlane + farPlane) / (nearPlane - farPlane);
	_data[2][w] = -1.0f;
	_data[3][z] = (2.0f * nearPlane * farPlane) / (nearPlane - farPlane);
}

//==========================================================================================================================
//Translations
//==========================================================================================================================
Matrix4 Matrix4::Translate(F32 xVal, F32 yVal)
{
	Matrix4 mat{1.0f};

	mat[3][x] = xVal;
	mat[3][y] = yVal;

	return mat;
}

Matrix4 Matrix4::Translate(F32 xVal, F32 yVal, F32 zVal)
{
	Matrix4 mat{1.0f};

	mat[3][x] = xVal;
	mat[3][y] = yVal;
	mat[3][z] = zVal;

	return mat;	
}

Matrix4 Matrix4::Translate(const Vector4& vec)
{
	Matrix4 mat{1.0f};

	mat[3][x] = vec[x];
	mat[3][y] = vec[y];
	mat[3][z] = vec[z];

	return mat;	
}

void Matrix4::SetTranslate(F32 xVal, F32 yVal)
{
	MakeIdentity();

	_data[3][x] = xVal;
	_data[3][y] = yVal;
}

void Matrix4::SetTranslate(F32 xVal, F32 yVal, F32 zVal)
{
	MakeIdentity();			

	_data[3][x] = xVal;
	_data[3][y] = yVal;
	_data[3][z] = zVal;
}

void Matrix4::SetTranslate(const Vector4& vec)
{
	MakeIdentity(); 

	_data[3][x] = vec[x];
	_data[3][y] = vec[y];

	if(!vec.Is2D())
	{
		_data[3][z] = vec[z];
	}
}

void Matrix4::AddTranslate(F32 xVal, F32 yVal)
{
	_data[3][x] += xVal;
	_data[3][y] += yVal;
}

void Matrix4::AddTranslate(F32 xVal, F32 yVal, F32 zVal)
{
	_data[3][x] += xVal; 
	_data[3][y] += yVal; 
	_data[3][z] += zVal;
}

void Matrix4::AddTranslate(const Vector4& vec)
{
	_data[3][x] += vec[x];
	_data[3][y] += vec[y];
	
	if(!vec.Is2D()) 
	{
		_data[3][z] += vec[z];
	}
}

Vector4 Matrix4::TransformInverse(const Vector4& vec) const
{
	Vector4 tmp = vec;

	tmp[x] -= _data[3][x];
	tmp[y] -= _data[3][y];
	tmp[z] -= _data[3][z];

	return Vector4
	{
		tmp[x] * _data[0][x] +
		tmp[y] * _data[0][y] + 
		tmp[z] * _data[0][z],

		tmp[x] * _data[1][x] + 
		tmp[y] * _data[1][y] + 
		tmp[z] * _data[1][z],

		tmp[x] * _data[2][x] +
		tmp[y] * _data[2][y] + 
		tmp[z] * _data[2][z]
	};
}

//==========================================================================================================================
//Scaling
//==========================================================================================================================
Matrix4 Matrix4::Scale(F32 xVal, F32 yVal)
{
	Matrix4 mat{1.0f};

	mat[0][x] = xVal;
	mat[1][y] = yVal;

	return mat;
}

Matrix4 Matrix4::Scale(F32 xVal, F32 yVal, F32 zVal)
{
	Matrix4 mat{1.0f};

	mat[0][x] = xVal;
	mat[1][y] = yVal;
	mat[2][z] = zVal;

	return mat;
}

Matrix4 Matrix4::Scale(const Vector4& vec)
{
	Matrix4 mat{1.0f};

	mat[0][x] = vec[x];
	mat[1][y] = vec[y];
	mat[2][z] = vec[z];

	return mat;
}

void Matrix4::SetScale(F32 xVal, F32 yVal)
{
	MakeIdentity();

	_data[0][x] = xVal;
	_data[1][y] = yVal;
}

void Matrix4::SetScale(F32 xVal, F32 yVal, F32 zVal)
{
	MakeIdentity();

	_data[0][x] = xVal;
	_data[1][y] = yVal;
	_data[2][z] = zVal;
}

void Matrix4::SetScale(const Vector4& vec)
{
	MakeIdentity();

	_data[0][x] = vec[x];
	_data[1][y] = vec[y];
	
	if(!vec.Is2D()) 
	{
		_data[2][z] = vec[z];
	}
}

void Matrix4::AddScale(F32 xVal, F32 yVal)
{
	_data[0][x] += xVal;
	_data[1][y] += yVal;
}

void Matrix4::AddScale(F32 xVal, F32 yVal, F32 zVal)
{
	_data[0][x] += xVal;
	_data[1][y] += yVal;
	_data[2][z] += zVal;
}

void Matrix4::AddScale(const Vector4& vec)
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
Matrix4 Matrix4::RotateX(F32 val)
{
	val = RADIAN(val);
	Matrix4 mat{1.0f};

	mat[1][y] = cos(val);
	mat[1][z] = -sin(val);
	mat[2][y] = sin(val);
	mat[2][z] = cos(val);

	return mat;
}

Matrix4 Matrix4::RotateY(F32 val)
{
	val = RADIAN(val);
	Matrix4 mat{1.0f};

	mat[0][x] = cos(val);
	mat[0][z] = sin(val);
	mat[2][x] = -sin(val);
	mat[2][z] = cos(val);

	return mat;
}

Matrix4 Matrix4::RotateZ(F32 val)
{
	val = RADIAN(val);
	Matrix4 mat{1.0f};

	mat[0][x] = cos(val);
	mat[0][y] = -sin(val);
	mat[1][x] = sin(val);
	mat[1][y] = cos(val);

	return mat;
}

void Matrix4::SetRotateX(F32 val)
{
	val = RADIAN(val);

	MakeIdentity();

	_data[1][y] = cos(val);
	_data[1][z] = -sin(val);
	_data[2][y] = sin(val);
	_data[2][z] = cos(val);
}

void Matrix4::AddRotateX(F32 val)
{
	val = RADIAN(val);

	_data[1][y] += cos(val);
	_data[1][z] += -sin(val);
	_data[2][y] += sin(val);
	_data[2][z] += cos(val);
}

void Matrix4::SetRotateY(F32 val)
{
	val = RADIAN(val);

	MakeIdentity();

	_data[0][x] = cos(val);
	_data[0][z] = sin(val);
	_data[2][x] = -sin(val);
	_data[2][z] = cos(val);
}

void Matrix4::AddRotateY(F32 val)
{
	val = RADIAN(val);

	_data[0][x] += cos(val);
	_data[0][y] += sin(val);
	_data[2][x] += -sin(val);
	_data[2][y] += cos(val);	
}

void Matrix4::SetRotateZ(F32 val)
{
	val = RADIAN(val);

	MakeIdentity();

	_data[0][x] = cos(val);
	_data[0][y] = -sin(val);
	_data[1][x] = sin(val);
	_data[1][y] = cos(val);
}

void Matrix4::AddRotateZ(F32 val)
{
	val = RADIAN(val);

	_data[0][x] += cos(val);
	_data[0][y] += -sin(val);
	_data[1][x] += sin(val);
	_data[1][y] += cos(val);
}

void Matrix4::SetRotate(F32 xVal, F32 yVal, F32 zVal)
{
	xVal = RADIAN(xVal);
	yVal = RADIAN(yVal);
	zVal = RADIAN(zVal);

	MakeIdentity();

	_data[0][x] = cos(yVal) * cos(zVal);
	_data[0][y] = -cos(yVal) * sin(zVal);
	_data[0][z] = sin(yVal);
	_data[1][x] = cos(xVal) * sin(zVal) + sin(xVal) * sin(yVal) * cos(zVal);
	_data[1][y] = cos(xVal) * cos(zVal) - sin(xVal) * sin(yVal) * sin(zVal);
	_data[1][z] = -sin(xVal) * cos(yVal);
	_data[2][x] = sin(xVal) * sin(zVal) - cos(xVal) * sin(yVal) * cos(zVal);
	_data[2][y] = sin(xVal) * cos(zVal) + cos(xVal) * sin(yVal) * sin(zVal);
	_data[2][z] = cos(xVal) * cos(yVal);
}

void Matrix4::AddRotation(F32 xVal, F32 yVal, F32 zVal)
{
	xVal = RADIAN(xVal);
	yVal = RADIAN(yVal);
	zVal = RADIAN(zVal);

	_data[0][x] += cos(yVal) * cos(zVal);
	_data[0][y] += -cos(yVal) * sin(zVal);
	_data[0][z] += sin(yVal);
	_data[1][x] += cos(xVal) * sin(zVal) + sin(xVal) * sin(yVal) * cos(zVal);
	_data[1][y] += cos(xVal) * cos(zVal) - sin(xVal) * sin(yVal) * sin(zVal);
	_data[1][z] += -sin(xVal) * cos(yVal);
	_data[2][x] += sin(xVal) * sin(zVal) - cos(xVal) * sin(yVal) * cos(zVal);
	_data[2][y] += sin(xVal) * cos(zVal) + cos(xVal) * sin(yVal) * sin(zVal);
	_data[2][z] += cos(xVal) * cos(yVal);
}

void Matrix4::SetOrientation(const Quaternion& q)
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

void Matrix4::SetOrientationAndPosition(const Quaternion& q, const Vector4& v)
{
	SetOrientation(q);
	
	_data[3][x] = v[x];
	_data[3][y] = v[y];
	_data[3][z] = v[z];
}

void Matrix4::SetOrientationAndPosition(const Quaternion& q, const Point& p)
{
	SetOrientation(q);
	
	_data[3][x] = p[x];
	_data[3][y] = p[y];
	_data[3][z] = p[z];
}

//==========================================================================================================================
//Inverse
//==========================================================================================================================

void Matrix4::SetInverse(void)
{
	F32 det = Determinate();

	if(det == 0.0f) return;

	F32 c00 = _Cofactor(Vector4(_data[y][y], _data[y][z], _data[y][w]),
						Vector4(_data[z][y], _data[z][z], _data[z][w]),
						Vector4(_data[w][y], _data[w][z], _data[w][w]));

	F32 c01 = _Cofactor(Vector4(_data[y][x], _data[y][z], _data[y][w]),
						Vector4(_data[z][x], _data[z][z], _data[z][w]),
						Vector4(_data[w][x], _data[w][z], _data[w][w]));

	F32 c02 = _Cofactor(Vector4(_data[y][x], _data[y][y], _data[y][w]),
						Vector4(_data[z][x], _data[z][y], _data[z][w]),
						Vector4(_data[w][x], _data[w][y], _data[w][w]));

	F32 c03 = _Cofactor(Vector4(_data[y][x], _data[y][y], _data[y][z]),
						Vector4(_data[z][x], _data[z][y], _data[z][z]),
						Vector4(_data[w][x], _data[w][y], _data[w][z]));

	Vector4 colx {c00, -c01, c02, -c03};

	F32 c10 = _Cofactor(Vector4(_data[x][y], _data[x][z], _data[x][w]),
						Vector4(_data[z][y], _data[z][z], _data[z][w]),
						Vector4(_data[w][y], _data[w][z], _data[w][w]));

	F32 c11 = _Cofactor(Vector4(_data[x][x], _data[x][z], _data[x][w]),
						Vector4(_data[z][x], _data[z][z], _data[z][w]),
						Vector4(_data[w][x], _data[w][z], _data[w][w]));

	F32 c12 = _Cofactor(Vector4(_data[x][x], _data[x][y], _data[x][w]),
						Vector4(_data[z][x], _data[z][y], _data[z][w]),
						Vector4(_data[w][x], _data[w][y], _data[w][w]));

	F32 c13 = _Cofactor(Vector4(_data[x][x], _data[x][y], _data[x][z]),
						Vector4(_data[z][x], _data[z][y], _data[z][z]),
						Vector4(_data[w][x], _data[w][y], _data[w][z]));

	Vector4 coly {-c10, c11, -c12, c13};

	F32 c20 = _Cofactor(Vector4(_data[x][y], _data[x][z], _data[x][w]),
						Vector4(_data[y][y], _data[y][z], _data[y][w]),
						Vector4(_data[w][y], _data[w][z], _data[w][w]));

	F32 c21 = _Cofactor(Vector4(_data[x][x], _data[x][z], _data[x][w]),
						Vector4(_data[y][x], _data[y][z], _data[y][w]),
						Vector4(_data[w][x], _data[w][z], _data[w][w]));

	F32 c22 = _Cofactor(Vector4(_data[x][x], _data[x][y], _data[x][w]),
						Vector4(_data[y][x], _data[y][y], _data[y][w]),
						Vector4(_data[w][x], _data[w][y], _data[w][w]));

	F32 c23 = _Cofactor(Vector4(_data[x][x], _data[x][y], _data[x][z]),
						Vector4(_data[y][x], _data[y][y], _data[y][z]),
						Vector4(_data[w][x], _data[w][y], _data[w][z]));

	Vector4 colz {c20, -c21, c22, -c23};

	F32 c30 = _Cofactor(Vector4(_data[x][y], _data[x][z], _data[x][w]),
						Vector4(_data[y][y], _data[y][z], _data[y][w]),
						Vector4(_data[z][y], _data[z][z], _data[z][w]));

	F32 c31 = _Cofactor(Vector4(_data[x][x], _data[x][z], _data[x][w]),
						Vector4(_data[y][x], _data[y][z], _data[y][w]),
						Vector4(_data[z][x], _data[z][z], _data[z][w]));

	F32 c32 = _Cofactor(Vector4(_data[x][x], _data[x][y], _data[x][w]),
						Vector4(_data[y][x], _data[y][y], _data[y][w]),
						Vector4(_data[z][x], _data[z][y], _data[z][w]));

	F32 c33 = _Cofactor(Vector4(_data[x][x], _data[x][y], _data[x][z]),
						Vector4(_data[y][x], _data[y][y], _data[y][z]),
						Vector4(_data[z][x], _data[z][y], _data[z][z]));

	Vector4 colw {-c30, c31, -c32, c33};

	Matrix4 adj { colx, coly, colz, colw };

	adj.Transpose();	

	adj	/= det;

	*this = adj;
}

void Matrix4::SetAsInverse(const Matrix4& mat)
{
	*this = mat;
	SetInverse();
}

Matrix4 Matrix4::GetInverse(void) const
{
	Matrix4 ret = *this;

	ret.SetInverse();

	return ret;
}

F32 Matrix4::Determinate(void) const
{
	//This equation is very difficult to understand. It was ultimately taking from 3d Math Primer, page 165, Determinate of 
	//4x4 Matrix4 in expanded form.
	//m11 through m41 represent the cofactors of those sections of the Matrix4, which are added together to get the value
	F32 m11 = _data[0][0] * ( _data[1][1] * (_data[2][2] * _data[3][3] - _data[3][2] * _data[2][3])
			   			    + _data[2][1] * (_data[3][2] * _data[1][3] - _data[1][2] * _data[3][3])
			   				+ _data[3][1] * (_data[1][2] * _data[2][3] - _data[2][2] * _data[1][3]) );

	F32 m21 = _data[1][0] * ( _data[0][1] * (_data[2][2] * _data[3][3] - _data[3][2] * _data[2][3])
		 		   			+ _data[2][1] * (_data[3][2] * _data[0][3] - _data[0][2] * _data[3][3])
		 		   			+ _data[3][1] * (_data[0][2] * _data[2][3] - _data[2][2] * _data[0][3]) );

	F32 m31 = _data[2][0] * ( _data[0][1] * (_data[1][2] * _data[3][3] - _data[3][2] * _data[1][3])
		 		   			+ _data[1][1] * (_data[3][2] * _data[0][3] - _data[0][2] * _data[3][3])
		 		   			+ _data[3][1] * (_data[0][2] * _data[1][3] - _data[1][2] * _data[0][3]) );

	F32 m41 = _data[3][0] * ( _data[0][1] * (_data[1][2] * _data[2][3] - _data[2][2] * _data[1][3])
		 		   			+ _data[1][1] * (_data[2][2] * _data[0][3] - _data[0][2] * _data[2][3])
		 		   			+ _data[2][1] * (_data[0][2] * _data[1][3] - _data[1][2] * _data[0][3]) );

	return m11 - m21 + m31 - m41;
}



//==========================================================================================================================
//Resettings
//==========================================================================================================================
void Matrix4::Reset(F32 val)
{
	//Reset Matrix4
	_data[0] = Vector4(val, 0.0f, 0.0f, 0.0f);
	_data[1] = Vector4(0.0f, val, 0.0f, 0.0f);
	_data[2] = Vector4(0.0f, 0.0f, val, 0.0f);
	_data[3] = Vector4(0.0f, 0.0f, 0.0f, val);
}

//==========================================================================================================================
//Misc
//==========================================================================================================================
void Matrix4::Transpose(void)
{
	Vector4 newCol0 {_data[0][x], _data[1][x], _data[2][x], _data[3][x]};
	Vector4 newCol1 {_data[0][y], _data[1][y], _data[2][y], _data[3][y]};
	Vector4 newCol2 {_data[0][z], _data[1][z], _data[2][z], _data[3][z]};
	Vector4 newCol3 {_data[0][w], _data[1][w], _data[2][w], _data[3][w]};

	_data[0] = newCol0;
	_data[1] = newCol1;
	_data[2] = newCol2;
	_data[3] = newCol3;
}

void Matrix4::ComponentMulti(const Matrix4& mat)
{
	_data[0][x] *= mat[0][x];
	_data[0][y] *= mat[0][y];
	_data[0][z] *= mat[0][z];
	_data[0][w] *= mat[0][w];

	_data[1][x] *= mat[1][x];
	_data[1][y] *= mat[1][y];
	_data[1][z] *= mat[1][z];
	_data[1][w] *= mat[1][w];

	_data[2][x] *= mat[2][x];
	_data[2][y] *= mat[2][y];
	_data[2][z] *= mat[2][z];
	_data[2][w] *= mat[2][w];

	_data[3][x] *= mat[3][x];
	_data[3][y] *= mat[3][y];
	_data[3][z] *= mat[3][z];
	_data[3][w] *= mat[3][w];
}

Matrix4 Matrix4::Transform3x3(const Matrix4& mat) const
{
	Vector4 xCol 
	{
		_data[0][x] * mat[0][x] + _data[1][x] * mat[0][y] + _data[2][x] * mat[0][z],
		_data[0][y] * mat[0][x] + _data[1][y] * mat[0][y] + _data[2][y] * mat[0][z],
		_data[0][z] * mat[0][x] + _data[1][z] * mat[0][y] + _data[2][z] * mat[0][z],
		0.0f
	};

	Vector4 yCol
	{
		_data[0][x] * mat[1][x] + _data[1][x] * mat[1][y] + _data[2][x] * mat[1][z],
		_data[0][y] * mat[1][x] + _data[1][y] * mat[1][y] + _data[2][y] * mat[1][z],
		_data[0][z] * mat[1][x] + _data[1][z] * mat[1][y] + _data[2][z] * mat[1][z],
		0.0f
	};

	Vector4 zCol
	{
		_data[0][x] * mat[2][x] + _data[1][x] * mat[2][y] + _data[2][x] * mat[2][z],
		_data[0][y] * mat[2][x] + _data[1][y] * mat[2][y] + _data[2][y] * mat[2][z],
		_data[0][z] * mat[2][x] + _data[1][z] * mat[2][y] + _data[2][z] * mat[2][z],
		0.0f
	};

	Vector4 wCol {0.0f, 0.0f, 0.0f, 1.0f};

	return Matrix4(xCol, yCol, zCol, wCol);
}

Vector4 Matrix4::Transform3x3(const Vector4& vec) const
{
	return Vector4(_data[0][x] * vec[x] + _data[1][x] * vec[y] + _data[2][x] * vec[z],
				   _data[0][y] * vec[x] + _data[1][y] * vec[y] + _data[2][y] * vec[z],
				   _data[0][z] * vec[x] + _data[1][z] + vec[y] + _data[2][z] * vec[z],
				   _data[0][w] * vec[x] + _data[1][w] + vec[y] + _data[2][w] + vec[z]);
}

//==========================================================================================================================
//
//Look At Matrices
//
//==========================================================================================================================

Matrix4 Matrix4::LookAt(const Vector4& cameraPos, const Vector4& target, const Vector4& up)
{
	Matrix4 mat{1.0f};

	Vector4 zAxis = cameraPos - target;
	zAxis.Normalize();

	Vector4 xAxis = up.CrossProduct(zAxis);
	xAxis.Normalize();

	Vector4 yAxis = zAxis.CrossProduct(xAxis);
	yAxis.Normalize();

	mat[0][0] = xAxis[0];
	mat[0][1] = yAxis[0];
	mat[0][2] = zAxis[0];
	mat[0][3] = 0.0f;

	mat[1][0] = xAxis[1];
	mat[1][1] = yAxis[1];
	mat[1][2] = zAxis[1];
	mat[1][3] = 0.0f;

	mat[2][0] = xAxis[2];
	mat[2][1] = yAxis[2];
	mat[2][2] = zAxis[2];
	mat[2][3] = 0.0f;

	mat[3] = Vector4(-xAxis.Dot(cameraPos), -yAxis.Dot(cameraPos), -zAxis.Dot(cameraPos), 1.0f);

	return mat;
}

void Matrix4::SetLookAt(const Vector4& cameraPos, const Vector4& target, const Vector4& up)
{
	MakeIdentity();

	Vector4 zAxis = cameraPos - target;
	zAxis.Normalize();

	Vector4 xAxis = up.CrossProduct(zAxis);
	xAxis.Normalize();

	Vector4 yAxis = zAxis.CrossProduct(xAxis);
	yAxis.Normalize();

	_data[0][0] = xAxis[0];
	_data[0][1] = yAxis[0];
	_data[0][2] = zAxis[0];
	_data[0][3] = 0.0f;

	_data[1][0] = xAxis[1];
	_data[1][1] = yAxis[1];
	_data[1][2] = zAxis[1];
	_data[1][3] = 0.0f;

	_data[2][0] = xAxis[2];
	_data[2][1] = yAxis[2];
	_data[2][2] = zAxis[2];
	_data[2][3] = 0.0f;

	_data[3] = Vector4(-xAxis.Dot(cameraPos), -yAxis.Dot(cameraPos), -zAxis.Dot(cameraPos), 1.0f);		
}

Matrix4 Matrix4::FPSView(const Vector4& cameraPos, F32 pitch, F32 yaw)
{
	assert(pitch >= -90.0f);
	assert(pitch <= 90.0f);
	assert(yaw >= 0.0f);
	assert(yaw <= 360.0f);

	F32 cosPitch = cos(pitch);
	F32 sinPitch = sin(pitch);
	F32 cosYaw 	 = cos(yaw);
	F32 sinYaw   = sin(yaw);

	Matrix4 mat{1.0f};

	Vector4 xAxis{ cosYaw, 0.0f, -sinYaw };
	Vector4 yAxis{ sinYaw * sinPitch, cosPitch, cosYaw * sinPitch };
	Vector4 zAxis{ sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw };

	mat[0][0] = xAxis[0];
	mat[0][1] = yAxis[0];
	mat[0][2] = zAxis[0];
	mat[0][3] = 0.0f;

	mat[1][0] = xAxis[1];
	mat[1][1] = yAxis[1];
	mat[1][2] = zAxis[1];
	mat[1][3] = 0.0f;

	mat[2][0] = xAxis[2];
	mat[2][1] = yAxis[2];
	mat[2][2] = zAxis[2];
	mat[2][3] = 0.0f;

	mat[3] = Vector4(-xAxis.Dot(cameraPos), -yAxis.Dot(cameraPos), -zAxis.Dot(cameraPos), 1.0f);

	return mat;
}

void Matrix4::SetFPSView(const Vector4& cameraPos, F32 pitch, F32 yaw)
{
	assert(pitch >= -90.0f);
	assert(pitch <= 90.0f);
	assert(yaw >= 0.0f);
	assert(yaw <= 360.0f);

	F32 cosPitch = cos(pitch);
	F32 sinPitch = sin(pitch);
	F32 cosYaw 	 = cos(yaw);
	F32 sinYaw   = sin(yaw);

	Vector4 xAxis{ cosYaw, 0.0f, -sinYaw };
	Vector4 yAxis{ sinYaw * sinPitch, cosPitch, cosYaw * sinPitch };
	Vector4 zAxis{ sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw };

	_data[0][0] = xAxis[0];
	_data[0][1] = yAxis[0];
	_data[0][2] = zAxis[0];
	_data[0][3] = 0.0f;

	_data[1][0] = xAxis[1];
	_data[1][1] = yAxis[1];
	_data[1][2] = zAxis[1];
	_data[1][3] = 0.0f;

	_data[2][0] = xAxis[2];
	_data[2][1] = yAxis[2];
	_data[2][2] = zAxis[2];
	_data[2][3] = 0.0f;

	_data[3] = Vector4(-xAxis.Dot(cameraPos), -yAxis.Dot(cameraPos), -zAxis.Dot(cameraPos), 1.0f);	
}

//==========================================================================================================================
//
//Operator Overloads
//
//==========================================================================================================================
Matrix4& Matrix4::operator=(const Matrix4& mat) 
{
	_data[0][x] = mat[0][x];
	_data[0][y] = mat[0][y];
	_data[0][z] = mat[0][z];
	_data[0][w] = mat[0][w];

	_data[1][x] = mat[1][x];
	_data[1][y] = mat[1][y];
	_data[1][z] = mat[1][z];
	_data[1][w] = mat[1][w];

	_data[2][x] = mat[2][x];
	_data[2][y] = mat[2][y];
	_data[2][z] = mat[2][z];
	_data[2][w] = mat[2][w];

	_data[3][x] = mat[3][x];
	_data[3][y] = mat[3][y];
	_data[3][z] = mat[3][z];
	_data[3][w] = mat[3][w];

	return *this;
}

Matrix4 Matrix4::operator*(const Matrix4& mat) const
{
	Vector4 xCol 
	{
		_data[0][x] * mat[0][x] + _data[1][x] * mat[0][y] + _data[2][x] * mat[0][z] + _data[3][x] * mat[0][w],
		_data[0][y] * mat[0][x] + _data[1][y] * mat[0][y] + _data[2][y] * mat[0][z] + _data[3][y] * mat[0][w],
		_data[0][z] * mat[0][x] + _data[1][z] * mat[0][y] + _data[2][z] * mat[0][z] + _data[3][z] * mat[0][w],
		_data[0][w] * mat[0][x] + _data[1][w] * mat[0][y] + _data[2][w] * mat[0][z] + _data[3][w] * mat[0][w],

	};

	Vector4 yCol
	{
		_data[0][x] * mat[1][x] + _data[1][x] * mat[1][y] + _data[2][x] * mat[1][z] + _data[3][x] * mat[1][w],
		_data[0][y] * mat[1][x] + _data[1][y] * mat[1][y] + _data[2][y] * mat[1][z] + _data[3][y] * mat[1][w],
		_data[0][z] * mat[1][x] + _data[1][z] * mat[1][y] + _data[2][z] * mat[1][z] + _data[3][z] * mat[1][w],
		_data[0][w] * mat[1][x] + _data[1][w] * mat[1][y] + _data[2][w] * mat[1][z] + _data[3][w] * mat[1][w],
	};

	Vector4 zCol
	{
		_data[0][x] * mat[2][x] + _data[1][x] * mat[2][y] + _data[2][x] * mat[2][z] + _data[3][x] * mat[2][w],
		_data[0][y] * mat[2][x] + _data[1][y] * mat[2][y] + _data[2][y] * mat[2][z] + _data[3][y] * mat[2][w],
		_data[0][z] * mat[2][x] + _data[1][z] * mat[2][y] + _data[2][z] * mat[2][z] + _data[3][z] * mat[2][w],
		_data[0][w] * mat[2][x] + _data[1][w] * mat[2][y] + _data[2][w] * mat[2][z] + _data[3][w] * mat[2][w],
	};

	Vector4 wCol
	{
		_data[0][x] * mat[3][x] + _data[1][x] * mat[3][y] + _data[2][x] * mat[3][z] + _data[3][x] * mat[3][w],
		_data[0][y] * mat[3][x] + _data[1][y] * mat[3][y] + _data[2][y] * mat[3][z] + _data[3][y] * mat[3][w],
		_data[0][z] * mat[3][x] + _data[1][z] * mat[3][y] + _data[2][z] * mat[3][z] + _data[3][z] * mat[3][w],
		_data[0][w] * mat[3][x] + _data[1][w] * mat[3][y] + _data[2][w] * mat[3][z] + _data[3][w] * mat[3][w],
	};

	return Matrix4(xCol, yCol, zCol, wCol);
}

Vector4 Matrix4::operator*(const Vector4& vec) const
{
	return Vector4(_data[0][x] * vec[x] + _data[1][x] * vec[y] + _data[2][x] * vec[z] + _data[3][x] * vec[w],
				   _data[0][y] * vec[x] + _data[1][y] * vec[y] + _data[2][y] * vec[z] + _data[3][y] * vec[w],
				   _data[0][z] * vec[x] + _data[1][z] + vec[y] + _data[2][z] * vec[z] + _data[3][z] * vec[w],
				   _data[0][w] * vec[x] + _data[1][w] + vec[y] + _data[2][w] + vec[z] + _data[3][w] * vec[w]);
}

Point Matrix4::operator*(const Point& point) const
{
	return Point(_data[0][x] * point[x] + _data[1][x] * point[y] + _data[2][x] * point[z] + _data[3][x] * point[w],
				 _data[0][y] * point[x] + _data[1][y] * point[y] + _data[2][y] * point[z] + _data[3][y] * point[w],
				 _data[0][z] * point[x] + _data[1][z] + point[y] + _data[2][z] * point[z] + _data[3][z] * point[w],
				 _data[0][w] * point[x] + _data[1][w] + point[y] + _data[2][w] + point[z] + _data[3][w] * point[w]);
}

Matrix4& Matrix4::operator/=(F32 val)
{
	_data[x][x] /= val;
	_data[x][y] /= val;
	_data[x][z] /= val;
	_data[x][w] /= val;
	
	_data[y][x] /= val;
	_data[y][y] /= val;
	_data[y][z] /= val;
	_data[y][w] /= val;

	_data[z][x] /= val;
	_data[z][y] /= val;
	_data[z][z] /= val;
	_data[z][w] /= val;

	_data[w][x] /= val;
	_data[w][y] /= val;
	_data[w][z] /= val;
	_data[w][w] /= val;

	return *this;
}

F32 Matrix4::_Cofactor(const Vector4& col1, const Vector4& col2, const Vector4& col3) const
{
	return col1[x] * (col2[y] * col3[z] - col3[y] * col2[z])
		 + col2[x] * (col3[y] * col1[z] - col1[y] * col3[z])
		 + col3[x] * (col1[y] * col2[z] - col2[y] * col1[z]);
}