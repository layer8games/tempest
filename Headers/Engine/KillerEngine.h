
/*========================================================================
The KillerEngine class is designed to be the interface to starting up the
Engine. This class will really just be a function and instance holder for
other classes in the engine, but will actually do very little of its own. 

A lot of the functions that will be here will not be required to use in
order to use the engine. They will be present as helper classes, not
intended for required use. 

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#pragma once

//=====Engine includes=====
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/Controller.h>
#include <Engine/WinProgram.h>
#include <Engine/Timer.h>
#include <Engine/LevelManager.h>
//#include <Engine/TextureManager.h>

namespace KM = KillerMath;

namespace KillerEngine 
{

	class KillerEngine 
	{

	public:
//==========================================================================================================================
//
//Interface
//
//==========================================================================================================================
		void Init(const S32 width, const S32 height, const string title, const bool fullscreen);

		void ShutDown(void);
		
		bool Running(void) 
		{ 
			return LevelManager::Instance()->GetRunning(); 
		}

		void End(void) 
		{ 
			LevelManager::Instance()->SetRunning(false); 
		}

		void LoadTexture(const string path, const U32 id, const S32 width, const S32 height) 
		{ 
			//TextureManager::Instance()->LoadTexture(path, id, width, height); 
		}
		
		void AddLevelToManager(Level* level) 
		{ 
			LevelManager::Instance()->AddLevel(level); 
		}

		void SetActiveLevel(const U32 id) 
		{ 
			LevelManager::Instance()->SetActiveLevel(id); 
		}

		void Update(void);

		void Render(void);
//==========================================================================================================================
//
//Singleton functions
//
//==========================================================================================================================
		static shared_ptr<KillerEngine> Instance();		

	protected:
//==========================================================================================================================
//
//Constructor
//
//==========================================================================================================================		
		KillerEngine(void);

	private:
//==========================================================================================================================
//
//Members
//
//==========================================================================================================================
		static shared_ptr<KillerEngine> _instance;

	};

}//End namespace