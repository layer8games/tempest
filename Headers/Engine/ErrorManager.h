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
		NOT_ERROR, 			///< Default value. Shouldn't ever be used.
		UNKNOWN_ERROR,		///< Fall through code, indicates an error in the setting of an error.
		APPLICATION,		///< Indicates and error in the end application, not the engine itself. 
		ENGINE,				///< Indicates the error is in the engine's main code, not very specific.
		MATH, 				///< Indicates an error in the math section of the engine.
		PHYSICS,			///< Indicates the error is in the KillerPhysics namespace. 
		WINDOWS,			///< Indicates that the error is related to the windowing system. 
		OPENGL,				///< Indicates that the error is in OpenGL related code.
		SHADER,				///< Indicates that the error is caused by OpenGL shader compilation.
		GLFW,			 	///< Indicates an error in the code wrapping around the GLFW library. 
		TEXTURE_MANAGER, 	///< Indicates an error in the TextureManager class of the engine. 
		GAMEOBJECT,			///< Indicates an error in the GameObject class of the engine. 
		FREETYPE,			///< Indicates an error in the code wrapper around FreeType.
	};
//==========================================================================================================================
//Documentation
//==========================================================================================================================
/*! A singleton class that will display any errors that can happen during the initialization of any of the components of the 
	engine. It will be flushed out later to include more details. */
	class ErrorManager 
	{
	public:
//==========================================================================================================================
//
//Destructor
//
//==========================================================================================================================
/*! Default destructor. No special actions taken */		
		~ErrorManager(void);

//==========================================================================================================================
//
//Singleton Functions
//
//==========================================================================================================================		
/*! Singlton function. Returns pointer to global ErrorManager instance. */		
		static shared_ptr<ErrorManager> Instance(void);

//==========================================================================================================================
//
//ErrorManager Functions
//
//==========================================================================================================================
/*! Adds an error into the Manager's map of errors. Any number of message can be in the Manager.
	\param code ErrorCode: Displayed to hint where the error happened.
	\param message string: A string that will be displayed to the user giving additional details about the nature of the 
	error. */
		void SetError(ErrorCode code, string message);

/*! Displays any errors that have been added to the manager. This function loops over all the errors that have been added
	and displayed them one by one. Messages are never removed once they are thrown. */		
		void DisplayErrors(void);

	protected:
//==========================================================================================================================
//
//Constructor
//
//==========================================================================================================================
/*! Default constructor. No special actions are taken. Protected because this class follows the singleton pattern */		
		ErrorManager(void);

	private:
		static shared_ptr<ErrorManager> _instance;	///< Global singleton instance.

		U32       			 _numErrors;			///< Total count of errors.
		map<U32, ErrorCode>  _errorCodes;			///< List of active error codes.
		map<U32, string>     _errorMessages;		///< List of active error messages.
	};//End class
}//End namespace