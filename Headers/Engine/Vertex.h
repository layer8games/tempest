/*========================================================================


This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Vector2.h>
#include <Engine/Vector3.h>
#include <Engine/Color.h>

namespace KM = KillerMath;

namespace KillerEngine
{
	struct Vertex2D
	 {
	 	KM::Vector2 position;
	 	KM::Vector2 texCoord;
	 	Color color;
	 	S32 texID;

	 	Vertex2D(KM::Vector2 pos)
	 	{
	 		position = pos;
	 	}

	 	Vertex2D(KM::Vector2 pos, Color col)
	 	{
	 		position = pos;
	 		color = col;
	 	}
	 };

	 struct Vertex3D
	 {
	 	KM::Vector3 position;
	 	KM::Vector3 normal;
	 	KM::Vector2 texCoord;
	 	Color color;
	 	S32 texID;
	 };
}//end Namespace