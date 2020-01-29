#pragma once

//=====Engine includes=====
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/Controller.h>
#include <Engine/GameWindow.h>
#include <Engine/Timer.h>
#include <Engine/Level.h>
#include <Engine/GameObjectManager.h>

namespace TM = TempestMath;

namespace Tempest 
{
//==========================================================================================================================
//Documentation
//========================================================================================================================== 
	/// The KillerEngine class is designed to be the interface to starting up the Engine. This class will really just be a 
	/// function and instance holder for other classes in the engine, but will actually do very little of its own. 
	
	/// A lot of the functions that will be here will not be required to use in order to use the engine. They will be present 
	/// as helper classes, not intended for required use. 
	class Engine
	{

	public:
//==========================================================================================================================
//
//Interface
//
//==========================================================================================================================
		/// Wrapper for GameWindow::Init. Sets up the Window and OpenGL
		/// \param width S32: describes width of window.
		/// \param height S32: describes height of the window.
		/// \param title string: sent to system to generate title of window.
		/// \param fullscreen bool: tells system to use fullscreen or not. 
		TEMPEST_API void Init(const S32 width, const S32 height, const string title, const bool fullscreen);
		
		// Check if simulation is still running.
		inline bool Running(void) 
		{ 
			return GameWindow::Instance()->GetRunning(); 
		}

		/// Wrapper for LevelManager::SetRunning(). Sets Running to false. This stops the Main Game Loop from running. Calling this is the same as Quitting the program.
		inline void End(void) 
		{ 
			GameWindow::Instance()->EndRunning(); 
		}

		/// Changes the currently updating and active level. Exit is called, then Enter is called. Must call v_Init before passing. 
		/// \param level is the pointer to set active
		inline void SetActiveLevel(p_Level level)
		{
			_activeLevel->v_Exit();
			_activeLevel = level;
			_activeLevel->v_Enter();
		}

		/// Wrapper for steps needed update steps. Calls the following in order.
		/// - GameWindow::ProcessWndEvents()
		/// - Timer::Update()
		/// - Controller::Update()
		/// - LevelManager::Update()
		/// - ErrorManager::DisplayErrors()	
		TEMPEST_API void Update(void);

		/// Wrapper for steps needed to render. Calls the following in order
		/// - LevelManager::Render()
		/// - GameWindow::BufferSwap()
		/// - ErrorManager::DisplayErrors() 
		TEMPEST_API void Render(void);

//==========================================================================================================================
//
//Singleton functions
//
//==========================================================================================================================
		/// Singleton function to get global instance of Engine.
		TEMPEST_API static shared_ptr<Engine> Instance();

	protected:
//==========================================================================================================================
//
//Constructor
//
//==========================================================================================================================		
		/// Default Constructor. It does not do anything. 	
		Engine(void);

	private:
//==========================================================================================================================
//
//Members
//
//==========================================================================================================================
		static shared_ptr<Engine> _instance;	///< Singleton global instance.
		p_Level					  _activeLevel; ///< Currently Active updating and Rendering Level.
	};
	typedef shared_ptr<Engine> p_Engine;
}//End namespace