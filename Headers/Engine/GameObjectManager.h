#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>

namespace Tempest
{
/// A general manager class for all GameObject that are created. In the past, there have been a lot of issues with the way that
/// GameObjects are stored. In the past, this was done in the Level, but this creates issues with persistence and ownership. 
/// The purpose of this manager is to simplify this by registering all GameObjects in the GameObjectManager, using their ID 
/// as their lookup key. The Level will then store just the ID of the GameObjects that it cares about, or that it registered, 
/// and will look these up for rendering and updating. Only persisten, multilevel objects should be registered in this way. 
	class GameObjectManager
	{
	public:
	//==========================================================================================================================
	//
	//Constructors	 	
	//
	//==========================================================================================================================
		~GameObjectManager(void);

	//==========================================================================================================================
	//
	//Functions
	//
	//==========================================================================================================================
		static shared_ptr<GameObjectManager> Instance(void);

	protected:
		GameObjectManager(void);

	private:
		static shared_ptr<GameObjectManager> _instance;

	};//end Class
	typedef shared_ptr<GameObjectManager> p_GameObjectManager;
}