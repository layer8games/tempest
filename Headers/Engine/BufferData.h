#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>


namespace Tempest
{
	/// Helper ID's for shader info.	
	enum TEMPEST_API BufferData
	{
		VERTEX_BUFFER = 0,
		VERTEX_POS = 0,
		FRAGMENT_BUFFER = 1,
		FRAGMENT_POS = 2,
		TEX_COORD_BUFFER = 2,
		TEX_COORD_POS = 1,
		INDEX_BUFFER = 3,
		NORMAL_BUFFER = 4,
		NORMAL_POS = 3,
		NUM_VBO = 5
	};
}