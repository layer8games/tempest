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
	 };

	 struct Vertex3D
	 {
	 	KM::Vector3 position;
	 	F32 		xscale;
	 	F32			yscale;
	 	F32			zscale;
	 	KM::Vector3 normal;
	 	KM::Vector2 texCoord;
	 	Color color;
	 	S32 texID;

	 	void ScaleAll(F32 scale)
	 	{
	 		xscale = scale; 
	 		yscale = scale; 
	 		zscale = scale;
	 	}
	 };
}//end Namespace