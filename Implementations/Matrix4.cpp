#include <Engine/Matrix4.h>

using namespace TempestMath;

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

Matrix4::Matrix4(const real val)
:
_data{Vector4(val, 0.0f, 0.0f, 0.0f),
      Vector4(0.0f, val, 0.0f, 0.0f),
      Vector4(0.0f, 0.0f, val, 0.0f),
      Vector4(0.0f, 0.0f, 0.0f, 1.0f)}
{  }

Matrix4::Matrix4( real m00, real m01, real m02, real m03,
                  real m10, real m11, real m12, real m13,
                  real m20, real m21, real m22, real m23,
                  real m30, real m31, real m32, real m33)
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
const std::vector<real> Matrix4::GetElems(void) const
{
    std::vector<real> elems;
    
    elems.push_back(_data[0].x);
    elems.push_back(_data[0].y);
    elems.push_back(_data[0].z);
    elems.push_back(_data[0].w);
    elems.push_back(_data[1].x);
    elems.push_back(_data[1].y);
    elems.push_back(_data[1].z);
    elems.push_back(_data[1].w);
    elems.push_back(_data[2].x);
    elems.push_back(_data[2].y);
    elems.push_back(_data[2].z);
    elems.push_back(_data[2].w);
    elems.push_back(_data[3].x);
    elems.push_back(_data[3].y);
    elems.push_back(_data[3].z);
    elems.push_back(_data[3].w);

    return elems;
}

//==========================================================================================================================
//Projections
//==========================================================================================================================
void Matrix4::MakeOrthographic(real left, real right, real bottom, real top, real nearPlane, real farPlane)
{
    //Reset Matrix4
    MakeIdentity();

    assert(right - left != 0.0f);
    assert(top - bottom != 0.0f);
    assert(farPlane - nearPlane != 0.0f);

    //Diagnal
    _data[0].x = 2.0f / (right - left);
    _data[1].y = 2.0f / (top - bottom);
    _data[2].z = -2.0f / (farPlane - nearPlane);
    _data[3].w = 1.0f;

    //Transform "Vector4"
    _data[3].x = -(right + left) / (right - left);
    _data[3].y = -(top + bottom) / (top - bottom);
    _data[3].z = -(farPlane + nearPlane) / (farPlane - nearPlane);
}

void Matrix4::MakePerspective(real fieldOfView, real aspectRatio, real nearPlane, real farPlane)
{
    assert(nearPlane - farPlane != 0.0f);

    real S = 1.0f / real_tan(RADIAN(0.5f * fieldOfView));

    //Reset Matrix4 
    MakeIdentity();

    _data[0].x = S / aspectRatio;
    _data[1].y = S;
    _data[2].z = (nearPlane + farPlane) / (nearPlane - farPlane);
    _data[2].w = -1.0f;
    _data[3].z = (2.0f * nearPlane * farPlane) / (nearPlane - farPlane);
}

//==========================================================================================================================
//Translations
//==========================================================================================================================
Matrix4 Matrix4::Translate(real xVal, real yVal)
{
    Matrix4 mat{1.0f};

    mat[3].x = xVal;
    mat[3].y = yVal;

    return mat;
}

Matrix4 Matrix4::Translate(real xVal, real yVal, real zVal)
{
    Matrix4 mat{1.0f};

    mat[3].x = xVal;
    mat[3].y = yVal;
    mat[3].z = zVal;

    return mat;	
}

Matrix4 Matrix4::Translate(const Vector4& vec)
{
    Matrix4 mat{1.0f};

    mat[3].x = vec.x;
    mat[3].y = vec.y;
    mat[3].z = vec.z;

    return mat;	
}

void Matrix4::SetTranslate(real xVal, real yVal)
{
    _data[3].x = xVal;
    _data[3].y = yVal;
}

void Matrix4::SetTranslate(real xVal, real yVal, real zVal)
{
    _data[3].x = xVal;
    _data[3].y = yVal;
    _data[3].z = zVal;
}

void Matrix4::SetTranslate(const Vector2& vec)
{
    _data[3].x = vec.x;
    _data[3].y = vec.y;
    _data[3].z = 0.0f;
}

void Matrix4::SetTranslate(const Vector3 & vec)
{
    _data[3].x = vec.x;
    _data[3].y = vec.y;
    _data[3].z = vec.z;
}


void Matrix4::SetTranslate(const Vector4& vec)
{
    _data[3].x = vec.x;
    _data[3].y = vec.y;
    _data[3].z = vec.z;
}

Vector4 Matrix4::TransformInverse(const Vector4& vec) const
{
    Vector4 tmp = vec;

    tmp.x -= _data[3].x;
    tmp.y -= _data[3].y;
    tmp.z -= _data[3].z;

    return Vector4
    {
        tmp.x * _data[0].x +
        tmp.y * _data[0].y + 
        tmp.z * _data[0].z,

        tmp.x * _data[1].x + 
        tmp.y * _data[1].y + 
        tmp.z * _data[1].z,

        tmp.x * _data[2].x +
        tmp.y * _data[2].y + 
        tmp.z * _data[2].z, 
        
        0.0f
    };
}

Point4 Matrix4::TransformInverse(const Point4& vec) const
{
    Point4 tmp = vec;

    tmp.x -= _data[3].x;
    tmp.y -= _data[3].y;
    tmp.z -= _data[3].z;

    return Point4
    {
        tmp.x * _data[0].x +
        tmp.y * _data[0].y +
        tmp.z * _data[0].z,

        tmp.x * _data[1].x +
        tmp.y * _data[1].y +
        tmp.z * _data[1].z,

        tmp.x * _data[2].x +
        tmp.y * _data[2].y +
        tmp.z * _data[2].z,
        
        1.0f
    };
}

//==========================================================================================================================
//Scaling
//==========================================================================================================================
Matrix4 Matrix4::Scale(real xVal, real yVal)
{
    Matrix4 mat{1.0f};

    mat[0].x = xVal;
    mat[1].y = yVal;

    return mat;
}

Matrix4 Matrix4::Scale(real xVal, real yVal, real zVal)
{
    Matrix4 mat{1.0f};

    mat[0].x = xVal;
    mat[1].y = yVal;
    mat[2].z = zVal;

    return mat;
}

Matrix4 Matrix4::Scale(const Vector4& vec)
{
    Matrix4 mat{1.0f};

    mat[0].x = vec.x;
    mat[1].y = vec.y;
    mat[2].z = vec.z;

    return mat;
}

Matrix4 Matrix4::Scale(const Vector3& vec)
{
    Matrix4 mat{1.0f};

    mat[0].x = vec.x;
    mat[1].y = vec.y;
    mat[2].z = vec.z;

    return mat;
}

Matrix4 Matrix4::Scale(const Vector2& vec)
{
    Matrix4 mat{1.0f};

    mat[0].x = vec.x;
    mat[1].y = vec.y;
    mat[2].z = 0.0f;

    return mat;
}

void Matrix4::SetScale(real xVal, real yVal)
{
    MakeIdentity();

    _data[0].x = xVal;
    _data[1].y = yVal;
}

void Matrix4::SetScale(real xVal, real yVal, real zVal)
{
    MakeIdentity();

    _data[0].x = xVal;
    _data[1].y = yVal;
    _data[2].z = zVal;
}

void Matrix4::SetScale(const Vector2& vec)
{
    MakeIdentity();

    _data[0].x = vec.x;
    _data[1].y = vec.y;
}

void Matrix4::SetScale(const Vector3& vec)
{
    MakeIdentity();

    _data[0].x = vec.x;
    _data[1].y = vec.y;
    _data[2].z = vec.z;
}

void Matrix4::SetScale(const Vector4& vec)
{
    MakeIdentity();

    _data[0].x = vec.x;
    _data[1].y = vec.y;
    _data[2].z = vec.z;
}

//==========================================================================================================================
//Rotations
//==========================================================================================================================
Matrix4 Matrix4::RotateX(real val)
{
    val = RADIAN(val);
    Matrix4 mat{1.0f};

    mat[1].y = real_cos(val);
    mat[1].z = -real_sin(val);
    mat[2].y = real_sin(val);
    mat[2].z = real_cos(val);

    return mat;
}

Matrix4 Matrix4::RotateY(real val)
{
    val = RADIAN(val);
    Matrix4 mat{1.0f};

    mat[0].x = real_cos(val);
    mat[0].z = real_sin(val);
    mat[2].x = -real_sin(val);
    mat[2].z = real_cos(val);

    return mat;
}

Matrix4 Matrix4::RotateZ(real val)
{
    val = RADIAN(val);
    Matrix4 mat{1.0f};

    mat[0].x = real_cos(val);
    mat[0].y = -real_sin(val);
    mat[1].x = real_sin(val);
    mat[1].y = real_cos(val);

    return mat;
}

void Matrix4::SetRotateX(real val)
{
    val = RADIAN(val);

    MakeIdentity();

    _data[1].y = real_cos(val);
    _data[1].z = -real_sin(val);
    _data[2].y = real_sin(val);
    _data[2].z = real_cos(val);
}

void Matrix4::AddRotateX(real val)
{
    val = RADIAN(val);

    _data[1].y += real_cos(val);
    _data[1].z += -real_sin(val);
    _data[2].y += real_sin(val);
    _data[2].z += real_cos(val);
}

void Matrix4::SetRotateY(real val)
{
    val = RADIAN(val);

    MakeIdentity();

    _data[0].x = real_cos(val);
    _data[0].z = real_sin(val);
    _data[2].x = -real_sin(val);
    _data[2].z = real_cos(val);
}

void Matrix4::AddRotateY(real val)
{
    val = RADIAN(val);

    _data[0].x += real_cos(val);
    _data[0].y += real_sin(val);
    _data[2].x += -real_sin(val);
    _data[2].y += real_cos(val);	
}

void Matrix4::SetRotateZ(real val)
{
    val = RADIAN(val);

    MakeIdentity();

    _data[0].x = real_cos(val);
    _data[0].y = -real_sin(val);
    _data[1].x = real_sin(val);
    _data[1].y = real_cos(val);
}

void Matrix4::AddRotateZ(real val)
{
    val = RADIAN(val);

    _data[0].x += real_cos(val);
    _data[0].y += -real_sin(val);
    _data[1].x += real_sin(val);
    _data[1].y += real_cos(val);
}

void Matrix4::SetRotate(real xVal, real yVal, real zVal)
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

void Matrix4::AddRotation(real xVal, real yVal, real zVal)
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

void Matrix4::SetOrientation(const Quaternion& q)
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

void Matrix4::SetOrientationAndPosition(const Quaternion& q, const Vector4& v)
{
    SetOrientation(q);
    SetTranslate(v);
}

void Matrix4::SetOrientationAndPosition(const Quaternion& q, const Point2& p)
{
    SetOrientation(q);
    SetTranslate(p);
}

void Matrix4::SetOrientationAndPosition(const Quaternion& q, const Point3& p)
{
    SetOrientation(q);
    
    SetTranslate(p);
}

void Matrix4::SetOrientationAndPosition(const Quaternion& q, const Point4& p)
{
    SetOrientation(q);
    
    _data[3].x = p.x;
    _data[3].y = p.y;
    _data[3].z = p.z;
}

void Matrix4::SetOrientationAndPosition(const Quaternion& q, const Point4& p)
{
    SetOrientation(q);
    
    _data[3].x = p.x;
    _data[3].y = p.y;
    _data[3].z = p.z;
}

//==========================================================================================================================
//Inverse
//==========================================================================================================================

void Matrix4::SetInverse(void)
{
    real det = Determinate();

    if(det == 0.0f) return;

    real c00 = _Cofactor(Vector4(_data[1].y, _data[1].z, _data[1].w, 0.0f),
                         Vector4(_data.z.y, _data.z.z, _data.z.w, 0.0f),
                         Vector4(_data.w.y, _data.w.z, _data.w.w, 0.0f));

    real c01 = _Cofactor(Vector4(_data[1].x, _data[1].z, _data[1].w, 0.0f),
                         Vector4(_data.z.x, _data.z.z, _data.z.w, 0.0f),
                         Vector4(_data.w.x, _data.w.z, _data.w.w, 0.0f));

    real c02 = _Cofactor(Vector4(_data[1].x, _data[1].y, _data[1].w, 0.0f),
                         Vector4(_data.z.x, _data.z.y, _data.z.w, 0.0f),
                         Vector4(_data.w.x, _data.w.y, _data.w.w, 0.0f));

    real c03 = _Cofactor(Vector4(_data[1].x, _data[1].y, _data[1].z, 0.0f),
                         Vector4(_data.z.x, _data.z.y, _data.z.z, 0.0f),
                         Vector4(_data.w.x, _data.w.y, _data.w.z, 0.0f));

    Vector4 colx {c00, -c01, c02, -c03};

    real c10 = _Cofactor(Vector4(_data.x.y, _data.x.z, _data.x.w, 0.0f),
                         Vector4(_data.z.y, _data.z.z, _data.z.w, 0.0f),
                         Vector4(_data.w.y, _data.w.z, _data.w.w, 0.0f));

    real c11 = _Cofactor(Vector4(_data.x.x, _data.x.z, _data.x.w, 0.0f),
                         Vector4(_data.z.x, _data.z.z, _data.z.w, 0.0f),
                         Vector4(_data.w.x, _data.w.z, _data.w.w, 0.0f));

    real c12 = _Cofactor(Vector4(_data.x.x, _data.x.y, _data.x.w, 0.0f),
                         Vector4(_data.z.x, _data.z.y, _data.z.w, 0.0f),
                         Vector4(_data.w.x, _data.w.y, _data.w.w, 0.0f));

    real c13 = _Cofactor(Vector4(_data.x.x, _data.x.y, _data.x.z, 0.0f),
                         Vector4(_data.z.x, _data.z.y, _data.z.z, 0.0f),
                         Vector4(_data.w.x, _data.w.y, _data.w.z, 0.0f));

    Vector4 coly {-c10, c11, -c12, c13};

    real c20 = _Cofactor(Vector4(_data.x.y, _data.x.z, _data.x.w, 0.0f),
                         Vector4(_data[1].y, _data[1].z, _data[1].w, 0.0f),
                         Vector4(_data.w.y, _data.w.z, _data.w.w, 0.0f));

    real c21 = _Cofactor(Vector4(_data.x.x, _data.x.z, _data.x.w, 0.0f),
                         Vector4(_data[1].x, _data[1].z, _data[1].w, 0.0f),
                         Vector4(_data.w.x, _data.w.z, _data.w.w, 0.0f));

    real c22 = _Cofactor(Vector4(_data.x.x, _data.x.y, _data.x.w, 0.0f),
                         Vector4(_data[1].x, _data[1].y, _data[1].w, 0.0f),
                         Vector4(_data.w.x, _data.w.y, _data.w.w, 0.0f));

    real c23 = _Cofactor(Vector4(_data.x.x, _data.x.y, _data.x.z, 0.0f),
                         Vector4(_data[1].x, _data[1].y, _data[1].z, 0.0f),
                         Vector4(_data.w.x, _data.w.y, _data.w.z, 0.0f));

    Vector4 colz {c20, -c21, c22, -c23};

    real c30 = _Cofactor(Vector4(_data.x.y, _data.x.z, _data.x.w, 0.0f),
                         Vector4(_data[1].y, _data[1].z, _data[1].w, 0.0f),
                         Vector4(_data.z.y, _data.z.z, _data.z.w, 0.0f));

    real c31 = _Cofactor(Vector4(_data.x.x, _data.x.z, _data.x.w, 0.0f),
                         Vector4(_data[1].x, _data[1].z, _data[1].w, 0.0f),
                         Vector4(_data.z.x, _data.z.z, _data.z.w, 0.0f));

    real c32 = _Cofactor(Vector4(_data.x.x, _data.x.y, _data.x.w, 0.0f),
                         Vector4(_data[1].x, _data[1].y, _data[1].w, 0.0f),
                         Vector4(_data.z.x, _data.z.y, _data.z.w, 0.0f));

    real c33 = _Cofactor(Vector4(_data.x.x, _data.x.y, _data.x.z, 0.0f),
                         Vector4(_data[1].x, _data[1].y, _data[1].z, 0.0f),
                         Vector4(_data.z.x, _data.z.y, _data.z.z, 0.0f));

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

real Matrix4::Determinate(void) const
{
    //This equation is very difficult to understand. It was ultimately taking from 3d Math Primer, page 165, Determinate of 
    //4x4 Matrix4 in expanded form.
    //m11 through m41 represent the cofactors of those sections of the Matrix4, which are added together to get the value
    real m11 = _data[0][0] * ( _data[1][1] * (_data[2][2] * _data[3][3] - _data[3][2] * _data[2][3])
                             + _data[2][1] * (_data[3][2] * _data[1][3] - _data[1][2] * _data[3][3])
                             + _data[3][1] * (_data[1][2] * _data[2][3] - _data[2][2] * _data[1][3]) );

    real m21 = _data[1][0] * ( _data[0][1] * (_data[2][2] * _data[3][3] - _data[3][2] * _data[2][3])
                             + _data[2][1] * (_data[3][2] * _data[0][3] - _data[0][2] * _data[3][3])
                             + _data[3][1] * (_data[0][2] * _data[2][3] - _data[2][2] * _data[0][3]) );

    real m31 = _data[2][0] * ( _data[0][1] * (_data[1][2] * _data[3][3] - _data[3][2] * _data[1][3])
                             + _data[1][1] * (_data[3][2] * _data[0][3] - _data[0][2] * _data[3][3])
                             + _data[3][1] * (_data[0][2] * _data[1][3] - _data[1][2] * _data[0][3]) );

    real m41 = _data[3][0] * ( _data[0][1] * (_data[1][2] * _data[2][3] - _data[2][2] * _data[1][3])
                             + _data[1][1] * (_data[2][2] * _data[0][3] - _data[0][2] * _data[2][3])
                             + _data[2][1] * (_data[0][2] * _data[1][3] - _data[1][2] * _data[0][3]) );

    return m11 - m21 + m31 - m41;
}



//==========================================================================================================================
//Resettings
//==========================================================================================================================
void Matrix4::Reset(real val)
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
    Vector4 newCol0 {_data[0].x, _data[1].x, _data[2].x, _data[3].x};
    Vector4 newCol1 {_data[0].y, _data[1].y, _data[2].y, _data[3].y};
    Vector4 newCol2 {_data[0].z, _data[1].z, _data[2].z, _data[3].z};
    Vector4 newCol3 {_data[0].w, _data[1].w, _data[2].w, _data[3].w};

    _data[0] = newCol0;
    _data[1] = newCol1;
    _data[2] = newCol2;
    _data[3] = newCol3;
}

void Matrix4::ComponentMulti(const Matrix4& mat)
{
    _data[0].x *= mat[0].x;
    _data[0].y *= mat[0].y;
    _data[0].z *= mat[0].z;
    _data[0].w *= mat[0].w;

    _data[1].x *= mat[1].x;
    _data[1].y *= mat[1].y;
    _data[1].z *= mat[1].z;
    _data[1].w *= mat[1].w;

    _data[2].x *= mat[2].x;
    _data[2].y *= mat[2].y;
    _data[2].z *= mat[2].z;
    _data[2].w *= mat[2].w;

    _data[3].x *= mat[3].x;
    _data[3].y *= mat[3].y;
    _data[3].z *= mat[3].z;
    _data[3].w *= mat[3].w;
}

Matrix4 Matrix4::Transform3x3(const Matrix4& mat) const
{
    Vector4 xCol 
    {
        _data[0].x * mat[0].x + _data[1].x * mat[0].y + _data[2].x * mat[0].z,
        _data[0].y * mat[0].x + _data[1].y * mat[0].y + _data[2].y * mat[0].z,
        _data[0].z * mat[0].x + _data[1].z * mat[0].y + _data[2].z * mat[0].z,
        0.0f
    };

    Vector4 yCol
    {
        _data[0].x * mat[1].x + _data[1].x * mat[1].y + _data[2].x * mat[1].z,
        _data[0].y * mat[1].x + _data[1].y * mat[1].y + _data[2].y * mat[1].z,
        _data[0].z * mat[1].x + _data[1].z * mat[1].y + _data[2].z * mat[1].z,
        0.0f
    };

    Vector4 zCol
    {
        _data[0].x * mat[2].x + _data[1].x * mat[2].y + _data[2].x * mat[2].z,
        _data[0].y * mat[2].x + _data[1].y * mat[2].y + _data[2].y * mat[2].z,
        _data[0].z * mat[2].x + _data[1].z * mat[2].y + _data[2].z * mat[2].z,
        0.0f
    };

    Vector4 wCol {0.0f, 0.0f, 0.0f, 1.0f};

    return Matrix4(xCol, yCol, zCol, wCol);
}

Vector4 Matrix4::Transform3x3(const Vector4& vec) const
{
    return Vector4(_data[0].x * vec.x + _data[1].x * vec.y + _data[2].x * vec.z,
                   _data[0].y * vec.x + _data[1].y * vec.y + _data[2].y * vec.z,
                   _data[0].z * vec.x + _data[1].z + vec.y + _data[2].z * vec.z,
                   _data[0].w * vec.x + _data[1].w + vec.y + _data[2].w + vec.z);
}

//==========================================================================================================================
//
//Look At Matrices
//
//==========================================================================================================================
Matrix4 Matrix4::LookAt(const Point4& cameraPos, const Point4& target, const Vector4& up)
{
    Matrix4 mat{1.0f};

    Vector4 zAxis = Vector4(cameraPos - target);
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

Matrix4 Matrix4::LookAt(const Point3& cameraPos, const Point3& target, const Vector3& up)
{
    Matrix4 mat{1.0f};

    Vector3 zAxis = Vector3(cameraPos - target);
    zAxis.Normalize();

    Vector3 xAxis = up.CrossProduct(zAxis);
    xAxis.Normalize();

    Vector3 yAxis = zAxis.CrossProduct(xAxis);
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

Matrix4 Matrix4::FPSView(const Vector4& cameraPos, real pitch, real yaw)
{
    assert(pitch >= -90.0f);
    assert(pitch <= 90.0f);
    assert(yaw >= 0.0f);
    assert(yaw <= 360.0f);

    real cosPitch = real_cos(pitch);
    real sinPitch = real_sin(pitch);
    real cosYaw 	 = real_cos(yaw);
    real sinYaw   = real_sin(yaw);

    Matrix4 mat{1.0f};

    Vector4 xAxis{cosYaw, 0.0f, -sinYaw, 0.0f};
    Vector4 yAxis{sinYaw * sinPitch, cosPitch, cosYaw * sinPitch, 0.0f};
    Vector4 zAxis{sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw, 0.0f};

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

void Matrix4::SetFPSView(const Vector4& cameraPos, real pitch, real yaw)
{
    assert(pitch >= -90.0f);
    assert(pitch <= 90.0f);
    assert(yaw >= 0.0f);
    assert(yaw <= 360.0f);

    real cosPitch = real_cos(pitch);
    real sinPitch = real_sin(pitch);
    real cosYaw   = real_cos(yaw);
    real sinYaw   = real_sin(yaw);

    Vector4 xAxis{cosYaw, 0.0f, -sinYaw, 0.0f};
    Vector4 yAxis{sinYaw * sinPitch, cosPitch, cosYaw * sinPitch, 0.0f};
    Vector4 zAxis{sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw, 0.0f};

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
    _data[0].x = mat[0].x;
    _data[0].y = mat[0].y;
    _data[0].z = mat[0].z;
    _data[0].w = mat[0].w;

    _data[1].x = mat[1].x;
    _data[1].y = mat[1].y;
    _data[1].z = mat[1].z;
    _data[1].w = mat[1].w;

    _data[2].x = mat[2].x;
    _data[2].y = mat[2].y;
    _data[2].z = mat[2].z;
    _data[2].w = mat[2].w;

    _data[3].x = mat[3].x;
    _data[3].y = mat[3].y;
    _data[3].z = mat[3].z;
    _data[3].w = mat[3].w;

    return *this;
}

Matrix4 Matrix4::operator*(const Matrix4& mat) const
{
    Vector4 xCol 
    {
        _data[0].x * mat[0].x + _data[1].x * mat[0].y + _data[2].x * mat[0].z + _data[3].x * mat[0].w,
        _data[0].y * mat[0].x + _data[1].y * mat[0].y + _data[2].y * mat[0].z + _data[3].y * mat[0].w,
        _data[0].z * mat[0].x + _data[1].z * mat[0].y + _data[2].z * mat[0].z + _data[3].z * mat[0].w,
        _data[0].w * mat[0].x + _data[1].w * mat[0].y + _data[2].w * mat[0].z + _data[3].w * mat[0].w,

    };

    Vector4 yCol
    {
        _data[0].x * mat[1].x + _data[1].x * mat[1].y + _data[2].x * mat[1].z + _data[3].x * mat[1].w,
        _data[0].y * mat[1].x + _data[1].y * mat[1].y + _data[2].y * mat[1].z + _data[3].y * mat[1].w,
        _data[0].z * mat[1].x + _data[1].z * mat[1].y + _data[2].z * mat[1].z + _data[3].z * mat[1].w,
        _data[0].w * mat[1].x + _data[1].w * mat[1].y + _data[2].w * mat[1].z + _data[3].w * mat[1].w,
    };

    Vector4 zCol
    {
        _data[0].x * mat[2].x + _data[1].x * mat[2].y + _data[2].x * mat[2].z + _data[3].x * mat[2].w,
        _data[0].y * mat[2].x + _data[1].y * mat[2].y + _data[2].y * mat[2].z + _data[3].y * mat[2].w,
        _data[0].z * mat[2].x + _data[1].z * mat[2].y + _data[2].z * mat[2].z + _data[3].z * mat[2].w,
        _data[0].w * mat[2].x + _data[1].w * mat[2].y + _data[2].w * mat[2].z + _data[3].w * mat[2].w,
    };

    Vector4 wCol
    {
        _data[0].x * mat[3].x + _data[1].x * mat[3].y + _data[2].x * mat[3].z + _data[3].x * mat[3].w,
        _data[0].y * mat[3].x + _data[1].y * mat[3].y + _data[2].y * mat[3].z + _data[3].y * mat[3].w,
        _data[0].z * mat[3].x + _data[1].z * mat[3].y + _data[2].z * mat[3].z + _data[3].z * mat[3].w,
        _data[0].w * mat[3].x + _data[1].w * mat[3].y + _data[2].w * mat[3].z + _data[3].w * mat[3].w,
    };

    return Matrix4(xCol, yCol, zCol, wCol);
}

Vector3 Matrix4::operator*(const Vector3& vec) const
{
    return Vector3(_data[0].x * vec.x + _data[1].x * vec.y + _data[2].x * vec.z + _data[3].x,
                   _data[0].y * vec.x + _data[1].y * vec.y + _data[2].y * vec.z + _data[3].y,
                   _data[0].z * vec.x + _data[1].z + vec.y + _data[2].z * vec.z + _data[3].z);
}

Vector4 Matrix4::operator*(const Vector4& vec) const
{
    return Vector4(_data[0].x * vec.x + _data[1].x * vec.y + _data[2].x * vec.z + _data[3].x * vec.w,
                   _data[0].y * vec.x + _data[1].y * vec.y + _data[2].y * vec.z + _data[3].y * vec.w,
                   _data[0].z * vec.x + _data[1].z + vec.y + _data[2].z * vec.z + _data[3].z * vec.w,
                   _data[0].w * vec.x + _data[1].w + vec.y + _data[2].w + vec.z + _data[3].w * vec.w);
}

Point3 Matrix4::operator*(const Point3& point) const
{
    return Point3(_data[0].x * point.x + _data[1].x * point.y + _data[2].x * point.z + _data[3].x,
                  _data[0].y * point.x + _data[1].y * point.y + _data[2].y * point.z + _data[3].y,
                  _data[0].z * point.x + _data[1].z + point.y + _data[2].z * point.z + _data[3].z);
}

Point4 Matrix4::operator*(const Point4& point) const
{
    return Point4(_data[0].x * point.x + _data[1].x * point.y + _data[2].x * point.z + _data[3].x * point.w,
                  _data[0].y * point.x + _data[1].y * point.y + _data[2].y * point.z + _data[3].y * point.w,
                  _data[0].z * point.x + _data[1].z + point.y + _data[2].z * point.z + _data[3].z * point.w,
                  _data[0].w * point.x + _data[1].w + point.y + _data[2].w + point.z + _data[3].w * point.w);
}

Matrix4& Matrix4::operator/=(real val)
{
    _data.x.x /= val;
    _data.x.y /= val;
    _data.x.z /= val;
    _data.x.w /= val;
    
    _data[1].x /= val;
    _data[1].y /= val;
    _data[1].z /= val;
    _data[1].w /= val;

    _data.z.x /= val;
    _data.z.y /= val;
    _data.z.z /= val;
    _data.z.w /= val;

    _data.w.x /= val;
    _data.w.y /= val;
    _data.w.z /= val;
    _data.w.w /= val;

    return *this;
}

real Matrix4::_Cofactor(const Vector4& col1, const Vector4& col2, const Vector4& col3) const
{
    return col1.x * (col2.y * col3.z - col3.y * col2.z)
         + col2.x * (col3.y * col1.z - col1.y * col3.z)
         + col3.x * (col1.y * col2.z - col2.y * col1.z);
}