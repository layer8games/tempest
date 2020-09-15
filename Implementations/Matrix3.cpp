#include "stdafx.h"
#include "Engine/Matrix3.h"
using namespace TempestMath;

Matrix3::Matrix3(void)
    :
    _data(1.0f)
{  }

Matrix3::Matrix3(const Vector3& x, const Vector3& y, const Vector3& z)
    :    
    _data(x.GetRawData(), y.GetRawData(), z.GetRawData())
{  }

Matrix3::Matrix3(const Vector4& x, const Vector4& y, const Vector4& z)
    :
    _data(x.GetRawData(), y.GetRawData(), z.GetRawData())
{  }


Matrix3::Matrix3(const real val)
    :
    _data(val)
{  }

Matrix3::Matrix3( real m00, real m01, real m02,
                  real m10, real m11, real m12,
                  real m20, real m21, real m22 )
    :
    _data(m00, m01, m02,
          m10, m11, m12,
          m20, m21, m22)
{  }

Matrix3::Matrix3(const Matrix3& otherMatrix)
    :
    _data(otherMatrix.GetRawData())
{  }

Matrix3::Matrix3(glm::mat3 matrix)
    :
    _data(matrix)
{  }

Matrix3 Matrix3::Scale(real xVal, real yVal, real zVal)
{
    
    return Matrix3(glm::scale(glm::vec3(xVal, yVal, zVal)));
}

Matrix3 Matrix3::Scale(const Vector3& vec)
{
    return Matrix3(glm::scale(vec.GetRawData()));
}

void Matrix3::SetScale(real xVal, real yVal, real zVal)
{
    _data = glm::scale(glm::vec3(xVal, yVal, zVal));
}

void Matrix3::SetScale(const Vector3& vec)
{
    _data = glm::scale(vec.GetRawData());
}

void Matrix3::RotateX(real val)
{
    val = RADIAN(val);
    _data = glm::rotate(val, glm::vec3(1.0f, 0.0f, 0.0f));
}

void Matrix3::AddRotateX(real val)
{
    val = RADIAN(val);
    _data += glm::rotate(val, glm::vec3(1.0f, 0.0f, 0.0f));
}

void Matrix3::RotateY(real val)
{
    val = RADIAN(val);
    _data = glm::rotate(val, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Matrix3::AddRotateY(real val)
{
    val = RADIAN(val);
    _data += glm::rotate(val, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Matrix3::RotateZ(real val)
{
    val = RADIAN(val);
    _data = glm::rotate(val, glm::vec3(0.0f, 0.0f, 1.0f));
}

void Matrix3::AddRotateZ(real val)
{
    val = RADIAN(val);
    _data += glm::rotate(val, glm::vec3(0.0f, 0.0f, 1.0f));
}

void Matrix3::SetOrientation(const Quaternion& q)
{
    _data = glm::toMat3(q.GetRawData());
}

void Matrix3::SetInverse(void)
{
   _data = glm::inverse(_data);
}

void Matrix3::SetAsInverse(const Matrix3& mat)
{
    _data = glm::inverse(mat.GetRawData());
}

Matrix3 Matrix3::GetInverse(void) const
{
    return Matrix3(glm::inverse(_data));
}

real Matrix3::Determinate(void) const
{
    return glm::determinant(_data);
}

void Matrix3::MakeIdentity(void)
{
     _data = glm::mat3(1.0f);
}

void Matrix3::Reset(real val)
{
    _data = glm::mat4(val);
}

void Matrix3::Transpose(void)
{
    _data = glm::transpose(_data);
}

void Matrix3::ComponentMulti(const Matrix3& mat)
{
    _data = glm::matrixCompMult(_data, mat.GetRawData());
}

Matrix3& Matrix3::operator=(const Matrix3& mat) 
{
    _data = mat.GetRawData();

    return *this;
}

Matrix3 Matrix3::operator*(const Matrix3& mat) const
{
    return Matrix3(_data * mat.GetRawData());
}

Vector3 Matrix3::operator*(const Vector3& vec) const
{
    glm::vec3 transformed = _data * vec.GetRawData();
    return Vector3(transformed.x, transformed.y, transformed.z);

}

Matrix3& Matrix3::operator/=(real val)
{
    _data /= val;

    return *this;
}

glm::mat3 Matrix3::GetRawData(void) const
{
    return _data;
}
