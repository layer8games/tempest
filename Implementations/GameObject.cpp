#include <Engine/GameObject.h>
#include <iostream>

using namespace Tempest;

//==========================================================================================================================
//
//Static Member
//
//==========================================================================================================================
U32 GameObject::_nextID = 1;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
GameObject::GameObject(void)
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
	_isSprite(false),
	_ID(_nextID)
{
	++_nextID;	
}

GameObject::GameObject(const GameObject& obj)
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
	_isSprite(obj.IsSprite()),
	_ID(obj.GetID())
{  }

GameObject::~GameObject(void)
{  }

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
//==========================================================================================================================
//v_Render
//==========================================================================================================================
void GameObject::DefaultRender(void)
{
	_shader->Use(true);
	_mesh->BindVAO(true);

	if(_texture != nullptr)
	{
		BindTexture(true);
	}

	if(_isSprite)
	{
		_shader->SetUniform("sprite_color", _color);
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

//==========================================================================================================================
//v_InitVertexData
//==========================================================================================================================
void GameObject::v_InitBuffers(void)
{
	_mesh->InitOpenGLData();
}

//==========================================================================================================================
//
//Functions
//==========================================================================================================================
void GameObject::UpdateInternals(void)
{
	_CalculateCachedData();
}

void GameObject::MakeSprite(void)
{
	_isSprite = true;
	_position.Make2D();

	TM::Point topRight(1.0f, 1.0f, 0.0f);
	TM::Point topLeft(-1.0f, 1.0f, 0.0f);
	TM::Point bottomRight(1.0f, -1.0f, 0.0f);
	TM::Point bottomLeft(-1.0f, -1.0f, 0.0);

	TM::Point top(0.0f, 0.5f);

	_mesh->AddVertex(Vertex(topLeft, 0.0f, 0.0f));
	_mesh->AddVertex(Vertex(topRight, 1.0f, 0.0f));
	_mesh->AddVertex(Vertex(bottomRight, 1.0f, 1.0f));

	_mesh->AddVertex(Vertex(topLeft, 0.0f, 0.0f));
	_mesh->AddVertex(Vertex(bottomRight, 1.0f, 1.0f));
	_mesh->AddVertex(Vertex(bottomLeft, 0.0f, 1.0f));

	v_InitBuffers();

	_shader = ShaderManager::Instance()->GetShader(SPRITE);
}

//==========================================================================================================================
//Protected
//==========================================================================================================================
void GameObject::DefaultAwake(void)
{
	UpdateInternals();
}

//==========================================================================================================================
//Private
//==========================================================================================================================
void GameObject::_CalculateCachedData(void)
{
	//_modelTOWorldCache =  TM::Matrix4::Translate(_position) * TM::Matrix4::Scale(_scale);

	_modelTOWorldCache.SetOrientationAndPosition(_orientation, _position);
	_modelTOWorldCache = _modelTOWorldCache * TM::Matrix4::Scale(_scale);
}