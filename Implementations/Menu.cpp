#include <Engine/Menu.h>

using namespace KillerEngine;
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Menu::Menu(void)
:
_wrap(false),
_selectorPosIndex(UINT_MAX),
_menuPos(0.0f, 0.0f),
_itemOffset(0.0f, 0.0f),
_selectorOffset(0.0f, 0.0f),
_offsetFromTitle(0.0, 0.0f),
_title(nullptr),
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
	//If this is not the first item
	if(!_itemList.empty())
	{
		MenuItem last = _itemList.back();
		item.pos = _itemList.back().pos + _itemOffset;
		item.text->SetPosition(item.pos);
	}
	//If this is the first item to be added
	else
	{
		item.pos = _menuPos + _offsetFromTitle;
		item.text->SetPosition(item.pos);

		if(_selector != nullptr)
		{
			_selector->SetPosition(item.pos +  _selectorOffset);
			_selectorPosIndex = 0;
		}
	}

	_itemList.push_back(item);
	_UpdateItemPositions();
}

void Menu::RemoveItem(U32 index)
{
	if(index < _itemList.size())
	{
		_itemList.erase(_itemList.begin() + index);
		
		if(_selectorPosIndex >= index)
		{
			--_selectorPosIndex;
			SetSelectorPosition(_selectorPosIndex);
		}
	}

	_UpdateItemPositions();
}

void Menu::MoveSelectorUp(void)
{
	if(_selectorPosIndex == 0)
	{
		if(_wrap)
		{
			_selectorPosIndex = _itemList.size() - 1; 	
		}
	}
	else
	{
		--_selectorPosIndex;
	}

	if(_selector != nullptr)
	{
		_selector->SetPosition(_itemList[_selectorPosIndex].pos + _selectorOffset);
	}
}

void Menu::MoveSelectorDown(void)
{
	if(_selectorPosIndex == _itemList.size() - 1)
	{
		if(_wrap) 
		{
			_selectorPosIndex = 0;
		}
	}
	else
	{
		++_selectorPosIndex;
	}

	if(_selector != nullptr)
	{
		_selector->SetPosition(_itemList[_selectorPosIndex].pos + _selectorOffset);
	}
}

void Menu::SetSelectorPosition(U32 index)
{
	if(index < _itemList.size())
	{
		_selectorPosIndex = index;
		_selector->SetPosition(_itemList[_selectorPosIndex].pos + _selectorOffset);
	}
}

void Menu::CallSelectedAction(void)
{
	_itemList[_selectorPosIndex].Action();
}

//==========================================================================================================================
//
//Private Functions
//
//==========================================================================================================================
void Menu::_UpdateItemPositions(void)
{
	if(_title != nullptr)
	{
		_title->SetPosition(_menuPos);
	}

	if(!_itemList.empty())
	{
		_itemList[0].pos = _menuPos + _offsetFromTitle;
		_itemList[0].text->SetPosition(_itemList[0].pos);
		
		if(_selector != nullptr)
		{
			_selector->SetPosition(_itemList[0].pos + _selectorOffset);
			_selectorPosIndex = 0;	
		}
		
		for(U32 i = 1; i > _itemList.size(); ++i)
		{
			_itemList[i].pos = _itemList[i - i].pos + _itemOffset;
			_itemList[i].text->SetPosition(_itemList[i].pos);
		}
	}
}