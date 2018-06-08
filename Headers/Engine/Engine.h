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
//==========================================================================================================================
//Documentation
//==========================================================================================================================
/*! The KillerEngine class is designed to be the interface to starting up the Engine. This class will really just be a 
	function and instance holder for other classes in the engine, but will actually do very little of its own. 

	A lot of the functions that will be here will not be required to use in order to use the engine. They will be present 
	as helper classes, not intended for required use. */
	class Engine
	{

	public:
//==========================================================================================================================
//
//Interface
//
//==========================================================================================================================
/*! Wrapper for WinProgram::Init. Sets up the Window and OpenGL
	\param width S32: describes width of window.
	\param height S32: describes height of the window.
	\param title string: sent to system to generate title of window.
	\param fullscreen bool: tells system to use fullscreen or not. */
		void Init(const S32 width, const S32 height, const string title, const bool fullscreen);

/*! Wrapper for LevelManager::ShutDown(void) */
		void ShutDown(void);
		
/*! Check if simulation is still running. */
		inline bool Running(void) 
		{ 
			return LevelManager::Instance()->GetRunning(); 
		}

/*! Wrapper for LevelManager::SetRunning(). Sets Running to false. This stops the Main Game Loop from running. Calling this is the same as Quitting the program. */ 
		inline void End(void) 
		{ 
			LevelManager::Instance()->SetRunning(false); 
		}

/*! Wrapper for TextureManager::LoadTexture(). Saves an handle to a loaded texture in OpenGL by ID
	\param path string: filepath to the texture image
	\param id U32: id for texture. Will be used to call it later. 
	\param width S32: width in pixels of texture
	\param height S32: height in pixels of texture */
		inline void LoadTexture(const string path, const U32 id, const S32 width, const S32 height) 
		{ 
			TextureManager::Instance()->LoadTexture(path, id, width, height); 
		}
/*!  Wrapper for LevelManager::AddLevel(). Adds level that can be set as active. 
	\param level shared_ptr<Level>: Level to be added. */
		inline void AddLevelToManager(shared_ptr<Level> level)
		{ 
			LevelManager::Instance()->AddLevel(level); 
		}

/*! Wrapper for LevelManager::SetActive(). Sets level with id to be active level
	\param id const U32: id of level. */

		inline void SetActiveLevel(const U32 id) 
		{ 
			LevelManager::Instance()->SetActiveLevel(id); 
		}

/*! Wrapper for steps needed update steps. Calls the following in order.
	 - WinProgram::ProcessWndEvents()
	 - Timer::Update()
	 - Controller::Update()
	 - LevelManager::Update()
	 - ErrorManager::DisplayErrors() */		
		void Update(void);

/*! Wrapper for steps needed to render. Calls the following in order
	- LevelManager::Render()
	- WinProgram::BufferSwap()
	- ErrorManager::DisplayErrors() */
		void Render(void);
//==========================================================================================================================
//
//Singleton functions
//
//==========================================================================================================================
/*! Singleton function to get global instance of Engine. */
		static shared_ptr<Engine> Instance();		

	protected:
//==========================================================================================================================
//
//Constructor
//
//==========================================================================================================================		
		Engine(void);

	private:
//==========================================================================================================================
//
//Members
//
//==========================================================================================================================
		static shared_ptr<Engine> _instance;	///< Singleton global instance.

	};

}//End namespace