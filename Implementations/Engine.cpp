#include <Engine/Engine.h>

using namespace Tempest;

//==========================================================================================================================
//
//Constructor
//
//==========================================================================================================================		
Engine::Engine(void) 
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

//==========================================================================================================================
//ShutDown
//==========================================================================================================================
void Engine::ShutDown(void)
{
	LevelManager::Instance()->ShutDown();
}	

//=======================================================================================================
//Update
//=======================================================================================================
void Engine::Update(void) 
{
	GameWindow::Instance()->Update();

	TM::Timer::Instance()->Update();
	
	Controller::Instance()->Update();
	
	LevelManager::Instance()->Update();

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
	LevelManager::Instance()->Render();

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