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
		WinProgram::Instance()->ShutDown();
		ErrorManager::Instance()->ShutDown();
		Renderer::Instance()->ShutDown();
		MapManager::Instance()->ShutDown();
		TextureManager::Instance()->ShutDown();
		Controller::Instance()->ShutDown();
		KM::Timer::Instance()->ShutDown();

		delete _instance;
	}	

//=======================================================================================================
//Update
//=======================================================================================================
	void KillerEngine2D::Update(void) 
	{
		WinProgram::Instance()->ProcessWndEvents();

		KM::Timer::Instance()->Update();
		
		Controller::Instance()->Update();
		
		MapManager::Instance()->Update();

		ErrorManager::Instance()->DisplayErrors();
	}

//=======================================================================================================
//FunctionName
//=======================================================================================================
	void KillerEngine2D::Render(void) 
	{
		MapManager::Instance()->Render();

		Renderer::Instance()->Draw();

		WinProgram::Instance()->BufferSwap();
		
		ErrorManager::Instance()->DisplayErrors();
	}

//==========================================================================================================================
//
//Singleton functions
//
//==========================================================================================================================
	KillerEngine2D* KillerEngine2D::_instance = NULL;

	KillerEngine2D* KillerEngine2D::Instance(void) 
	{
		if(_instance == NULL) { _instance = new KillerEngine2D(); }

		return _instance;
	}

}//End namespace