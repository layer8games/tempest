#include "stdafx.h"
#include <Engine/ErrorManager.h>
#include <iostream>
using namespace Tempest;

p_ErrorManager ErrorManager::_instance = nullptr;
ErrorManager::ErrorManager(void) 
:
_consoleOut(false),
_numErrors(0),
_errorCodes(),
_errorMessages()
{  }

ErrorManager::~ErrorManager(void)
{  }

p_ErrorManager ErrorManager::Instance(void) 
{
    if(_instance == NULL) 
    { 
        _instance = p_ErrorManager(new ErrorManager()); 
    }
    return _instance;
}
	
void ErrorManager::SetError(ErrorCode code, string message) 
{
    _errorCodes.push_back(code);
    _errorMessages.push_back(message);
    _numErrors++;
}

void ErrorManager::ThrowError(ErrorCode code, string message)
{
    SetError(code, message);
    DisplayErrors();
}

bool ErrorManager::DisplayErrors(void) 
{
    if (_numErrors > 0) 
    {
        for (U32 i = 0; i < _numErrors; ++i) 
        {
            //Set extra text in message
            _errorMessages[i] += "\nWould you like to close the game?";

            switch (_errorCodes[i]) 
            {
                case NOT_ERROR:
                    //TODO::Need to log these some how
                break;
                case UNKNOWN_ERROR: 
                    if(_consoleOut) 
                    {
                        std::cout << "UNKNOWN_ERROR: " << _errorMessages[i].c_str() << std::endl;
                    }
                    
                    if(_MessageBox(_errorMessages[i], "UNKNOWN_ERROR Found"))
                    {
                        return true;
                    }
                break;
                case APPLICATION: 
                    if(_consoleOut) 
                    {
                        std::cout << "APPLICATION Error: " << _errorMessages[i].c_str() << std::endl;
                    }
                    
                    if(_MessageBox(_errorMessages[i], "APPLICATION Found"))
                    {
                        return true;
                    }
                break;
                case ENGINE: 
                    if(_consoleOut) 
                    {
                        std::cout << "ENGINE Error: " << _errorMessages[i].c_str() << std::endl;
                    }
                    
                    if(_MessageBox(_errorMessages[i], "KILLER_ENGINE Found"))
                    {
                        return true;
                    }
                break;
                case MATH:
                    if(_consoleOut)
                    {
                        std::cout << "MATH error: " << _errorMessages[i].c_str() << std::endl;
                    }
                    
                    if(_MessageBox(_errorMessages[i], "MATH Found"))
                    {
                        return true;
                    }
                break;
                case PHYSICS: 
                    if(_consoleOut)
                    {
                        std::cout << "PHYSICS Error: " << _errorMessages[i].c_str() << std::endl;
                    }
                    
                    if(_MessageBox(_errorMessages[i], "PHYSICS Found"))
                    {
                        return true;
                    }
                break;
                case WINDOWS: 
                    if(_consoleOut)
                    {
                        std::cout << "WINDOWS Error: " << _errorMessages[i].c_str() << std::endl;
                    }
                    
                    if(_MessageBox(_errorMessages[i], "WINDOWS Found"))
                    {
                        return true;
                    }
                break;
                case OPENGL: 
                    if(_consoleOut)
                    {
                        std::cout << "OPENGL Error: " << _errorMessages[i].c_str() << std::endl;
                    }
                    
                    if(_MessageBox(_errorMessages[i], "OPENGL Found"))
                    {
                        return true;
                    }				
                break;
                case SHADER:
                    if(_consoleOut)
                    {
                        std::cout << "SHADER Error: " << _errorMessages[i].c_str() << std::endl;
                    }
                    
                    if(_MessageBox(_errorMessages[i], "SHADER Found"))
                    {
                        return true;
                    }				
                break;
                case GLFW:
                    if(_consoleOut)
                    {
                        std::cout << "GLFW Error: " << _errorMessages[i].c_str() << std::endl;
                    }
                    
                    if(_MessageBox(_errorMessages[i], "GLFW Found"))
                    {
                        return true;
                    }
                break;
                case TEXTURE_MANAGER:
                    if(_consoleOut)
                    {
                        std::cout << "TEXTURE_MANAGER Error: " << _errorMessages[i].c_str() << std::endl;
                    }
                    
                    if(_MessageBox(_errorMessages[i], "TEXTURE_MANAGER Found"))
                    {
                        return true;
                    }
                break;
                case GAMEOBJECT:
                    if(_consoleOut)
                    {
                        std::cout << "GAMEOBJECT Error: " << _errorMessages[i].c_str() << std::endl;
                    }
                    
                    if(_MessageBox(_errorMessages[i], "GAMEOBJECT Found"))
                    {
                        return true;
                    }
                break;
                case FREETYPE:
                    if(_consoleOut)
                    {
                        std::cout << "FREETYPE Error: " << _errorMessages[i].c_str() << std::endl;
                    }
                    
                    if(_MessageBox(_errorMessages[i], "FREETYPE Found"))
                    {
                        return true;
                    }
                break;
                case AUDIO:
                    if(_consoleOut)
                    {
                        std::cout << "AUDIO Error: " << _errorMessages[i].c_str() << std::endl;
                    }
                    
                    if(_MessageBox(_errorMessages[i], "AUDIO Found"))
                    {
                        return true;
                    }
                break;
                default:
                    //TODO::handle case 
                break;
            }
        }

        _errorMessages.clear();
        _errorCodes.clear();
        _numErrors = 0;	
    }

    return false;
}

void ErrorManager::SetConsoleOut(bool state)
{
    _consoleOut = state;
}

bool ErrorManager::_MessageBox(string errorMessage, string errorCode)
{
    if(MessageBox(NULL, errorMessage.c_str(), errorCode.c_str(), MB_ICONERROR | MB_YESNO) == IDYES)
    {
        return true;
    }
    else
    {
        return false;
    }
}