/*========================================================================
The character data from a font file used to give the offset in the texture 
image for rendering a character in game. 

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>

namespace KillerEngine
{
	struct CharacterData
	{
		S32 id;
		S32 x;
		S32 y;
		S32 width;
		S32 height;
		S32 xoffset;
		S32 yoffset;
		S32 xadvance;
	};
}//end Namespace