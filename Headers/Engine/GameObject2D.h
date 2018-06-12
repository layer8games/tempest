#pragma once

//===== Engine Includes ======
#include <Engine/Atom.h>
#include <Engine/Sprite.h>
#include <Engine/Texture.h>
#include <Engine/ErrorManager.h>
#include <Engine/Vector2.h>
#include <Engine/Color.h>

namespace KM = KillerMath;

namespace KillerEngine 
{
//==========================================================================================================================
//Documentation
//==========================================================================================================================
/*! The Game Object is the abstract class, (PURE VIRTUAL) that all objects that will be placed in the game will inherit from. 
	It will hold and define the cell, and will include all calls for updating and rendering. Therewill be a component map 
	which will hold anything that the object will need in the game. 

	All of the functions in this class are inlined becuase they are all trivial. The virtual functions are there so that the 
	interface can be the same for all derived classes. By doing this, the world manager will be able to have a map of 
	GameObjects to be rendered in a specific world. 

	The GameObject itself is an interface to generic functions that each object that will be rendered will need to be drawn to 
	the screen. The GameObject holds a private Sprite member that will contain all the logic for which rendering algorithm is 
	used. 

	Accessors are created for the derived classes to access the cell, but the cell is to be accessed directly only by the 
	GameObject itself. 

	GameObject2D will specifically apply to 2D game objects.  */
	class GameObject2D
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
/*! Default Constsructor. Set's all members to 0 and _active to true. SetID() is called as part of the body */
		GameObject2D(void);

/*! Copy Constructor. Calls GetID(), GetActive(), GetSprite(), GetPosition(), GetWidth(), GetHeight(), GetColor() */
		GameObject2D(const GameObject2D& obj);

/*! Destructor. No special functions */
		virtual ~GameObject2D(void);	

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
/*! Pure Virtual fucntion. Will be called during Level::UpdateObjects on each object, which will define what needs to happen 
	in the update section of the loop. */
		virtual void v_Update(void)=0;

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
//=====ID=====		
/*! Returns the ID used for the GameObject2D. */
		inline const U32 GetID(void) const
		{ 
			return _ID; 
		}

/*! Sets the id of this instance. The id is determind by _nextID. This insures that each GameObject3D will have a unique id
	although there could be a collission with GameObject3D::_ID.  */		
		inline void SetID(void) 
		{
			_ID = _nextID;
			++_nextID;
		}

//=====Dimensions=====		
/*! Returns the width of the object. */
		F32 GetWidth(void) const;

/*! Sets the width of the object.
	\param w F32. New width of the object. */
		void SetWidth(F32 w);

/*! Returns the height of the object. */
		F32 GetHeight(void) const;

/*! Sets the height of the object.
	\param h F32. New hieght of the object. */
		void SetHeight(F32 h);

/*! Sets both the width and height of the object.
	\param w F32. New width
	\param h F32. New height */
		void SetDimensions(F32 w, F32 h);

//=====Color=====
/*! Returns the color of the object. This is stored exclusively in the GameObject2D and is not duplicated in the Sprite. */
		const Color& GetColor(void) const;

/*! Sets the color of the object.
	\param col Color&. New Color */
		void SetColor(const Color& col);

/*! Sets the color of the object. This version called Color::SetRed, Color::SetGreen and Color::SetBlue. Note that Color::SetAlpha is not called.
	\param red F32. Red value passed to Color::SetRed
	\param green F32. Green value passed to Color::SetGreen
	\param blue F32. Blue value passed to Color::SetBlue */
		void SetColor(F32 red, F32 green, F32 blue);

//=====Texture=====
/*! Returns curren texture ID for object. Like Color, this value is not duplciated in the Sprite. */
		U32 GetTextureID(void) const;

/*! Sets Texture for the object. 
	\param id U32. Texture id from TextureManager.
	\param top F32. Used for setting up UV coordinates. Represents max "y" in the UV.
	\param bottom F32. Used for setting up UV coordinates. Represents min "y" in uv.
	\param right F32. Used for setting up UV coordinates. Represents max "x" in uv.
	\param left F32. Used for setting up UV coordinates. Represents min "x" in uv. */
		void SetTexture(U32 id, const F32 top, const F32 bottom, const F32 right, const F32 left);

/*! Sets Texture for object. UV's are set to be [0.0f, 1.0f], [0.0f, 1.0f].
	\param id U32. Texture id from TextureManager */
		void SetTexture(U32 id);

//=====Active=====
/*! Returns if object is active or not. Determines if object will have v_Update called, and if it wlll be added to render in Level::UpdateObject
	and in Level::RenderObjects. True indicates that it will be updated and rendered. False indicates that it will not. */
		bool GetActive(void) const;

/*! Sets the active state of the object to true. */
		void SetActive(void);
		
/*! Sets the active state of the object to false. */
		void SetInactive(void);

//=====Sprite=====
/*! Returns the Sprite. This member cannot be set. */
		inline const Sprite& GetSprite(void) const
		{
			return _sprite;
		}

//=====Position=====
/*! Returns the position of the object in World Space. */
		const KM::Vector2& GetPosition(void) const;
		
/*! Sets the position of the object in World Space.
	\param pos Vector2&. New position. */
		void SetPosition(const KM::Vector2& pos);
		
/*! Sets the position of the object in World Space. Calls Vector2::SetX and Vector2::SetY
	\param x F32. X value of new position.
	\param y F32. Y value of new position. */
		void SetPosition(F32 x, F32 y);

/*! Scales the position of the object in World Space. Wrapper for Vector2::AddScaledVector.
	\param v Vector2&. Vector to add to position.
	\param scale F32. Scale to use when adding vector to position. */
		void AddScaledPosition(const KM::Vector2& v, F32 scale);

	private:	
		static U32 				_nextID;		///< Global member used to track the next unique ID for GambeObject2D
		U32 					_ID;			///< ID for this instance of the GameObject2D
		bool 	 				_active;		///< Tracks if the object should be updated and rendered
		Sprite					_sprite;		///< Used for Rendering the object as a 2D Sprite.
		KM::Vector2 			_position;		///< Position in World Space
		F32						_width;			///< Width of the object. 
		F32 					_height;		///< Height of the object.
		Color 					_color;			///< Color of the object.
	};

	

}//End namespace