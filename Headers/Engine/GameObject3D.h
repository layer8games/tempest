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
#pragma once

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

		GameObject3D(const GameObject3D& obj);

		 virtual ~GameObject3D(void);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
		virtual void v_Update(void)=0;

		virtual void v_Render(void)
		{  }

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================		
//==========================================================================================================================
//ID
//==========================================================================================================================
		inline const U32 GetID(void) const
		{
			return _ID; 
		}

		inline void SetID(void)
		{
			_ID = _nextID;
			++_nextID;
		}

//==========================================================================================================================
//Active
//==========================================================================================================================
		bool GetActive(void) const;

		void SetActive(void);

		void SetInactive(void);

//==========================================================================================================================
//Position
//==========================================================================================================================		
		const KM::Vector3& GetPosition(void) const;

		void SetPosition(const KM::Vector3& pos);

		void SetPosition(F32 x, F32 y, F32 z);

		void AddScaledPosition(const KM::Vector3& v, F32 scale);

//==========================================================================================================================
//Dimensions
//==========================================================================================================================
		F32 GetWidth(void) const;

		void SetWidth(F32 w);

		F32 GetHeight(void) const;

		void SetHeight(F32 h);

		void SetDimensions(F32 w, F32 h);

//==========================================================================================================================
//Model
//==========================================================================================================================
		inline const Model& GetModel(void) const
		{
			return _model;
		}

		inline void SetModel(Model& model)
		{
			_model = model;
		}

		inline void AddVertex(Vertex3D vert)
		{
			_model.AddVertex(vert);
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
		Model			_model;
		KM::Vector3	   	_position;
		F32 			_width;
		F32 			_height;

	};//end Class
}//end Namespace