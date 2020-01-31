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

void Level::DefaultRender(void)
{
	RenderObjects();
}

Level::GridPos Level::_ConvertIndexToTileData(U32 index, U32 width, U32 height)
{
	GridPos pos;
	pos.x = index % width;
	pos.y = height - (index / height);

	return pos;
}

// TODO:: Look into this warning about using too much memory here. This could be an issue.
std::vector<Level::TileData> Level::_ImportTMXMapData(string filepath)
{
	std::map<U32, TileData> tiles;
	std::vector<TileData> objects;
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

		typedef rapidxml::xml_node<>* xmlNode;
		typedef rapidxml::xml_document<char> xmlDoc;

		xmlDoc doc;
		doc.parse<0>(&buffer[0]);

		xmlNode map_node = doc.first_node("map");
		xmlNode tileset_node = map_node->first_node("tileset");

		U32 mapWidth = std::stoul(map_node->first_attribute("width")->value());
		U32 mapHeight = std::stoul(map_node->first_attribute("height")->value());
		U32 tileWidth = std::stoul(map_node->first_attribute("tilewidth")->value());
		U32 tileHeight = std::stoul(map_node->first_attribute("tileheight")->value());

		string tileSetFilePath = tileset_node->first_attribute("source")->value();

		typedef std::vector<U32> U32Array;
		std::vector<U32Array> data_array;

		for(xmlNode l=map_node->first_node("layer"); l; l=l->next_sibling("layer"))
		{
			data_array.push_back(_SplitU32(l->first_node("data")->value(), ','));
		}

		if(tileSetFilePath.find(".tsx") != std::string::npos)
		{
			std::ifstream tilesetFile(tileSetFilePath);

			if(!tilesetFile)
			{
				ErrorManager::Instance()->SetError(ENGINE, "Level::ImportTMXMapData could not open file " + tileSetFilePath);
			}

			std::vector<char> tile_buffer((std::istreambuf_iterator<char>(tilesetFile)), std::istreambuf_iterator<char>());

			//xml file must be 0 terminating
			tile_buffer.push_back('\0');

			tilesetFile.close();

			xmlDoc tile_doc;
			tile_doc.parse<0>(&tile_buffer[0]);

			// t == tile node
			for(xmlNode t=tile_doc.first_node("tileset")->first_node("tile"); t; t=t->next_sibling("tile"))
			{
				TileData data;
				data.id = std::stoul(t->first_attribute("id")->value());
				//// add 1, for 0 indexing
				data.id += 1;

				// child nodes of the tile
				xmlNode child = t->first_node("properties");
				if(child)
				{
					for(child=child->first_node("property"); child; child=child->next_sibling("property"))
					{
						string name = child->first_attribute("name")->value();
						if(name == "type")
						{
							data.type = child->first_attribute("value")->value();
						}
					}
				}

				child = t->first_node("image");
				data.imageWidth = std::stoul(child->first_attribute("width")->value());
				data.imageHeight = std::stoul(child->first_attribute("height")->value());
				data.imageFilePath = child->first_attribute("source")->value();

				tiles.insert({data.id, data});
			}
		}
		else
		{
			ErrorManager::Instance()->SetError(ENGINE, "Level::ImportTMXMapData no valid tileset found in tmx file");
		}

		std::cout << "tiles now has " << tiles[1].imageFilePath << " and " << tiles[2].imageFilePath << "... etc..." << std::endl;

		for(auto data : data_array)
		{
			for(U32 i = 0; i < data.size(); ++i)
			{
				if(data[i] > 0)
				{
					Level::GridPos pos = _ConvertIndexToTileData(i, mapWidth, mapHeight);
					TM::Point cartPos{ };
					cartPos[x] = pos.x * static_cast<F32>(tileWidth);
					cartPos[y] = pos.y * static_cast<F32>(tileHeight);

					TileData object = tiles[data[i]];
					object.pos = cartPos;

					objects.push_back(object);
				}
			}
		}
	}
	else
	{
		ErrorManager::Instance()->SetError(ENGINE, "Level::ImportTMXMaqData: Invalid file type!");
	}

	return objects;
}

std::vector<U32> Level::_SplitU32(string text, char delim) const
{
	std::vector<U32> data;
	std::stringstream stream(text);
	string item;

	while(std::getline(stream, item, delim))
	{
		data.push_back(std::stoul(item.c_str()));
	}

	return data;
}