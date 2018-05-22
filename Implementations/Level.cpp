#include <Engine/Level.h>

using namespace KillerEngine;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
Level::Level(void) 
: 
_mapWidth(0),
_mapHeight(0),
_mapTopBorder(0),
_mapBottomBorder(0),
_mapRightBorder(0),
_mapLeftBorder(0),
_bgColor(),
_2DForceRegistry()
{  }

Level::~Level(void)
{  }

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
void Level::v_Integrate(void)
{
	_2DForceRegistry.UpdateForces();

	for(auto i : _2DParticles)
	{
		if(i.second->GetActive())
		{
			i.second->Integrate();
		}
	}
}

void Level::v_Render(void)
{ 
	RenderObjects(); 
}

//=============================================================================
//
//AddObjectToLevel
//
//=============================================================================
void Level::AddObjectToLevel(const GameObject2D& obj)
{
	_2DWorldObjects.insert({obj.GetID(), std::shared_ptr<GameObject2D>( const_cast<GameObject2D*>(&obj) )});
	
	if(_2DWorldObjects.find(obj.GetID()) == _2DWorldObjects.end()) 
	{ 
		ErrorManager::Instance()->SetError(EC_KillerEngine, "Unable to AddLevel to _2DWorldObjects"); 
	}
}

void Level::AddObjectToLevel(shared_ptr<GameObject2D> obj)
{
	_2DWorldObjects.insert({obj->GetID(), obj});
	
	if(_2DWorldObjects.find(obj->GetID()) == _2DWorldObjects.end()) 
	{ 
		ErrorManager::Instance()->SetError(EC_KillerEngine, "Unable to AddLevel to _2DWorldObjects"); 
	}
}

void Level::AddParticle2DToLevel(shared_ptr<KP::Particle2D> particle, shared_ptr<KP::Particle2DForceGenerator> generator)
{
	_2DParticles.insert({particle->GetID(), particle});

	if(_2DParticles.find(particle->GetID()) == _2DParticles.end())
	{
		ErrorManager::Instance()->SetError(EC_KillerEngine, "Unable to Add Particle to Level. Level.h line 80");
	}

	if(generator != nullptr)
	{
		_2DForceRegistry.Add(particle, generator);
	}
}

void Level::AddObject3DToLevel(const GameObject3D& obj)
{
	_3DWorldObjects.insert({obj.GetID(), std::shared_ptr<GameObject3D>( const_cast<GameObject3D*>(&obj) )});
	
	if(_3DWorldObjects.find(obj.GetID()) == _3DWorldObjects.end()) 
	{ 
		ErrorManager::Instance()->SetError(EC_KillerEngine, "Unable to AddLevel to _3DWorldObjects"); 
	}
}

void Level::AddTextToLevel(std::shared_ptr<RenderedText> text)
{
	_textList.push_back(text);
}

void Level::_AddTile(TileData data)
{
	_2DTileData.insert(std::map<U32, TileData>::value_type(data.tileID, data));

	if(_2DTileData.find(data.tileID) == _2DTileData.end())
	{
		ErrorManager::Instance()->SetError(EC_KillerEngine, "Unable to add tile to _2DTileData");
	}
}

//=============================================================================
//
//RemoveObjectFromLevel
//
//=============================================================================
void Level::Remove2DObjectFromLevel(U32 id)
{
	std::map<U32, std::shared_ptr<GameObject2D>>::iterator i = _2DWorldObjects.find(id);

	_2DWorldObjects.erase(i);
}

void Level::Remove3DObjectFromLevel(U32 id)
{
	std::map<U32, std::shared_ptr<GameObject3D>>::iterator i = _3DWorldObjects.find(id);

	_3DWorldObjects.erase(i);
}

//==========================================================================================================================
//
//Render
//
//==========================================================================================================================	
void Level::RenderObjects(void)
{
//==========================================================================================================================
//Render Sprites
//==========================================================================================================================	
	for(auto i : _2DWorldObjects) 
	{
		if(i.second->GetActive())
		{
			//const Sprite& sprite = i.second->GetSprite();
			if(i.second->GetSprite().GetShader() != SpriteRenderer::Instance()->GetShader())
			{
				SpriteRenderer::Instance()->SetShader(i.second->GetSprite().GetShader());
			}
			//i.second->v_Render();
			//_batch.AddToBatch(i.second->GetSprite(), i.second.GetWidth(), i.second.GetHeight());
			SpriteRenderer::Instance()->AddToBatch
			(
				i.second->GetPosition(), 
				i.second->GetWidth(), 
				i.second->GetHeight(), 
				i.second->GetColor(),
				i.second->GetTextureID(),
				i.second->GetSprite().GetUVBottomTop(),
				i.second->GetSprite().GetUVLeftRight()
			);
		}
	}

//==========================================================================================================================
//Render Particle2Ds
//==========================================================================================================================
	for(auto i : _2DParticles) 
	{
		if(i.second->GetActive())
		{
			//const Sprite& sprite = i.second->GetSprite();
			if(i.second->GetSprite().GetShader() != SpriteRenderer::Instance()->GetShader())
			{
				SpriteRenderer::Instance()->SetShader(i.second->GetSprite().GetShader());
			}
			//i.second->v_Render();
			//_batch.AddToBatch(i.second->GetSprite(), i.second.GetWidth(), i.second.GetHeight());
			SpriteRenderer::Instance()->AddToBatch
			(
				i.second->GetPosition(), 
				i.second->GetWidth(), 
				i.second->GetHeight(), 
				i.second->GetColor(),
				i.second->GetTextureID(),
				i.second->GetSprite().GetUVBottomTop(),
				i.second->GetSprite().GetUVLeftRight()
			);
		}
	}

//==========================================================================================================================
//Render 3D Objects
//==========================================================================================================================	
	for(auto i : _3DWorldObjects)
	{
		if(i.second->GetActive())
		{
			if(i.second->GetModel().GetShader() != ModelRenderer::Instance()->GetShader())
			{
				ModelRenderer::Instance()->SetShader(i.second->GetModel().GetShader());
			}

			ModelRenderer::Instance()->DrawNow(i.second->GetModel(), i.second->GetModelView());
		}
	}	

//==========================================================================================================================
//Render Text
//==========================================================================================================================

	for(std::shared_ptr<RenderedText> text : _textList)
	{
		std::vector<std::shared_ptr<RenderedCharacter>> charList = text->GetCharacterList();

		if(charList[0]->GetSprite().GetShader() != SpriteRenderer::Instance()->GetShader())
		{
			SpriteRenderer::Instance()->SetShader(charList[0]->GetSprite().GetShader());
		}

		for(std::shared_ptr<RenderedCharacter> character : charList)
		{
			SpriteRenderer::Instance()->AddToBatch
			(
				character->GetPosition(),
				character->GetWidth(),
				character->GetHeight(),
				character->GetColor(),
				character->GetSprite().GetTextureID(),
				character->GetSprite().GetUVBottomTop(),
				character->GetSprite().GetUVLeftRight()
			);
		}
	}
}

void Level::UpdateObjects(void)
{
	for(auto i : _2DWorldObjects)
	{
		if(i.second->GetActive())
		{
			i.second->v_Update();
		}
	}

	for(auto i : _2DParticles )
	{
		if(i.second->GetActive())
		{
			i.second->v_Update();
		}
	}

//==========================================================================================================================
//Later: Add code for the models here
//==========================================================================================================================
}
//==========================================================================================================================
//
//TMX file Importer
//
//==========================================================================================================================	
void Level::Importer2D(string tmxFilePath)
{

	tinyxml2::XMLDocument doc;
	doc.LoadFile(tmxFilePath.c_str());

	if(!doc.Error())
	{
//==========================================================================================================================
//Caputre map data
//==========================================================================================================================			
		LevelData mapData;
		

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
						 
			mapData.color = Color(r, g, b);
		}
		else
		{
			ErrorManager::Instance()->SetError(EC_KillerEngine, "Unable to open element or node");
		}

		//=====Set Level variables=====
		SetLevelWidth(mapData.mapWidth * mapData.tileWidth);
		SetLevelHeight(mapData.mapHeight * mapData.tileHeight);
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

					texData.type = v_StringToTileData(name);				
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

						//=====Add Object to Level=====
						S32 tile = csvData[i] - '0';

						TileData currentTile = _2DTileData.find(tile)->second;

						//Broken for now anyway, need to find a better way to do this overall
						//AddObjectToLevel(v_CreateObject(currentTile.type, 
						//			   KM::Vector2( (F32)(x * mapData.tileWidth)+(currentTile.width / 2), (F32)(y * mapData.tileHeight)+(currentTile.height / 2)),
						//			   currentTile.textureID,
						//			   (F32)currentTile.width, (F32)currentTile.height));
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

}//end Importer

//==========================================================================================================================
//
//StringToEnum
//
//==========================================================================================================================
Level::ObjectType Level::v_StringToTileData(string s)
{
	if(s == "Background") { return ObjectType::BACKGROUND; }
	
	else if(s == "Environment") { return ObjectType::ENVIRONMENT; }	
	
	else if(s == "Player") { return ObjectType::PLAYER;	}	
	
	else if(s == "Enemy") { return ObjectType::ENEMY; }
	
	else
	{	
		ErrorManager::Instance()->SetError(EC_KillerEngine, "No such object tag during import of file " + s);
		return ObjectType::END;
	}
}