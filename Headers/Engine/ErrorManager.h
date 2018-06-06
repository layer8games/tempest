#pragma once

//=====Engine includes=====
#include <Engine/Atom.h>

//=====STL includes=====
#include <map>
using std::map;

namespace KillerEngine 
{
	
//==========================================================================================================================
//
//Enum Error codes
//
//==========================================================================================================================
/*! \file ErrorManager.h */
/*! \enum ErrorCode Error codes that are used to give a hint as to where to code that is throwing the error is written. These are disaplyed
	to the user in a pop up window when the end application is run. These are paired with a more detailed message when the
	end error is set. */	
	enum ErrorCode 
	{
		EC_NoError = 0, 		///< Default value. Shouldn't ever be used.
		EC_Unknown,				///< Fall through code, indicates an error in the setting of an error.
		EC_Game,				///< Indicates the error is in the end application, or the game, not the engine.
		EC_Engine,				///< Indicates the error is in the engine's main code, not very specific.
		EC_Physics,				///< Indicates the error is in the KillerPhysics namespace. 
		EC_Windows,				///< Indicates that the error is related to the windowing system. 
		EC_OpenGL,				///< Indicates that the error is in OpenGL related code.
		EC_OpenGL_Shader,		///< Indicates that the error is caused by OpenGL shader compilation.
		EC_DirectInput,			///< Depricated. Indicates that the error is with the DirectInput setup.
		EC_TextureManager,		///< Indicates that the error occured when trying to load a texture into memory.
		EC_GameObject,			///< Indicates that the issue is in a game object specifically. 
	};
//==========================================================================================================================
//Documentation
//==========================================================================================================================
/*! A singleton class that will display any errors that can happen during the initialization of any of the components of the 
	engine. It will be flushed out later to include more details.  */
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