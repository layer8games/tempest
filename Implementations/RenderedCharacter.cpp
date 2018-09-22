#include <Engine/RenderedCharacter.h>

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
RenderedCharacter::RenderedCharacter(void) 
: 
_id(_nextID), 
_pos(0.0f),
_width(0.0f),
_height(0.0f),
_color()
{
	++_nextID;
}

RenderedCharacter::~RenderedCharacter(void)
{  }