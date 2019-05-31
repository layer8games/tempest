#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/AudioManager.h>
#include <Engine/Vector3.h>
#include <Engine/AudioClip.h>

namespace KM = KillerMath;

namespace KillerEngine
{
	class AudioClip;

	class AudioSource
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		AudioSource(void);

		~AudioSource(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
		void Play(void);

		void Stop(void);

		void Pause(void);

		void AddClip(shared_ptr<AudioClip> clip);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		inline bool GetPlaying(void) const
		{
			return _playing;
		}

		void SetLooping(bool state);

		inline bool GetLooping(void) const
		{
			return _looping;
		}

		inline const U32 GetSourceID(void) const
		{
			return _sourceID;
		}

		void SetPitch(F32 pitch);

		inline F32 GetPitch(void) const
		{
			return _pitch;
		}

		void SetGain(F32 gain);

		inline F32 GetGain(void) const
		{
			return _gain;
		}

		void SetPosition(const KM::Vector3& pos);

		void SetPosition(F32 xVal, F32 yVal, F32 zVal);

		const KM::Vector3& GetPosition(void) const
		{
			return _position;
		}

		void SetVelocity(const KM::Vector3& vel);

		void SetVelocity(F32 xVal, F32 yVal, F32 zVal);

		const KM::Vector3& GetVelocity(void) const
		{
			return _velocity;
		}

		const shared_ptr<AudioClip> GetClip(void) const
		{
			if(_clip == nullptr)
			{
				return nullptr;
			}
			
			return _clip;
		}

	private:
		bool _playing;
		bool _looping;
		U32 _sourceID;
		F32 _pitch;
		F32 _gain;
		KM::Vector3 _position;
		KM::Vector3 _velocity;
		shared_ptr<AudioClip> _clip; ///< AudioClip holds the buffer the plays the sounds. Assume one clip per source for now.
	};//end Class
}//end Namespace
