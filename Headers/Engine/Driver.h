#pragma once

//=====Engine includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/Input.h>
#include <Engine/GameWindow.h>
#include <Engine/OpenGLGameWindow.h>
#include <Engine/DirectXGameWindow.h>
#include <Engine/Timer.h>
#include <Engine/Level.h>
#include <Engine/GameObjectManager.h>
#include <Engine/Point2.h>
#include <Engine/CameraController.h>
#include <Engine/Color.h>

namespace TM = TempestMath;
namespace TC = TempestCollisions;

namespace Tempest 
{
    class Level;
    typedef shared_ptr<Level> p_Level;

    class Driver
    {
    public:
        TEMPEST_API void Init(S32 width, S32 height, string title, bool fullscreen, bool openGL=true);

        TEMPEST_API void ShutDown(void);
        
        TEMPEST_API bool Running(void);
        
        TEMPEST_API void End(void);

        TEMPEST_API void SetActiveLevel(p_Level level);

        TEMPEST_API void Update(void);

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

        TEMPEST_API void SetScreenColor(const Color& col);
        
        TEMPEST_API static shared_ptr<Driver> Instance();

        TEMPEST_API void ResetMouseCursor(void);

        TEMPEST_API void ToggleMouseCursor(bool state);

        TEMPEST_API void ToggleWireFrame(void);

    protected:        
        Driver(void);

    private:
        static shared_ptr<Driver> _instance;	
        bool _running;
        std::unique_ptr<GameWindow> _window;
        p_Level _activeLevel; 
    };
    typedef shared_ptr<Driver> p_Driver;
}//End namespace