#include <Engine/Matrix.h>

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
void Matrix::MakeOrthographic(F32 left, F32 right, F32 bottom, F32 top, F32 nearPlane, F32 farPlane)
{
	//Reset Matrix
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

void Matrix::MakePerspective(F32 fieldOfView, F32 aspectRatio, F32 nearPlane, F32 farPlane)
{
	assert(nearPlane - farPlane != 0.0f);

	F32 S = 1.0f / tan(RADIAN(0.5f * fieldOfView));

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
Matrix Matrix::Translate(F32 xVal, F32 yVal)
{
	Matrix mat{1.0f};

	mat[3][x] = xVal;
	mat[3][y] = yVal;

	return mat;
}

Matrix Matrix::Translate(F32 xVal, F32 yVal, F32 zVal)
{
	Matrix mat{1.0f};

	mat[3][x] = xVal;
	mat[3][y] = yVal;
	mat[3][z] = zVal;

	return mat;	
}

Matrix Matrix::Translate(const Vector& vec)
{
	Matrix mat{1.0f};

	mat[3][x] = vec[x];
	mat[3][y] = vec[y];
	mat[3][z] = vec[z];

	return mat;	
}

void Matrix::SetTranslate(F32 xVal, F32 yVal)
{
	MakeIdentity();

	_columns[3][x] = xVal;
	_columns[3][y] = yVal;
}

void Matrix::SetTranslate(F32 xVal, F32 yVal, F32 zVal)
{
	MakeIdentity();			

	_columns[3][x] = xVal;
	_columns[3][y] = yVal;
	_columns[3][z] = zVal;
}

void Matrix::SetTranslate(const Vector& vec)
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
Matrix Matrix::Scale(F32 xVal, F32 yVal)
{
	Matrix mat{1.0f};

	mat[0][x] = xVal;
	mat[1][y] = yVal;

	return mat;
}

Matrix Matrix::Scale(F32 xVal, F32 yVal, F32 zVal)
{
	Matrix mat{1.0f};

	mat[0][x] = xVal;
	mat[1][y] = yVal;
	mat[2][z] = zVal;

	return mat;
}

Matrix Matrix::Scale(const Vector& vec)
{
	Matrix mat{1.0f};

	mat[0][x] = vec[x];
	mat[1][y] = vec[y];
	mat[2][z] = vec[z];

	return mat;
}

void Matrix::SetScale(F32 xVal, F32 yVal)
{
	MakeIdentity();

	_columns[0][x] = xVal;
	_columns[1][y] = yVal;
}

void Matrix::SetScale(F32 xVal, F32 yVal, F32 zVal)
{
	MakeIdentity();

	_columns[0][x] = xVal;
	_columns[1][y] = yVal;
	_columns[2][z] = zVal;
}

void Matrix::SetScale(const Vector& vec)
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
Matrix Matrix::RotateX(F32 val)
{
	val = RADIAN(val);
	Matrix mat{1.0f};

	mat[1][y] = cos(val);
	mat[1][z] = -sin(val);
	mat[2][y] = sin(val);
	mat[2][z] = cos(val);

	return mat;
}

Matrix Matrix::RotateY(F32 val)
{
	val = RADIAN(val);
	Matrix mat{1.0f};

	mat[0][x] = cos(val);
	mat[0][z] = sin(val);
	mat[2][x] = -sin(val);
	mat[2][z] = cos(val);

	return mat;
}

Matrix Matrix::RotateZ(F32 val)
{
	val = RADIAN(val);
	Matrix mat{1.0f};

	mat[0][x] = cos(val);
	mat[0][y] = -sin(val);
	mat[1][x] = sin(val);
	mat[1][y] = cos(val);

	return mat;
}

void Matrix::SetRotateX(F32 val)
{
	val = RADIAN(val);

	MakeIdentity();

	_columns[1][y] = cos(val);
	_columns[1][z] = -sin(val);
	_columns[2][y] = sin(val);
	_columns[2][z] = cos(val);
}

void Matrix::AddRotateX(F32 val)
{
	val = RADIAN(val);

	_columns[1][y] += cos(val);
	_columns[1][z] += -sin(val);
	_columns[2][y] += sin(val);
	_columns[2][z] += cos(val);
}

void Matrix::SetRotateY(F32 val)
{
	val = RADIAN(val);

	MakeIdentity();

	_columns[0][x] = cos(val);
	_columns[0][z] = sin(val);
	_columns[2][x] = -sin(val);
	_columns[2][z] = cos(val);
}

void Matrix::AddRotateY(F32 val)
{
	val = RADIAN(val);

	_columns[0][x] += cos(val);
	_columns[0][y] += sin(val);
	_columns[2][x] += -sin(val);
	_columns[2][y] += cos(val);	
}

void Matrix::SetRotateZ(F32 val)
{
	val = RADIAN(val);

	MakeIdentity();

	_columns[0][x] = cos(val);
	_columns[0][y] = -sin(val);
	_columns[1][x] = sin(val);
	_columns[1][y] = cos(val);
}

void Matrix::AddRotateZ(F32 val)
{
	val = RADIAN(val);

	_columns[0][x] += cos(val);
	_columns[0][y] += -sin(val);
	_columns[1][x] += sin(val);
	_columns[1][y] += cos(val);
}

void Matrix::SetRotate(F32 xVal, F32 yVal, F32 zVal)
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

void Matrix::AddRotation(F32 xVal, F32 yVal, F32 zVal)
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

//==========================================================================================================================
//
//Look At Matrices
//
//==========================================================================================================================

Matrix Matrix::LookAt(const Vector& cameraPos, const Vector& target, const Vector& up)
{
	Matrix mat{1.0f};

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

	mat[3] = Vector(-xAxis.DotProduct(cameraPos), -yAxis.DotProduct(cameraPos), -zAxis.DotProduct(cameraPos), 1.0f);

	return mat;
}

void Matrix::SetLookAt(const Vector& cameraPos, const Vector& target, const Vector& up)
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

	_columns[3] = Vector(-xAxis.DotProduct(cameraPos), -yAxis.DotProduct(cameraPos), -zAxis.DotProduct(cameraPos), 1.0f);		
}

Matrix Matrix::FPSView(const Vector& cameraPos, F32 pitch, F32 yaw)
{
	assert(pitch >= -90.0f);
	assert(pitch <= 90.0f);
	assert(yaw >= 0.0f);
	assert(yaw <= 360.0f);

	F32 cosPitch = cos(pitch);
	F32 sinPitch = sin(pitch);
	F32 cosYaw 	 = cos(yaw);
	F32 sinYaw   = sin(yaw);

	Matrix mat{1.0f};

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

	mat[3] = Vector(-xAxis.DotProduct(cameraPos), -yAxis.DotProduct(cameraPos), -zAxis.DotProduct(cameraPos), 1.0f);

	return mat;
}

void Matrix::SetFPSView(const Vector& cameraPos, F32 pitch, F32 yaw)
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

	_columns[3] = Vector(-xAxis.DotProduct(cameraPos), -yAxis.DotProduct(cameraPos), -zAxis.DotProduct(cameraPos), 1.0f);	
}

Vector Matrix::operator*(const Vector& vec)
{
	return Vector( _columns[0][x] * vec[x] + _columns[1][x] * vec[y] + _columns[2][x] * vec[z] + _columns[3][x] * vec[w],
				   _columns[0][y] * vec[x] + _columns[1][y] * vec[y] + _columns[2][y] * vec[z] + _columns[3][y] * vec[w],
				   _columns[0][z] * vec[x] + _columns[1][z] + vec[y] + _columns[2][z] * vec[z] + _columns[3][z] * vec[w],
				   _columns[0][w] * vec[x] + _columns[1][w] + vec[y] + _columns[2][w] + vec[z] + _columns[3][w] * vec[w] );
}