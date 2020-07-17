#include "stdafx.h"
#include <Engine/GameObject3D.h>
using namespace Tempest;

GameObject3D::GameObject3D(void)
    :
    _name(),
    _shader(nullptr),
    _mesh(nullptr),
    _level(nullptr),
    _boundingBox(),
    _activeUpdate(true),
    _activeRender(true),
    _modelToWorldCache(),
    _scale(1.0f),
    _pixelScale(1.0f),
    _position(0.0f),
    _orientation(0.0f),
    _color(1.0f),
    _texture(nullptr)
{  }

GameObject3D::~GameObject3D(void)
{  }

void GameObject3D::Init(string filepath)
{
    // TODO: Create default 3D shader, add to ShaderManager
    //SetShader(TE::ShaderManager::Instance()->GetShader(_defaultShaderID));
    _mesh->LoadOBJ(filepath);

    /*TM::Point4 topRight(1.0f, 1.0f, 0.0f, 1.0f);
    TM::Point4 topLeft(-1.0f, 1.0f, 0.0f, 1.0f);
    TM::Point4 bottomRight(1.0f, -1.0f, 0.0f, 1.0f);
    TM::Point4 bottomLeft(-1.0f, -1.0f, 0.0f, 1.0f);

    TM::Point2 top(0.0f, 0.5f);

    TexCoord uvTopLeft{0.0f, 0.0f};
    TexCoord uvTopRight{1.0f, 0.0f};
    TexCoord uvBottomLeft{0.0f, 1.0f};
    TexCoord uvBottomRight(1.0f, 1.0f);

    Vertex one{ };
    one.position = topLeft;
    one.texCoord = uvTopLeft;

    Vertex two{ };
    two.position = topRight;
    two.texCoord = uvTopRight;

    Vertex three{ };
    three.position = bottomRight;
    three.texCoord = uvBottomRight;

    Vertex four{ };
    four.position = bottomLeft;
    four.texCoord = uvBottomLeft;


    _mesh->AddVertex(one);
    _mesh->AddVertex(two);
    _mesh->AddVertex(three);

    _mesh->AddVertex(one);
    _mesh->AddVertex(three);
    _mesh->AddVertex(four);

    _mesh->InitOpenGLData();

    _shader = ShaderManager::Instance()->GetShader(SPRITE);*/
}

void GameObject3D::Init(string filepath, U32 shaderID)
{
    SetShader(ShaderManager::Instance()->GetShader(shaderID));
    _mesh->LoadOBJ(filepath);
}

void GameObject3D::v_Render(void)
{
    DefaultRender();
}

void GameObject3D::v_Awake(void)
{
    DefaultAwake();
}

void GameObject3D::v_OnEvent(Event event)
{  }

void GameObject3D::v_OnCollide(U32 otherObjectID)
{  }

void GameObject3D::UpdateInternals(void)
{
    _CalculateCachedData();
}

const TM::Matrix4& GameObject3D::GetModelMatrix(void) const
{
    return _modelToWorldCache;
}

const TM::Matrix4 GameObject3D::GetModelMatrixRot(void) const
{
    TM::Matrix4 mat = _modelToWorldCache; 
    mat.Translate(0.0f, 0.0f, 0.0f);
    return mat;
}

const string GameObject3D::GetName(void) const
{
    return _name;
}

void GameObject3D::SetName(string name)
{
    _name = name;
}

bool GameObject3D::GetActiveUpdate(void) const
{
    return _activeUpdate;
}

void GameObject3D::SetActiveUpdate(bool state)
{
    _activeUpdate = state;
}

bool GameObject3D::GetActiveRender(void) const
{
    return _activeRender;
}

void GameObject3D::SetActiveRender(bool state)
{
    _activeRender = state;
}

const TM::Point3& GameObject3D::GetPosition(void) const
{
    return _position;
}

void GameObject3D::SetPosition(const TM::Point3& pos)
{
    _position = pos;
    _boundingBox.SetCenter(_position);
}

void GameObject3D::SetPosition(const TM::Vector3& pos)
{
    _position.x = pos.x;
    _position.y = pos.y;
    _position.z = pos.z;
    _boundingBox.SetCenter(_position);
}

void GameObject3D::SetPosition(F32 xVal, F32 yVal, F32 zVal)
{
    _position.x = xVal;
    _position.y = yVal;
    _position.z = zVal;
    _boundingBox.SetCenter(_position);
}

void GameObject3D::AddScaledPosition(const TM::Vector4& pos, F32 scale)
{
    _position.AddScaledVector(pos, scale);
    _boundingBox.SetCenter(_position);
}

void GameObject3D::AddScaledPosition(const TM::Vector3& pos, F32 scale)
{
    _position.AddScaledVector(pos, scale);
    _boundingBox.SetCenter(_position);
}

void GameObject3D::AddScaledPosition(const TM::Point3& point, F32 scale)
{
    _position.AddScaledPoint(point, scale);
    _boundingBox.SetCenter(_position);
}

void GameObject3D::SetPixelScale(const TM::Vector3& size)
{
    _pixelScale = size;
    _scale = _scale * _pixelScale;
    _boundingBox.SetHalfDimensions(_scale);
}

const TM::Vector3& GameObject3D::GetPixelScale(void) const
{
    return _pixelScale;
}

const TM::Vector3& GameObject3D::GetScale(void) const
{
    return _scale;
}

void GameObject3D::SetScale(const TM::Vector3& scale)
{
    _scale = scale * _pixelScale;
    _boundingBox.SetHalfDimensions(_scale);
}

void GameObject3D::SetScale(F32 val)
{
    _scale = _pixelScale * val;
    _boundingBox.SetHalfDimensions(_scale);
}

void GameObject3D::SetScale(F32 xVal, F32 yVal, F32 zVal)
{
    _scale.x = xVal * _pixelScale.x;
    _scale.y = yVal * _pixelScale.y;
    _scale.z = zVal * _pixelScale.z;
    _boundingBox.SetHalfDimensions(_scale);
}

const TM::Quaternion& GameObject3D::GetOrientation(void) const
{
    return _orientation;
}

void GameObject3D::SetOrientation(const TM::Quaternion& q)
{
    _orientation = q;
}

void GameObject3D::SetOrientation(const TM::Vector3& vec)
{
    _orientation.RotateByEuler(vec);
}

void GameObject3D::SetOrientation(real yaw, real pitch, real roll)
{
    _orientation.RotateByEuler(yaw, pitch, roll);
}

void GameObject3D::AddOrientation(const TM::Vector3& vec)
{
    _orientation.AddEuler(vec);
}

void GameObject3D::AddOrientation(real yaw, real pitch, real roll)
{
    _orientation.AddEuler(yaw, pitch, roll);
}

void GameObject3D::NormalizeOrientation(void)
{
    _orientation.Normalize();
}

void GameObject3D::SetColor(const Color& col)
{
    _color = col;
}

void GameObject3D::SetColor(F32 red, F32 green, F32 blue)
{
    _color[0] = red;
    _color[1] = green;
    _color[2] = blue;
}

const Color& GameObject3D::GetColor(void) const
{
    return _color;
}

bool GameObject3D::OverlapCheck(const shared_ptr<GameObject3D> other)
{
    return _boundingBox.TestCollision(other->GetBounding());
}

const TC::AABB& GameObject3D::GetBounding(void) const
{
    return _boundingBox;
}

void GameObject3D::SetTexture(p_Texture texture)
{
    _texture = texture;
            
    if(_shader != nullptr)
    {
        _shader->SetUniform("has_texture", true);
    }
}

p_Texture GameObject3D::GetTexture(void) const
{
    return _texture;
}

void GameObject3D::BindTexture(bool state)
{
    if(_texture != nullptr)
    {
        _texture->Bind(state);
    }
}

const p_Shader GameObject3D::GetShader(void) const
{
    return _shader;
}

void GameObject3D::SetShader(const p_Shader shader)
{
    _shader = shader;
}

p_Mesh GameObject3D::GetMesh(void) const
{
    return _mesh;
}

void GameObject3D::SetMesh(p_Mesh mesh)
{
    _mesh = mesh;
}

void GameObject3D::DefaultAwake(void)
{
    UpdateInternals();
}

void GameObject3D::DefaultRender(void)
{
    _shader->Use(true);
    _mesh->BindVAO(true);

    if(_texture != nullptr)
    {
        BindTexture(true);
    }

    // Remove later
    _shader->SetUniform("sprite_color", _color);
    //
    _shader->SetUniform("model", GetModelMatrix());

    _mesh->v_Render();

    _shader->Use(false);
    _mesh->BindVAO(false);

    if(_texture != nullptr)
    {
        BindTexture(false);
    }
}

void GameObject3D::DefaultUpdate(void)
{
    UpdateInternals();
}

void GameObject3D::_CalculateCachedData(void)
{
    // TODO: Actually test this, once rendering is back up and running. 
    _modelToWorldCache.Rotate(_orientation);
    _modelToWorldCache.Translate(_position);
    _modelToWorldCache.Scale(_scale);
}

Level* GameObject3D::GetLevel(void) const
{
    return _level;
}

void GameObject3D::SetLevel(Level* level)
{
    _level = level;
}