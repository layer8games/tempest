#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Vector.h>

namespace KM = KillerMath;

namespace KillerPhysics
{
	struct BoundingBox
	{
		KM::Vector center;
		KM::Vector halfSize;
	};//end Struct
}//end Namespace
