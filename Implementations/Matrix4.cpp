#include "stdafx.h"
#include <Engine/Matrix4.h>
using namespace TempestMath;

Matrix4::Matrix4(void)
    :
    column1(1.0f, 0.0f, 0.0f, 0.0f),
    column2(0.0f, 1.0f, 0.0f, 0.0f),
    column3(0.0f, 0.0f, 1.0f, 0.0f),
    column4(0.0f, 0.0f, 0.0f, 1.0f)
{  }

Matrix4::Matrix4(const Vector4& x, const Vector4& y, const Vector4& z)
    :
    column1(x),
    column2(y),
    column3(z), 
    column4(0.0f, 0.0f, 0.0f, 1.0f)
{  }

Matrix4::Matrix4(const Vector4& x, const Vector4& y, const Vector4& z, const Vector4& w)
    :
    column1(x), 
    column2(y),
    column3(z), 
    column4(w)
{  }

Matrix4::Matrix4(const real val)
    :
    column1(val, 0.0f, 0.0f, 0.0f),
    column2(0.0f, val, 0.0f, 0.0f),
    column3(0.0f, 0.0f, val, 0.0f),
    column4(0.0f, 0.0f, 0.0f, 1.0f)
{  }

Matrix4::Matrix4( real m00, real m01, real m02, real m03,
                  real m10, real m11, real m12, real m13,
                  real m20, real m21, real m22, real m23,
                  real m30, real m31, real m32, real m33)
    :
    column1(m00, m01, m02, m03),
    column2(m10, m11, m12, m13),
    column3(m20, m21, m22, m23),
    column4(m30, m31, m32, m33)
{  }

Matrix4::Matrix4(const Matrix4& otherMatrix)
    :
    column1(otherMatrix.column1),
    column2(otherMatrix.column2),
    column3(otherMatrix.column3),
    column4(otherMatrix.column4)
{  }

const std::vector<real> Matrix4::GetElems(void) const
{
    std::vector<real> elems;
    
    elems.push_back(column1.x);
    elems.push_back(column1.y);
    elems.push_back(column1.z);
    elems.push_back(column1.w);
    elems.push_back(column2.x);
    elems.push_back(column2.y);
    elems.push_back(column2.z);
    elems.push_back(column2.w);
    elems.push_back(column3.x);
    elems.push_back(column3.y);
    elems.push_back(column3.z);
    elems.push_back(column3.w);
    elems.push_back(column4.x);
    elems.push_back(column4.y);
    elems.push_back(column4.z);
    elems.push_back(column4.w);

    return elems;
}

void Matrix4::Update(const Quaternion& rotation, const Point3& position, const Vector3 scale) const
{

}

void Matrix4::MakeOrthographic(real left, real right, real bottom, real top, real nearPlane, real farPlane)
{
    //Reset Matrix4
    MakeIdentity();

    assert(right - left != 0.0f);
    assert(top - bottom != 0.0f);
    assert(farPlane - nearPlane != 0.0f);

    //Diagnal
    column1.x = 2.0f / (right - left);
    column2.y = 2.0f / (top - bottom);
    column3.z = -2.0f / (farPlane - nearPlane);
    column4.w = 1.0f;

    //Transform "Vector4"
    column4.x = -(right + left) / (right - left);
    column4.y = -(top + bottom) / (top - bottom);
    column4.z = -(farPlane + nearPlane) / (farPlane - nearPlane);
}

void Matrix4::MakePerspective(real fieldOfView, real aspectRatio, real nearPlane, real farPlane)
{
    assert(nearPlane - farPlane != 0.0f);

    real S = 1.0f / real_tan(RADIAN(0.5f * fieldOfView));

    //Reset Matrix4 
    MakeIdentity();

    column1.x = S / aspectRatio;
    column2.y = S;
    column3.z = (nearPlane + farPlane) / (nearPlane - farPlane);
    column3.w = -1.0f;
    column4.z = (2.0f * nearPlane * farPlane) / (nearPlane - farPlane);
}

Matrix4 Matrix4::CreateTranslationMatrix(real xVal, real yVal)
{
    Matrix4 mat{1.0f};

    mat.column4.x = xVal;
    mat.column4.y = yVal;

    return mat;
}

Matrix4 Matrix4::CreateTranslationMatrix(real xVal, real yVal, real zVal)
{
    Matrix4 mat{1.0f};

    mat.column4.x = xVal;
    mat.column4.y = yVal;
    mat.column4.z = zVal;

    return mat;	
}

Matrix4 Matrix4::CreateTranslationMatrix(const Vector4& vec)
{
    Matrix4 mat{1.0f};

    mat.column4.x = vec.x;
    mat.column4.y = vec.y;
    mat.column4.z = vec.z;

    return mat;	
}

void Matrix4::Translate(real xVal, real yVal)
{
    column4.x = xVal;
    column4.y = yVal;
}

void Matrix4::Translate(real xVal, real yVal, real zVal)
{
    column4.x = xVal;
    column4.y = yVal;
    column4.z = zVal;
}

void Matrix4::Translate(const Point2& point)
{
    column4.x = point.x;
    column4.y = point.y;
    column4.z = 0.0f;
}

void Matrix4::Translate(const Point3& point)
{
    column4.x = point.x;
    column4.y = point.y;
    column4.z = point.z;
}

void Matrix4::Translate(const Vector2& vec)
{
    column4.x = vec.x;
    column4.y = vec.y;
    column4.z = 0.0f;
}

void Matrix4::Translate(const Vector3& vec)
{
    column4.x = vec.x;
    column4.y = vec.y;
    column4.z = vec.z;
}

void Matrix4::Translate(const Vector4& vec)
{
    column4.x = vec.x;
    column4.y = vec.y;
    column4.z = vec.z;
}

Vector4 Matrix4::TransformInverse(const Vector4& vec) const
{
    Vector4 tmp = vec;

    tmp.x -= column4.x;
    tmp.y -= column4.y;
    tmp.z -= column4.z;

    return Vector4
    {
        tmp.x * column1.x +
        tmp.y * column1.y + 
        tmp.z * column1.z,

        tmp.x * column2.x + 
        tmp.y * column2.y + 
        tmp.z * column2.z,

        tmp.x * column3.x +
        tmp.y * column3.y + 
        tmp.z * column3.z, 
        
        0.0f
    };
}

Point4 Matrix4::TransformInverse(const Point4& vec) const
{
    Point4 tmp = vec;

    tmp.x -= column4.x;
    tmp.y -= column4.y;
    tmp.z -= column4.z;

    return Point4
    {
        tmp.x * column1.x +
        tmp.y * column1.y +
        tmp.z * column1.z,

        tmp.x * column2.x +
        tmp.y * column2.y +
        tmp.z * column2.z,

        tmp.x * column3.x +
        tmp.y * column3.y +
        tmp.z * column3.z,
        
        1.0f
    };
}

Matrix4 Matrix4::CreateScale(real xVal, real yVal)
{
    Matrix4 mat{1.0f};

    mat.column1.x = xVal;
    mat.column2.y = yVal;

    return mat;
}

Matrix4 Matrix4::CreateScale(real xVal, real yVal, real zVal)
{
    Matrix4 mat{1.0f};

    mat.column1.x = xVal;
    mat.column2.y = yVal;
    mat.column3.z = zVal;

    return mat;
}

Matrix4 Matrix4::CreateScale(const Vector4& vec)
{
    Matrix4 mat{1.0f};

    mat.column1.x = vec.x;
    mat.column2.y = vec.y;
    mat.column3.z = vec.z;

    return mat;
}

Matrix4 Matrix4::CreateScale(const Vector3& vec)
{
    Matrix4 mat{1.0f};

    mat.column1.x = vec.x;
    mat.column2.y = vec.y;
    mat.column3.z = vec.z;

    return mat;
}

Matrix4 Matrix4::CreateScale(const Vector2& vec)
{
    Matrix4 mat{1.0f};

    mat.column1.x = vec.x;
    mat.column2.y = vec.y;
    mat.column3.z = 0.0f;

    return mat;
}

void Matrix4::Scale(real xVal, real yVal)
{
    MakeIdentity();

    column1.x = xVal;
    column2.y = yVal;
}

void Matrix4::Scale(real xVal, real yVal, real zVal)
{
    MakeIdentity();

    column1.x = xVal;
    column2.y = yVal;
    column3.z = zVal;
}

void Matrix4::Scale(const Vector2& vec)
{
    MakeIdentity();

    column1.x = vec.x;
    column2.y = vec.y;
}

void Matrix4::Scale(const Vector3& vec)
{
    MakeIdentity();

    column1.x = vec.x;
    column2.y = vec.y;
    column3.z = vec.z;
}

void Matrix4::Scale(const Vector4& vec)
{
    MakeIdentity();

    column1.x = vec.x;
    column2.y = vec.y;
    column3.z = vec.z;
}

void Matrix4::RotateX(real val)
{
    val = RADIAN(val);

    column2.y = real_cos(val);
    column2.z = -real_sin(val);
    column3.y = real_sin(val);
    column3.z = real_cos(val);
}

void Matrix4::AddRotateX(real val)
{
    val = RADIAN(val);

    column2.y += real_cos(val);
    column2.z += -real_sin(val);
    column3.y += real_sin(val);
    column3.z += real_cos(val);
}

void Matrix4::RotateY(real val)
{
    val = RADIAN(val);

    column1.x = real_cos(val);
    column1.z = real_sin(val);
    column3.x = -real_sin(val);
    column3.z = real_cos(val);
}

void Matrix4::AddRotateY(real val)
{
    val = RADIAN(val);

    column1.x += real_cos(val);
    column1.y += real_sin(val);
    column3.x += -real_sin(val);
    column3.y += real_cos(val);	
}

void Matrix4::RotateZ(real val)
{
    val = RADIAN(val);

    MakeIdentity();

    column1.x = real_cos(val);
    column1.y = -real_sin(val);
    column2.x = real_sin(val);
    column2.y = real_cos(val);
}

void Matrix4::AddRotateZ(real val)
{
    val = RADIAN(val);

    column1.x += real_cos(val);
    column1.y += -real_sin(val);
    column2.x += real_sin(val);
    column2.y += real_cos(val);
}

void Matrix4::SetRotate(real xVal, real yVal, real zVal)
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

void Matrix4::AddRotation(real xVal, real yVal, real zVal)
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

void Matrix4::Rotate(const Quaternion& q)
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

void Matrix4::SetInverse(void)
{
    real det = Determinate();

    if(det == 0.0f) return;

    real c00 = _Cofactor(Vector4(column2.y, column2.z, column2.w, 0.0f),
                         Vector4(column3.y, column3.z, column3.w, 0.0f),
                         Vector4(column4.y, column4.z, column4.w, 0.0f));

    real c01 = _Cofactor(Vector4(column2.x, column2.z, column2.w, 0.0f),
                         Vector4(column3.x, column3.z, column3.w, 0.0f),
                         Vector4(column4.x, column4.z, column4.w, 0.0f));

    real c02 = _Cofactor(Vector4(column2.x, column2.y, column2.w, 0.0f),
                         Vector4(column3.x, column3.y, column3.w, 0.0f),
                         Vector4(column4.x, column4.y, column4.w, 0.0f));

    real c03 = _Cofactor(Vector4(column2.x, column2.y, column2.z, 0.0f),
                         Vector4(column3.x, column3.y, column3.z, 0.0f),
                         Vector4(column4.x, column4.y, column4.z, 0.0f));

    Vector4 colx {c00, -c01, c02, -c03};

    real c10 = _Cofactor(Vector4(column1.y, column1.z, column1.w, 0.0f),
                         Vector4(column3.y, column3.z, column3.w, 0.0f),
                         Vector4(column4.y, column4.z, column4.w, 0.0f));

    real c11 = _Cofactor(Vector4(column1.x, column1.z, column1.w, 0.0f),
                         Vector4(column3.x, column3.z, column3.w, 0.0f),
                         Vector4(column4.x, column4.z, column4.w, 0.0f));

    real c12 = _Cofactor(Vector4(column1.x, column1.y, column1.w, 0.0f),
                         Vector4(column3.x, column3.y, column3.w, 0.0f),
                         Vector4(column4.x, column4.y, column4.w, 0.0f));

    real c13 = _Cofactor(Vector4(column1.x, column1.y, column1.z, 0.0f),
                         Vector4(column3.x, column3.y, column3.z, 0.0f),
                         Vector4(column4.x, column4.y, column4.z, 0.0f));

    Vector4 coly {-c10, c11, -c12, c13};

    real c20 = _Cofactor(Vector4(column1.y, column1.z, column1.w, 0.0f),
                         Vector4(column2.y, column2.z, column2.w, 0.0f),
                         Vector4(column4.y, column4.z, column4.w, 0.0f));

    real c21 = _Cofactor(Vector4(column1.x, column1.z, column1.w, 0.0f),
                         Vector4(column2.x, column2.z, column2.w, 0.0f),
                         Vector4(column4.x, column4.z, column4.w, 0.0f));

    real c22 = _Cofactor(Vector4(column1.x, column1.y, column1.w, 0.0f),
                         Vector4(column2.x, column2.y, column2.w, 0.0f),
                         Vector4(column4.x, column4.y, column4.w, 0.0f));

    real c23 = _Cofactor(Vector4(column1.x, column1.y, column1.z, 0.0f),
                         Vector4(column2.x, column2.y, column2.z, 0.0f),
                         Vector4(column4.x, column4.y, column4.z, 0.0f));

    Vector4 colz {c20, -c21, c22, -c23};

    real c30 = _Cofactor(Vector4(column1.y, column1.z, column1.w, 0.0f),
                         Vector4(column2.y, column2.z, column2.w, 0.0f),
                         Vector4(column3.y, column3.z, column3.w, 0.0f));

    real c31 = _Cofactor(Vector4(column1.x, column1.z, column1.w, 0.0f),
                         Vector4(column2.x, column2.z, column2.w, 0.0f),
                         Vector4(column3.x, column3.z, column3.w, 0.0f));

    real c32 = _Cofactor(Vector4(column1.x, column1.y, column1.w, 0.0f),
                         Vector4(column2.x, column2.y, column2.w, 0.0f),
                         Vector4(column3.x, column3.y, column3.w, 0.0f));

    real c33 = _Cofactor(Vector4(column1.x, column1.y, column1.z, 0.0f),
                         Vector4(column2.x, column2.y, column2.z, 0.0f),
                         Vector4(column3.x, column3.y, column3.z, 0.0f));

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
    real m11 = column1.x * ( column2.y * (column3.z * column4.w - column4.z * column3.w)
                             + column3.y * (column4.z * column2.w - column2.z * column4.w)
                             + column4.y * (column2.z * column3.w - column3.z * column2.w) );

    real m21 = column2.x * ( column1.y * (column3.z * column4.w - column4.z * column3.w)
                             + column3.y * (column4.z * column1.w - column1.z * column4.w)
                             + column4.y * (column1.z * column3.w - column3.z * column1.w) );

    real m31 = column3.x * ( column1.y * (column2.z * column4.w - column4.z * column2.w)
                             + column2.y * (column4.z * column1.w - column1.z * column4.w)
                             + column4.y * (column1.z * column2.w - column2.z * column1.w) );

    real m41 = column4.x * ( column1.y * (column2.z * column3.w - column3.z * column2.w)
                             + column2.y * (column3.z * column1.w - column1.z * column3.w)
                             + column3.y * (column1.z * column2.w - column2.z * column1.w) );

    return m11 - m21 + m31 - m41;
}

void Matrix4::Reset(real val)
{
    //Reset Matrix4
    column1 = Vector4(val, 0.0f, 0.0f, 0.0f);
    column2 = Vector4(0.0f, val, 0.0f, 0.0f);
    column3 = Vector4(0.0f, 0.0f, val, 0.0f);
    column4 = Vector4(0.0f, 0.0f, 0.0f, val);
}

void Matrix4::Transpose(void)
{
    Vector4 newCol0 {column1.x, column2.x, column3.x, column4.x};
    Vector4 newCol1 {column1.y, column2.y, column3.y, column4.y};
    Vector4 newCol2 {column1.z, column2.z, column3.z, column4.z};
    Vector4 newCol3 {column1.w, column2.w, column3.w, column4.w};

    column1 = newCol0;
    column2 = newCol1;
    column3 = newCol2;
    column4 = newCol3;
}

void Matrix4::ComponentMulti(const Matrix4& mat)
{
    column1.x *= mat.column1.x;
    column1.y *= mat.column1.y;
    column1.z *= mat.column1.z;
    column1.w *= mat.column1.w;

    column2.x *= mat.column2.x;
    column2.y *= mat.column2.y;
    column2.z *= mat.column2.z;
    column2.w *= mat.column2.w;

    column3.x *= mat.column3.x;
    column3.y *= mat.column3.y;
    column3.z *= mat.column3.z;
    column3.w *= mat.column3.w;

    column4.x *= mat.column4.x;
    column4.y *= mat.column4.y;
    column4.z *= mat.column4.z;
    column4.w *= mat.column4.w;
}

Matrix4 Matrix4::Transform3x3(const Matrix4& mat) const
{
    Vector4 xCol 
    {
        column1.x * mat.column1.x + column2.x * mat.column1.y + column3.x * mat.column1.z,
        column1.y * mat.column1.x + column2.y * mat.column1.y + column3.y * mat.column1.z,
        column1.z * mat.column1.x + column2.z * mat.column1.y + column3.z * mat.column1.z,
        0.0f
    };

    Vector4 yCol
    {
        column1.x * mat.column2.x + column2.x * mat.column2.y + column3.x * mat.column2.z,
        column1.y * mat.column2.x + column2.y * mat.column2.y + column3.y * mat.column2.z,
        column1.z * mat.column2.x + column2.z * mat.column2.y + column3.z * mat.column2.z,
        0.0f
    };

    Vector4 zCol
    {
        column1.x * mat.column3.x + column2.x * mat.column3.y + column3.x * mat.column3.z,
        column1.y * mat.column3.x + column2.y * mat.column3.y + column3.y * mat.column3.z,
        column1.z * mat.column3.x + column2.z * mat.column3.y + column3.z * mat.column3.z,
        0.0f
    };

    Vector4 wCol {0.0f, 0.0f, 0.0f, 1.0f};

    return Matrix4(xCol, yCol, zCol, wCol);
}

Vector4 Matrix4::Transform3x3(const Vector4& vec) const
{
    return Vector4(column1.x * vec.x + column2.x * vec.y + column3.x * vec.z,
                   column1.y * vec.x + column2.y * vec.y + column3.y * vec.z,
                   column1.z * vec.x + column2.z + vec.y + column3.z * vec.z,
                   column1.w * vec.x + column2.w + vec.y + column3.w + vec.z);
}

Matrix4 Matrix4::LookAt(const Point4& cameraPos, const Point4& target, const Vector4& up)
{
    Matrix4 mat{1.0f};

    Vector4 zAxis = Vector4(cameraPos - target);
    zAxis.Normalize();

    Vector4 xAxis = up.CrossProduct(zAxis);
    xAxis.Normalize();

    Vector4 yAxis = zAxis.CrossProduct(xAxis);
    yAxis.Normalize();

    mat.column1.x = xAxis.x;
    mat.column1.y = yAxis.x;
    mat.column1.z = zAxis.x;
    mat.column1.w = 0.0f;

    mat.column2.x = xAxis.y;
    mat.column2.y = yAxis.y;
    mat.column2.z = zAxis.y;
    mat.column2.w = 0.0f;

    mat.column3.x = xAxis.z;
    mat.column3.y = yAxis.z;
    mat.column3.z = zAxis.z;
    mat.column3.w = 0.0f;

    mat.column4 = Vector4(-xAxis.Dot(cameraPos), -yAxis.Dot(cameraPos), -zAxis.Dot(cameraPos), 1.0f);

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

    mat.column1.x = xAxis.x;
    mat.column1.y = yAxis.x;
    mat.column1.z = zAxis.x;
    mat.column1.w = 0.0f;

    mat.column2.x = xAxis.y;
    mat.column2.y = yAxis.y;
    mat.column2.z = zAxis.y;
    mat.column2.w = 0.0f;

    mat.column3.x = xAxis.z;
    mat.column3.y = yAxis.z;
    mat.column3.z = zAxis.z;
    mat.column3.w = 0.0f;

    mat.column4 = Vector4(-xAxis.Dot(cameraPos), -yAxis.Dot(cameraPos), -zAxis.Dot(cameraPos), 1.0f);

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

    column1.x = xAxis.x;
    column1.y = yAxis.x;
    column1.z = zAxis.x;
    column1.w = 0.0f;

    column2.x = xAxis.y;
    column2.y = yAxis.y;
    column2.z = zAxis.y;
    column2.w = 0.0f;

    column3.x = xAxis.z;
    column3.y = yAxis.z;
    column3.z = zAxis.z;
    column3.w = 0.0f;

    column4 = Vector4(-xAxis.Dot(cameraPos), -yAxis.Dot(cameraPos), -zAxis.Dot(cameraPos), 1.0f);		
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

    mat.column1.x = xAxis.x;
    mat.column1.y = yAxis.x;
    mat.column1.z = zAxis.x;
    mat.column1.w = 0.0f;

    mat.column2.x = xAxis.y;
    mat.column2.y = yAxis.y;
    mat.column2.z = zAxis.y;
    mat.column2.w = 0.0f;

    mat.column3.x = xAxis.z;
    mat.column3.y = yAxis.z;
    mat.column3.z = zAxis.z;
    mat.column3.w = 0.0f;

    mat.column4 = Vector4(-xAxis.Dot(cameraPos), -yAxis.Dot(cameraPos), -zAxis.Dot(cameraPos), 1.0f);

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

    column1.x = xAxis.x;
    column1.y = yAxis.x;
    column1.z = zAxis.x;
    column1.w = 0.0f;

    column2.x = xAxis.y;
    column2.y = yAxis.y;
    column2.z = zAxis.y;
    column2.w = 0.0f;

    column3.x = xAxis.z;
    column3.y = yAxis.z;
    column3.z = zAxis.z;
    column3.w = 0.0f;

    column4 = Vector4(-xAxis.Dot(cameraPos), -yAxis.Dot(cameraPos), -zAxis.Dot(cameraPos), 1.0f);	
}

Matrix4& Matrix4::operator=(const Matrix4& mat) 
{
    column1.x = mat.column1.x;
    column1.y = mat.column1.y;
    column1.z = mat.column1.z;
    column1.w = mat.column1.w;

    column2.x = mat.column2.x;
    column2.y = mat.column2.y;
    column2.z = mat.column2.z;
    column2.w = mat.column2.w;

    column3.x = mat.column3.x;
    column3.y = mat.column3.y;
    column3.z = mat.column3.z;
    column3.w = mat.column3.w;

    column4.x = mat.column4.x;
    column4.y = mat.column4.y;
    column4.z = mat.column4.z;
    column4.w = mat.column4.w;

    return *this;
}

Matrix4 Matrix4::operator*(const Matrix4& mat) const
{
    Vector4 xCol 
    {
        column1.x * mat.column1.x + column2.x * mat.column1.y + column3.x * mat.column1.z + column4.x * mat.column1.w,
        column1.y * mat.column1.x + column2.y * mat.column1.y + column3.y * mat.column1.z + column4.y * mat.column1.w,
        column1.z * mat.column1.x + column2.z * mat.column1.y + column3.z * mat.column1.z + column4.z * mat.column1.w,
        column1.w * mat.column1.x + column2.w * mat.column1.y + column3.w * mat.column1.z + column4.w * mat.column1.w,

    };

    Vector4 yCol
    {
        column1.x * mat.column2.x + column2.x * mat.column2.y + column3.x * mat.column2.z + column4.x * mat.column2.w,
        column1.y * mat.column2.x + column2.y * mat.column2.y + column3.y * mat.column2.z + column4.y * mat.column2.w,
        column1.z * mat.column2.x + column2.z * mat.column2.y + column3.z * mat.column2.z + column4.z * mat.column2.w,
        column1.w * mat.column2.x + column2.w * mat.column2.y + column3.w * mat.column2.z + column4.w * mat.column2.w,
    };

    Vector4 zCol
    {
        column1.x * mat.column3.x + column2.x * mat.column3.y + column3.x * mat.column3.z + column4.x * mat.column3.w,
        column1.y * mat.column3.x + column2.y * mat.column3.y + column3.y * mat.column3.z + column4.y * mat.column3.w,
        column1.z * mat.column3.x + column2.z * mat.column3.y + column3.z * mat.column3.z + column4.z * mat.column3.w,
        column1.w * mat.column3.x + column2.w * mat.column3.y + column3.w * mat.column3.z + column4.w * mat.column3.w,
    };

    Vector4 wCol
    {
        column1.x * mat.column4.x + column2.x * mat.column4.y + column3.x * mat.column4.z + column4.x * mat.column4.w,
        column1.y * mat.column4.x + column2.y * mat.column4.y + column3.y * mat.column4.z + column4.y * mat.column4.w,
        column1.z * mat.column4.x + column2.z * mat.column4.y + column3.z * mat.column4.z + column4.z * mat.column4.w,
        column1.w * mat.column4.x + column2.w * mat.column4.y + column3.w * mat.column4.z + column4.w * mat.column4.w,
    };

    return Matrix4(xCol, yCol, zCol, wCol);
}

Vector3 Matrix4::operator*(const Vector3& vec) const
{
    return Vector3(column1.x * vec.x + column2.x * vec.y + column3.x * vec.z + column4.x,
                   column1.y * vec.x + column2.y * vec.y + column3.y * vec.z + column4.y,
                   column1.z * vec.x + column2.z + vec.y + column3.z * vec.z + column4.z);
}

Vector4 Matrix4::operator*(const Vector4& vec) const
{
    return Vector4(column1.x * vec.x + column2.x * vec.y + column3.x * vec.z + column4.x * vec.w,
                   column1.y * vec.x + column2.y * vec.y + column3.y * vec.z + column4.y * vec.w,
                   column1.z * vec.x + column2.z + vec.y + column3.z * vec.z + column4.z * vec.w,
                   column1.w * vec.x + column2.w + vec.y + column3.w + vec.z + column4.w * vec.w);
}

Point3 Matrix4::operator*(const Point3& point) const
{
    return Point3(column1.x * point.x + column2.x * point.y + column3.x * point.z + column4.x,
                  column1.y * point.x + column2.y * point.y + column3.y * point.z + column4.y,
                  column1.z * point.x + column2.z + point.y + column3.z * point.z + column4.z);
}

Point4 Matrix4::operator*(const Point4& point) const
{
    return Point4(column1.x * point.x + column2.x * point.y + column3.x * point.z + column4.x * point.w,
                  column1.y * point.x + column2.y * point.y + column3.y * point.z + column4.y * point.w,
                  column1.z * point.x + column2.z + point.y + column3.z * point.z + column4.z * point.w,
                  column1.w * point.x + column2.w + point.y + column3.w + point.z + column4.w * point.w);
}

Matrix4& Matrix4::operator/=(real val)
{
    column1.x /= val;
    column1.y /= val;
    column1.z /= val;
    column1.w /= val;
    
    column2.x /= val;
    column2.y /= val;
    column2.z /= val;
    column2.w /= val;

    column3.x /= val;
    column3.y /= val;
    column3.z /= val;
    column3.w /= val;

    column4.x /= val;
    column4.y /= val;
    column4.z /= val;
    column4.w /= val;

    return *this;
}

real Matrix4::_Cofactor(const Vector4& col1, const Vector4& col2, const Vector4& col3) const
{
    return col1.x * (col2.y * col3.z - col3.y * col2.z)
         + col2.x * (col3.y * col1.z - col1.y * col3.z)
         + col3.x * (col1.y * col2.z - col2.y * col1.z);
}