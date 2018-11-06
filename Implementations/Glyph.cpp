#include <Engine/Glyph.h>
#include <iostream>

using namespace KillerEngine;

//==========================================================================================================================
//Static Init
//==========================================================================================================================
	static U32 _nextID = 1;
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Glyph::Glyph(void) 
:
_character(),
_characterData()
{
	GameObject::MakeSprite();
}

Glyph::~Glyph(void)
{  }

void Glyph::v_Render(void)
{
	GameObject::v_Render();
}