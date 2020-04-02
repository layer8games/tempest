#include <Engine/GameObject3D.h>

using namespace Tempest;

//==========================================================================================================================
//
//Static Member
//
//==========================================================================================================================
U32 GameObject3D::_nextID = 1;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
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
    _activeUpdate(true),
    _activeRender(true),
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
    _activeUpdate(obj.GetActiveUpdate()),
    _activeRender(obj.GetActiveRender()),
    _ID(obj.GetID())
{  }

GameObject3D::~GameObject3D(void)
{  }

//==========================================================================================================================
//
//Functions
//==========================================================================================================================
void GameObject3D::UpdateInternals(void)
{
    _CalculateCachedData();
}

//==========================================================================================================================
//Protected
//==========================================================================================================================
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

//==========================================================================================================================
//Private
//==========================================================================================================================
void GameObject3D::_CalculateCachedData(void)
{
    _modelTOWorldCache.SetOrientationAndPosition(_orientation, _position);
    _modelTOWorldCache = _modelTOWorldCache * TM::Matrix4::Scale(_scale);
}