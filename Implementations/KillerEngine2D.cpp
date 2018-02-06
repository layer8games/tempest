#include <Engine/KillerEngine2D.h>

namespace KillerEngine 
{
//==========================================================================================================================
//
//Constructor
//
//==========================================================================================================================		
	KillerEngine2D::KillerEngine2D(void) 
	{  }

//==========================================================================================================================
//
//Interface
//
//==========================================================================================================================
//=======================================================================================================
//Init
//=======================================================================================================
	void KillerEngine2D::Init(const S32 width, const S32 height, const string title, const bool fullscreen) 
	{
		WinProgram::Instance()->Init(width, height, title, fullscreen);

		//Controller::Instance()->Init(WinProgram::Instance()->GetHINSTANCE(), WinProgram::Instance()->GetHWND());

		ErrorManager::Instance()->DisplayErrors();
	}

//==========================================================================================================================
//ShutDown
//==========================================================================================================================
	void KillerEngine2D::ShutDown(void)
	{
		LevelManager::Instance()->ShutDown();
	}	

//=======================================================================================================
//Update
//=======================================================================================================
	void KillerEngine2D::Update(void) 
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
	void KillerEngine2D::Render(void) 
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
	shared_ptr<KillerEngine2D> KillerEngine2D::_instance = NULL;

	shared_ptr<KillerEngine2D> KillerEngine2D::Instance(void) 
	{
		if(_instance == NULL) 
		{ 
			_instance = shared_ptr<KillerEngine2D>(new KillerEngine2D()); 
		}

		return _instance;
	}

}//End namespace