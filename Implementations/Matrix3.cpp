#include <Engine/Matrix3.h>

using namespace TempestMath;

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


Matrix3::Matrix3(const real val)
:
_data{ Vector3(val, 0.0f, 0.0f),
       Vector3(0.0f, val, 0.0f),
       Vector3(0.0f, 0.0f, val) }
{  }

Matrix3::Matrix3( real m00, real m01, real m02,
                  real m10, real m11, real m12,
                  real m20, real m21, real m22 )
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
const std::vector<real> Matrix3::GetElems(void) const
{
    std::vector<real> elems;
    
    elems.push_back(_data[0].x);
    elems.push_back(_data[0].y);
    elems.push_back(_data[0].z);
    elems.push_back(_data[1].x);
    elems.push_back(_data[1].y);
    elems.push_back(_data[1].z);
    elems.push_back(_data[2].x);
    elems.push_back(_data[2].y);
    elems.push_back(_data[2].z);

    return elems;
}


//==========================================================================================================================
//Scaling
//==========================================================================================================================
Matrix3 Matrix3::Scale(real xVal, real yVal)
{
    Matrix3 mat{1.0f};

    mat[0].x = xVal;
    mat[1].y = yVal;

    return mat;
}

Matrix3 Matrix3::Scale(real xVal, real yVal, real zVal)
{
    Matrix3 mat{1.0f};

    mat[0].x = xVal;
    mat[1].y = yVal;
    mat[2].z = zVal;

    return mat;
}

Matrix3 Matrix3::Scale(const Vector3& vec)
{
    Matrix3 mat{1.0f};

    mat[0].x = vec.x;
    mat[1].y = vec.y;
    mat[2].z = vec.z;

    return mat;
}

Matrix3 Matrix3::Scale(const Vector4& vec)
{
    Matrix3 mat{1.0f};

    mat[0].x = vec.x;
    mat[1].y = vec.y;
    mat[2].z = vec.z;

    return mat;
}

void Matrix3::SetScale(real xVal, real yVal)
{
    MakeIdentity();

    _data[0].x = xVal;
    _data[1].y = yVal;
}

void Matrix3::SetScale(real xVal, real yVal, real zVal)
{
    MakeIdentity();

    _data[0].x = xVal;
    _data[1].y = yVal;
    _data[2].z = zVal;
}

void Matrix3::SetScale(const Vector2& vec)
{
    MakeIdentity();

    _data[0].x = vec.x;
    _data[1].y = vec.y;
    _data[2].z = 1.0f;
}

void Matrix3::SetScale(const Vector3& vec)
{
    MakeIdentity();

    _data[0].x = vec.x;
    _data[1].y = vec.y;
    _data[2].z = vec.z;
}

void Matrix3::SetScale(const Vector4& vec)
{
    MakeIdentity();

    _data[0].x = vec.x;
    _data[1].y = vec.y;
    _data[2].z = vec.z;
}

//==========================================================================================================================
//Rotations
//==========================================================================================================================
Matrix3 Matrix3::RotateX(real val)
{
    val = RADIAN(val);
    Matrix3 mat{1.0f};

    mat[1].y = real_cos(val);
    mat[1].z = -real_sin(val);
    mat[2].y = real_sin(val);
    mat[2].z = real_cos(val);

    return mat;
}

Matrix3 Matrix3::RotateY(real val)
{
    val = RADIAN(val);
    Matrix3 mat{1.0f};

    mat[0].x = real_cos(val);
    mat[0].z = real_sin(val);
    mat[2].x = -real_sin(val);
    mat[2].z = real_cos(val);

    return mat;
}

Matrix3 Matrix3::RotateZ(real val)
{
    val = RADIAN(val);
    Matrix3 mat{1.0f};

    mat[0].x = real_cos(val);
    mat[0].y = -real_sin(val);
    mat[1].x = real_sin(val);
    mat[1].y = real_cos(val);

    return mat;
}

void Matrix3::SetRotateX(real val)
{
    val = RADIAN(val);

    MakeIdentity();

    _data[1].y = real_cos(val);
    _data[1].z = -real_sin(val);
    _data[2].y = real_sin(val);
    _data[2].z = real_cos(val);
}

void Matrix3::AddRotateX(real val)
{
    val = RADIAN(val);

    _data[1].y += real_cos(val);
    _data[1].z += -real_sin(val);
    _data[2].y += real_sin(val);
    _data[2].z += real_cos(val);
}

void Matrix3::SetRotateY(real val)
{
    val = RADIAN(val);

    MakeIdentity();

    _data[0].x = real_cos(val);
    _data[0].z = real_sin(val);
    _data[2].x = -real_sin(val);
    _data[2].z = real_cos(val);
}

void Matrix3::AddRotateY(real val)
{
    val = RADIAN(val);

    _data[0].x += real_cos(val);
    _data[0].y += real_sin(val);
    _data[2].x += -real_sin(val);
    _data[2].y += real_cos(val);	
}

void Matrix3::SetRotateZ(real val)
{
    val = RADIAN(val);

    MakeIdentity();

    _data[0].x = real_cos(val);
    _data[0].y = -real_sin(val);
    _data[1].x = real_sin(val);
    _data[1].y = real_cos(val);
}

void Matrix3::AddRotateZ(real val)
{
    val = RADIAN(val);

    _data[0].x += real_cos(val);
    _data[0].y += -real_sin(val);
    _data[1].x += real_sin(val);
    _data[1].y += real_cos(val);
}

void Matrix3::SetRotate(real xVal, real yVal, real zVal)
{
    xVal = RADIAN(xVal);
    yVal = RADIAN(yVal);
    zVal = RADIAN(zVal);

    MakeIdentity();

    _data[0].x = real_cos(yVal) * real_cos(zVal);
    _data[0].y = -real_cos(yVal) * real_sin(zVal);
    _data[0].z = real_sin(yVal);
    _data[1].x = real_cos(xVal) * real_sin(zVal) + real_sin(xVal) * real_sin(yVal) * real_cos(zVal);
    _data[1].y = real_cos(xVal) * real_cos(zVal) - real_sin(xVal) * real_sin(yVal) * real_sin(zVal);
    _data[1].z = -real_sin(xVal) * real_cos(yVal);
    _data[2].x = real_sin(xVal) * real_sin(zVal) - real_cos(xVal) * real_sin(yVal) * real_cos(zVal);
    _data[2].y = real_sin(xVal) * real_cos(zVal) + real_cos(xVal) * real_sin(yVal) * real_sin(zVal);
    _data[2].z = real_cos(xVal) * real_cos(yVal);
}

void Matrix3::AddRotation(real xVal, real yVal, real zVal)
{
    xVal = RADIAN(xVal);
    yVal = RADIAN(yVal);
    zVal = RADIAN(zVal);

    _data[0].x += real_cos(yVal) * real_cos(zVal);
    _data[0].y += -real_cos(yVal) * real_sin(zVal);
    _data[0].z += real_sin(yVal);
    _data[1].x += real_cos(xVal) * real_sin(zVal) + real_sin(xVal) * real_sin(yVal) * real_cos(zVal);
    _data[1].y += real_cos(xVal) * real_cos(zVal) - real_sin(xVal) * real_sin(yVal) * real_sin(zVal);
    _data[1].z += -real_sin(xVal) * real_cos(yVal);
    _data[2].x += real_sin(xVal) * real_sin(zVal) - real_cos(xVal) * real_sin(yVal) * real_cos(zVal);
    _data[2].y += real_sin(xVal) * real_cos(zVal) + real_cos(xVal) * real_sin(yVal) * real_sin(zVal);
    _data[2].z += real_cos(xVal) * real_cos(yVal);
}

void Matrix3::SetOrientation(const Quaternion& q)
{
    real q_w = q[0];
    real q_x = q[1];
    real q_y = q[2];
    real q_z = q[3];

    _data[0].x = 1.0f - ((2.0f * q_y * q_y) + (2.0f * q_z * q_z));
    _data[0].y = 2.0f * q_x * q_y - 2.0f * q_z * q_w;
    _data[0].z = 2.0f * q_x * q_z + 2.0f * q_y * q_w;

    _data[1].x = 2.0f * q_w * q_y + 2.0f * q_z * q_w;
    _data[1].y = 1.0f - ((2.0f * q_x * q_x) + (2.0f * q_z * q_z));
    _data[1].z = 2.0f * q_y * q_z - 2.0f * q_x * q_w;

    _data[2].x = 2.0f * q_x * q_z - 2.0f * q_y * q_w;
    _data[2].y = 2.0f * q_y * q_z + 2.0f * q_x * q_w;
    _data[2].z = 1 - ((2.0f * q_x * q_x) + (2.0f * q_y * q_y));
}

//==========================================================================================================================
//Inverse
//==========================================================================================================================
void Matrix3::SetInverse(void)
{
    real det = Determinate();

    if(det == 0.0f) return;

    // Find the minors based on the cofactors
    real c0x = _Cofactor(_data[1].y, _data[1].z, _data[2].y, _data[2].z);

    real c0y = _Cofactor(_data[1].x, _data[1].z, _data[2].x, _data[2].z);

    real c0z = _Cofactor(_data[1].x, _data[1].y, _data[2].x, _data[2].y);

    Vector3 colx {c0x, -c0y, c0z};

    real c1x = _Cofactor(_data[0].y, _data[0].z, _data[2].y, _data[2].z);

    real c1y = _Cofactor(_data[0].x, _data[0].z, _data[2].x, _data[2].z);

    real c1z = _Cofactor(_data[0].x, _data[0].y, _data[2].x, _data[2].y);

    Vector3 coly {-c1x, c1y, -c1z};

    real c2x = _Cofactor(_data[0].y, _data[0].z, _data[1].y, _data[1].z);

    real c2y = _Cofactor(_data[0].x, _data[0].z, _data[1].x, _data[1].z);

    real c2z = _Cofactor(_data[0].x, _data[0].y, _data[1].x, _data[1].y);

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

real Matrix3::Determinate(void) const
{
    return _data[0].x * (_data[1].y * _data[2].z - _data[2].y * _data[1].z)
         + _data[1].x * (_data[2].y * _data[0].z - _data[0].y * _data[2].z)
         + _data[2].x * (_data[0].y * _data[1].z - _data[1].y * _data[0].z);
}

//==========================================================================================================================
//Resettings
//==========================================================================================================================
void Matrix3::Reset(real val)
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
    Vector3 newCol0 {_data[0].x, _data[1].x, _data[2].x};
    Vector3 newCol1 {_data[0].y, _data[1].y, _data[2].y};
    Vector3 newCol2 {_data[0].z, _data[1].z, _data[2].z};

    _data[0] = newCol0;
    _data[1] = newCol1;
    _data[2] = newCol2;
}

void Matrix3::ComponentMulti(const Matrix3& mat)
{
    _data[0].x *= mat[0].x;
    _data[0].y *= mat[0].y;
    _data[0].z *= mat[0].z;

    _data[1].x *= mat[1].x;
    _data[1].y *= mat[1].y;
    _data[1].z *= mat[1].z;

    _data[2].x *= mat[2].x;
    _data[2].y *= mat[2].y;
    _data[2].z *= mat[2].z;
}

Matrix3 Matrix3::Transform(const Matrix3& mat) const
{
    Vector3 xCol 
    {
        _data[0].x * mat[0].x + _data[1].x * mat[0].y + _data[2].x * mat[0].z,
        _data[0].y * mat[0].x + _data[1].y * mat[0].y + _data[2].y * mat[0].z,
        _data[0].z * mat[0].x + _data[1].z * mat[0].y + _data[2].z * mat[0].z
    };

    Vector3 yCol
    {
        _data[0].x * mat[1].x + _data[1].x * mat[1].y + _data[2].x * mat[1].z,
        _data[0].y * mat[1].x + _data[1].y * mat[1].y + _data[2].y * mat[1].z,
        _data[0].z * mat[1].x + _data[1].z * mat[1].y + _data[2].z * mat[1].z
    };

    Vector3 zCol
    {
        _data[0].x * mat[2].x + _data[1].x * mat[2].y + _data[2].x * mat[2].z,
        _data[0].y * mat[2].x + _data[1].y * mat[2].y + _data[2].y * mat[2].z,
        _data[0].z * mat[2].x + _data[1].z * mat[2].y + _data[2].z * mat[2].z
    };

    return Matrix3(xCol, yCol, zCol);
}

Vector4 Matrix3::Transform(const Vector4& vec) const
{
    return Vector4( _data[0].x * vec.x + _data[1].x * vec.y + _data[2].x * vec.z,
                    _data[0].y * vec.x + _data[1].y * vec.y + _data[2].y * vec.z,
                    _data[0].z * vec.x + _data[1].z + vec.y + _data[2].z * vec.z,
                   0.0f);
}

//==========================================================================================================================
//
//Operator Overloads
//
//==========================================================================================================================
Matrix3& Matrix3::operator=(const Matrix3& mat) 
{
    _data[0].x = mat[0].x;
    _data[0].y = mat[0].y;
    _data[0].z = mat[0].z;

    _data[1].x = mat[1].x;
    _data[1].y = mat[1].y;
    _data[1].z = mat[1].z;

    _data[2].x = mat[2].x;
    _data[2].y = mat[2].y;
    _data[2].z = mat[2].z;

    return *this;
}

Matrix3 Matrix3::operator*(const Matrix3& mat) const
{
    Vector3 xCol 
    {
        _data[0].x * mat[0].x + _data[1].x * mat[0].y + _data[2].x * mat[0].z,
        _data[0].y * mat[0].x + _data[1].y * mat[0].y + _data[2].y * mat[0].z,
        _data[0].z * mat[0].x + _data[1].z * mat[0].y + _data[2].z * mat[0].z 

    };

    Vector3 yCol
    {
        _data[0].x * mat[1].x + _data[1].x * mat[1].y + _data[2].x * mat[1].z,
        _data[0].y * mat[1].x + _data[1].y * mat[1].y + _data[2].y * mat[1].z,
        _data[0].z * mat[1].x + _data[1].z * mat[1].y + _data[2].z * mat[1].z
    };

    Vector3 zCol
    {
        _data[0].x * mat[2].x + _data[1].x * mat[2].y + _data[2].x * mat[2].z,
        _data[0].y * mat[2].x + _data[1].y * mat[2].y + _data[2].y * mat[2].z,
        _data[0].z * mat[2].x + _data[1].z * mat[2].y + _data[2].z * mat[2].z
    };


    return Matrix3(xCol, yCol, zCol);
}

Vector4 Matrix3::operator*(const Vector4& vec) const
{
    return Vector4( _data[0].x * vec.x + _data[1].x * vec.y + _data[2].x * vec.z,
                    _data[0].y * vec.x + _data[1].y * vec.y + _data[2].y * vec.z,
                    _data[0].z * vec.x + _data[1].z + vec.y + _data[2].z * vec.z,
                   0.0f);
}

Matrix3& Matrix3::operator/=(real val)
{
    _data.x.x /= val;
    _data.x.y /= val;
    _data.x.z /= val;
    
    _data.y.x /= val;
    _data.y.y /= val;
    _data.y.z /= val;

    _data.z.x /= val;
    _data.z.y /= val;
    _data.z.z /= val;

    return *this;
}

real Matrix3::_Cofactor(real c00, real c01, real c10, real c11) const
{
    return c00 * c11 - c10 * c01;
}