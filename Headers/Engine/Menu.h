#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/Point2.h>
#include <Engine/Text.h>
#include <Engine/GameObject2D.h>

namespace TM = TempestMath;

//===== STL Includes =====
#include <vector>

namespace Tempest
{
    struct MenuItem
    {
        TM::Point2 		  pos;
        shared_ptr<Text>  text;

        void (*Action)(void) = NULL;
    };

    class Menu
    {
    public:
        TEMPEST_API Menu(void);

        TEMPEST_API ~Menu(void);

        inline bool GetActive(void) const
        {
            return _active;
        }


        TEMPEST_API void SetActive(bool state);


        TEMPEST_API void AddItem(MenuItem item);

        TEMPEST_API void RemoveItem(U32 index);

        TEMPEST_API void MoveSelectorUp(void);

        TEMPEST_API void MoveSelectorDown(void);

        TEMPEST_API void SetSelectorPosition(U32 index);

        TEMPEST_API void CallSelectedAction(void);

        inline void SetWrap(bool state)
        {
            _wrap = state;
        }

        inline bool GetWrap(void)
        {
            return _wrap;
        }
        
        inline U32 GetTotalItems(void)
        {
            return _itemList.size();
        }

        inline void SetPosition(const TM::Point2& pos)
        {
            _menuPos = pos;
            _UpdateItemPositions();
        }

        inline void SetPosition(real xPos, real yPos)
        {
            _menuPos.x = xPos;
            _menuPos.y = yPos;
            _UpdateItemPositions();
        }

        inline const TM::Point2& GetPosition(void)
        {
            return _menuPos;
        }

        inline void SetItemOffset(const TM::Point2& offset)
        {
            _itemOffset = offset;
            _UpdateItemPositions();
        }

        inline void SetItemOffset(real xPos, real yPos)
        {
            _itemOffset.x = xPos;
            _itemOffset.y = yPos;
            _UpdateItemPositions();
        }

        inline const TM::Point2& GetItemOffset(void)
        {
            return _itemOffset;
        }

        inline void SetSelectorOffset(const TM::Point2& offset)
        {
            _selectorOffset = offset;
            _UpdateItemPositions();
        }

        inline void SetSelectorOffset(real xPos, real yPos)
        {
            _selectorOffset.x = xPos;
            _selectorOffset.y = yPos;
            _UpdateItemPositions();
        }

        inline const TM::Point2& GetSelectorOffset(void)
        {
            return _selectorOffset;
        }

        inline void SetTitleOffset(const TM::Point2& pos)
        {
            _offsetFromTitle = pos;
            _UpdateItemPositions();
        }

        inline void SetTitleOffset(real xPos, real yPos)
        {
            _offsetFromTitle.x = xPos;
            _offsetFromTitle.y = yPos;
            _UpdateItemPositions();
        }

        inline const TM::Point2& GetTitleOffset(void)
        {
            return _offsetFromTitle;
        }

        inline void SetTitle(const Text& text)
        {
            _title = shared_ptr<Text>(const_cast<TE::Text*>(&text));
            _title->SetPosition(_menuPos);
        }

        inline void SetTitle(shared_ptr<Text> text)
        {
            _title = text;
            _title->SetPosition(_menuPos);
        }

        inline shared_ptr<Text> GetTitle(void)
        {
            return _title;
        }

        inline const std::vector<MenuItem>& GetItemList(void)
        {
            return _itemList;
        }

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
        TEMPEST_API void _UpdateItemPositions(void);

        bool					_active;		
        bool					_wrap;			
        U32 					_selectorPosIndex;
        TM::Point2 				_menuPos;		
        TM::Point2 		 		_itemOffset;	
        TM::Point2 				_selectorOffset;
        TM::Point2 				_offsetFromTitle;
        p_Text					_title;			
        std::vector<MenuItem> 	_itemList;		
        p_GameObject2D			_selector;		
        
    };//end Class
    typedef shared_ptr<Menu> p_Menu;
}//end Namespace
