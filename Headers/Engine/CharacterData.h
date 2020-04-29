/*========================================================================
The character data from a font file used to give the offset in the texture 
image for rendering a character in game. 

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/Texture.h>

namespace Tempest
{
    struct CharacterData
    {
        S32 width;
        S32 height;
        S32 bearingX;
        S32 bearingY;
        S32 xAdvance;
        shared_ptr<Texture> texture;
    };
}//end Namespace