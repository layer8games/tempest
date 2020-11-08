#include "stdafx.h"
#include <Engine/Matrix4.h>
using namespace TempestMath;

Matrix4::Matrix4(void)
    :
    _data(1.0f)
{  }

Matrix4::Matrix4(const real val)
    :
    _data(val)
{  }

Matrix4::Matrix4(const Matrix4& otherMatrix)
    :
    _data(otherMatrix.GetRawData())
{  }

Matrix4::Matrix4(glm::mat4 matrix)
    :
    _data(matrix)
{  }

glm::mat4 Matrix4::GetRawData(void) const
{
    return _data;
}

#include <iostream>

void Matrix4::MakeOrthographic(real right, real left, real bottom, real top, real nearPlane, real farPlane)
{
    std::cout << "left: " << left << " | right: " << right << std::endl;
    _data = glm::ortho(left, right, bottom, top, nearPlane, farPlane);
}

void Matrix4::MakePerspective(real fieldOfView, real aspectRatio, real nearPlane, real farPlane)
{
   _data = glm::perspective(fieldOfView, aspectRatio, nearPlane, farPlane);
}

Matrix4 Matrix4::CreateTranslationMatrix(real xVal, real yVal)
{
    Matrix4 mat{glm::translate(glm::mat4(1.0f), glm::vec3(xVal, yVal, 1.0f))};

    return mat;
}

Matrix4 Matrix4::CreateTranslationMatrix(real xVal, real yVal, real zVal)
{
    return Matrix4(glm::translate(glm::vec3(xVal, yVal, zVal)));
}

Matrix4 Matrix4::CreateTranslationMatrix(const Vector3& vec)
{
    return Matrix4(glm::translate(vec.GetRawData()));
}

void Matrix4::Translate(real xVal, real yVal)
{
    _data = glm::translate(glm::vec3(xVal, yVal, 0.0f));
}

void Matrix4::Translate(real xVal, real yVal, real zVal)
{
    _data = glm::translate(glm::vec3(xVal, yVal, zVal));
}

void Matrix4::Translate(const Vector2& vec)
{
    _data = glm::translate(glm::vec3(vec.GetX(), vec.GetY(), 0.0f));
}

void Matrix4::Translate(const Vector3& vec)
{
    _data = glm::translate(vec.GetRawData());
}

void Matrix4::Translate(const Vector4& vec)
{
    _data = glm::translate(glm::vec3(vec.GetRawData()));
}

Vector4 Matrix4::TransformInverse(const Vector4& vec) const
{
    return GetInverse() * vec;
}

Vector3 Matrix4::TransformInverse(const Vector3& vec) const
{
    return GetInverse() * vec;
}

Matrix4 Matrix4::CreateScale(real xVal, real yVal)
{
    return Matrix4(glm::scale(glm::vec3(xVal, yVal, 0.0f)));
}

Matrix4 Matrix4::CreateScale(real xVal, real yVal, real zVal)
{
    return Matrix4(glm::scale(glm::vec3(xVal, yVal, zVal)));
}

Matrix4 Matrix4::CreateScale(const Vector3& vec)
{
    return Matrix4(glm::scale(vec.GetRawData()));
}

Matrix4 Matrix4::CreateScale(const Vector2& vec)
{
    return Matrix4(glm::scale(glm::vec3(vec.GetX(), vec.GetY(), 0.0f)));
}

void Matrix4::Scale(real xVal, real yVal)
{
    _data = glm::scale(glm::vec3(xVal, yVal, 0.0f));
}

void Matrix4::Scale(real xVal, real yVal, real zVal)
{
    _data = glm::scale(glm::vec3(xVal, yVal, zVal));
}

void Matrix4::Scale(const Vector2& vec)
{
    _data = glm::scale(glm::vec3(vec.GetX(), vec.GetY(), 0.0f));
}

void Matrix4::Scale(const Vector3& vec)
{
    _data = glm::scale(vec.GetRawData());
}

void Matrix4::RotateX(real val)
{
    val = RADIAN(val);
    _data = glm::rotate(val, glm::vec3(1.0f, 0.0f, 0.0f));
}

void Matrix4::AddRotateX(real val)
{
    val = RADIAN(val);
    _data += glm::rotate(val, glm::vec3(1.0f, 0.0f, 0.0f));
}

void Matrix4::RotateY(real val)
{
    val = RADIAN(val);
    _data = glm::rotate(val, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Matrix4::AddRotateY(real val)
{
    val = RADIAN(val);

    _data += glm::rotate(val, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Matrix4::RotateZ(real val)
{
    val = RADIAN(val);
    _data = glm::rotate(val, glm::vec3(0.0f, 0.0f, 1.0f));
}

void Matrix4::AddRotateZ(real val)
{
    val = RADIAN(val);
    _data += glm::rotate(val, glm::vec3(0.0f, 0.0f, 1.0f));
}

void Matrix4::Rotate(const Quaternion& q)
{
    _data = glm::toMat4(q.GetRawData());
}

void Matrix4::SetInverse(void)
{
   _data = glm::inverse(_data);
}

void Matrix4::SetAsInverse(const Matrix4& mat)
{
    _data = glm::inverse(mat.GetRawData());
}

Matrix4 Matrix4::GetInverse(void) const
{
    return Matrix4(glm::inverse(_data));
}

real Matrix4::Determinate(void) const
{
    return glm::determinant(_data);
}

void Matrix4::MakeIdentity(void)
{
    _data = glm::mat4(1.0f);
}

void Matrix4::Reset(real val)
{
    _data = glm::mat4(val);
}

void Matrix4::Transpose(void)
{
    _data = glm::transpose(_data);
}

Matrix4 Matrix4::LookAt(const Point3& cameraPos, const Point3& target, const Vector3& up)
{
    return Matrix4(glm::lookAt(cameraPos.GetRawData(), target.GetRawData(), up.GetRawData()));
}

void Matrix4::SetLookAt(const Point3& cameraPos, const Point3& target, const Vector3& up)
{
   _data = glm::lookAt(cameraPos.GetRawData(), target.GetRawData(), up.GetRawData());
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

    glm::mat4 mat{1.0f};

    Vector4 xAxis{cosYaw, 0.0f, -sinYaw, 0.0f};
    Vector4 yAxis{sinYaw * sinPitch, cosPitch, cosYaw * sinPitch, 0.0f};
    Vector4 zAxis{sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw, 0.0f};

    mat[0].x = xAxis.GetX();
    mat[0].y = yAxis.GetX();
    mat[0].z = zAxis.GetX();
    mat[0].w = 0.0f;

    mat[1].x = xAxis.GetY();
    mat[1].y = yAxis.GetY();
    mat[1].z = zAxis.GetY();
    mat[1].w = 0.0f;

    mat[2].x = xAxis.GetZ();
    mat[2].y = yAxis.GetZ();
    mat[2].z = zAxis.GetZ();
    mat[2].w = 0.0f;

    mat[3] = glm::vec4(-xAxis.Dot(cameraPos), -yAxis.Dot(cameraPos), -zAxis.Dot(cameraPos), 1.0f);

    return Matrix4(mat);
}

void Matrix4::SetFPSView(const Vector4& cameraPos, real pitch, real yaw)
{
   assert(pitch >= -90.0f);
    assert(pitch <= 90.0f);
    assert(yaw >= 0.0f);
    assert(yaw <= 360.0f);

    real cosPitch = real_cos(pitch);
    real sinPitch = real_sin(pitch);
    real cosYaw 	 = real_cos(yaw);
    real sinYaw   = real_sin(yaw);

    _data = glm::mat4(1.0f);

    Vector4 xAxis{cosYaw, 0.0f, -sinYaw, 0.0f};
    Vector4 yAxis{sinYaw * sinPitch, cosPitch, cosYaw * sinPitch, 0.0f};
    Vector4 zAxis{sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw, 0.0f};

    _data[0].x = xAxis.GetX();
    _data[0].y = yAxis.GetX();
    _data[0].z = zAxis.GetX();
    _data[0].w = 0.0f;

    _data[1].x = xAxis.GetY();
    _data[1].y = yAxis.GetY();
    _data[1].z = zAxis.GetY();
    _data[1].w = 0.0f;

    _data[2].x = xAxis.GetZ();
    _data[2].y = yAxis.GetZ();
    _data[2].z = zAxis.GetZ();
    _data[2].w = 0.0f;

    _data[3] = glm::vec4(-xAxis.Dot(cameraPos), -yAxis.Dot(cameraPos), -zAxis.Dot(cameraPos), 1.0f);
}

Matrix4& Matrix4::operator=(const Matrix4& mat) 
{
    _data = mat.GetRawData();
    return *this;
}

Matrix4 Matrix4::operator*(const Matrix4& mat) const
{
    return Matrix4(_data * mat.GetRawData());
}

Vector2 Matrix4::operator*(const Vector2& vec) const
{
    glm::vec3 result = _data * glm::vec4(vec.GetRawData(), 0.0f, 0.0f);
    return Vector2(result.x, result.y);
}

Vector3 Matrix4::operator*(const Vector3& vec) const
{
    glm::vec3 result = _data * glm::vec4(vec.GetRawData(), 0.0f);
    return Vector3(result.x, result.y, result.z);
}

Vector4 Matrix4::operator*(const Vector4& vec) const
{
    glm::vec4 result = _data * vec.GetRawData();
    return Vector4(result.x, result.y, result.z, result.w);
}

Matrix4& Matrix4::operator/=(real val)
{
   _data /= val;
   return *this;
}