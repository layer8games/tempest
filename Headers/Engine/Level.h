#pragma once

//===Killer1 includes===
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/GameObject2D.h>
#include <Engine/GameWindow.h>
#include <Engine/TextureManager.h>
#include <Engine/EnvironmentObject.h>
#include <Engine/Vector4.h>
#include <Engine/Color.h>
#include <Engine/Text.h>
#include <Engine/ForceRegistry.h>
#include <Engine/Text.h>
#include <Engine/RigidBody2D.h>
#include <Engine/Point.h>

namespace TM = TempestMath;
namespace TP = TempestPhysics;

//===== Third party includes =====
#include <rapidxml.hpp>

//=====STL includes=====
#include <map>
#include <vector>
#include <fstream>
#include <algorithm>

namespace Tempest 
{

	///	The Level is the building block for game project. It holds all of the objects that will be rendered to the screen and 
	///	controls what the update logic is. The Level itself is an abstract class, intended to be implemented on the user end.
	///	Some engines will call this a scene or a world. 
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

		///	Sets call values to 0 and calls default constructors. 
		TEMPEST_API Level(void);


		///	Deletes the pointer to the Camera. 
		TEMPEST_API virtual ~Level(void);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================

		///	Abstract function. Used to Initialize the default values, instantiate any objects that will be used and generally get 
		///	things ready to go.
		///	\param id is the ID used in the LevelManager.
		///	\param w is the width of the Level.
		///	\param h is the height of the Level. 
		TEMPEST_API virtual void v_Init(void)=0;


		///	Abstract function. Used to control what needs to happen during an update. Please note, objects added to the level 
		///	are already being updated as part of Level::UpdateLevel.
		TEMPEST_API virtual void v_Update(void)=0;
		

		///	Wrapper around Level::RenderObjects. It is virtual to allow for optional customization.
		TEMPEST_API virtual void v_Render(void);

		/// Called when the Level is made active, this defines a series of actions to be taken in order for this. 
		/// Level to be up and going.
		TEMPEST_API virtual void v_Enter(void)
		{
			DefaultEnter();
		}

		/// Called when the Level is about to be deactivated. This is a clean up chance, to dump anything that needs to be
		/// dumped and clean up anything that needs to be cleaned up. Right now, this is stubbed out and unimplemented.
		TEMPEST_API virtual void v_Exit(void)
		{  }

		/// Default behavior for a standard awake. Behavior: Calls GameWindow::ResetCamera
		TEMPEST_API void DefaultEnter(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================

		///	Default actions that need to be called each frame. Right now, that is only Camera::v_Update.
		TEMPEST_API void UpdateLevel(void);


		///	Converts the ref to a smart_ptr and adds the GameObject to the Level.
		///	\param obj is the object to be added.
		TEMPEST_API void AddObjectToLevel(const GameObject2D& obj);


		///	Adds GameObject pointer to the Level.
		///	\param obj is the pointer to be added.
		TEMPEST_API void AddObjectToLevel(p_GameObject2D obj);


		///	Registers a KillerPhysics::RigidBody2D with a KillerPhysics::ForcerGenerator. This only works because they are pointers. 
		///	\param RigidBody2D is the pointer that needs to be registered with the generator. 
		///	\param generator is the force to apply to the RigidBody2D.
		inline void RegisterRigidBody2DForce(TP::p_RigidBody2D body, TP::p_ForceGenerator generator)
		{
			_forceRegistry.Add(body, generator);
		}


		///	Adds the Glyphs in a Text to the Level as GameObjects.
		///	\param text is the Text to get the Glyphs from.
		TEMPEST_API void AddTextToLevel(const Text& text);


		///	Adds the Glyphs in a Text to the Level as GameObjects.
		///	\param text is shared pointer Text to get the Glyphs from.
		TEMPEST_API void AddTextToLevel(shared_ptr<Text> text);

		/// Removes the Glyphs in a Text from the Level based on their GameObject::_ID
		/// \param text is the Text that contains the Glyphs to remove
		TEMPEST_API void RemoveTextFromLevel(const Text& text);

		/// Update Text to display new Glyphs. This is a wrapper around RemoveTextFromLevel and AddTextToLevel. This will edit the existing 
		/// Text object to have the new string that is passed in.
		/// \param text is the Text that contains the Glyphs to update
		/// \param updatedCharacters is the new string that will be sent to Text::AddText, updating text.
		TEMPEST_API void UpdateText(Text& text, string updatedCharacters);

		///	Removes the GameObject with id from the Level.
		///	\param id of the GameObject to remove.
		TEMPEST_API void RemoveObjectFromLevel(U32 id);

		///	Loops over all of the GameObject and KillerPhysics::RigidBody2D that have been added to the Level, and calls GameObject::v_Update
		///	if they are active for updates. 
		TEMPEST_API void UpdateObjects(void);

		///	Loops over all of the GameObject and KillerPhysics::RigidBody2D that have been added to the Level, and calls GameObject::v_Render
		///	if they are active for rendering. 
		TEMPEST_API void RenderObjects(void);

		///	Loops over all GameObjects and KillerPhysics::RigidBody2D that have bee added to the level and calls GameObject::SetUniform for the
		///	type that is passed in. This is a template function. 
		///	\param name is the name of the uniform to set. This must match what is found in the shader. 
		///	\param type is the dynamic type that is passed into the shader.  
		template <class T>
		inline void SetObjectUniforms(string name, const T& type)
		{
			for(auto i : _localGameObjects)
			{
				i.second->GetShader()->SetUniform(name, type);
			}
		}

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================		
		///	Changes the set background color for the Level. It also calls Level::ActivateBackgroundColor
		inline void SetBackgroundColor(const Color& c) 
		{ 
			_bgColor = c;
			ActivateBackgroundColor();
		}
		

		///	Forces the current background color to be activated in OpenGL.
		inline void ActivateBackgroundColor(void) 
		{ 
			GameWindow::Instance()->GetCamera()->SetColor(_bgColor); 
		}
		

		///	Returns the width of the play area of the Level.
		inline S32 GetWidth(void) const 
		{ 
			return _width; 
		}
		

		///	Returns the height of the play area of the Level.
		inline S32 GetHeight(void) const 
		{ 
			return _height; 
		}
		

		///	Changes the width of the play area of the Level.
		///	\param w is the new width.
		inline void SetWidth(S32 w)  
		{ 
			_width = w; 
		}
		

		///	Changes the height of the play area of the Level.
		///	\param h is the new height.
		inline void SetHeight(S32 h) 
		{ 
			_height = h; 
		}
		

		///	Helper function that allows you to change the play area dimensions at the same time. 
		inline void SetDimensions(S32 w, S32 h) 
		{ 
			_width  = w; 
			_height = h; 
		}
		

		///	Set the top bounds.
		///	\param top is the new border.
		inline void SetTopBorder(S32 top) 
		{ 
			_topBorder = top; 
		}


		///	Set the bottom bounds.
		///	\param bottom is the new border.
		inline void SetBottomBorder(S32 bottom) 
		{ 
			_bottomBorder = bottom; 
		}


		///	Set the right bounds.
		///	\param right is the new border.
		inline void SetRightBorder(S32 right) 
		{ 
			_rightBorder = right;
		}


		///	Set the left bounds.
		///	\param left is the new border.
		inline void SetLeftBorder(S32 left) 
		{ 
			_leftBorder = left; 
		}


		///	Helper function to set all borders of the play area of the Level at the same time. 
		///	\param top is the top border.
		///	\param bottom is the bottom border.
		///	\param right is the right border.
		///	\param left is the left border.
		inline void SetBorders(S32 top, S32 bottom, S32 right, S32 left)
		{
			_topBorder = top;
			_bottomBorder = bottom;
			_leftBorder = left;
			_rightBorder = right;
		}
		

		///	Returns the top border.
		inline S32 GetTopBorder(void) const 
		{ 
			return _topBorder; 
		}


		///	 Returns the bottom border.
		inline S32 GetBottomBorder(void) const 
		{ 
			return _bottomBorder; 
		}
		

		///	Returns the left border.
		inline S32 GetLeftBorder(void) const 
		{ 
			return _leftBorder; 
		}


		///	Returns the right border.
		inline S32 GetRightBorder(void) const 
		{
			return _rightBorder; 
		}

 
		///	 Sets the depth of the play area 
		inline void SetDepth(S32 d)
		{
			_depth = d;
		}

 
		///	 Returns the depth of the play area.
		inline S32 GetDepth(void)
		{
			return _depth;
		}

 
		///	 Sets the near border of the play area. 
		inline void SetNearBorder(S32 n)
		{
			_nearBorder = n;
		}

 
		///	 Sets the far border of the play area. 
		inline void SetFarBorder(S32 f)
		{
			_farBorder = f;
		}

 
		///	Returns the near border of the play area.  
		inline S32 GetNearBorder(void)
		{
			return _nearBorder;
		}

 
		///	Returns the far border of the play area.  
		inline S32 GetFarBorder(void)
		{
			return _farBorder;
		}


		///	Sets a new ID for the Level. Use with caution.
		inline void SetID(U32 id) 
		{ 
			_ID = id; 
		}


		///	Returns the Level ID. This will only match the LevelManager ID if you set it correctly.
		inline U32 GetID(void) const
		{
			return _ID;
		}

	protected:
		struct TileData
		{
			U32 id;
			U32 imageWidth;
			U32 imageHeight;
			string type;
			string imageFilePath;
			TM::Point pos;
		};

		struct GridPos
		{
			S32 x;
			S32 y;
		};
		
		/// Default actions to take if no other rendering steps are needed. Loops over all local GameObjects calling
		/// GameObject::v_Render for each.
		TEMPEST_API void DefaultRender(void);

		TEMPEST_API GridPos _ConvertIndexToTileData(U32 index, U32 width, U32 height);

		TEMPEST_API std::vector<TileData> _ImportTMXMapData(string filepath);

		/// Return count of how many objects have been registered
		inline U32 GetObjectCount(void)
		{
			return _localGameObjects.size();
		}

		//==========================================================================================================================
		//
		//Protected data
		//
		//==========================================================================================================================		
		std::map<U32, p_GameObject2D>	  _localGameObjects; ///< List of all GameObjects included in the Level. This is protected, levels should have access to their registered objects
		
	private:
		/// Helper function to split a list of numbers apart. This is intended to be used with a list of numbers separated by a 
		/// standard character, for instance, a list of space or comma separated numbers. The numbers are read as strings and
		/// converted into U32 types.
		/// \param text is string to break apart. It should be numbers separated by a common character.
		/// \param delim is the character that separates each number in list.
		std::vector<U32> _SplitU32(string text, char delim) const;
//==========================================================================================================================
//
//Data
//
//==========================================================================================================================		
		S32     _width;											///< Total width of the play area in the Level. Enforced only by convention.
		S32     _height;										///< Total height of the play area in the Level. Enforced only by convention.
		S32     _topBorder;										///< Optional "north" border of the Level.
		S32     _bottomBorder;									///< Optional "south" border of the Level.
		S32     _rightBorder;									///< Optional "east" border of the Level.
		S32     _leftBorder;									///< Optional "west" border of the Level.
		S32		_depth; 										///< Total depth of the play area in the Level.
		S32		_nearBorder;									///< Optional close border of the Level.
		S32 	_farBorder;										///< Optional far border of the Level.
		Color   _bgColor;										///< Color used for the background of the rendering window.
		U32     _ID;											///< ID used in the LevelManager.
		TP::ForceRegistry _forceRegistry; 						///< KillerPhysics::ForceRegistry used to allow physics forces to be applied.
	};
	typedef shared_ptr<Level> p_Level;
}//End namespace