#include "stdafx.h"
#include "Engine/Driver.h"
using namespace Tempest;

p_Driver Driver::_instance = nullptr;
Driver::Driver(void) 
    :
    _running(false),
    _activeLevel(nullptr),
    _window(nullptr)
{  }

void Driver::Init(S32 width, S32 height, string title, bool fullscreen, bool openGL) 
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

void Driver::ShutDown(void)
{
    GameObjectManager::Instance()->Shutdown();
    _activeLevel.reset();
    _window->v_EndRunning();
    //_window.reset();
}

bool Driver::Running(void) 
{ 
    return _running; 
}

void Driver::End(void) 
{   
    _running = false;
}

void Driver::SetActiveLevel(p_Level level)
{
        if(_activeLevel != nullptr)
        {
            _activeLevel->v_Exit();
        }

        _activeLevel = level;
        
        _activeLevel->v_Enter();
}

void Driver::Update(void) 
{
    if(_running)
    {
        _window->Update();

        TM::Timer::Instance()->Update(_window->v_GetTime());

        Input::Instance()->Update();

        CameraController::Instance()->UpdateCamera();
        _activeLevel->v_Update();
        
        GameObjectManager::Instance()->UpdateObjects();
        GameObjectManager::Instance()->CheckCollisions();


        if(ErrorManager::Instance()->DisplayErrors())
        {
            End();
        }
    }
}

void Driver::Render(void) 
{
    if(_running)
    {
        GameObjectManager::Instance()->RenderObjects();

        _window->v_BufferSwap();

        //If User indicated they want to close they Game
        if(ErrorManager::Instance()->DisplayErrors())
        {
            End();
        }
    }
}

TM::Point2 Driver::GetMousePos(void)
{
    return _window->v_GetMousePos();
}

TM::Point2 Driver::GetMousePosInScreen(void)
{
    return _window->v_GetMousePosInScreen();
}

void Driver::EnableMouseCursor(void)
{
    _window->v_EnableMouseCursor();
}

S32 Driver::GetScreenWidth(void)
{
    return _window->GetScreenWidth();
}

S32 Driver::GetScreenHeight(void)
{
    return _window->GetScreenHeight();
}

F32 Driver::GetScreenRight(void)
{
    return _window->GetScreenRight();
}

F32 Driver::GetScreenLeft(void)
{
    return _window->GetScreenLeft();
}

F32 Driver::GetScreenTop(void)
{
    return _window->GetScreenTop();
}

F32 Driver::GetScreenBottom(void)
{
    return _window->GetScreenBottom();
}

void Driver::DisplayFPS(void)
{
    _window->v_DisplayFPS();
}

void Driver::SetScreenColor(const Color& col)
{
    _window->v_SetScreenColor(col);
}

p_Driver Driver::Instance(void) 
{
    if(_instance == NULL) 
    { 
        _instance = shared_ptr<Driver>(new Driver()); 
    }

    return _instance;
}

void Driver::ResetMouseCursor(void)
{
    _window->v_ResetMouseCursor();
}

void Driver::ToggleMouseCursor(bool state)
{
    if(state)
    {
        _window->v_EnableMouseCursor();
    }
    else
    {
        _window->v_DisableMouseCursor();
    }
}

void Driver::ToggleWireFrame(void)
{
    _window->v_ToggleWireFrame();
}