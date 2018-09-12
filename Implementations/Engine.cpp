#include <Engine/Engine.h>

using namespace KillerEngine;

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
	WinProgram::Instance()->Init(width, height, title, fullscreen);

	//Controller::Instance()->Init(WinProgram::Instance()->GetHINSTANCE(), WinProgram::Instance()->GetHWND());

	ErrorManager::Instance()->DisplayErrors();
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
	WinProgram::Instance()->ProcessEvents();

	KM::Timer::Instance()->Update();
	
	Controller::Instance()->Update();
	
	LevelManager::Instance()->Update();

	ErrorManager::Instance()->DisplayErrors();
}

//=======================================================================================================
//FunctionName
//=======================================================================================================
void Engine::Render(void) 
{
	LevelManager::Instance()->Render();

	WinProgram::Instance()->BufferSwap();
	
	ErrorManager::Instance()->DisplayErrors();
}

//==========================================================================================================================
//
//Singleton functions
//
//==========================================================================================================================
shared_ptr<Engine> Engine::_instance = NULL;

shared_ptr<Engine> Engine::Instance(void) 
{
	if(_instance == NULL) 
	{ 
		_instance = shared_ptr<Engine>(new Engine()); 
	}

	return _instance;
}