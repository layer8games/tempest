#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/AudioListener.h>
#include <Engine/AudioClip.h>
#include <Engine/AudioSource.h>

//===== OpenAL =====
#include <OpenAL/al.h>
#include <OpenAL/alc.h>

//===== STL Includes =====
#include <map>

namespace KillerEngine
{
	class AudioListener;
	class AudioClip;
	class AudioSource;

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

		void AddClip(U32 id, shared_ptr<AudioClip> clip);

		void RemoveClip(U32 id);

		void AddSource(U32 id, shared_ptr<AudioSource> source);

		void RemoveSource(U32 id);

		void PlaySource(U32 id);

		void StopSource(U32 id);

		void PauseSource(U32 id);

		void AddClipToSource(U32 clipID, U32 sourceID);

		string GetALCerror(ALCenum error);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		inline void SetListener(shared_ptr<AudioListener> listener)
		{
			_listener = listener;
		}

		inline shared_ptr<AudioListener> GetListener(void)
		{
			return _listener;
		}

		shared_ptr<AudioClip> GetClip(U32 id);

		shared_ptr<AudioSource> GetSource(U32 id);


	protected:
//==========================================================================================================================
//Constructor
//==========================================================================================================================
		AudioManager(void);

	private:
		static shared_ptr<AudioManager> _instance;
		ALCdevice* 						_device;
		ALCcontext* 					_context;
		shared_ptr<AudioListener> _listener;
		std::map<U32, shared_ptr<AudioClip>> _clips;
		std::map<U32, shared_ptr<AudioSource>> _sources;

	};//end Class
}//end Namespace
