#include <Engine/Level.h>
#include <iostream>

using namespace Tempest;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
Level::Level(void) 
: 
_width(0),
_height(0),
_topBorder(0),
_bottomBorder(0),
_rightBorder(0),
_leftBorder(0),
_depth(0),
_nearBorder(0),
_farBorder(0),
_bgColor(),
_ID(0),
_localGameObjects(),
_forceRegistry()
{  }

Level::~Level(void)
{
	_localGameObjects.clear();
}

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
void Level::v_Render(void)
{ 
	DefaultRender();
}

void Level::DefaultEnter(void)
{
	GameWindow::Instance()->ResetCamera();
	ActivateBackgroundColor();
}

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================

void Level::UpdateLevel(void)
{
	_forceRegistry.UpdateForces();

	for(auto obj : _localGameObjects)
	{
		if(obj.second->GetActiveUpdate())
		{
			obj.second->v_Update();
		}
	}
}

void Level::AddObjectToLevel(const GameObject& obj)
{
	_localGameObjects.insert({ obj.GetID(), shared_ptr<GameObject>(const_cast<GameObject*>(&obj)) });
	_localGameObjects[obj.GetID()]->GetShader()->SetUniform("projection", GameWindow::Instance()->GetCamera()->GetProjectionMatrix4());

	if(_localGameObjects.find(obj.GetID()) == _localGameObjects.end())
	{
		ErrorManager::Instance()->SetError(ENGINE, "Level::AddObjectToLevel Unable to add GameObject to level.");
	}
}

void Level::AddObjectToLevel(p_GameObject obj)
{
	obj->GetShader()->SetUniform("projection", GameWindow::Instance()->GetCamera()->GetProjectionMatrix4());

	_localGameObjects.insert({obj->GetID(), obj});

	if(_localGameObjects.find(obj->GetID()) == _localGameObjects.end())
	{
		ErrorManager::Instance()->SetError(ENGINE, "Level::AddObjectToLevel Unable to add GameObject to level.");
	}
}

void Level::AddTextToLevel(const Text& text)
{
	//text->SetUniforms("projection", _camera->GetProjectionMatrix4());

	//_textList.push_back(text);
	std::vector<p_Glyph> v = text.GetCharacterList();
	for(auto i : v)
	{
		AddObjectToLevel(i);
	}
}

void Level::AddTextToLevel(shared_ptr<Text> text)
{
	std::vector<p_Glyph> v = text->GetCharacterList();
	for(auto i : v)
	{
		AddObjectToLevel(i);
	}
}

void Level::RemoveTextFromLevel(const Text& text)
{
	std::vector<p_Glyph> v = text.GetCharacterList();

	for(auto i : v)
	{
		RemoveObjectFromLevel(i->GetID());
	}
}

void Level::UpdateText(Text& text, string updatedCharacters)
{
	RemoveTextFromLevel(text);

	text.AddText(updatedCharacters);

	AddTextToLevel(text);
}

//=============================================================================
//
//RemoveObjectFromLevel
//
//=============================================================================
void Level::RemoveObjectFromLevel(U32 id)
{
	//Assume that if an ID is not a GameObject, then it could be derived type.
	if(_localGameObjects.find(id) != _localGameObjects.end())
	{
		_localGameObjects.erase(id);
	}
	else
	{
		ErrorManager::Instance()->SetError(ENGINE, "Level::RemoveObjectFromLevel, ln 163, no object found with id " + id);
	}
}

//==========================================================================================================================
//
//Update and Render all objects
//
//==========================================================================================================================	
void Level::UpdateObjects(void)
{
	for(auto i : _localGameObjects)
	{
		if(i.second->GetActiveUpdate())
		{
			i.second->UpdateInternals();
			i.second->v_Update();
		}
	}
}
	
void Level::RenderObjects(void)
{
	for(auto i : _localGameObjects)
	{
		if(i.second->GetActiveRender())
		{
			i.second->GetShader()->SetUniform("view", GameWindow::Instance()->GetCamera()->GetViewMatrix4());
			i.second->v_Render();
		}
	}	
}

shared_ptr<GameObject> Level::GetGameObject(U32 id)
{
	shared_ptr<GameObject> obj = _localGameObjects[id];

	if(obj == nullptr)
	{
		//ErrorManager::Instance()->SetError(ENGINE, "Level::GetGameObject ln 233, unable to find object with id " + id);
		return nullptr;
	}

	return obj;
}

void Level::DefaultRender(void)
{
	RenderObjects();
}