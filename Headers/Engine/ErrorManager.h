#pragma once

//=====Engine includes=====
#include "stdafx.h"
#include <Engine/Atom.h>

//=====STL includes=====
#include <vector>

namespace Tempest 
{
    enum TEMPEST_API ErrorCode 
    {
        NOT_ERROR, 		
        UNKNOWN_ERROR,	
        APPLICATION,	
        ENGINE,			
        MATH, 			
        PHYSICS,		
        WINDOWS,		
        OPENGL,			
        SHADER,			
        GLFW,			 
        TEXTURE_MANAGER, 
        GAMEOBJECT,		
        FREETYPE,		
        AUDIO 			
    };

    class ErrorManager
    {
    public: 
        TEMPEST_API ~ErrorManager(void);
		
        TEMPEST_API static shared_ptr<ErrorManager> Instance(void);

        TEMPEST_API void SetError(ErrorCode code, string message);

        TEMPEST_API void ThrowError(ErrorCode code, string message);

        TEMPEST_API bool DisplayErrors(void);

        TEMPEST_API void SetConsoleOut(bool state);

    protected:
        ErrorManager(void);

    private:
        bool _MessageBox(string errorMessage, string errorCode);

        static shared_ptr<ErrorManager>	_instance;	
        bool _consoleOut;
        U32 _numErrors;	
        std::vector<ErrorCode> _errorCodes;
        std::vector<string> _errorMessages;
    };//End class
    typedef shared_ptr<ErrorManager> p_ErrorManager;
}//End namespace