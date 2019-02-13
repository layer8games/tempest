#include <Engine/Matrix3.h>

using namespace KillerMath;

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Matrix3::Matrix3(void)
:
_columns{Vector(1.0f, 0.0f, 0.0f, 0.0f),
		 Vector(0.0f, 1.0f, 0.0f, 0.0f),
		 Vector(0.0f, 0.0f, 1.0f, 0.0f),
		 Vector(0.0f, 0.0f, 0.0f, 1.0f)}
{  }

Matrix3::Matrix3(const Vector& x, const Vector& y, const Vector& z)
:
_columns{x, y, z, Vector(0.0f, 0.0f, 0.0f, 1.0f)}
{  }

Matrix3::Matrix3(const Vector& x, const Vector& y, const Vector& z, const Vector& w)
:
_columns{x, y, z, w}
{  }

Matrix3::Matrix3(const F32 val)
:
_columns{Vector(val, 0.0f, 0.0f, 0.0f),
		 Vector(0.0f, val, 0.0f, 0.0f),
		 Vector(0.0f, 0.0f, val, 0.0f),
		 Vector(0.0f, 0.0f, 0.0f, 1.0f)}
{  }

Matrix3::Matrix3( F32 m00, F32 m01, F32 m02, F32 m03,
				F32 m10, F32 m11, F32 m12, F32 m13,
				F32 m20, F32 m21, F32 m22, F32 m23,
				F32 m30, F32 m31, F32 m32, F32 m33)
:
_columns{Vector(m00, m01, m02, m03),
		 Vector(m10, m11, m12, m13),
		 Vector(m20, m21, m22, m23),
		 Vector(m30, m31, m32, m33)}
{  }

Matrix3::Matrix3(const Matrix3& M)
:
_columns{M[0], M[1], M[2], M[3]}
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
void Matrix3::MakeOrthographic(F32 left, F32 right, F32 bottom, F32 top, F32 nearPlane, F32 farPlane)
{
	//Reset Matrix3
	MakeIdentity();

	assert(right - left != 0.0f);
	assert(top - bottom != 0.0f);
	assert(farPlane - nearPlane != 0.0f);

	//Diagnal
	_columns[0][x] = 2.0f / (right - left);
	_columns[1][y] = 2.0f / (top - bottom);
	_columns[2][z] = -2.0f / (farPlane - nearPlane);
	_columns[3][w] = 1.0f;

	//Transform "Vector"
	_columns[3][x] = -(right + left) / (right - left);
	_columns[3][y] = -(top + bottom) / (top - bottom);
	_columns[3][z] = -(farPlane + nearPlane) / (farPlane - nearPlane);
}

void Matrix3::MakePerspective(F32 fieldOfView, F32 aspectRatio, F32 nearPlane, F32 farPlane)
{
	assert(nearPlane - farPlane != 0.0f);

	F32 S = 1.0f / tan(RADIAN(0.5f * fieldOfView));

	//Reset Matrix3 
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
Matrix3 Matrix3::Translate(F32 xVal, F32 yVal)
{
	Matrix3 mat{1.0f};

	mat[3][x] = xVal;
	mat[3][y] = yVal;

	return mat;
}

Matrix3 Matrix3::Translate(F32 xVal, F32 yVal, F32 zVal)
{
	Matrix3 mat{1.0f};

	mat[3][x] = xVal;
	mat[3][y] = yVal;
	mat[3][z] = zVal;

	return mat;	
}

Matrix3 Matrix3::Translate(const Vector& vec)
{
	Matrix3 mat{1.0f};

	mat[3][x] = vec[x];
	mat[3][y] = vec[y];
	mat[3][z] = vec[z];

	return mat;	
}

void Matrix3::SetTranslate(F32 xVal, F32 yVal)
{
	MakeIdentity();

	_columns[3][x] = xVal;
	_columns[3][y] = yVal;
}

void Matrix3::SetTranslate(F32 xVal, F32 yVal, F32 zVal)
{
	MakeIdentity();			

	_columns[3][x] = xVal;
	_columns[3][y] = yVal;
	_columns[3][z] = zVal;
}

void Matrix3::SetTranslate(const Vector& vec)
{
	MakeIdentity(); 

	_columns[3][x] = vec[x];
	_columns[3][y] = vec[y];

	if(!vec.Is2D())
	{
		_columns[3][z] = vec[z];
	}
}

void Matrix3::AddTranslate(F32 xVal, F32 yVal)
{
	_columns[3][x] += xVal;
	_columns[3][y] += yVal;
}

void Matrix3::AddTranslate(F32 xVal, F32 yVal, F32 zVal)
{
	_columns[3][x] += xVal; 
	_columns[3][y] += yVal; 
	_columns[3][z] += zVal;
}

void Matrix3::AddTranslate(const Vector& vec)
{
	_columns[3][x] += vec[x];
	_columns[3][y] += vec[y];
	
	if(!vec.Is2D()) 
	{
		_columns[3][z] += vec[z];
	}
}

Vector Matrix3::TransformInverse(const Vector vec) const
{
	Vector tmp = vec;

	tmp[x] -= _columns[3][x];
	tmp[y] -= _columns[3][y];
	tmp[z] -= _columns[3][z];

	return Vector
	{
		tmp[x] * _columns[0][x] +
		tmp[y] * _columns[0][y] + 
		tmp[z] * _columns[0][z],

		tmp[x] * _columns[1][x] + 
		tmp[y] * _columns[1][y] + 
		tmp[z] * _columns[1][z],

		tmp[x] * _columns[2][x] +
		tmp[y] * _columns[2][y] + 
		tmp[z] * _columns[2][z]
	};
}

Vector Matrix3::TransformDirection(const Vector& vec) const
{
	return Vector
	{
		vec[x] * _columns[0][x] + 
		vec[y] * _columns[1][x] + 
		vec[z] * _columns[2][x],

		vec[x] * _columns[0][y] + 
		vec[y] * _columns[1][y] + 
		vec[z] * _columns[2][y],

		vec[x] * _columns[0][z] + 
		vec[y] * _columns[1][z] + 
		vec[z] * _columns[2][z],
	};
}

Vector Matrix3::TransformInverseDirection(const Vector& vec) const
{
	return Vector
	{
		vec[x] * _columns[0][x] + 
		vec[y] * _columns[0][y] + 
		vec[z] * _columns[0][z],

		vec[x] * _columns[1][x] + 
		vec[y] * _columns[1][y] + 
		vec[z] * _columns[1][z],

		vec[x] * _columns[2][x] + 
		vec[y] * _columns[2][y] + 
		vec[z] * _columns[2][z],
	};
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
	F32 det = Determinate();

	if(det == 0.0f) return;

	F32 c00 = Determinate3x3(Vector(_columns[y][y], _columns[y][z], _columns[y][w]),
							 Vector(_columns[z][y], _columns[z][z], _columns[z][w]),
							 Vector(_columns[w][y], _columns[w][z], _columns[w][w]));

	F32 c01 = Determinate3x3(Vector(_columns[y][x], _columns[y][z], _columns[y][w]),
							 Vector(_columns[z][x], _columns[z][z], _columns[z][w]),
							 Vector(_columns[w][x], _columns[w][z], _columns[w][w]));

	F32 c02 = Determinate3x3(Vector(_columns[y][x], _columns[y][y], _columns[y][w]),
							 Vector(_columns[z][x], _columns[z][y], _columns[z][w]),
							 Vector(_columns[w][x], _columns[w][y], _columns[w][w]));

	F32 c03 = Determinate3x3(Vector(_columns[y][x], _columns[y][y], _columns[y][z]),
							 Vector(_columns[z][x], _columns[z][y], _columns[z][z]),
							 Vector(_columns[w][x], _columns[w][y], _columns[w][z]));

	Vector colx {c00, -c01, c02, -c03};

	F32 c10 = Determinate3x3(Vector(_columns[x][y], _columns[x][z], _columns[x][w]),
							 Vector(_columns[z][y], _columns[z][z], _columns[z][w]),
							 Vector(_columns[w][y], _columns[w][z], _columns[w][w]));

	F32 c11 = Determinate3x3(Vector(_columns[x][x], _columns[x][z], _columns[x][w]),
							 Vector(_columns[z][x], _columns[z][z], _columns[z][w]),
							 Vector(_columns[w][x], _columns[w][z], _columns[w][w]));

	F32 c12 = Determinate3x3(Vector(_columns[x][x], _columns[x][y], _columns[x][w]),
							 Vector(_columns[z][x], _columns[z][y], _columns[z][w]),
							 Vector(_columns[w][x], _columns[w][y], _columns[w][w]));

	F32 c13 = Determinate3x3(Vector(_columns[x][x], _columns[x][y], _columns[x][z]),
							 Vector(_columns[z][x], _columns[z][y], _columns[z][z]),
							 Vector(_columns[w][x], _columns[w][y], _columns[w][z]));

	Vector coly {-c10, c11, -c12, c13};

	F32 c20 = Determinate3x3(Vector(_columns[x][y], _columns[x][z], _columns[x][w]),
							 Vector(_columns[y][y], _columns[y][z], _columns[y][w]),
							 Vector(_columns[w][y], _columns[w][z], _columns[w][w]));

	F32 c21 = Determinate3x3(Vector(_columns[x][x], _columns[x][z], _columns[x][w]),
							 Vector(_columns[y][x], _columns[y][z], _columns[y][w]),
							 Vector(_columns[w][x], _columns[w][z], _columns[w][w]));

	F32 c22 = Determinate3x3(Vector(_columns[x][x], _columns[x][y], _columns[x][w]),
							 Vector(_columns[y][x], _columns[y][y], _columns[y][w]),
							 Vector(_columns[w][x], _columns[w][y], _columns[w][w]));

	F32 c23 = Determinate3x3(Vector(_columns[x][x], _columns[x][y], _columns[x][z]),
							 Vector(_columns[y][x], _columns[y][y], _columns[y][z]),
							 Vector(_columns[w][x], _columns[w][y], _columns[w][z]));

	Vector colz {c20, -c21, c22, -c23};

	F32 c30 = Determinate3x3(Vector(_columns[x][y], _columns[x][z], _columns[x][w]),
							 Vector(_columns[y][y], _columns[y][z], _columns[y][w]),
							 Vector(_columns[z][y], _columns[z][z], _columns[z][w]));

	F32 c31 = Determinate3x3(Vector(_columns[x][x], _columns[x][z], _columns[x][w]),
							 Vector(_columns[y][x], _columns[y][z], _columns[y][w]),
							 Vector(_columns[z][x], _columns[z][z], _columns[z][w]));

	F32 c32 = Determinate3x3(Vector(_columns[x][x], _columns[x][y], _columns[x][w]),
							 Vector(_columns[y][x], _columns[y][y], _columns[y][w]),
							 Vector(_columns[z][x], _columns[z][y], _columns[z][w]));

	F32 c33 = Determinate3x3(Vector(_columns[x][x], _columns[x][y], _columns[x][z]),
							 Vector(_columns[y][x], _columns[y][y], _columns[y][z]),
							 Vector(_columns[z][x], _columns[z][y], _columns[z][z]));

	Vector colw {-c30, c31, -c32, c33};

	Matrix3 adj { colx, coly, colz, colw };

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
	//This equation is very difficult to understand. It was ultimately taking from 3d Math Primer, page 165, Determinate of 
	//4x4 Matrix3 in expanded form.
	//m11 through m41 represent the cofactors of those sections of the Matrix3, which are added together to get the value
	F32 m11 = _columns[0][0] * (   _columns[1][1] * (_columns[2][2] * _columns[3][3] - _columns[3][2] * _columns[2][3])
			   					+ _columns[2][1] * (_columns[3][2] * _columns[1][3] - _columns[1][2] * _columns[3][3])
			   					+ _columns[3][1] * (_columns[1][2] * _columns[2][3] - _columns[2][2] * _columns[1][3]) );

	F32 m21 = _columns[1][0] * (   _columns[0][1] * (_columns[2][2] * _columns[3][3] - _columns[3][2] * _columns[2][3])
		 		   				+ _columns[2][1] * (_columns[3][2] * _columns[0][3] - _columns[0][2] * _columns[3][3])
		 		   				+ _columns[3][1] * (_columns[0][2] * _columns[2][3] - _columns[2][2] * _columns[0][3]) );

	F32 m31 = _columns[2][0] * (   _columns[0][1] * (_columns[1][2] * _columns[3][3] - _columns[3][2] * _columns[1][3])
		 		   				+ _columns[1][1] * (_columns[3][2] * _columns[0][3] - _columns[0][2] * _columns[3][3])
		 		   				+ _columns[3][1] * (_columns[0][2] * _columns[1][3] - _columns[1][2] * _columns[0][3]) );

	F32 m41 = _columns[3][0] * (   _columns[0][1] * (_columns[1][2] * _columns[2][3] - _columns[2][2] * _columns[1][3])
		 		   				+ _columns[1][1] * (_columns[2][2] * _columns[0][3] - _columns[0][2] * _columns[2][3])
		 		   				+ _columns[2][1] * (_columns[0][2] * _columns[1][3] - _columns[1][2] * _columns[0][3]) );

	return m11 - m21 + m31 - m41;
}

F32 Matrix3::Determinate3x3(Vector& col1, Vector& col2, Vector& col3)
{
	return col1[x] * (col2[y] * col3[z] - col3[y] * col2[z])
		 + col2[x] * (col3[y] * col1[z] - col1[y] * col3[z])
		 + col3[x] * (col1[y] * col2[z] - col2[y] * col1[z]);
}

//==========================================================================================================================
//Resettings
//==========================================================================================================================
void Matrix3::Reset(F32 val)
{
	//Reset Matrix3
	_columns[0] = Vector(val, 0.0f, 0.0f, 0.0f);
	_columns[1] = Vector(0.0f, val, 0.0f, 0.0f);
	_columns[2] = Vector(0.0f, 0.0f, val, 0.0f);
	_columns[3] = Vector(0.0f, 0.0f, 0.0f, val);
}

//==========================================================================================================================
//Misc
//==========================================================================================================================
void Matrix3::Transpose(void)
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

void Matrix3::ComponentMulti(const Matrix3& mat)
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

Matrix3 Matrix3::Transform3x3(const Matrix3& mat) const
{
	Vector xCol 
	{
		_columns[0][x] * mat[0][x] + _columns[1][x] * mat[0][y] + _columns[2][x] * mat[0][z],
		_columns[0][y] * mat[0][x] + _columns[1][y] * mat[0][y] + _columns[2][y] * mat[0][z],
		_columns[0][z] * mat[0][x] + _columns[1][z] * mat[0][y] + _columns[2][z] * mat[0][z],
		0.0f
	};

	Vector yCol
	{
		_columns[0][x] * mat[1][x] + _columns[1][x] * mat[1][y] + _columns[2][x] * mat[1][z],
		_columns[0][y] * mat[1][x] + _columns[1][y] * mat[1][y] + _columns[2][y] * mat[1][z],
		_columns[0][z] * mat[1][x] + _columns[1][z] * mat[1][y] + _columns[2][z] * mat[1][z],
		0.0f
	};

	Vector zCol
	{
		_columns[0][x] * mat[2][x] + _columns[1][x] * mat[2][y] + _columns[2][x] * mat[2][z],
		_columns[0][y] * mat[2][x] + _columns[1][y] * mat[2][y] + _columns[2][y] * mat[2][z],
		_columns[0][z] * mat[2][x] + _columns[1][z] * mat[2][y] + _columns[2][z] * mat[2][z],
		0.0f
	};

	Vector wCol {0.0f, 0.0f, 0.0f, 1.0f};

	return Matrix3(xCol, yCol, zCol, wCol);
}

Vector Matrix3::Transform3x3(const Vector& vec) const
{
	return Vector( _columns[0][x] * vec[x] + _columns[1][x] * vec[y] + _columns[2][x] * vec[z],
				   _columns[0][y] * vec[x] + _columns[1][y] * vec[y] + _columns[2][y] * vec[z],
				   _columns[0][z] * vec[x] + _columns[1][z] + vec[y] + _columns[2][z] * vec[z],
				   _columns[0][w] * vec[x] + _columns[1][w] + vec[y] + _columns[2][w] + vec[z] );
}

//==========================================================================================================================
//
//Look At Matrices
//
//==========================================================================================================================

Matrix3 Matrix3::LookAt(const Vector& cameraPos, const Vector& target, const Vector& up)
{
	Matrix3 mat{1.0f};

	Vector zAxis = cameraPos - target;
	zAxis.Normalize();

	Vector xAxis = up.CrossProduct(zAxis);
	xAxis.Normalize();

	Vector yAxis = zAxis.CrossProduct(xAxis);
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

	mat[3] = Vector(-xAxis.Dot(cameraPos), -yAxis.Dot(cameraPos), -zAxis.Dot(cameraPos), 1.0f);

	return mat;
}

void Matrix3::SetLookAt(const Vector& cameraPos, const Vector& target, const Vector& up)
{
	MakeIdentity();

	Vector zAxis = cameraPos - target;
	zAxis.Normalize();

	Vector xAxis = up.CrossProduct(zAxis);
	xAxis.Normalize();

	Vector yAxis = zAxis.CrossProduct(xAxis);
	yAxis.Normalize();

	_columns[0][0] = xAxis[0];
	_columns[0][1] = yAxis[0];
	_columns[0][2] = zAxis[0];
	_columns[0][3] = 0.0f;

	_columns[1][0] = xAxis[1];
	_columns[1][1] = yAxis[1];
	_columns[1][2] = zAxis[1];
	_columns[1][3] = 0.0f;

	_columns[2][0] = xAxis[2];
	_columns[2][1] = yAxis[2];
	_columns[2][2] = zAxis[2];
	_columns[2][3] = 0.0f;

	_columns[3] = Vector(-xAxis.Dot(cameraPos), -yAxis.Dot(cameraPos), -zAxis.Dot(cameraPos), 1.0f);		
}

Matrix3 Matrix3::FPSView(const Vector& cameraPos, F32 pitch, F32 yaw)
{
	assert(pitch >= -90.0f);
	assert(pitch <= 90.0f);
	assert(yaw >= 0.0f);
	assert(yaw <= 360.0f);

	F32 cosPitch = cos(pitch);
	F32 sinPitch = sin(pitch);
	F32 cosYaw 	 = cos(yaw);
	F32 sinYaw   = sin(yaw);

	Matrix3 mat{1.0f};

	Vector xAxis{ cosYaw, 0.0f, -sinYaw };
	Vector yAxis{ sinYaw * sinPitch, cosPitch, cosYaw * sinPitch };
	Vector zAxis{ sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw };

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

	mat[3] = Vector(-xAxis.Dot(cameraPos), -yAxis.Dot(cameraPos), -zAxis.Dot(cameraPos), 1.0f);

	return mat;
}

void Matrix3::SetFPSView(const Vector& cameraPos, F32 pitch, F32 yaw)
{
	assert(pitch >= -90.0f);
	assert(pitch <= 90.0f);
	assert(yaw >= 0.0f);
	assert(yaw <= 360.0f);

	F32 cosPitch = cos(pitch);
	F32 sinPitch = sin(pitch);
	F32 cosYaw 	 = cos(yaw);
	F32 sinYaw   = sin(yaw);

	Vector xAxis{ cosYaw, 0.0f, -sinYaw };
	Vector yAxis{ sinYaw * sinPitch, cosPitch, cosYaw * sinPitch };
	Vector zAxis{ sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw };

	_columns[0][0] = xAxis[0];
	_columns[0][1] = yAxis[0];
	_columns[0][2] = zAxis[0];
	_columns[0][3] = 0.0f;

	_columns[1][0] = xAxis[1];
	_columns[1][1] = yAxis[1];
	_columns[1][2] = zAxis[1];
	_columns[1][3] = 0.0f;

	_columns[2][0] = xAxis[2];
	_columns[2][1] = yAxis[2];
	_columns[2][2] = zAxis[2];
	_columns[2][3] = 0.0f;

	_columns[3] = Vector(-xAxis.Dot(cameraPos), -yAxis.Dot(cameraPos), -zAxis.Dot(cameraPos), 1.0f);	
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

Matrix3 Matrix3::operator*(const Matrix3& mat) const
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

	return Matrix3(xCol, yCol, zCol, wCol);
}

Vector Matrix3::operator*(const Vector& vec) const
{
	return Vector( _columns[0][x] * vec[x] + _columns[1][x] * vec[y] + _columns[2][x] * vec[z] + _columns[3][x] * vec[w],
				   _columns[0][y] * vec[x] + _columns[1][y] * vec[y] + _columns[2][y] * vec[z] + _columns[3][y] * vec[w],
				   _columns[0][z] * vec[x] + _columns[1][z] + vec[y] + _columns[2][z] * vec[z] + _columns[3][z] * vec[w],
				   _columns[0][w] * vec[x] + _columns[1][w] + vec[y] + _columns[2][w] + vec[z] + _columns[3][w] * vec[w] );
}

Matrix3& Matrix3::operator/=(F32 val)
{
	_columns[x][x] /= val;
	_columns[x][y] /= val;
	_columns[x][z] /= val;
	_columns[x][w] /= val;
	
	_columns[y][x] /= val;
	_columns[y][y] /= val;
	_columns[y][z] /= val;
	_columns[y][w] /= val;

	_columns[z][x] /= val;
	_columns[z][y] /= val;
	_columns[z][z] /= val;
	_columns[z][w] /= val;

	_columns[w][x] /= val;
	_columns[w][y] /= val;
	_columns[w][z] /= val;
	_columns[w][w] /= val;

	return *this;
}