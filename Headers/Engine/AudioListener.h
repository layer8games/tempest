#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Vector3.h>
#include <Engine/AudioManager.h>

namespace TM = TempestMath;

namespace Tempest
{
/// In OpenAL, the listener is the hearer of any playing AudioSources. This is how 3D sound is achieved. This is a wrapper
/// around OpenAL calls that set the internal state of the listener in OpenAL. These should be viewed as in World Coordinate
/// space.
	class TEMPEST_API AudioListener
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
/// Calls AudioManger::Instace to insure that there is an OpenAL device and context already set up.
		AudioListener(void);

/// No implemenatation. The listener is not an OpenAL object, it is just a state of the context, since each context can only
/// ever have a single listener.
		~AudioListener(void);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
/// Returns the current orientation of the listener. Note, this is the cached version, OpenAL is not queried for these values.
		inline const F32* GetOrientation(void) const
		{
			return _orientation;
		}

/// Sets a new orientation for the listener. This needs to be a 6 value array, or there will be issues.
/// \param orienation is the new orientation as an array.
		void SetOrientation(F32* orientation);

/// Sets a new orientation for the listener. This needs to be a 6 value array, or there will be issues. 
/// \param orienation is the new orientation as an array.
///	void SetOrientation(F32* orientation);

/// Returns the current position of the listenser. Note, this is the cached version, OpenAL is not queried for these values.
		inline const TM::Vector3& GetPosition(void) const
		{
			return _position;
		}

/// Sets the new position state of the listener.
/// \param pos is the new position in world space.
		void SetPosition(const TM::Vector3& pos);

/// Sets the new position state of the listener.
/// \param xVal is the new x position in world space.
///  \param yVal is the new y position in world space.
/// \param zVal is the new z position in world space.
		void SetPosition(F32 xVal, F32 yVal, F32 zVal);

/// Returns the current velocity of the listenser. Note, this is the cached version, OpenAL is not queried for these values.
		inline const TM::Vector3& GetVelocity(void) const
		{
			return _velocity;
		}

/// Sets the new velocity state of the listener.
/// \param vel is the new velocity in world space.
		void SetVelocity(const TM::Vector3 vel);

/// Sets the new velocity state of the listener.
/// \param xVal is the new x velocity in world space.
/// \param yVal is the new y velocity in world space.
/// \param zVal is the new z velocity in world space.
		void SetVelocity(F32 xVal, F32 yVal, F32 zVal);

	private:
		F32 		_orientation[6]; ///< Orientation of the listener. Not sure what the 6 values really mean. This can probably be changed.
		TM::Vector3 _position;		 ///< Position of the listener in world space. 
		TM::Vector3 _velocity;		 ///< Velocity of the listener in world space.

	};//end Class
	typedef shared_ptr<AudioListener> p_AudioListener;
}//end Namespace
