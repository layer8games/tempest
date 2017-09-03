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

GameObject2D will specifically apply to 2D game objects. 

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#ifndef GAME_OBJECT2D_H
#define GAME_OBJECT2D_H

//===== Engine Includes ======
#include <Engine/Atom.h>
#include <Engine/Sprite.h>
#include <Engine/Texture.hpp>
#include <Engine/ErrorManager.h>
#include <Engine/Vector2.h>
#include <Engine/Color.h>

namespace KM = KillerMath;

//===== STD includes =====
#include <memory>

namespace KillerEngine 
{
	
	class GameObject2D
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		GameObject2D(void);

		virtual ~GameObject2D(void);

		//void v_ShutDown(void);		

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
//=====ID=====		
		const U32 GetID(void) 
		{ 
			return _ID; 
		}

		void SetID(void) 
		{
			_ID = _nextID;
			++_nextID;
		}

//=====Dimensions=====
//Settings are virtual so that each GameObject
//Can make sure to update its sprite, if it has one
//with a default version in the case of no sprite.
		
		virtual const F32 GetWidth(void);

		virtual void SetWidth(F32 w);

		virtual const F32 GetHeight(void);

		virtual void SetHeight(F32 h);

		virtual void SetDimensions(F32 w, F32 h);

//=====Color=====
		const Color& GetColor(void);

		void SetColor(Color& col);

		void SetColor(F32 red, F32 blue, F32 green);

//=====Texture=====
		const  U32 GetTextureID(void);

		void SetTexture(U32 id, const F32 top, const F32 bottom, const F32 right, const F32 left);

		void SetTexture(U32 id);

//=====Active=====
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

//=====Sprite=====
		const std::shared_ptr<Sprite> GetSprite(void);

		void SetSprite(Sprite* p_Sprite) 
		{ 
			_sprite = std::shared_ptr<Sprite>(p_Sprite); 
		}	

		void RenderSprite(void);

//=====Position=====
		KM::Vector2& GetPosition(void) 
		{ 
			return _position; 
		}
		
		void SetPosition(KM::Vector2& pos) 
		{ 
			_position = pos;
			_sprite->SetPosition(_position); 
		}

		void SetPosition(F32 x, F32 y) 
		{ 
			_position = KM::Vector2(x, y);
			_sprite->SetPosition(_position);
		}

		void ScalePosition(const KM::Vector2& v, F32 scale)
		{				
			_position.AddScaledVector(v, scale);
			_sprite->SetPosition(_position);
		}

		void virtual v_SetPosition(KM::Vector2& pos)
		{
			_position = pos;
		}

		void virtual v_SetPosition(F32 x, F32 y)
		{
			_position = KM::Vector2(x, y);
		}

		void virtual v_ScalePosition(const KM::Vector2& v, F32 scale)
		{
			_position.AddScaledVector(v, scale);
		}

//=====Velocity=====
		const KM::Vector2& GetVelocity(void) 
		{ 
			return _velocity; 
		}

		void SetVelocity(KM::Vector2& v) 
		{ 
			_velocity = v; 
		}

		void ScaleVelocity(const KM::Vector2& vec, F32 scale)
		{
			_velocity.AddScaledVector(vec, scale);
		}

		void SetVelocity(F32 x, F32 y) 
		{ 
			_velocity = KM::Vector2(x, y); 
		}

//=====Acceleration=====
		const KM::Vector2& GetAcceleration(void) 
		{ 
			return _acceleration; 
		}

		void SetAcceleration(KM::Vector2& a) 
		{ 
			_acceleration = a; 
		}

		void ScaleAcceleration(const KM::Vector2& vec, F32 scale)
		{
			_acceleration.AddScaledVector(vec, scale);
		}

		void SetAcceleration(F32 x, F32 y) 
		{
		 	_acceleration = KM::Vector2(x, y); 
		}

	protected:
//==========================================================================================================================
//
//GameObject Functions
//
//==========================================================================================================================
//=====Sprite Factories=====
//==SqrSprite==
		void CreateSqrSprite(KM::Vector2& pos, Color& col, Texture& texture);
		
		void CreateSqrSprite(void);


	private:	
		static U32 				_nextID;
		U32 					_ID;
		bool 	 				_active;
		std::shared_ptr<Sprite>	_sprite;
		KM::Vector2 			_position;
		KM::Vector2				_velocity;
		KM::Vector2				_acceleration;	
	};

	

}//End namespace

#endif