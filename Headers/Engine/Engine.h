#pragma once

//=====Engine includes=====
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/Controller.h>
#include <Engine/GameWindow.h>
#include <Engine/OpenGLGameWindow.h>
#include <Engine/Timer.h>
#include <Engine/Level.h>
#include <Engine/GameObjectManager.h>
#include <Engine/Point2.h>
#include <Engine/Camera.h>

namespace TM = TempestMath;

namespace Tempest 
{
    class Level;
    typedef shared_ptr<Level> p_Level;
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
        /// Wrapper for OpenGLGameWindow::Init. Sets up the Window and OpenGL
        /// \param width S32: describes width of window.
        /// \param height S32: describes height of the window.
        /// \param title string: sent to system to generate title of window.
        /// \param fullscreen bool: tells system to use fullscreen or not. 
        TEMPEST_API void Init(const S32 width, const S32 height, const string title, const bool fullscreen);
        
        // Check if simulation is still running.
        inline bool Running(void) 
        { 
            return _window->GetRunning(); 
        }

        /// Wrapper for LevelManager::SetRunning(). Sets Running to false. This stops the Main Game Loop from running. Calling this is the same as Quitting the program.
        inline void End(void) 
        { 
            _window->v_EndRunning(); 
        }

        /// Changes the currently updating and active level. Exit is called, then Enter is called. Must call v_Init before passing. 
        /// \param level is the pointer to set active
        TEMPEST_API void SetActiveLevel(p_Level level);

        /// Wrapper for steps needed update steps. Calls the following in order.
        /// - OpenGLGameWindow::ProcessWndEvents()
        /// - Timer::Update()
        /// - Controller::Update()
        /// - LevelManager::Update()
        /// - ErrorManager::DisplayErrors()	
        TEMPEST_API void Update(void);

        /// Wrapper for steps needed to render. Calls the following in order
        /// - LevelManager::Render()
        /// - OpenGLGameWindow::BufferSwap()
        /// - ErrorManager::DisplayErrors() 
        TEMPEST_API void Render(void);

        TEMPEST_API TM::Point2 GetMousePos(void);

        TEMPEST_API TM::Point2 GetMousePosInScreen(void);

        TEMPEST_API void EnableMouseCursor(void);

        TEMPEST_API S32 GetScreenWidth(void);

        TEMPEST_API S32 GetScreenHeight(void);

        TEMPEST_API F32 GetScreenRight(void);

        TEMPEST_API F32 GetScreenLeft(void);

        TEMPEST_API F32 GetScreenTop(void);

        TEMPEST_API F32 GetScreenBottom(void);

        TEMPEST_API void DisplayFPS(void);

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
        std::unique_ptr<GameWindow> _window;
        p_Level _activeLevel; ///< Currently Active updating and Rendering Level.
    };
    typedef shared_ptr<Engine> p_Engine;
}//End namespace