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

namespace Tempest
{
	class AudioListener;
	class AudioClip;
	class AudioSource;

///	Global manager to hold cached AudioSources and AudioClips. It can start and stop cached sources, and assign clips to sources
///	that have been registered with it. It does this using a map. ID's are U32 value. The values are pointers. It also holds the
///	single context and device for the game. Later, there may be a need to have multiple contextes. If this happens, this will
///	need to be abstracted out to its own class. The manager follows the same singleton pattern as other managers in the KillerEngine.
	class TEMPEST_API AudioManager
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
///	Sets the AudioListener pointer to nullptr, clears out all AudioClips and AudioSources, and deletes the OpenAL context and
///	device. 
		~AudioManager(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
///	Singleton pattern. Returns a pointer to the global instance of the manager. 
		static shared_ptr<AudioManager> Instance(void);

///	Registers an AudioClip with an ID to the manager. 
///	\param id is the unique ID for this clip. 
///	\param clip is a pointer to the clip to register with the manager.
		void AddClip(U32 id, shared_ptr<AudioClip> clip);

///	Experimental function. It needs to be tested if this created memory issues. It created a new pointer to an AudioClip, and 
///	calls AudioClip::LoadWAV, then registers this with the manager.
///	\param id is the unique ID used to register the clip after creation. 
///	\param filepath is the path to the audio file used by the clip.
		void LoadClip(U32 id, string filepath);

///	Unregisters an AudioClip from the manager.
///	\param id is the unique ID for the clip that is to be unregistered. 
		void RemoveClip(U32 id);

///	Registers an AudioSource with ID to the manager.
///	\param id is the unique ID for this source. 
///	\param source is a pointer to the source to register with the manager.
		void AddSource(U32 id, shared_ptr<AudioSource> source);

///	Experimental function. This created a new AudioSource pointer that is then registered with the manager for later use.
///	It needs to be test if this creates any memory issues.
///	\param id is the unique ID used to register the new source 
		void LoadSource(U32 id);

///	Unregisters an AudioSource from the manager. 
///	\param id is the unique ID of the source to unregister from the manager.
		void RemoveSource(U32 id);

///	Calls AudioSource::Play on the source with the given ID. No check is done in the manager to make sure this works, it 
///	relies on the source to do any checking. 
///	\param id is the unique ID of the source to play.
		void PlaySource(U32 id);

///	Calls AudioSource::Stop on the source with the given ID. No check is done in the manager to make sure this works, it 
///	relies on the source to do any checking. 
///	\param id is the unique ID of the source to Stop.
		void StopSource(U32 id);

///	Calls AudioSource::Pause on the source with the given ID. No check is done in the manager to make sure this works, it 
///	relies on the source to do any checking. 
///	\param id is the unique ID of the source to Pause.
		void PauseSource(U32 id);

///	Calls AudioSource::Restart on the source with the given ID. No check is done in the manager to make sure this works, it 
///	relies on the source to do any checking. 
///	\param id is the unique ID of the source to Restart.
		void RestartSource(U32 id);

///	Assigns a registered AudioClip to a registered AudioSource in the manager. This is a helper function for better abstract
///	operations.
///	\param clipID is the ID of the clip that is assigned. 
///	\param sourceID si the ID of the source that will be assigned the clip.
		void AddClipToSource(U32 clipID, U32 sourceID);

///	Helper function that returns a string version of an OpenAL error. Used any time that you need to convert and OpenAL error
///	code into a string.
///	\param error is the OpenAL error code returned by alGetError().
		string GetALCerror(ALCenum error);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
///	Experimental function. Sets the listener to a new pointer. This needs to be tested to see if it causes any memory issues.
		inline void SetListener(void)
		{
			_listener = make_shared<AudioListener>();
		}

///	Sets the listener to the given pointer. 
///	\param listener is the new pointer that will be used.
		inline void SetListener(shared_ptr<AudioListener> listener)
		{
			_listener = listener;
		}

///	Returns a pointer to the current listener. Note, this is NOT const. This was done as a pattern experiment. Instead of 
///	writting functions for all the different operations you may want to perform on a listener, it is returned as writable
///	so that you can call any functions that you need to.
		inline shared_ptr<AudioListener> GetListener(void)
		{
			return _listener;
		}

///	Returns the registered AudioClip with the given ID. If no clip is found with the ID, a nullptr is returned. 
///	\param id is the unique ID for the desired clip.
		shared_ptr<AudioClip> GetClip(U32 id);

///	Returns the registered AudioSource wit h the given ID. If no source is found with the ID, a nullptr is returned. \
///	\param id is the unique ID for the desired source.
		shared_ptr<AudioSource> GetSource(U32 id);


	protected:
//==========================================================================================================================
//Constructor
//==========================================================================================================================
///	Created the OpenAL device handle and context handle. Also contains commented out code that would return a list of available
///	devices, if it is ever desired to allow a user to select which device they would like the audio to play on.
		AudioManager(void);

	private:
		static shared_ptr<AudioManager> 	   _instance; 	///< Global instance of the manager. Singleton pattern.
		ALCdevice* 							   _device;		///< OpenAL device handle.
		ALCcontext* 						   _context;	///< OpenAL context handle.
		shared_ptr<AudioListener> 			   _listener;	///< Pointer to the listener for this context.
		std::map<U32, shared_ptr<AudioClip>>   _clips;		///< Collection of registered clips.
		std::map<U32, shared_ptr<AudioSource>> _sources;	///< Collection of registered sources.

	};//end Class
}//end Namespace
