#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Point.h>
#include <Engine/Text.h>
#include <Engine/GameObject.h>

namespace KM = KillerMath;

//===== STL Includes =====
#include <vector>

namespace KillerEngine
{
	struct MenuItem
	{
		KM::Point pos;
		Text 	  text;

		void (*Action)(void) = NULL;
	};

	class Menu
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		Menu(void);

		~Menu(void);

//==========================================================================================================================
//
//Fucntions
//
//==========================================================================================================================
		void AddItem(MenuItem item);

		void RemoveItem(U8 index);

		void MoveSelectorUp(void);

		void MoveSelectorDown(void);

		void SetSelectorPos(U8 index);

		void CallSelectedAction(void);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		inline S32 GetTotalItems(void)
		{
			return _totalItems;
		}

		inline void SetPosition(const KM::Point& pos)
		{
			_menuPos = pos;
			_UpdateItemPositions();
		}

		inline void SetPosition(F32 xPos, F32 yPos)
		{
			_menuPos[x] = xPos;
			_menuPos[y] = yPos;
			_UpdateItemPositions();
		}

		inline const KM::Point& GetPosition(void)
		{
			return _menuPos;
		}

		inline void SetItemOffset(const KM::Point& offset)
		{
			_itemOffset = offset;
			_UpdateItemPositions();
		}

		inline void SetItemOffset(F32 xPos, F32 yPos)
		{
			_itemOffset[x] = xPos;
			_itemOffset[y] = yPos;
			_UpdateItemPositions();
		}

		inline const KM::Point& GetItemOffset(void)
		{
			return _itemOffset;
		}

		inline void SetSelectorOffset(const KM::Point& offset)
		{
			_selectorOffset = offset;
			_UpdateItemPositions();
		}

		inline void SetSelectorOffset(F32 xPos, F32 yPos)
		{
			_selectorOffset[x] = xPos;
			_selectorOffset[y] = yPos;
			_UpdateItemPositions();
		}

		inline const KM::Point& GetSelectorOffset(void)
		{
			return _selectorOffset;
		}

		inline void SetOffsetFromTitle(const KM::Point& pos)
		{
			_offsetFromTitle = pos;
			_UpdateItemPositions();
		}

		inline void SetOffsetFromTitle(F32 xPos, F32 yPos)
		{
			_offsetFromTitle[x] = xPos;
			_offsetFromTitle[y] = yPos;
			_UpdateItemPositions();
		}

		inline const KM::Point& GetOffsetFromTitle(void)
		{
			return _offsetFromTitle;
		}

		inline void SetTitle(const Text& text)
		{
			_title = text;
			_title.SetPosition(_menuPos);
		}

		inline const Text& GetTitle(void)
		{
			return _title;
		}

		inline const std::vector<MenuItem>& GetItemList(void)
		{
			return _itemList;
		}

	private:
//==========================================================================================================================
//
//Private Functions
//
//==========================================================================================================================
		void _UpdateItemPositions(void);

//==========================================================================================================================
//
//Data
//
//==========================================================================================================================
		S32 				 	_totalItems;
		S32 					_selectorPosIndex;
		KM::Point 				_menuPos;
		KM::Point 		 		_itemOffset;
		KM::Point 				_selectorOffset;
		KM::Point 				_offsetFromTitle;
		Text 					_title;
		std::vector<MenuItem> 	_itemList;
		shared_ptr<GameObject>	_selector;
		
	};//end Class
}//end Namespace
