/*========================================================================
A Level is what the different states of game will be. Each Level re-
presents  

The Level can render 2D and 3D objects with and without physics. 

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#pragma once

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
#include <Engine/ModelRenderer.h>
#include <Engine/RenderedText.h>
#include <Engine/RenderedCharacter.h>
#include <Engine/Particle2D.h>
#include <Engine/Particle2DForceRegistry.h>

namespace KM = KillerMath;
namespace KP =KillerPhysics;

//=====STL includes=====
#include <map>
#include <vector>
#include <fstream>
#include <algorithm>

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
//Class structs, enums and typedefs
//
//==========================================================================================================================	
	public:
		//typedef std::map<U32, shared_ptr<GameObject2D>> 2DObjectList;
		//typedef std::map<U32, shared_ptr<GameObject3D>> 3DObjectList;
		//typedef std::map<U32, shared_ptr<KP::Particle2D>>   2DParticleList;
		//typedef std::vector<shared_ptr<RenderedText>> TextList;


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

		virtual ~Level(void);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================

		virtual void v_InitLevel(U32 id, S32 w, S32 h, Color& c)=0;

		inline virtual void v_InitLevel(U32 id, string tmxFilePath)
		{
			SetID(id);
			Importer2D(tmxFilePath);
		}
		
		virtual void v_Update(void)=0;

		virtual void v_Integrate(void);
		
		virtual void v_Render(void);

/*		virtual GameObject2D* v_CreateObject(ObjectType type, Vector2& pos, F32 w, F32 h) 
		{
			ErrorManager::Instance()->SetError(EC_Game, "CreateObject not defined in your Level");
			return NULL; 
		}
*/
		virtual GameObject2D* v_CreateObject(ObjectType type, KM::Vector2& pos, U32 textureID, F32 w, F32 h)
		{
			ErrorManager::Instance()->SetError(EC_KillerEngine, "Attempted to call v_CreateObject without Level Implementation");
			return nullptr;
		}

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		void AddObjectToLevel(const GameObject2D& obj);

		void AddObjectToLevel(shared_ptr<GameObject2D> obj);

		void AddParticle2DToLevel(shared_ptr<KP::Particle2D> particle, shared_ptr<KP::Particle2DForceGenerator> generator=nullptr);

		inline void RegisterParticle2DForce(shared_ptr<KP::Particle2D> particle, shared_ptr<KP::Particle2DForceGenerator> generator)
		{
			_2DForceRegistry.Add(particle, generator);
		}

		void AddObject3DToLevel(const GameObject3D& obj);

		void AddTextToLevel(shared_ptr<RenderedText> text);
		
		void Remove2DObjectFromLevel(U32 id);

		void Remove3DObjectFromLevel(U32 id);

		void RenderObjects(void);

		void UpdateObjects(void);
		
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
		void _AddTile(TileData data);


		S32   _mapWidth;
		S32   _mapHeight;
		S32   _mapTopBorder;
		S32   _mapBottomBorder;
		S32   _mapRightBorder;
		S32   _mapLeftBorder;
		Color _bgColor;
		U32 _ID;
		std::map<U32, shared_ptr<GameObject2D>>   _2DWorldObjects;
		std::map<U32, shared_ptr<GameObject3D>>   _3DWorldObjects;
		std::map<U32, shared_ptr<KP::Particle2D>> _2DParticles;
		std::vector<shared_ptr<RenderedText>>     _textList;
		std::map<U32, TileData> _2DTileData;
		//SpriteBatch _batch;
		KP::Particle2DForceRegistry _2DForceRegistry;
	};
}//End namespace