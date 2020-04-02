#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Point.h>
#include <Engine/Text.h>
#include <Engine/GameObject2D.h>

namespace TM = TempestMath;

//===== STL Includes =====
#include <vector>

namespace Tempest
{
///	A struct to hold all the information needed for an item in a Menu. 
	struct MenuItem
	{
		TM::Point 		  pos;	///< Position of the Text. Used for quick reference, useful even though its duplicated. 
		shared_ptr<Text>  text;	///< Pointer a Text, used for the look of the item in the Menu. Call Level::AddTextToLevel first. 

///	Callback function used when the item is activated. Must use the same signature. 
		void (*Action)(void) = NULL;
	};

///	A basic menu class to help create in game menus. These are similar to Doom style menues. There is a selector that can be
///	any type of GameObject, followed by Text with an optional title. The Text is wrapped into a MenuItem, complete with a 
///	callback function to determine what happens when an item is activated. An item is activated when the selector is next
///	to is and Menu::CallSelectedAction is called.
///	This is not a super robust menu system. The follow features could help it out a lot. 
///	1. It could use an active state, so that it can be toggled on and off.
///	2. AddItem could use a parameter to allow to set a new position for an item. For example, add a new item to the top or
///	   middle of the list instead of just the end.  
	class Menu
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
///	Default constructor. No implemenatation. Sets everything to 0, except the selectorPosIndex, which is set to UINT_MAX.
		TEMPEST_API Menu(void);

///	Default desctructor. Clears the itemList.
		TEMPEST_API ~Menu(void);

//==========================================================================================================================
//
//Fucntions
//
//==========================================================================================================================
///	Returns if the Menu and all its items are active
		inline bool GetActive(void) const
		{
			return _active;
		}


///	Sets the Menu and all its items to the given state, true = active, false = not active
///	\param state is the new state you wish to set.
		TEMPEST_API void SetActive(bool state);


///	 Adds a new MenuItem to the bottom of the list. If no MenuItems are present yet, it sets the first item below the title, 
///	 if one is present. It also set up the selector position, if it hasn't been set yet. 
///	 \param item is the new item to add to the list. 
		TEMPEST_API void AddItem(MenuItem item);

///	Removes item given the position from the list. The rest of the list is rearranged to suppor this. 
///	\param index is the item to remove. These are 0 indexed.
		TEMPEST_API void RemoveItem(U32 index);

///	Moves the selector up one position on the list. If it reaches the top, it will either stop, or wrap, based on the 
///	configuration. 
		TEMPEST_API void MoveSelectorUp(void);

///	Moves the selector down one position on the list. If it reaches the bottom, it will either stop or wrap, based on the
///	configuration. 
		TEMPEST_API void MoveSelectorDown(void);

///	Manually sets the selector to a given position in the list. If the index is out of range, nothing happens. 
///	\param index is the 0 indexed position to set the selector to. 
		TEMPEST_API void SetSelectorPosition(U32 index);

///	Calls the currently select MenuItem callback Action function. If this is not set, nothing happens. 
		TEMPEST_API void CallSelectedAction(void);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
///	Sets if the menu selector should wrap when it reaches the top or bottom. 
///	\param state configures the options. True for wrapping, false for no wrapping. 
		inline void SetWrap(bool state)
		{
			_wrap = state;
		}

///	 Returns if the Menu is currently configured to wrap or not. 
		inline bool GetWrap(void)
		{
			return _wrap;
		}
		
///	Returns the total number of items in the Menu. This calls std::vector::size
		inline U32 GetTotalItems(void)
		{
			return _itemList.size();
		}

///	Updates the position of the Menu, the title and all the items. Calls Menu::_UpdateItemPositions
///	\param pos is the new position of the whole Menu. 
		inline void SetPosition(const TM::Point& pos)
		{
			_menuPos = pos;
			_UpdateItemPositions();
		}

///	Updates the position of the Menu, the title and all the items. Calls Menu::_UpdateItemPositions
///	\param xPos is the x coodinate position. 
///	\param yPos is the y coodinate position. 
		inline void SetPosition(F32 xPos, F32 yPos)
		{
			_menuPos[x] = xPos;
			_menuPos[y] = yPos;
			_UpdateItemPositions();
		}

///	Returns the position of the Menu. 
		inline const TM::Point& GetPosition(void)
		{
			return _menuPos;
		}

///	 Sets the offset of each item from the one above it. Calls Menu::_UpdateItemPositions. 
///	 \param offset is the offset. This is added to the MenuItem::pos, so it should be negative to go left or 
///	 down, and positive to go right or up. 
		inline void SetItemOffset(const TM::Point& offset)
		{
			_itemOffset = offset;
			_UpdateItemPositions();
		}

///	 Sets the offset of each item from the one before it. Calls Menu::_UpdateItemPositions. 
///	 \param xPos is the offset. Should be negative to go left or positive to go right. 
///	 \param yPos is the offset. Should be negative to down or positive to go up. 
		inline void SetItemOffset(F32 xPos, F32 yPos)
		{
			_itemOffset[x] = xPos;
			_itemOffset[y] = yPos;
			_UpdateItemPositions();
		}

///	Returns the current offset of each time to the one before it.
		inline const TM::Point& GetItemOffset(void)
		{
			return _itemOffset;
		}

///	Sets the offset for the selector from the item it is next to. Calls Menu::_UpdateItemPositions 
///	\param offset is the offset. Should be positive to move it right or up, and negative to move it left or down. 
		inline void SetSelectorOffset(const TM::Point& offset)
		{
			_selectorOffset = offset;
			_UpdateItemPositions();
		}

///	 Sets the offset for the selector from the item it is next to. Calls Menu::_UpdateItemPositions
///	 \param xPos is the offset. Should be negative to go left or positive to go right. 
///	 \param yPos is the offset. Should be negative to down or positive to go up. 
		inline void SetSelectorOffset(F32 xPos, F32 yPos)
		{
			_selectorOffset[x] = xPos;
			_selectorOffset[y] = yPos;
			_UpdateItemPositions();
		}

///	Returns the offset for the selector from the item it is next to.
		inline const TM::Point& GetSelectorOffset(void)
		{
			return _selectorOffset;
		}

///	 Sets the offset for the first item in the list from the title. Calls Menu::_UpdateItemPositions
///	 \param pos is the offset from the title. Should be positive to move it up or right, negative for down or left. 
		inline void SetTitleOffset(const TM::Point& pos)
		{
			_offsetFromTitle = pos;
			_UpdateItemPositions();
		}

///	 Sets the offset for the first item in the list from the title. Calls Menu::_UpdateItemPositions
///	 \param xPos is the offset. Should be negative to go left or positive to go right. 
///	 \param yPos is the offset. Should be negative to down or positive to go up. 
		inline void SetTitleOffset(F32 xPos, F32 yPos)
		{
			_offsetFromTitle[x] = xPos;
			_offsetFromTitle[y] = yPos;
			_UpdateItemPositions();
		}

///	Returns the current offset for the first item from the title. 
		inline const TM::Point& GetTitleOffset(void)
		{
			return _offsetFromTitle;
		}

///	Sets the title for the menu. 
///	\param text is the title. It will be converted to a shared_ptr<Text>.
		inline void SetTitle(const Text& text)
		{
			_title = shared_ptr<Text>(const_cast<TE::Text*>(&text));
			_title->SetPosition(_menuPos);
		}

///	Sets the title for the menu. 
///	\param text is the title.
		inline void SetTitle(shared_ptr<Text> text)
		{
			_title = text;
			_title->SetPosition(_menuPos);
		}

///	Returns a shared_ptr to the Title of the Menu. 
		inline shared_ptr<Text> GetTitle(void)
		{
			return _title;
		}

///	 Returns the list of all MenuItems for the Menu. 
		inline const std::vector<MenuItem>& GetItemList(void)
		{
			return _itemList;
		}

///	Sets the selector for the Menu. 
///	\param obj is a pointer to the GameObject type that will act as the selector. If itemList is not empty, it will set
///	the selector to the first position. 
		inline void SetSelector(p_GameObject2D obj)
		{
			_selector = obj;

			if(!_itemList.empty())
			{
				_selectorPosIndex = 0;
				SetSelectorPosition(0);
			}
		}

	private:
//==========================================================================================================================
//
//Private Functions
//
//==========================================================================================================================
///	Updates the title, and all MenuItems in the list to the current position, based on _menuPos and the offsets. 
		TEMPEST_API void _UpdateItemPositions(void);

//==========================================================================================================================
//
//Data
//
//==========================================================================================================================
		bool					_active;			///< Sets if the menu and all its items are active for rendering and update.
		bool					_wrap;				///< Configures if the selector should wrap around the Menu or not. True == wrap, false == Don't wrap.
		U32 					_selectorPosIndex;	///< Index that tracks the location of the selector in relation to _itemList.
		TM::Point 				_menuPos;			///< Position of the Menu. Used to update everything in Menu::_UpdateItemPositions
		TM::Point 		 		_itemOffset;		///< Offset of each MenuItem from the one before it. 
		TM::Point 				_selectorOffset;	///< Offset of the selector from the MenuItem it is next to. 
		TM::Point 				_offsetFromTitle;	///< Offset of the first MenuItem from the title. 
		p_Text					_title;				///< Pointer to the a Text title. 
		std::vector<MenuItem> 	_itemList;			///< Internal list of all MenuItems. 
		p_GameObject2D			_selector;			///< Selector to move and activate MenuItems. 
		
	};//end Class
	typedef shared_ptr<Menu> p_Menu;
}//end Namespace
