#include <Engine/Engine.h>

using namespace Tempest;

//==========================================================================================================================
//
//Constructor
//
//==========================================================================================================================		
Engine::Engine(void) 
    :
    _activeLevel(nullptr)
{  }

//==========================================================================================================================
//
//Interface
//
//==========================================================================================================================
//=======================================================================================================
//Init
//=======================================================================================================
void Engine::Init(const S32 width, const S32 height, const string title, const bool fullscreen) 
{
    _window = std::unique_ptr<GameWindow>(new OpenGLGameWindow());
    
    _window->v_Init(width, height, title, fullscreen);
   
    if(ErrorManager::Instance()->DisplayErrors())
    {
        End();
    }
}	

//=======================================================================================================
//Update
//=======================================================================================================
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
    _window->Update();

    TM::Timer::Instance()->Update(_window->v_GetTime());
    
    Controller::Instance()->Update();
    
    GameObjectManager::Instance()->UpdateObjects();

    _activeLevel->UpdateLevel();
    _activeLevel->v_Update();

    //If User indicated they want to close they Game
    if(ErrorManager::Instance()->DisplayErrors())
    {
        End();
    }
}

//=======================================================================================================
//FunctionName
//=======================================================================================================
void Engine::Render(void) 
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
    return _window->GetWidth();
}

S32 Engine::GetScreenHeight(void)
{
    return _window->GetHeight();
}

F32 Engine::GetScreenRight(void)
{
    return _window->GetScreenRight();
}

F32 Engine::GetScreenLeft(void)
{
    return _window->GetScreenLeft();
}

F32 Engine::GetSCreenTop(void)
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

//==========================================================================================================================
//
//Singleton functions
//
//==========================================================================================================================
p_Engine Engine::_instance = NULL;

p_Engine Engine::Instance(void) 
{
    if(_instance == NULL) 
    { 
        _instance = shared_ptr<Engine>(new Engine()); 
    }

    return _instance;
}