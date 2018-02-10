/*========================================================================
A singleton class that will display any errors that can happen during
the initialization of any of the components of the engine. It will be
flushed out later to include more details. 

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#pragma once

//=====Engine includes=====
#include <Engine/Atom.h>

//=====STL includes=====
#include <map>
using std::map;
#include <memory>
using std::shared_ptr;

namespace KillerEngine 
{
	
//==========================================================================================================================
//
//Enum Error codes
//
//==========================================================================================================================
	enum ErrorCode 
	{
		EC_NoError = 0,
		EC_Unknown,
		EC_Game,
		EC_KillerEngine,
		EC_Windows,
		EC_OpenGL,
		EC_OpenGL_Shader,
		EC_DirectInput,
		EC_TextureManager,
		EC_GameObject,
	};

	class ErrorManager 
	{
public:
//==========================================================================================================================
//
//Destructor
//
//==========================================================================================================================
		~ErrorManager(void);

//==========================================================================================================================
//
//Singleton Functions
//
//==========================================================================================================================		
		static shared_ptr<ErrorManager> Instance(void);

//==========================================================================================================================
//
//ErrorManager Functions
//
//==========================================================================================================================
		void SetError(ErrorCode code, string message);
		
		void DisplayErrors(void);

protected:
//==========================================================================================================================
//
//Constructor
//
//==========================================================================================================================
		ErrorManager(void);

private:
		static shared_ptr<ErrorManager> _instance;

		U32       			 _numErrors;
		map<U32, ErrorCode>  _errorCodes;
		map<U32, string>     _errorMessages;
	};//End class
}//End namespace