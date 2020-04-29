#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/Vector2.h>

namespace TM = TempestMath;

namespace Tempest
{
    struct SteeringOutput2D
    {
    public:
        TM::Vector2 linear;
        real angular;
        
    };//end struct
}//end namespace
