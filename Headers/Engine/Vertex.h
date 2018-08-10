/*========================================================================


This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Vector.h>
#include <Engine/Color.h>

namespace KM = KillerMath;

namespace KillerEngine
{
	struct Vertex
	{
		KM::Vector position;
		F32 	   uCoord;
		F32		   vCoord;
		Color 	   color;

		Vertex(void)
		: position(), uCoord(0.0f), vCoord(0.0f), color()
		{  }

		Vertex(KM::Vector pos)
		: position(pos), uCoord(0.0f), vCoord(0.0f), color()
		{  }

		Vertex(KM::Vector pos, Color col)
		: position(pos), uCoord(0.0f), vCoord(0.0f), color(col)
		{  }

		Vertex(KM::Vector pos, F32 u, F32 v)
		: position(pos), uCoord(u), vCoord(v), color()
		{  }
	};
}//end Namespace