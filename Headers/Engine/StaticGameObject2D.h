#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/GameObject2D.h>

namespace Tempest
{
	class StaticGameObject2D : public GameObject2D
	{
	public:
		TEMPEST_API StaticGameObject2D(void);

		TEMPEST_API ~StaticGameObject2D(void);

		TEMPEST_API void v_Update(void) final;

	private:

	};//end Class
	typedef shared_ptr<StaticGameObject2D> p_StaticGameObject2D;
}
