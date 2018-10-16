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
#include <Engine/GameObject.h>
#include <Engine/WinProgram.h>
#include <Engine/TextureManager.h>
#include <Engine/EnvironmentObject.h>
#include <Engine/Vector.h>
#include <Engine/Color.h>
#include <Engine/Text.h>
#include <Engine/Particle.h>
#include <Engine/ParticleForceRegistry.h>
#include <Engine/Camera.h>

namespace KM = KillerMath;
namespace KP =KillerPhysics;

//=====STL includes=====
#include <map>
#include <vector>
#include <fstream>
#include <algorithm>

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

/*		virtual GameObject* v_CreateObject(ObjectType type, Vector& pos, F32 w, F32 h) 
		{
			ErrorManager::Instance()->SetError(EC_Game, "CreateObject not defined in your Level");
			return NULL; 
		}
*/
		virtual GameObject* v_CreateObject(ObjectType type, KM::Vector& pos, U32 textureID, F32 w, F32 h)
		{
			ErrorManager::Instance()->SetError(ENGINE, "Attempted to call v_CreateObject without Level Implementation");
			return nullptr;
		}

//==========================================================================================================================
//
//Camera Functions
//
//==========================================================================================================================
		void UpdateLevel(void);

		void AddObjectToLevel(const GameObject& obj);

		void AddObjectToLevel(shared_ptr<GameObject> obj);

		void AddObjectToLevel(const KP::Particle& obj);

		void AddObjectToLevel(shared_ptr<KP::Particle> obj);

		void AddParticleToLevel(shared_ptr<KP::Particle> particle, shared_ptr<KP::ParticleForceGenerator> generator=nullptr);

		inline void RegisterParticleForce(shared_ptr<KP::Particle> particle, shared_ptr<KP::ParticleForceGenerator> generator)
		{
			_forceRegistry.Add(particle, generator);
		}

		void AddTextToLevel(shared_ptr<Text> text);
		
		void RemoveObjectFromLevel(U32 id);

		void RenderObjects(void);

		void UpdateObjects(void);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================		
		
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

		void SetCamera(shared_ptr<Camera> cam)
		{
			_camera = cam;
		}

		const shared_ptr<Camera> GetCamera(void)
		{
			return _camera;
		}

	protected:
		void Importer2D(string tmxFilePath);

		virtual ObjectType v_StringToTileData(string s);

	private:
//==========================================================================================================================
//
//Private Functions
//
//==========================================================================================================================		
		void _AddTile(TileData data);

//==========================================================================================================================
//
//Data
//
//==========================================================================================================================		
		S32     _mapWidth;
		S32     _mapHeight;
		S32     _mapTopBorder;
		S32     _mapBottomBorder;
		S32     _mapRightBorder;
		S32     _mapLeftBorder;
		Color   _bgColor;
		U32     _ID;
		shared_ptr<Camera> 						  _camera;
		std::map<U32, shared_ptr<GameObject>>	  _gameObjects;
		std::map<U32, shared_ptr<KP::Particle>>   _particles;
		std::vector<shared_ptr<Text>>     		  _textList;
		std::map<U32, TileData> 				  _2DTileData;
		//SpriteRenderer _batch;
		KP::ParticleForceRegistry _forceRegistry;
	};
}//End namespace