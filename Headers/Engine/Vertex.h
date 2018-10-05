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
		KM::Vector normal;
		TexCoord   texCoord;
		Color 	   color;

		Vertex(void)
		: position(0.0f), normal(0.0f), texCoord(0.0f, 0.0f), color()
		{  }

		Vertex(KM::Vector pos)
		: position(pos), normal(0.0f), texCoord(0.0f, 0.0f), color()
		{  }

		Vertex(const KM::Vector& pos, Color col)
		: position(pos), normal(0.0f), texCoord(0.0f, 0.0f), color(col)
		{  }

		Vertex(const KM::Vector& pos, F32 u, F32 v)
		: position(pos), normal(0.0f), texCoord(u, v), color()
		{  }

		Vertex(const KM::Vector& pos, const KM::Vector& norm)
		: position(pos), normal(norm), texCoord(0.0f, 0.0f), color()
		{  }

		Vertex(const KM::Vector& pos, const KM::Vector& norm, F32 u, F32 v)
		: position(pos), normal(norm), texCoord(u, v), color()
		{  }	
	};
}//end Namespace