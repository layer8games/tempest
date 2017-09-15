/*========================================================================
The character data from a font file used to give the offset in the texture 
image for rendering a character in game. 

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#ifndef CHARACTER_DATA_H
#define CHARACTER_DATA_H

//=====Engine Includes=====
#include <Engine/Atom.h>

namespace 
{
	struct CharacterData
	{
		U32 id;
		U32 x;
		U32 y;
		U32 width;
		U32 height;
		U32 xoffset;
		U32 yoffset;
		U32 xadvance;
	};
}//end Namespace
#endif