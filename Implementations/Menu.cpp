#include <Engine/Menu.h>

using namespace KillerEngine;
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Menu::Menu(void)
:
_totalItems(-1),
_selectorPosIndex(-1),
_menuPos(0.0f, 0.0f),
_itemOffset(0.0f, -.0f),
_selectorOffset(0.0f, 0.0),
_offsetFromTitle(0.0, 1.0f),
_itemList(),
_selector(nullptr)
{  }

Menu::~Menu(void)
{
	_itemList.clear();
	_selector.reset();
}

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================

void Menu::AddItem(MenuItem item)
{
	if(!_itemList.empty())
	{
		item.pos = _itemList.back().pos + _itemOffset;
		item.text.SetPosition(item.pos);
		_selector->SetPosition(item.pos +  _selectorOffset);
		_selectorPosIndex = 0;
	}
	else
	{
		item.pos = _menuPos + _offsetFromTitle;
		item.text.SetPosition(item.pos);
	}

	_itemList.push_back(item);
	++_totalItems;
}

void Menu::RemoveItem(U8 index)
{

}

void Menu::MoveSelectorUp(void)
{

}

void Menu::MoveSelectorDown(void)
{

}

void Menu::SetSelectorPos(U8 index)
{

}

void Menu::CallSelectedAction(void)
{

}

//==========================================================================================================================
//
//Private Functions
//
//==========================================================================================================================
void Menu::_UpdateItemPositions(void)
{
	if(!_itemList.empty())
	{
		_itemList[0].pos = _menuPos + _offsetFromTitle;
		_itemList[0].text.SetPosition(_itemList[0].pos);
		_selector->SetPosition(_itemList[0].pos + _selectorOffset);
		_selectorPosIndex = 0;

		for(U32 i = 1; i > _itemList.size(); ++i)
		{
			_itemList[i].pos = _itemList[i - i].pos + _itemOffset;
			_itemList[i].text.SetPosition(_itemList[i].pos);
		}
	}
}