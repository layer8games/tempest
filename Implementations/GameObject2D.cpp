#include "stdafx.h"
#include <Engine/GameObject2D.h>
using namespace Tempest;

U32 GameObject2D::_nextID = 1;
GameObject2D::GameObject2D(void)
    :
    _name(),
    _defaultPixelSize(32.0f),
    _scale(1.0f),
    _modelToWorldCache(),
    _position(0.0f),
    _scaleInPixels(32.0f, 32.0f),
    _orientation(0.0f),
    _color(1.0f),
    _boundingBox(),
    _texture(nullptr),
    _shader(nullptr),
    _mesh(make_shared<Mesh>()),
    _activeUpdate(true),
    _activeRender(true),
    _ID(_nextID)
{
    ++_nextID;
}

GameObject2D::GameObject2D(const GameObject2D& obj)
    :
    _modelToWorldCache(obj.GetModelMatrix()),
    _position(obj.GetPosition()),
    _scale(obj.GetScale()),
    _orientation(obj.GetOrientation()),
    _color(obj.GetColor()),
    _texture(obj.GetTexture()),
    _shader(obj.GetShader()),
    _activeUpdate(obj.GetActiveUpdate()),
    _activeRender(obj.GetActiveRender()),
    _ID(obj.GetID())
{  }

GameObject2D::~GameObject2D(void)
{  }

void GameObject2D::Init(void)
{
    TM::Point4 topRight(1.0f, 1.0f, 0.0f, 1.0f);
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

    _shader = ShaderManager::Instance()->GetShader(SPRITE);
}

void GameObject2D::v_Render(void)
{
    DefaultRender();
}

void GameObject2D::v_Awake(void)
{
    DefaultAwake();
}

void GameObject2D::UpdateInternals(void)
{
    _CalculateCachedData();
}

const TM::Matrix4& GameObject2D::GetModelMatrix(void) const
{
    return _modelToWorldCache;
}

const TM::Matrix4 GameObject2D::GetModelMatrixRot(void) const
{
    TM::Matrix4 mat = _modelToWorldCache;
    mat.SetTranslate(0.0f, 0.0f, 0.0f);
    return mat;
}

const bool GameObject2D::GetActive(void) const
{
    return _activeUpdate && _activeRender;
}

void GameObject2D::SetActive(bool state)
{
    if(!_activeUpdate || !_activeRender)
    {
        v_Awake();
    }

    _activeUpdate = state;
    _activeRender = state;
}

void GameObject2D::SetActive(void)
{
    v_Awake();
    _activeUpdate = true;
    _activeRender = true;
}

void GameObject2D::SetInactive(void)
{
    _activeUpdate = false;
    _activeRender = false;
}

const bool GameObject2D::GetActiveUpdate(void) const
{
    return _activeUpdate;
}

void GameObject2D::SetActiveUpdate(bool state)
{
    _activeUpdate = state;
}

void GameObject2D::SetActiveUpdate(void)
{
    _activeUpdate = true;
}

void GameObject2D::SetInactiveUpdate(void)
{
    _activeUpdate = false;
}

const bool GameObject2D::GetActiveRender(void) const
{
    return _activeRender;
}

void GameObject2D::SetActiveRender(bool state)
{
    _activeRender = state;
}

void GameObject2D::SetActiveRender(void)
{
    _activeRender = true;
}

void GameObject2D::SetInactiveRender(void)
{
    _activeRender = false;
}

U32 GameObject2D::GetID(void) const
{
    return _ID;
}

void GameObject2D::SetName(string name)
{
    _name = name;
}

string GameObject2D::GetName(void) const
{
    return _name;
}

const TM::Point2& GameObject2D::GetPosition(void) const
{
    return _position;
}

void GameObject2D::SetPosition(const TM::Point2& pos)
{
    _position = pos;
    _boundingBox.SetCenter(_position);
}

void GameObject2D::SetPosition(F32 xVal, F32 yVal)
{
    _position.x = xVal;
    _position.y = yVal;
    _boundingBox.SetCenter(_position);
}

void GameObject2D::SetPositionX(F32 xval)
{
    _position.x = xval;
    _boundingBox.SetCenter(_position);
}

void GameObject2D::SetPositionY(F32 yVal)
{
    _position.y = yVal;
    _boundingBox.SetCenter(_position);
}

void GameObject2D::AddPosition(const TM::Point2& newPosition)
{
    _position += newPosition;
}

void GameObject2D::AddPosition(const TM::Vector2& newPosition)
{
    _position += newPosition;
}

void GameObject2D::SetDefaultPixelSize(F32 scale)
{
    _defaultPixelSize = scale;
}

const TM::Vector2& GameObject2D::GetScaleInPixels(void) const
{
    return _scaleInPixels;
}

F32 GameObject2D::GetScale(void) const
{
    return _scale;
}

void GameObject2D::SetScaleInPixels(const TM::Vector2& scale)
{
    _scaleInPixels = scale;
    _boundingBox.SetHalfDimensions(_scaleInPixels);
}

void GameObject2D::SetScaleInPixels(F32 xVal, F32 yVal)
{
    _scaleInPixels.x = xVal;
    _scaleInPixels.y = yVal;
    _boundingBox.SetHalfDimensions(_scaleInPixels);
}

void GameObject2D::SetScale(F32 val)
{
    _scale = val;
    _scaleInPixels = _defaultPixelSize * val;
    _boundingBox.SetHalfDimensions(_scaleInPixels);
}

real GameObject2D::GetOrientation(void) const
{
    return _orientation;
}

void GameObject2D::SetOrientation(real angle)
{
    _orientation = angle;
    _ClampOrientation();
}

void GameObject2D::AddOrientation(real angle)
{
    _orientation += angle;
    _ClampOrientation();
}

void GameObject2D::SetColor(const Color& col)
{
    _color = col;
}

void GameObject2D::SetColor(F32 red, F32 green, F32 blue)
{
    _color[0] = red;
    _color[1] = green;
    _color[2] = blue;
}

const Color& GameObject2D::GetColor(void) const
{
    return _color;
}

bool GameObject2D::OverlapCheck(const shared_ptr<GameObject2D> other)
{
    return _boundingBox.TestCollision(other->GetBounding());
}

const TC::AABB& GameObject2D::GetBounding(void) const
{
    return _boundingBox;
}

void GameObject2D::SetTexture(p_Texture texture)
{
    _texture = texture;
    _shader->SetUniform("has_texture", true);
}

p_Texture GameObject2D::GetTexture(void) const
{
    return _texture;
}

void GameObject2D::BindTexture(bool state)
{
    _texture->Bind(state);
}

const p_Shader GameObject2D::GetShader(void) const
{
    return _shader;
}

void GameObject2D::SetShader(const p_Shader shader)
{
    _shader = shader;
}

void GameObject2D::SetMesh(p_Mesh mesh)
{
    _mesh = mesh;
}

void GameObject2D::DefaultAwake(void)
{
    UpdateInternals();
}

void GameObject2D::DefaultRender(void)
{
    _shader->Use(true);
    _mesh->BindVAO(true);

    if(_texture != nullptr)
    {
        BindTexture(true);
    }

    _shader->SetUniform("sprite_color", _color);
    _shader->SetUniform("model", GetModelMatrix());

    _mesh->v_Render();

    _shader->Use(false);
    _mesh->BindVAO(false);

    if(_texture != nullptr)
    {
        BindTexture(false);
    }
}

void GameObject2D::DefaultUpdate(void)
{
    UpdateInternals();
}

void GameObject2D::_CalculateCachedData(void)
{
    _modelToWorldCache.SetRotateZ(_orientation);
    _modelToWorldCache.SetTranslate(_position);
    _modelToWorldCache = _modelToWorldCache * TM::Matrix4::Scale(_scaleInPixels);
}

void GameObject2D::_ClampOrientation(void)
{
    if(_orientation > 360.0f)
    {
        _orientation -= 360.0f;
    }
    else if(_orientation < -360.0f)
    {
        _orientation += 360.0f;
    }
}