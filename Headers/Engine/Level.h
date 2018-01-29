/*========================================================================
A world is what the different states of game will be. Each world re-
presents  

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#ifndef LEVEL_H
#define LEVEL_H

//===Killer1 includes===
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/GameObject2D.h>
#include <Engine/GameObject3D.h>
#include <Engine/WinProgram.h>
#include <Engine/TextureManager.h>
#include <Engine/EnvironmentObject.h>
#include <Engine/Vector2.h>
#include <Engine/Color.h>
#include <Engine/SpriteBatch.h>
#include <Engine/RenderedText.h>
#include <Engine/RenderedCharacter.h>

namespace KM = KillerMath;

//=====STL includes=====
#include <map>
#include <vector>
#include <fstream>
#include <algorithm>
#include <memory>

#include <TinyXML/tinyxml2.h>

//=====OGL includes
#include <GL/gl.h>
#include <GL/glu.h>

namespace KillerEngine 
{
	class Level
	{
//==========================================================================================================================
//
//Class structs and enums
//
//==========================================================================================================================	
	protected:
		enum ObjectType
		{
			BACKGROUND,
			ENVIRONMENT,
			PLAYER,
			ENEMY,
			END
		};

	private:
		
		struct TileData
		{
			int tileID;
			int width;
			int height;
			string texturePath;
			ObjectType type;
			int textureID;
			int posX;
		};

		struct LevelData
		{
			int   mapWidth;
			int   mapHeight;
			int   tileWidth;
			int   tileHeight;
			Color color;
		};
			

	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================		
		Level(void);

		~Level(void);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================

		virtual void v_InitLevel(U32 id, S32 w, S32 h, Color& c)=0;

		virtual void v_InitLevel(U32 id, string tmxFilePath)
		{
			SetID(id);
			Importer2D(tmxFilePath);
		}
		
		virtual void v_Update(void)=0;
		
		virtual void v_Render(void) 
		{ 
			RenderObjects(); 
		}

/*		virtual GameObject2D* v_CreateObject(ObjectType type, Vector2& pos, F32 w, F32 h) 
		{
			ErrorManager::Instance()->SetError(EC_Game, "CreateObject not defined in your Level");
			return NULL; 
		}
*/
		virtual GameObject2D* v_CreateObject(ObjectType type, KM::Vector2& pos, U32 textureID, F32 w, F32 h)
		{
			ErrorManager::Instance()->SetError(EC_KillerEngine, "Attempted to call v_CreateObject without Level Implementation");
			return NULL;
		}

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		void AddObjectToLevel(GameObject2D* obj);

		void AddObject3DToLevel(GameObject3D* obj);

		void AddTextToLevel(std::shared_ptr<RenderedText> text);
		
		void Remove2DObjectFromLevel(U32 id);

		void Remove3DObjectFromLevel(U32 id);

		void RenderObjects(void);
		
		void SetBackgroundColor(Color& c) 
		{ 
			_bgColor = c;
		}
		
		void ActivateBackgroundColor(void) 
		{ 
			WinProgram::Instance()->SetBackgroundColor(_bgColor); 
		}
		
		S32  GetLevelWidth(void) const 
		{ 
			return _mapWidth; 
		}
		
		S32  GetLevelHeight(void) const 
		{ 
			return _mapHeight; 
		}
		
		void SetLevelWidth(S32 w)  
		{ 
			_mapWidth = w; 
		}
		
		void SetLevelHeight(S32 h) 
		{ 
			_mapHeight = h; 
		}
		
		void SetLevelDimensions(S32 w, S32 h) 
		{ 
			_mapWidth  = w; 
			_mapHeight = h; 
		}
		
		void SetTopBorder(S32 top) 
		{ 
			_mapTopBorder = top; 
		}

		void SetBottomBorder(S32 bottom) 
		{ 
			_mapBottomBorder = bottom; 
		}

		void SetRightBorder(S32 right) 
		{ 
			_mapRightBorder = right;
		}

		void SetLeftBorder(S32 left) 
		{ 
			_mapLeftBorder = left; 
		}

		void SetLevelBorders(S32 top, S32 bottom, S32 right, S32 left)
		{
			_mapTopBorder = top;
			_mapBottomBorder = bottom;
			_mapLeftBorder = left;
			_mapRightBorder = right;
		}
		
		S32 GetTopBorder(void) const 
		{ 
			return _mapTopBorder; 
		}

		S32 GetBottomBorder(void) const 
		{ 
			return _mapBottomBorder; 
		}
		
		S32 GetLeftBorder(void) const 
		{ 
			return _mapLeftBorder; 
		}

		S32 GetRightBorder(void) const 
		{
			return _mapRightBorder; 
		}

		void SetID(U32 id) 
		{ 
			_ID = id; 
		}

		U32 GetID(void) const 
		{ 
			return _ID; 
		}

	protected:
		void Importer2D(string tmxFilePath);

		virtual ObjectType v_StringToTileData(string s);

	private:
		S32   _mapWidth;
		S32   _mapHeight;
		S32   _mapTopBorder;
		S32   _mapBottomBorder;
		S32   _mapRightBorder;
		S32   _mapLeftBorder;
		Color _bgColor;
		U32 _ID;
		std::map<U32, std::shared_ptr<GameObject2D>> _2DWorldObjects;
		std::map<U32, std::shared_ptr<GameObject3D>> _3DWorldObjects;
		std::vector<std::shared_ptr<RenderedText>>	 _textList;
		std::map<U32, TileData> _2DTileData;
		//SpriteBatch _batch;

		void _AddTile(TileData data);
	};
}//End namespace

#endif
