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
	GameWindow::Instance()->Init(width, height, title, fullscreen);

	//Controller::Instance()->Init(GameWindow::Instance()->GetHINSTANCE(), GameWindow::Instance()->GetHWND());
	
	//If User indicated they want to close they Game
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
	GameWindow::Instance()->Update();

	TM::Timer::Instance()->Update();
	
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

	GameObjectManager::Instance()->RenderObjects();

	GameWindow::Instance()->BufferSwap();
	
	//If User indicated they want to close they Game
	if(ErrorManager::Instance()->DisplayErrors())
	{
		End();
	}
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