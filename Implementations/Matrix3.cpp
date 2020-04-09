#include <Engine/Matrix3.h>

using namespace TempestMath;

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Matrix3::Matrix3(void)
    :
    column1(1.0f, 0.0f, 0.0f),
    column2(0.0f, 1.0f, 0.0f),
    column3(0.0f, 0.0f, 1.0f)
{  }

Matrix3::Matrix3(const Vector3& x, const Vector3& y, const Vector3& z)
    :    
    column1(x),
    column2(y),
    column3(z)
{  }

Matrix3::Matrix3(const Vector4& x, const Vector4& y, const Vector4& z)
    :
    column1(x), 
    column2(y),
    column3(z)
{  }


Matrix3::Matrix3(const real val)
    :
    column1(val, 0.0f, 0.0f),
    column2(0.0f, val, 0.0f),
    column3(0.0f, 0.0f, val)
{  }

Matrix3::Matrix3( real m00, real m01, real m02,
                  real m10, real m11, real m12,
                  real m20, real m21, real m22 )
    :
    column1(m00, m01, m02),
    column2(m10, m11, m12),
    column3(m20, m21, m22)
{  }

Matrix3::Matrix3(const Matrix3& otherMatrix)
    :
    column1(otherMatrix.column1),
    column2(otherMatrix.column2),
    column3(otherMatrix.column3)
{  }

//==========================================================================================================================
//
//Matrix3 functions
//
//==========================================================================================================================
const std::vector<real> Matrix3::GetElems(void) const
{
    std::vector<real> elems;
    
    elems.push_back(column1.x);
    elems.push_back(column1.y);
    elems.push_back(column1.z);
    elems.push_back(column2.x);
    elems.push_back(column2.y);
    elems.push_back(column2.z);
    elems.push_back(column3.x);
    elems.push_back(column3.y);
    elems.push_back(column3.z);

    return elems;
}


//==========================================================================================================================
//Scaling
//==========================================================================================================================
Matrix3 Matrix3::Scale(real xVal, real yVal)
{
    Matrix3 mat{1.0f};

    mat.column1.x = xVal;
    mat.column2.y = yVal;

    return mat;
}

Matrix3 Matrix3::Scale(real xVal, real yVal, real zVal)
{
    Matrix3 mat{1.0f};

    mat.column1.x = xVal;
    mat.column2.y = yVal;
    mat.column3.z = zVal;

    return mat;
}

Matrix3 Matrix3::Scale(const Vector3& vec)
{
    Matrix3 mat{1.0f};

    mat.column1.x = vec.x;
    mat.column2.y = vec.y;
    mat.column3.z = vec.z;

    return mat;
}

Matrix3 Matrix3::Scale(const Vector4& vec)
{
    Matrix3 mat{1.0f};

    mat.column1.x = vec.x;
    mat.column2.y = vec.y;
    mat.column3.z = vec.z;

    return mat;
}

void Matrix3::SetScale(real xVal, real yVal)
{
    MakeIdentity();

    column1.x = xVal;
    column2.y = yVal;
}

void Matrix3::SetScale(real xVal, real yVal, real zVal)
{
    MakeIdentity();

    column1.x = xVal;
    column2.y = yVal;
    column3.z = zVal;
}

void Matrix3::SetScale(const Vector2& vec)
{
    MakeIdentity();

    column1.x = vec.x;
    column2.y = vec.y;
    column3.z = 1.0f;
}

void Matrix3::SetScale(const Vector3& vec)
{
    MakeIdentity();

    column1.x = vec.x;
    column2.y = vec.y;
    column3.z = vec.z;
}

void Matrix3::SetScale(const Vector4& vec)
{
    MakeIdentity();

    column1.x = vec.x;
    column2.y = vec.y;
    column3.z = vec.z;
}

//==========================================================================================================================
//Rotations
//==========================================================================================================================
Matrix3 Matrix3::RotateX(real val)
{
    val = RADIAN(val);
    Matrix3 mat{1.0f};

    mat.column2.y = real_cos(val);
    mat.column2.z = -real_sin(val);
    mat.column3.y = real_sin(val);
    mat.column3.z = real_cos(val);

    return mat;
}

Matrix3 Matrix3::RotateY(real val)
{
    val = RADIAN(val);
    Matrix3 mat{1.0f};

    mat.column1.x = real_cos(val);
    mat.column1.z = real_sin(val);
    mat.column3.x = -real_sin(val);
    mat.column3.z = real_cos(val);

    return mat;
}

Matrix3 Matrix3::RotateZ(real val)
{
    val = RADIAN(val);
    Matrix3 mat{1.0f};

    mat.column1.x = real_cos(val);
    mat.column1.y = -real_sin(val);
    mat.column2.x = real_sin(val);
    mat.column2.y = real_cos(val);

    return mat;
}

void Matrix3::SetRotateX(real val)
{
    val = RADIAN(val);

    MakeIdentity();

    column2.y = real_cos(val);
    column2.z = -real_sin(val);
    column3.y = real_sin(val);
    column3.z = real_cos(val);
}

void Matrix3::AddRotateX(real val)
{
    val = RADIAN(val);

    column2.y += real_cos(val);
    column2.z += -real_sin(val);
    column3.y += real_sin(val);
    column3.z += real_cos(val);
}

void Matrix3::SetRotateY(real val)
{
    val = RADIAN(val);

    MakeIdentity();

    column1.x = real_cos(val);
    column1.z = real_sin(val);
    column3.x = -real_sin(val);
    column3.z = real_cos(val);
}

void Matrix3::AddRotateY(real val)
{
    val = RADIAN(val);

    column1.x += real_cos(val);
    column1.y += real_sin(val);
    column3.x += -real_sin(val);
    column3.y += real_cos(val);	
}

void Matrix3::SetRotateZ(real val)
{
    val = RADIAN(val);

    MakeIdentity();

    column1.x = real_cos(val);
    column1.y = -real_sin(val);
    column2.x = real_sin(val);
    column2.y = real_cos(val);
}

void Matrix3::AddRotateZ(real val)
{
    val = RADIAN(val);

    column1.x += real_cos(val);
    column1.y += -real_sin(val);
    column2.x += real_sin(val);
    column2.y += real_cos(val);
}

void Matrix3::SetRotate(real xVal, real yVal, real zVal)
{
    xVal = RADIAN(xVal);
    yVal = RADIAN(yVal);
    zVal = RADIAN(zVal);

    MakeIdentity();

    column1.x = real_cos(yVal) * real_cos(zVal);
    column1.y = -real_cos(yVal) * real_sin(zVal);
    column1.z = real_sin(yVal);
    column2.x = real_cos(xVal) * real_sin(zVal) + real_sin(xVal) * real_sin(yVal) * real_cos(zVal);
    column2.y = real_cos(xVal) * real_cos(zVal) - real_sin(xVal) * real_sin(yVal) * real_sin(zVal);
    column2.z = -real_sin(xVal) * real_cos(yVal);
    column3.x = real_sin(xVal) * real_sin(zVal) - real_cos(xVal) * real_sin(yVal) * real_cos(zVal);
    column3.y = real_sin(xVal) * real_cos(zVal) + real_cos(xVal) * real_sin(yVal) * real_sin(zVal);
    column3.z = real_cos(xVal) * real_cos(yVal);
}

void Matrix3::AddRotation(real xVal, real yVal, real zVal)
{
    xVal = RADIAN(xVal);
    yVal = RADIAN(yVal);
    zVal = RADIAN(zVal);

    column1.x += real_cos(yVal) * real_cos(zVal);
    column1.y += -real_cos(yVal) * real_sin(zVal);
    column1.z += real_sin(yVal);
    column2.x += real_cos(xVal) * real_sin(zVal) + real_sin(xVal) * real_sin(yVal) * real_cos(zVal);
    column2.y += real_cos(xVal) * real_cos(zVal) - real_sin(xVal) * real_sin(yVal) * real_sin(zVal);
    column2.z += -real_sin(xVal) * real_cos(yVal);
    column3.x += real_sin(xVal) * real_sin(zVal) - real_cos(xVal) * real_sin(yVal) * real_cos(zVal);
    column3.y += real_sin(xVal) * real_cos(zVal) + real_cos(xVal) * real_sin(yVal) * real_sin(zVal);
    column3.z += real_cos(xVal) * real_cos(yVal);
}

void Matrix3::SetOrientation(const Quaternion& q)
{
    real q_w = q.x;
    real q_x = q.y;
    real q_y = q.z;
    real q_z = q.w;

    column1.x = 1.0f - ((2.0f * q_y * q_y) + (2.0f * q_z * q_z));
    column1.y = 2.0f * q_x * q_y - 2.0f * q_z * q_w;
    column1.z = 2.0f * q_x * q_z + 2.0f * q_y * q_w;

    column2.x = 2.0f * q_w * q_y + 2.0f * q_z * q_w;
    column2.y = 1.0f - ((2.0f * q_x * q_x) + (2.0f * q_z * q_z));
    column2.z = 2.0f * q_y * q_z - 2.0f * q_x * q_w;

    column3.x = 2.0f * q_x * q_z - 2.0f * q_y * q_w;
    column3.y = 2.0f * q_y * q_z + 2.0f * q_x * q_w;
    column3.z = 1 - ((2.0f * q_x * q_x) + (2.0f * q_y * q_y));
}

//==========================================================================================================================
//Inverse
//==========================================================================================================================
void Matrix3::SetInverse(void)
{
    real det = Determinate();

    if(det == 0.0f) return;

    // Find the minors based on the cofactors
    real c0x = _Cofactor(column2.y, column2.z, column3.y, column3.z);

    real c0y = _Cofactor(column2.x, column2.z, column3.x, column3.z);

    real c0z = _Cofactor(column2.x, column2.y, column3.x, column3.y);

    Vector3 colx {c0x, -c0y, c0z};

    real c1x = _Cofactor(column1.y, column1.z, column3.y, column3.z);

    real c1y = _Cofactor(column1.x, column1.z, column3.x, column3.z);

    real c1z = _Cofactor(column1.x, column1.y, column3.x, column3.y);

    Vector3 coly {-c1x, c1y, -c1z};

    real c2x = _Cofactor(column1.y, column1.z, column2.y, column2.z);

    real c2y = _Cofactor(column1.x, column1.z, column2.x, column2.z);

    real c2z = _Cofactor(column1.x, column1.y, column2.x, column2.y);

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
    return column1.x * (column2.y * column3.z - column3.y * column2.z)
         + column2.x * (column3.y * column1.z - column1.y * column3.z)
         + column3.x * (column1.y * column2.z - column2.y * column1.z);
}

//==========================================================================================================================
//Resettings
//==========================================================================================================================
void Matrix3::Reset(real val)
{
    //Reset Matrix3
    column1 = Vector3(val, 0.0f, 0.0f);
    column2 = Vector3(0.0f, val, 0.0f);
    column3 = Vector3(0.0f, 0.0f, val);
}

//==========================================================================================================================
//Misc
//==========================================================================================================================
void Matrix3::Transpose(void)
{
    Vector3 newCol0 {column1.x, column2.x, column3.x};
    Vector3 newCol1 {column1.y, column2.y, column3.y};
    Vector3 newCol2 {column1.z, column2.z, column3.z};

    column1 = newCol0;
    column2 = newCol1;
    column3 = newCol2;
}

void Matrix3::ComponentMulti(const Matrix3& mat)
{
    column1.x *= mat.column1.x;
    column1.y *= mat.column1.y;
    column1.z *= mat.column1.z;

    column2.x *= mat.column2.x;
    column2.y *= mat.column2.y;
    column2.z *= mat.column2.z;

    column3.x *= mat.column3.x;
    column3.y *= mat.column3.y;
    column3.z *= mat.column3.z;
}

Matrix3 Matrix3::Transform(const Matrix3& mat) const
{
    Vector3 xCol 
    {
        column1.x * mat.column1.x + column2.x * mat.column1.y + column3.x * mat.column1.z,
        column1.y * mat.column1.x + column2.y * mat.column1.y + column3.y * mat.column1.z,
        column1.z * mat.column1.x + column2.z * mat.column1.y + column3.z * mat.column1.z
    };

    Vector3 yCol
    {
        column1.x * mat.column2.x + column2.x * mat.column2.y + column3.x * mat.column2.z,
        column1.y * mat.column2.x + column2.y * mat.column2.y + column3.y * mat.column2.z,
        column1.z * mat.column2.x + column2.z * mat.column2.y + column3.z * mat.column2.z
    };

    Vector3 zCol
    {
        column1.x * mat.column3.x + column2.x * mat.column3.y + column3.x * mat.column3.z,
        column1.y * mat.column3.x + column2.y * mat.column3.y + column3.y * mat.column3.z,
        column1.z * mat.column3.x + column2.z * mat.column3.y + column3.z * mat.column3.z
    };

    return Matrix3(xCol, yCol, zCol);
}

Vector4 Matrix3::Transform(const Vector4& vec) const
{
    return Vector4( column1.x * vec.x + column2.x * vec.y + column3.x * vec.z,
                    column1.y * vec.x + column2.y * vec.y + column3.y * vec.z,
                    column1.z * vec.x + column2.z + vec.y + column3.z * vec.z,
                   0.0f);
}

//==========================================================================================================================
//
//Operator Overloads
//
//==========================================================================================================================
Matrix3& Matrix3::operator=(const Matrix3& mat) 
{
    column1.x = mat.column1.x;
    column1.y = mat.column1.y;
    column1.z = mat.column1.z;

    column2.x = mat.column2.x;
    column2.y = mat.column2.y;
    column2.z = mat.column2.z;

    column3.x = mat.column3.x;
    column3.y = mat.column3.y;
    column3.z = mat.column3.z;

    return *this;
}

Matrix3 Matrix3::operator*(const Matrix3& mat) const
{
    Vector3 xCol 
    {
        column1.x * mat.column1.x + column2.x * mat.column1.y + column3.x * mat.column1.z,
        column1.y * mat.column1.x + column2.y * mat.column1.y + column3.y * mat.column1.z,
        column1.z * mat.column1.x + column2.z * mat.column1.y + column3.z * mat.column1.z 

    };

    Vector3 yCol
    {
        column1.x * mat.column2.x + column2.x * mat.column2.y + column3.x * mat.column2.z,
        column1.y * mat.column2.x + column2.y * mat.column2.y + column3.y * mat.column2.z,
        column1.z * mat.column2.x + column2.z * mat.column2.y + column3.z * mat.column2.z
    };

    Vector3 zCol
    {
        column1.x * mat.column3.x + column2.x * mat.column3.y + column3.x * mat.column3.z,
        column1.y * mat.column3.x + column2.y * mat.column3.y + column3.y * mat.column3.z,
        column1.z * mat.column3.x + column2.z * mat.column3.y + column3.z * mat.column3.z
    };


    return Matrix3(xCol, yCol, zCol);
}

Vector4 Matrix3::operator*(const Vector4& vec) const
{
    return Vector4( column1.x * vec.x + column2.x * vec.y + column3.x * vec.z,
                    column1.y * vec.x + column2.y * vec.y + column3.y * vec.z,
                    column1.z * vec.x + column2.z + vec.y + column3.z * vec.z,
                   0.0f);
}

Matrix3& Matrix3::operator/=(real val)
{
    column1.x /= val;
    column1.y /= val;
    column1.z /= val;
    
    column2.x /= val;
    column2.y /= val;
    column2.z /= val;

    column3.x /= val;
    column3.y /= val;
    column3.z /= val;

    return *this;
}

real Matrix3::_Cofactor(real c00, real c01, real c10, real c11) const
{
    return c00 * c11 - c10 * c01;
}