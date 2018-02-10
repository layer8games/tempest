#include <Engine/KillerEngine.h>

namespace KillerEngine 
{
//==========================================================================================================================
//
//Constructor
//
//==========================================================================================================================		
	KillerEngine::KillerEngine(void) 
	{  }

//==========================================================================================================================
//
//Interface
//
//==========================================================================================================================
//=======================================================================================================
//Init
//=======================================================================================================
	void KillerEngine::Init(const S32 width, const S32 height, const string title, const bool fullscreen) 
	{
		WinProgram::Instance()->Init(width, height, title, fullscreen);

		//Controller::Instance()->Init(WinProgram::Instance()->GetHINSTANCE(), WinProgram::Instance()->GetHWND());

		ErrorManager::Instance()->DisplayErrors();
	}

//==========================================================================================================================
//ShutDown
//==========================================================================================================================
	void KillerEngine::ShutDown(void)
	{
		LevelManager::Instance()->ShutDown();
	}	

//=======================================================================================================
//Update
//=======================================================================================================
	void KillerEngine::Update(void) 
	{
		WinProgram::Instance()->ProcessWndEvents();

		KM::Timer::Instance()->Update();
		
		Controller::Instance()->Update();
		
		LevelManager::Instance()->Update();

		ErrorManager::Instance()->DisplayErrors();
	}

//=======================================================================================================
//FunctionName
//=======================================================================================================
	void KillerEngine::Render(void) 
	{
		LevelManager::Instance()->Render();

		//Renderer::Instance()->Draw();

		WinProgram::Instance()->BufferSwap();
		
		ErrorManager::Instance()->DisplayErrors();
	}

//==========================================================================================================================
//
//Singleton functions
//
//==========================================================================================================================
	shared_ptr<KillerEngine> KillerEngine::_instance = NULL;

	shared_ptr<KillerEngine> KillerEngine::Instance(void) 
	{
		if(_instance == NULL) 
		{ 
			_instance = shared_ptr<KillerEngine>(new KillerEngine()); 
		}

		return _instance;
	}

}//End namespace