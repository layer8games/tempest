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

// Consider instead of making a void return, to return an array of tile data to create?

// TODO:: Look into this warning about using too much memory here. This could be an issue.s
void Level::ImportTMXMapData(string filepath)
{
	if(filepath.find(".tmx") != std::string::npos)
	{
		std::ifstream file(filepath);

		if(!file)
		{
			ErrorManager::Instance()->SetError(ENGINE, "Level::ImportTMXMapData Unable to open file at " + filepath);
		}

		std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		//xml file must be 0 terminating
		buffer.push_back('\0');

		file.close();

		rapidxml::xml_document<char> doc;
		doc.parse<0>(&buffer[0]);

		rapidxml::xml_node<>* map_node = doc.first_node("map");
		rapidxml::xml_node<>* tileset_node = map_node->first_node("tileset");
		

		U32 mapWidth = std::stoul(map_node->first_attribute("width")->value());
		U32 mapHeight = std::stoul(map_node->first_attribute("height")->value());
		U32 tileWidth = std::stoul(map_node->first_attribute("tilewidth")->value());
		U32 tileHeight = std::stoul(map_node->first_attribute("tileheight")->value());

		string tileSetFilePath = tileset_node->first_attribute("source")->value();

		typedef std::vector<U32> data_array;
		std::vector<data_array> layer_data;

		// l == layer_node
		for(rapidxml::xml_node<>* l=map_node->first_node("layer"); l; l=l->next_sibling("layer"))
		{
			// Create split function to get rid of the commas
			// save the data in value() to a data_array
			// push the saved data onto layer_data
		}


		// Open tileset
		// Create tile data for each tile in the set. IDs must match data_array entries

		// Create array of tile_data to be created by a factory at run time, maybe this is what gets returned.		
	}
	else
	{
		ErrorManager::Instance()->SetError(ENGINE, "Level::ImportTMXMaqData: Invalid file type!");
	}
}

void Level::DefaultRender(void)
{
	RenderObjects();
}

Level::TileData Level::_ConvertIndexToTileData(U32 index, U32 width, U32 height)
{
	TileData data;
	data.gridX = index % width;
	data.gridY = height - (index / height);

	return data;
}