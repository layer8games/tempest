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
	struct TexCoord
	{
		F32 u;
		F32 v;

		TexCoord(void)
		: u(0.0f), v(0.0f)
		{  }

		TexCoord(F32 s, F32 t)
		: u(s), v(t)
		{  }
	};

	struct Vertex
	{
		KM::Vector position;
		TexCoord   texCoord;
		Color 	   color;

		Vertex(void)
		: position(), texCoord(0.0f, 0.0f), color()
		{  }

		Vertex(KM::Vector pos)
		: position(pos), texCoord(0.0f, 0.0f), color()
		{  }

		Vertex(KM::Vector pos, Color col)
		: position(pos), texCoord(0.0f, 0.0f), color(col)
		{  }

		Vertex(KM::Vector pos, F32 u, F32 v)
		: position(pos), texCoord(u, v), color()
		{  }
	};
}//end Namespace