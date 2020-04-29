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