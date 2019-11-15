#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/AudioManager.h>
#include <Engine/Vector3.h>
#include <Engine/AudioClip.h>

namespace TM = TempestMath;

namespace Tempest
{
	class AudioClip;

	/// An AudioSource is the location from which an AudioClip will play. This holds a clip, a position, and velocity, and can
	/// be told to start, stop or pause its play. Currently the source only supports one clip, but later could support many
	/// clips in the form of buffers. This is a more advanced way to use OpenAL that is currently not supported. 
	class TEMPEST_API AudioSource
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
	/// Calls AudioManager::Instance to make sure that there is a device and context set up before the source is created with 
	/// OpenAL. It then sets up the source with OpenAL and saves the handle for use later. 
		AudioSource(void);

	/// Sets the AudioClip that this source has to a nullptr, then deletes its handle with OpenAL.
		~AudioSource(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
	/// Plays the clip that this source has. If the clip is already playing, nothing happens. This is different from what OpenAL 
	/// does, where it will start a clip over if it is already playing. 
		void Play(void);

	/// Stops the clip from playing, if it is playing currently. If the clip is not playing, it does not do anyything. If 
	/// AudioSource::Play is called again, the clip will begin again from the start.
		void Stop(void);

	/// Pauses the clip in its currently play. If AudioSource::Play is called again, it will start from its current place.
		void Pause(void);

	/// If the clip is already playing, then it will start the clip over from the beginning. If it is not currently playing, 
	/// then it will start playing from the beginning. 
		void Restart(void);

	/// Sets the clip that this source will use when it is played. 
	/// \param clip is a pointer to the clip that will be played. The clip should already have data, using the AudioClip::LoadWAV
	/// function. If it does not, then this will not play anything. 
		void AddClip(shared_ptr<AudioClip> clip);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
	/// Returns true if the clip is already playing. 
		bool GetPlaying(void) const;

	 /// Sets if the clip should loop as it plays. 
	 /// \param state should be true if you want the clip to loop, and false if you do not. 
		void SetLooping(bool state);

	/// Returns the current looping state of the clip on the source. 
		inline bool GetLooping(void) const
		{
			return _looping;
		}

	 /// Returns the OpenAL source handle.
		inline const U32 GetSourceID(void) const
		{
			return _sourceID;
		}

	/// Sets the pitch level for the source. This makes a call to OpenAL to set the state in OpenAL.
	/// \param pitch is the new pitch level. 
		void SetPitch(F32 pitch);

	/// Returns the current pitch level. Note, this is the cached version, it does not query OpenAL for this value. 
		inline F32 GetPitch(void) const
		{
			return _pitch;
		}

	/// Sets the gain level for the source. This makes a call to OpenAL to set the state in OpenAL.
	/// \param gain is the new gain level.
		void SetGain(F32 gain);

	/// Returns the current gain level. Note, this is the cached version, it doe snot query OpenAL for this value.
		inline F32 GetGain(void) const
		{
			return _gain;
		}

	/// Sets the position of the source in the sound space. This should be the same as world space. This makes a call to set 
	/// the position in OpenAL. 
	/// \param pos is the new position of the source. 
		void SetPosition(const TM::Vector3& pos);

	/// Sets the position of the source in the sound space. This should be the same as world space. This makes a call to set 
	/// the position in OpenAL. 
	/// \param xVal is the new x position of the source.
	/// \param yVal is the new y position of the source.
	/// \param zVal is the new z position of the source.
		void SetPosition(F32 xVal, F32 yVal, F32 zVal);

	/// Returns the position of the source. This should be in world space. Note, this is the cached version, it does not query 
	/// OpenAL for this value. 
		const TM::Vector3& GetPosition(void) const
		{
			return _position;
		}

	/// Sets the velocity of the source in the sound space. This should be in world space coordinates. This makes a call to set 
	/// the velocity in OpenAL. 
	/// \param vel is the new velocity of the source. 
		void SetVelocity(const TM::Vector3& vel);

	/// Sets the velocity of the source in the sound space. This should be in world space coordinates. This makes a call to set 
	/// the velocity in OpenAL. 
	/// \param xVal is the new x velocity of the source.
	/// \param yVal is the new y velocity of the source.
	/// \param zVal is the new z velocity of the source.
		void SetVelocity(F32 xVal, F32 yVal, F32 zVal);

	/// Returns the velocity of the source. This should be in world space. Note, this is the cached version, it does not query 
	/// OpenAL for this value. 
		const TM::Vector3& GetVelocity(void) const
		{
			return _velocity;
		}

	/// Returns a pointer to the clip this source uses. Note this is a const pointer, so you can't write it.
		const shared_ptr<AudioClip> GetClip(void) const
		{	
			return _clip;
		}

	private:
//==========================================================================================================================
//
//Private Functions
//
//==========================================================================================================================		
		S32 _GetPlayState(void) const;
		
		bool _looping;				 ///< True if the source should loop when it reaches the end.
		U32 _sourceID;				 ///< OpenAL handle to the source generated in OpenAL.
		F32 _pitch;					 ///< Pitch level for the source.
		F32 _gain;					 ///< Gain level for the source.
		TM::Vector3 _position;		 ///< World space position of the source.
		TM::Vector3 _velocity;		 ///< World space velocity of the source.
		shared_ptr<AudioClip> _clip; ///< AudioClip holds the buffer the plays the sounds. Assume one clip per source for now.
	};//end Class
	typedef shared_ptr<AudioSource> p_AudioSource;
}//end Namespace
