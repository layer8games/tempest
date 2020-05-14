#include "stdafx.h"
#include <Engine/Engine.h>
using namespace Tempest;

p_Engine Engine::_instance = nullptr;
Engine::Engine(void) 
    :
    _running(false),
    _activeLevel(nullptr),
    _window(nullptr)
{  }

void Engine::Init(S32 width, S32 height, string title, bool fullscreen, bool openGL) 
{
    if(openGL)
    {
        _window = std::unique_ptr<GameWindow>(new OpenGLGameWindow());
        _window->v_Init(width, height, title, fullscreen);
    }
    else
    {
        _window = std::unique_ptr<GameWindow>(new DirectXGameWindow());
        _window->v_Init(width, height, title, fullscreen);
    }
    
    if(ErrorManager::Instance()->DisplayErrors())
    {
        End();
    }

    _running = true;
}

void Engine::ShutDown(void)
{
    GameObjectManager::Instance()->Shutdown();
    _activeLevel.reset();
    _window->v_EndRunning();
    //_window.reset();
}

bool Engine::Running(void) 
{ 
    return _running; 
}

void Engine::End(void) 
{   
    _running = false;
}

void Engine::SetActiveLevel(p_Level level)
{
        if(_activeLevel != nullptr)
        {
            _activeLevel->v_Exit();
        }

        _activeLevel = level;
        
        _activeLevel->v_Enter();
}

void Engine::Update(void) 
{
    if(_running)
    {
        _window->Update();

        TM::Timer::Instance()->Update(_window->v_GetTime());

        Input::Instance()->Update();

        GameObjectManager::Instance()->UpdateObjects();
        GameObjectManager::Instance()->CheckCollisions();

        _activeLevel->v_Update();

        if(ErrorManager::Instance()->DisplayErrors())
        {
            End();
        }
    }
}

void Engine::Render(void) 
{
    if(_running)
    {
        _activeLevel->v_Render();

        // TODO:: Need to refactor this. See GameObjectManager TODO for details
        //GameObjectManager::Instance()->RenderObjects();

        _window->v_BufferSwap();

        //If User indicated they want to close they Game
        if(ErrorManager::Instance()->DisplayErrors())
        {
            End();
        }
    }
}

TM::Point2 Engine::GetMousePos(void)
{
    return _window->v_GetMousePos();
}

TM::Point2 Engine::GetMousePosInScreen(void)
{
    return _window->v_GetMousePosInScreen();
}

void Engine::EnableMouseCursor(void)
{
    _window->v_EnableMouseCursor();
}

S32 Engine::GetScreenWidth(void)
{
    return _window->GetScreenWidth();
}

S32 Engine::GetScreenHeight(void)
{
    return _window->GetScreenHeight();
}

F32 Engine::GetScreenRight(void)
{
    return _window->GetScreenRight();
}

F32 Engine::GetScreenLeft(void)
{
    return _window->GetScreenLeft();
}

F32 Engine::GetScreenTop(void)
{
    return _window->GetScreenTop();
}

F32 Engine::GetScreenBottom(void)
{
    return _window->GetScreenBottom();
}

void Engine::DisplayFPS(void)
{
    _window->v_DisplayFPS();
}

void Engine::SetScreenColor(const Color& col)
{
    _window->v_SetScreenColor(col);
}

p_Engine Engine::Instance(void) 
{
    if(_instance == NULL) 
    { 
        _instance = shared_ptr<Engine>(new Engine()); 
    }

    return _instance;
}