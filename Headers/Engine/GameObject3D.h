/*========================================================================
The Game Object is the abstract class, (PURE VIRTUAL) that all objects that 
will be placed in the game will inherit from. It will hold and define the 
cell, and will include all calls for updating and rendering. Therewill be a 
component map which will hold anything that the object will need in the game. 

All of the functions in this class are inlined becuase they are all 
trivial. The virtual functions are there so that the interface can
be the same for all derived classes. By doing this, the world manager
will be able to have a map of GameObjects to be rendered in a specific
world. 

The GameObject itself is an interface to generic functions that each obj-
ect that will be rendered will need to be drawn to the screen. The GameObj-
ect holds a private Sprite member that will contain all the logic for which
rendering algorithm is used. 

Accessors are created for the derived classes to access the cell, but the 
cell is to be accessed directly only by the GameObject itself.

GameObject3D will specficially apply to 3D game objects. 

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#ifndef GAME_OBJECT3D_H
#define GAME_OBJECT3D_H

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/Vector3.h>
#include <Engine/Model.h>

namespace KM = KillerMath;

namespace KillerEngine
{
	class GameObject3D
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		GameObject3D(void);

		~GameObject3D(void);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
		virtual void v_Update(void)=0;

		virtual void v_Render(void)=0;

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================		
//==========================================================================================================================
//ID
//==========================================================================================================================
		const U32 GetID(void)
		{
			return _ID; 
		}

		void SetID(void)
		{
			_ID = _nextID;
			++_nextID;
		}

//==========================================================================================================================
//Active
//==========================================================================================================================
		const bool GetActive(void)
		{
			return _active;
		}

		void SetActive(void)
		{
			_active = true; 
		}

		void SetInactive(void)
		{
			_active = false; 
		}

//==========================================================================================================================
//Position
//==========================================================================================================================		
		const KM::Vector3& GetPosition(void)
		{
			return _position;
		}

		void SetPosition(KM::Vector3& pos)
		{
			_position = pos; 
		}

//==========================================================================================================================
//Vecocity [as heading]
//==========================================================================================================================		
		const KM::Vector3& GetVelocity(void)
		{
			return _velocity;
		}

		void SetVelocity(KM::Vector3& vel)
		{
			_velocity = vel;
		}

//==========================================================================================================================
//Acceleration
//==========================================================================================================================		
		const KM::Vector3& GetAcceleration(void)
		{
			return _acceleration;
		}

		void SetAcceleration(const KM::Vector3& acc)
		{
			_acceleration = acc; 
		}
//==========================================================================================================================
//Scale
//==========================================================================================================================
		F32 GetScale(void)
		{
			return _scale;
		}

		void SetScale(F32 s)
		{
			_scale = s; 
		}

//==========================================================================================================================
//Model
//==========================================================================================================================
		Model& GetModel(void)
		{
			return _model;
		}

		void SetModel(Model& model)
		{
			_model = model;
		}
//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
	private:
		static U32 		_nextID;
		U32		   		_ID;
		bool	   		_active;
		KM::Vector3	   	_position;
		KM::Vector3	   	_velocity;
		KM::Vector3		_acceleration;
		F32 			_scale;
		Model			_model;

	};//end Class
}//end Namespace
#endif