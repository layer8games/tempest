#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Vector3.h>
#include <Engine/AudioManager.h>

namespace KM = KillerMath;

namespace KillerEngine
{
	class AudioListener
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		AudioListener(void);

		~AudioListener(void);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		inline const F32* GetOrientation(void) const
		{
			return _orientation;
		}

		void SetOrientation(F32* orientation);

		inline const KM::Vector3& GetPosition(void) const
		{
			return _position;
		}

		void SetPosition(const KM::Vector3& pos);

		inline const KM::Vector3& GetVelocity(void) const
		{
			return _velocity;
		}

		void SetVelocity(const KM::Vector3 vel);


	private:
		F32* 		_orientation;
		KM::Vector3 _position;
		KM::Vector3 _velocity;

	};//end Class
}//end Namespace
