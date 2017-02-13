#include <Engine/Map2D.h>
#include <iostream>

namespace KillerEngine 
{
	Map2D::Map2D(void) : _mapWidth(0),
					   		 _mapHeight(0),
					   		 _mapTopBorder(0),
					   		 _mapBottomBorder(0),
					   		 _mapRightBorder(0),
					   		 _mapLeftBorder(0),
					   		 _bgColor()
	{  }

//=============================================================================
//
//AddObjectToMap
//
//=============================================================================
	void Map2D::AddObjectToMap(GameObject2D* obj)
	{
		_worldObjects.insert(std::map<U32, GameObject2D*>::value_type(obj->GetID(), obj));
		
		if(_worldObjects.find(obj->GetID()) == _worldObjects.end()) 
		{ 
			ErrorManager::Instance()->SetError(EC_KillerEngine, "Unable to AddMap to _worldObjects"); 
		}
	}

	void Map2D::_AddTile(TileData data)
	{
		_tileData.insert(std::map<U32, TileData>::value_type(data.tileID, data));

		if(_tileData.find(data.tileID) == _tileData.end())
		{
			ErrorManager::Instance()->SetError(EC_KillerEngine, "Unable to add tile to _tileData");
		}
}

//=============================================================================
//
//RemoveObjectFromMap
//
//=============================================================================
	void Map2D::RemoveObjectFromMap(U32 id)
	{
		std::map<U32, GameObject2D*>::iterator i = _worldObjects.find(id);

		_worldObjects.erase(i);
	}

//==========================================================================================================================
//
//TMX file Importer
//
//==========================================================================================================================	
	void Map2D::Importer(string tmxFilePath)
	{

		tinyxml2::XMLDocument doc;
		doc.LoadFile(tmxFilePath.c_str());

		if(!doc.Error())
		{
//==========================================================================================================================
//Caputre map data
//==========================================================================================================================			
			MapData mapData;
			

			tinyxml2::XMLElement* elem = doc.RootElement();

			if(elem != NULL)
			{
				elem->QueryIntAttribute("width", &mapData.mapWidth);
				elem->QueryIntAttribute("height", &mapData.mapHeight);
				elem->QueryIntAttribute("tilewidth", &mapData.tileWidth);
				elem->QueryIntAttribute("tileheight", &mapData.tileHeight);
				
				string color = elem->Attribute("backgroundcolor");

				string red = "0x" + color.substr(1,2);
				string green = "0x" + color.substr(3,2);
				string blue = "0x" + color.substr(5,2);

				U32 ir = std::stoul(red, NULL, 16); 
				U32 ig = std::stoul(green, NULL, 16); 
				U32 ib = std::stoul(blue, NULL, 16); 

				F32 r = (F32)ir / 255;
				F32 g = (F32)ig / 255;
				F32 b = (F32)ib / 255;

				std::cout << "color " << r << " " << g << " " << b << "\n";
							 
				mapData.color = Col(r, g, b);
			}
			else
			{
				ErrorManager::Instance()->SetError(EC_KillerEngine, "Unable to open element or node");
			}

			//=====Set Map variables=====
			SetMapWidth(mapData.mapWidth * mapData.tileWidth);
			SetMapHeight(mapData.mapHeight * mapData.tileHeight);
			SetBackgroundColor(mapData.color);
//==========================================================================================================================
//Capture Tile Data
//==========================================================================================================================
			elem = doc.RootElement()->FirstChildElement("tileset");
			
			if(elem != NULL)
			{
				for(tinyxml2::XMLElement* e = elem->FirstChildElement("tile"); e != NULL; e = e->NextSiblingElement())
				{
					TileData texData;
					
					//=====Capture tile ID=====
					e->QueryIntAttribute("id", &texData.tileID);

					//Increase by one for now, but later this will be
					//increased by the <tileset firstgid="1"
					++texData.tileID;
					
					//=====Capture Custom Properties=====
					//ObjectType
					tinyxml2::XMLElement* p = e->FirstChildElement("properties")->FirstChildElement("property");

					string att = p->Attribute("name");
					
					if(att == "ObjectType")
					{
						string name = p->Attribute("value");
//=====Fix Object Type assignment here=====
						//for(U32 i = 0; i < name.size(); ++i)
						//{
						//	name[i] = std::toupper(name[i]);
						//}

						//texData.type = ObjectType::name;
	
						if(name == "Background")
						{
							texData.type = ObjectType::BACKGROUND;
						}
						else if(name == "Environment")
						{
							texData.type = ObjectType::ENVIRONMENT;
						}
						else if(name == "Player")
						{
							texData.type = ObjectType::PLAYER;
						}
						else if(name == "Enemy")
						{
							texData.type = ObjectType::ENEMY;
						}
						
						else
						{
							ErrorManager::Instance()->SetError(EC_KillerEngine, "No such object tag during import of file " + name);
						}
					}
					else
					{
						ErrorManager::Instance()->SetError(EC_KillerEngine, "In correct format for tile ObjectType.");
					}

					//TextureID
					p = e->FirstChildElement("properties")->FirstChildElement("property")->NextSiblingElement("property");

					att = p->Attribute("name");

					if(att == "TextureID")
					{
						p->QueryIntAttribute("value", &texData.textureID);
					}
					else
					{
						ErrorManager::Instance()->SetError(EC_KillerEngine, "In correct format for tile TextureID");
					}

					//=====Capture Image texData=====
					tinyxml2::XMLElement* image = e->FirstChildElement("image");

					image->QueryIntAttribute("width", &texData.width);
					image->QueryIntAttribute("height", &texData.height);
					texData.texturePath = image->Attribute("source");

					//=====ReFormat the texture URL=====
					for(auto i = texData.texturePath.begin(); i != texData.texturePath.end(); i++)
					{
						if(*i == '/')
						{
							*i = '\\';
						}
						if(*i == '.' && *(i+1) == '.')
						{
							texData.texturePath.erase(i, i + 1);
						}
					}

					texData.texturePath = "..\\Assets" + texData.texturePath;
					_AddTile(texData);
					TextureManager::Instance()->LoadTexture(texData.texturePath, texData.textureID, texData.width, texData.height);
				}
//==========================================================================================================================
//Caputre tile layout
//==========================================================================================================================
				elem = doc.RootElement()->FirstChildElement("layer")->FirstChildElement("data");
				string name = elem->Attribute("encoding");

				if(name == "csv")
				{
					string csvData = elem->GetText();

					for(U32 i = 0; i < csvData.size(); ++i)
					{
						csvData.erase(std::remove(csvData.begin(), csvData.end(), ','), csvData.end());
						csvData.erase(std::remove(csvData.begin(), csvData.end(), '\n'), csvData.end());
						
						if(csvData[i] > '0')
						{
							//=====Get X Y from csv data for textures=====
							U32 x;
							U32 y;
														
							U32 p = i + 1;

							if(p % mapData.mapWidth == 0) { x = mapData.mapWidth; }	
							else
							{
								U32 t = 1; 
								U32 m = p / mapData.mapWidth;
								while((m * mapData.mapWidth) + t != p)
								{
									++t;
								}
								x = t;
							}

							y = mapData.mapHeight - ((i + 1) / mapData.mapHeight);

							//=====Add Object to Map=====
							S32 tile = csvData[i] - '0';

							TileData currentTile = _tileData.find(tile)->second;

//=====Fix Factory here=====
							//AddObjectToMap(v_CreateObject(currentTile.type, 
							//			   Vec2( (x * mapData.tileWidth)+(currentTile.width / 2), (y * mapData.tileHeight)+(currentTile.height / 2)),
							//			   currentTile.textureID,
							//			   (F32)currentTile.width, (F32)currentTile.height));

							AddObjectToMap(new EnvironmentObject(Vec2( (x * mapData.tileWidth)+(currentTile.width / 2), (y * mapData.tileHeight)+(currentTile.height / 2)),
										   						currentTile.textureID,
										   						(F32)currentTile.width, (F32)currentTile.height));
						}
 					}
				}
				else
				{
					ErrorManager::Instance()->SetError(EC_KillerEngine, "Incorrect encoding in imported file, not csv, " + name);
				}
			}
			else
			{
				ErrorManager::Instance()->SetError(EC_KillerEngine, "Unable to open element or node");
			}
			
		}
		else
		{
			ErrorManager::Instance()->SetError(EC_KillerEngine, "Unable to open file path to .tmx file " + tmxFilePath);
		}

	}


}//End namespace