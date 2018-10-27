#include <Engine/ErrorManager.h>
#include <iostream>
	
using namespace KillerEngine;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
ErrorManager::ErrorManager(void) 
: 
_numErrors(0) 
{  }

ErrorManager::~ErrorManager(void)
{  }

//==========================================================================================================================
//
//Singleton Functions
//
//==========================================================================================================================
shared_ptr<ErrorManager> ErrorManager::_instance = NULL;

shared_ptr<ErrorManager> ErrorManager::Instance(void) 
{
	if(_instance == NULL) 
	{ 
		_instance = shared_ptr<ErrorManager>(new ErrorManager()); 
	}
	return _instance;
}

//==========================================================================================================================
//
//ErrorManager Functions
//
//==========================================================================================================================
//=======================================================================================================
//SetError
//=======================================================================================================	
void ErrorManager::SetError(ErrorCode code, string message) 
{
	_errorCodes[_numErrors]	   = code;
	_errorMessages[_numErrors] = message;
	_numErrors++;
}

//=======================================================================================================
//DisplayErrors
//=======================================================================================================
void ErrorManager::DisplayErrors(void) 
{
	if (_numErrors > 0) 
	{
		for (U32 i = 0; i < _numErrors; i++) 
		{
			switch (_errorCodes[i]) 
			{
				case NOT_ERROR:
					//TODO::Need to log these some how
				break;					 
				case UNKNOWN_ERROR: 
					std::cout << "UNKNOWN_ERROR: " << _errorMessages[i].c_str() << std::endl;
					MessageBox(NULL, _errorMessages[i].c_str(), "UNKNOWN", MB_ICONERROR | MB_OK);					
				break;
				case APPLICATION: 
					std::cout << "APPLICATION Error: " << _errorMessages[i].c_str() << std::endl;
					MessageBox(NULL, _errorMessages[i].c_str(), "APPLICATION", MB_ICONERROR | MB_OK);					
				break;
				case ENGINE: 
					std::cout << "ENGINE Error: " << _errorMessages[i].c_str() << std::endl;
					MessageBox(NULL, _errorMessages[i].c_str(), "KILLER_ENGINE", MB_ICONERROR | MB_OK);					
				break;
				case PHYSICS: 
					std::cout << "PHYCIS Error: " << _errorMessages[i].c_str() << std::endl;
					MessageBox(NULL, _errorMessages[i].c_str(), "PHYCIS", MB_ICONERROR | MB_OK);					
				break;
				case WINDOWS: 
					std::cout << "WINDOWS Error: " << _errorMessages[i].c_str() << std::endl;
					MessageBox(NULL, _errorMessages[i].c_str(), "WINDOWS", MB_ICONERROR | MB_OK);					
				break;
				case OPENGL: 
					std::cout << "OPENGL Error: " << _errorMessages[i].c_str() << std::endl;
					MessageBox(NULL, _errorMessages[i].c_str(), "OPENGL", MB_ICONERROR | MB_OK);					
				break;
				case SHADER:
					std::cout << "SHADER Error: " << _errorMessages[i].c_str() << std::endl;
					MessageBox(NULL, _errorMessages[i].c_str(), "SHADER", MB_ICONERROR | MB_OK);					
				break;
				case GLFW:
					std::cout << "GLFW Error: " << _errorMessages[i].c_str() << std::endl;
					MessageBox(NULL, _errorMessages[i].c_str(), "GLFW", MB_ICONERROR | MB_OK);					
				break;
				case TEXTURE_MANAGER:
					std::cout << "TEXTURE_MANAGER Error: " << _errorMessages[i].c_str() << std::endl;
					MessageBox(NULL, _errorMessages[i].c_str(), "TEXTURE_MANAGER", MB_ICONERROR | MB_OK);					
				break;
				case GAMEOBJECT:
					std::cout << "GAMEOBJECT Error: " << _errorMessages[i].c_str() << std::endl;
					MessageBox(NULL, _errorMessages[i].c_str(), "GAMEOBJECT", MB_ICONERROR | MB_OK);					
				break;
				case FREETYPE:
					std::cout << "FREETYPE Error: " << _errorMessages[i].c_str() << std::endl;
					MessageBox(NULL, _errorMessages[i].c_str(), "FREETYPE", MB_ICONERROR | MB_OK);					
				break;
				default:
					//TODO::handle case 
				break;
			}
		}	
	}
}