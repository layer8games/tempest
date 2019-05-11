#include <Engine/Menu.h>

using namespace KillerEngine;
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Menu::Menu(void)
:
_totalItems(0),
_selectorPosIndex(0),
_menuPos(0.0f, 0.0f),
_itemOffset(0.0f, 1.0f),
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
		item.pos[x] = _menuPos[x] + _offsetFromTitle[x];
		item.pos[y] = _menuPos[y] - _offsetFromTitle[y];

		item.text.SetPosition(item.pos);
	}
	else
	{
		item.pos[x] = _itemList.back().pos[x] + _itemOffset[x];
		item.pos[y] = _itemList.back().pos[y] - _itemOffset[y];

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