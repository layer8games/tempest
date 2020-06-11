#include "stdafx.h"
#include <Engine/GameObject3D.h>
using namespace Tempest;

U32 GameObject3D::_nextID = 1;

GameObject3D::GameObject3D(void)
    :
    _modelTOWorldCache(),
    _position(0.0f),
    _scale(1.0f),
    _orientation(0.0f),
    _color(1.0f),
    _boundingBox(),
    _texture(nullptr),
    _shader(nullptr),
    _mesh(make_shared<Mesh>()),
    _active(true),
    _render(true),
    _ID(_nextID)
{
    ++_nextID;	
}

GameObject3D::GameObject3D(const GameObject3D& obj)
    :
    _modelTOWorldCache(obj.GetModelMatrix()),
    _position(obj.GetPosition()),
    _scale(obj.GetScale()),
    _orientation(obj.GetOrientation()),
    _color(obj.GetColor()),
    _texture(obj.GetTexture()),
    _shader(obj.GetShader()),
    _active(obj.GetActive()),
    _render(obj.GetRendering()),
    _ID(obj.GetID())
{  }

GameObject3D::~GameObject3D(void)
{  }

void GameObject3D::Init(void)
{

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
    return _modelTOWorldCache;
}

const TM::Matrix4 GameObject3D::GetModelMatrixRot(void) const
{
    TM::Matrix4 mat = _modelTOWorldCache; 
    mat.SetTranslate(0.0f, 0.0f, 0.0f);
    return mat;
}

bool GameObject3D::GetActive(void) const
{
    return _active;
}

void GameObject3D::Activate(void)
{
    _active = true;
}

void GameObject3D::Deactivate(void)
{
    _active = false;
}

bool GameObject3D::GetRendering(void) const
{
    return _render;
}
        
void GameObject3D::StartRendering(void)
{
    _render = true;
}

void GameObject3D::StopRendering(void)
{
    _render = false;
}

const U32 GameObject3D::GetID(void) const
{
    return _ID;
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

const TM::Vector3& GameObject3D::GetScale(void) const
{
    return _scale;
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
    _modelTOWorldCache.SetOrientationAndPosition(_orientation, _position);
    _modelTOWorldCache = _modelTOWorldCache * TM::Matrix4::Scale(_scale);
}