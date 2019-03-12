/*========================================================================
A Level is what the different states of game will be. Each Level re-
presents  

The Level can render 2D and 3D objects with and without physics. 

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#pragma once

//===Killer1 includes===
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/GameObject.h>
#include <Engine/WinProgram.h>
#include <Engine/TextureManager.h>
#include <Engine/EnvironmentObject.h>
#include <Engine/Vector4.h>
#include <Engine/Color.h>
#include <Engine/Text.h>
#include <Engine/Particle.h>
#include <Engine/ForceRegistry.h>
#include <Engine/Camera.h>
#include <Engine/Text.h>

namespace KM = KillerMath;
namespace KP = KillerPhysics;

//=====STL includes=====
#include <map>
#include <vector>
#include <fstream>
#include <algorithm>

namespace KillerEngine 
{
/*!
	The Level is the building block for game project. It holds all of the objects that will be rendered to the screen and 
	controls what the update logic is. The Level itself is an abstract class, intended to be implemented on the user end.
	Some engines will call this a scene or a world. 
*/
	class Level
	{
//==========================================================================================================================
//
//Class structs, enums and typedefs
//
//==========================================================================================================================	
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================		
/*!
	Sets call values to 0 and calls default constructors. 
*/
		Level(void);

/*!
	Deletes the pointer to the Camera. 
*/
		virtual ~Level(void);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
/*!
	Abstract function. Used to Initialize the default values, instantiate any objects that will be used and generally get 
	things ready to go.
	\param id is the ID used in the LevelManager.
	\param w is the width of the Level.
	\param h is the height of the Level. 

*/
		virtual void v_InitLevel(U32 id, S32 w, S32 h, Color& c)=0;

/*!
	Abstract function. Used to control what needs to happen during an update. Please note, objects added to the level 
	are already being updated as part of Level::UpdateLevel.
*/
		virtual void v_Update(void)=0;

/*!
	Abstract function. Calls KillerPhysics::ForceRegistry::UpdateForces, then loops over each Physics object, calling
	KillerPhysics::Particle::v_Integrate function. It is virtual to allow for optional customization.
*/
		virtual void v_Integrate(void);
		
/*!
	Wrapper around Level::RenderObjects. It is virtual to allow for optional customization.
*/
		virtual void v_Render(void);

//==========================================================================================================================
//
//Camera Functions
//
//==========================================================================================================================
/*!
	Default actions that need to be called each frame. Right now, that is only Camera::v_Update.
*/
		void UpdateLevel(void);

/*!
	Converts the ref to a smart_ptr and adds the GameObject to the Level.
	\param obj is the object to be added.
*/
		void AddObjectToLevel(const GameObject& obj);

/*!
	Adds GameObject pointer to the Level.
	\param obj is the pointer to be added.
*/
		void AddObjectToLevel(shared_ptr<GameObject> obj);

/*!
	Even though KillerPhysics::Particle is a GameObject, the compiler can't tell the difference. This adds the physics object to 
	the Level.
	\param particle converted to a shared_ptr and added to the level. 
*/
		void AddParticleToLevel(const KP::Particle& particle);

/*!
	Even though KillerPhysics::Particle is a GameObject, the compiler can't tell the difference. This adds the physics object to 
	the Level.
	\param particle is the pointer to be added to the Level.
*/
		void AddParticleToLevel(shared_ptr<KP::Particle> particle);

/*!
	Helper function that allows to add a KillerPhysics::Particle and register it a force at the same time. 
	\param particle is the pointer to add.
	\param is the optional force to register the particle with.
*/
		void AddParticleToLevel(shared_ptr<KP::Particle> particle, shared_ptr<KP::ForceGenerator> generator=nullptr);

/*!
	Registers a KillerPhysics::Particle with a KillerPhysics::ForcerGenerator. This only works because they are pointers. 
	\param particle is the pointer that needs to be registered with the generator. 
	\param generator is the force to apply to the particle.
*/
		inline void RegisterParticleForce(shared_ptr<KP::Particle> particle, shared_ptr<KP::ForceGenerator> generator)
		{
			_forceRegistry.Add(particle, generator);
		}

/*!
	Adds the Glyphs in a Text to the Level as GameObjects.
	\param text is the Text to get the Glyphs from.
*/
		void AddTextToLevel(const Text& text);
		
/*!
	Removes the GameObject with id from the Level.
	\param id of the GameObject to remove.
*/
		void RemoveObjectFromLevel(U32 id);

/*!
	Loops over all of the GameObject and KillerPhysics::Particle that have been added to the Level, and calls GameObject::v_Update
	if they are active for updates. 
*/
		void UpdateObjects(void);

/*!
	Loops over all of the GameObject and KillerPhysics::Particle that have been added to the Level, and calls GameObject::v_Render
	if they are active for rendering. 
*/
		void RenderObjects(void);

		template <class T>
		inline void SetObjectUniforms(string name, const T& type)
		{
			for(auto i : _gameObjects)
			{
				i.second->SetUniform(name, type);
			}

			for(auto i : _particles)
			{
				i.second->SetUniform(name, type);
			}
		}

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================		
/*!
	Changes the set background color for the Level. It also calls Level::ActivateBackgroundColor
*/
		inline void SetBackgroundColor(Color& c) 
		{ 
			_bgColor = c;
			ActivateBackgroundColor();
		}
		
/*!
	Forces the current background color to be activated in OpenGL.
*/
		inline void ActivateBackgroundColor(void) 
		{ 
			WinProgram::Instance()->SetBackgroundColor(_bgColor); 
		}
		
/*!
	Returns the width of the play area of the Level.
*/
		inline S32 GetLevelWidth(void) const 
		{ 
			return _width; 
		}
		
/*!
	Returns the height of the play area of the Level.
*/
		inline S32 GetLevelHeight(void) const 
		{ 
			return _height; 
		}
		
/*!
	Changes the width of the play area of the Level.
	\param w is the new width.
*/
		inline void SetLevelWidth(S32 w)  
		{ 
			_width = w; 
		}
		
/*!
	Changes the height of the play area of the Level.
	\param h is the new height.
*/
		inline void SetLevelHeight(S32 h) 
		{ 
			_height = h; 
		}
		
/*!
	Helper function that allows you to change the play area dimensions at the same time. 
*/
		inline void SetLevelDimensions(S32 w, S32 h) 
		{ 
			_width  = w; 
			_height = h; 
		}
		
/*!
	Set the top bounds.
	\param top is the new border.
*/
		inline void SetTopBorder(S32 top) 
		{ 
			_topBorder = top; 
		}

/*!
	Set the bottom bounds.
	\param bottom is the new border.
*/
		inline void SetBottomBorder(S32 bottom) 
		{ 
			_bottomBorder = bottom; 
		}

/*!
	Set the right bounds.
	\param right is the new border.
*/
		inline void SetRightBorder(S32 right) 
		{ 
			_rightBorder = right;
		}

/*!
	Set the left bounds.
	\param left is the new border.
*/
		inline void SetLeftBorder(S32 left) 
		{ 
			_leftBorder = left; 
		}

/*!
	Helper function to set all borders of the play area of the Level at the same time. 
	\param top is the top border.
	\param bottom is the bottom border.
	\param right is the right border.
	\param left is the left border.
*/
		inline void SetLevelBorders(S32 top, S32 bottom, S32 right, S32 left)
		{
			_topBorder = top;
			_bottomBorder = bottom;
			_leftBorder = left;
			_rightBorder = right;
		}
		
/*!
	Returns the top border.
*/
		inline S32 GetTopBorder(void) const 
		{ 
			return _topBorder; 
		}

/*!
	 Returns the bottom border.
*/
		inline S32 GetBottomBorder(void) const 
		{ 
			return _bottomBorder; 
		}
		
/*!
	Returns the left border.
*/
		inline S32 GetLeftBorder(void) const 
		{ 
			return _leftBorder; 
		}

/*!
	Returns the right border.
*/
		inline S32 GetRightBorder(void) const 
		{
			return _rightBorder; 
		}

/*! 
	 Sets the depth of the play area 
*/
		inline void SetDepth(S32 d)
		{
			_depth = d;
		}

/*! 
	 Returns the depth of the play area.
*/
		inline S32 GetDepth(void)
		{
			return _depth;
		}

/*! 
	 Sets the near border of the play area. 
*/
		inline void SetNearBorder(S32 n)
		{
			_nearBorder = n;
		}

/*! 
	 Sets the far border of the play area. 
*/
		inline void SetFarBorder(S32 f)
		{
			_farBorder = f;
		}

/*! 
	Returns the near border of the play area.  
*/
		inline S32 GetNearBorder(void)
		{
			return _nearBorder;
		}

/*! 
	Returns the far border of the play area.  
*/
		inline S32 GetFarBorder(void)
		{
			return _farBorder;
		}

/*!
	Sets a new ID for the Level. Use with caution.
*/
		inline void SetID(U32 id) 
		{ 
			_ID = id; 
		}

/*!
	Returns the Level ID. This will only match the LevelManager ID if you set it correctly.
*/
		inline U32 GetID(void) const 
		{ 
			return _ID; 
		}

//===== Camera =====
/*!
	Sets the camera to a new Camera pointer, allowing you to change the Camera at run time. 
*/
		inline void SetCamera(Camera* cam)
		{
			_camera = cam;
		}

/*!
	Returns the current Camera.
*/
		inline const Camera* GetCamera(void)
		{
			return _camera;
		}

/*!
	Wrapper around Camera::SetOrthographic.
*/
		inline void SetCameraOrthographic(void)
		{
			_camera->SetOrthographic();
		}
		
	private:
//==========================================================================================================================
//
//Data
//
//==========================================================================================================================		
		S32     _width;												///< Total width of the play area in the Level. Enforced only by convention.
		S32     _height;											///< Total height of the play area in the Level. Enforced only by convention.
		S32     _topBorder;											///< Optional "north" border of the Level.
		S32     _bottomBorder;										///< Optional "south" border of the Level.
		S32     _rightBorder;										///< Optional "east" border of the Level.
		S32     _leftBorder;										///< Optional "west" border of the Level.
		S32		_depth; 											///< Total depth of the play area in the Level.
		S32		_nearBorder;										///< Optional close border of the Level.
		S32 	_farBorder;											///< Optional far border of the Level.
		Color   _bgColor;											///< Color used for the background of the rendering window.
		U32     _ID;												///< ID used in the LevelManager.
		Camera* _camera;											///< Pointer to a Camera object. 
		std::map<U32, shared_ptr<GameObject>>	  _gameObjects;		///< List of all GameObjects included in the Level.
		std::map<U32, shared_ptr<KP::Particle>>   _particles;		///< List of all KillerPhysics::Particles in the Level.
		KP::ForceRegistry _forceRegistry; 							///< KillerPhysics::ForceRegistry used to allow physics forces to be applied.
	};
}//End namespace