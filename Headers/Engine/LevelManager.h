/*========================================================================
The holder and controller of the the level objects. This will act as 
both a singleton and a state maching controller, where each level will
be a state that can be set to active. 

For now, all of the states that are to be used will be instantiated 
during the initialization in the main loop, however later, each level
will only be created once it is called, as part of a loading screen.

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#pragma once

//=====Killer1 includes=====
#include <Engine/Atom.h>
#include <Engine/Level.h>
#include <Engine/WinProgram.h>
#include <Engine/GameObject.h>
#include <Engine/ErrorManager.h>

namespace KP = KillerPhysics;

//=====STL includes=====
#include <map>

namespace KillerEngine 
{

	class LevelManager
	{
	public:
		~LevelManager(void);

		static LevelManager* Instance();

		void ShutDown(void)
		{
			delete _instance;
		}

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		void AddLevel(shared_ptr<Level> level);
		
		void RemoveLevel(U32 levelID);
		
		void SetActiveLevel(U32 levelID);
		
		U32 GetActiveLevelID(void) 
		{ 
			return _activeLevelID; 
		}

		inline shared_ptr<Level> GetActiveLevel(void)
		{
			return _activeLevel;
		}

		void EndGame(void)
		{
			WinProgram::Instance()->EndRunning();
		}

		void AddObjectToLevel(U32 id, const GameObject& obj);

		void AddObjectToLevel(U32 id, shared_ptr<GameObject> obj);

		void AddParticleToLevel(U32 id, shared_ptr<KP::Particle>, shared_ptr<KP::ParticleForceGenerator> generator=nullptr);
		
		void RemoveObjectFromLevel(U32 levelID, U32 ojbId);

//==========================================================================================================================
//
//Integrators
//
//==========================================================================================================================

		void Update(void);
		
		void Render(void);

	protected:
		LevelManager(void);

	private:
		std::map<U32, shared_ptr<Level>> _levels;
		shared_ptr<Level> 				 _activeLevel;
		U32 				   			_activeLevelID;			
		static LevelManager*     		_instance;

	};

}//End namespace