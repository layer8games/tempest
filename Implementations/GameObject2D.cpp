#include "stdafx.h"
#include <Engine/GameObject2D.h>
using namespace Tempest;

U32 GameObject2D::_nextID = 1;
GameObject2D::GameObject2D(void)
    :
    _modelToWorldCache(),
    _position(0.0f),
    _scale(32.0f),
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

void GameObject2D::UpdateInternals(void)
{
    _CalculateCachedData();
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
    _modelToWorldCache = _modelToWorldCache * TM::Matrix4::Scale(_scale);
}