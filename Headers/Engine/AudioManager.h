#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>

//===== OpenAL =====
#include <OpenAL/al.h>
#include <OpenAL/alc.h>

namespace KillerEngine
{
	class AudioManager
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		~AudioManager(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
		static shared_ptr<AudioManager> Instance(void);

		string GetALCerror(ALCenum error);

	protected:
//==========================================================================================================================
//Constructor
//==========================================================================================================================
		AudioManager(void);

	private:
		static shared_ptr<AudioManager> _instance;
		ALCdevice* 						_device;
		ALCcontext* 					_context;
		
	};//end Class
}//end Namespace
