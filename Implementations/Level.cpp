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
_gameObjects(),
_forceRegistry()
{  }

Level::~Level(void)
{
	_gameObjects.clear();
}

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
void Level::v_Render(void)
{ 
	RenderObjects(); 
}

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================

void Level::UpdateLevel(void)
{
	_forceRegistry.UpdateForces();
}

void Level::AddObjectToLevel(const GameObject& obj)
{
	_gameObjects.insert({ obj.GetID(), shared_ptr<GameObject>(const_cast<GameObject*>(&obj)) });
	// TODO:: Think about how this operation should happen. Right now this is not possible.
	//_gameObjects[obj.GetID()]->SetUniform("projection", GameWindow::Instance()->GetCamera()->GetProjectionMatrix4());

	if(_gameObjects.find(obj.GetID()) == _gameObjects.end())
	{
		ErrorManager::Instance()->SetError(ENGINE, "Level::AddObjectToLevel Unable to add GameObject to level.");
	}
}

void Level::AddObjectToLevel(p_GameObject obj)
{
	// TODO:: Think about how this operation should happen. Right now this is not possible.
	//obj->SetUniform("projection", GameWindow::Instance()->GetCamera()->GetProjectionMatrix4());

	_gameObjects.insert({obj->GetID(), obj});

	if(_gameObjects.find(obj->GetID()) == _gameObjects.end())
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
	if(_gameObjects.find(id) != _gameObjects.end())
	{
		_gameObjects.erase(id);
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
	for(auto i : _gameObjects)
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
	for(auto i : _gameObjects)
	{
		if(i.second->GetActiveRender())
		{
			// TODO:: Think about how this operation should happen. Right now this is not possible.
			//i.second->SetUniform("view", GameWindow::Instance()->GetCamera()->GetViewMatrix4());
			i.second->v_Render();
		}
	}	
}

void Level::DefaultAwake(void)
{
	GameWindow::Instance()->ResetCamera();
	ActivateBackgroundColor();
}

shared_ptr<GameObject> Level::GetGameObject(U32 id)
{
	shared_ptr<GameObject> obj = _gameObjects[id];

	if(obj == nullptr)
	{
		//ErrorManager::Instance()->SetError(ENGINE, "Level::GetGameObject ln 233, unable to find object with id " + id);
		return nullptr;
	}

	return obj;
}