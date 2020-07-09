#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/GameObject3D.h>

namespace Tempest
{
	class StaticGameObject3D : public GameObject3D
	{
	public:
		StaticGameObject3D(void);

		~StaticGameObject3D(void);

		void v_Update(void) final;

	private:

	};//end Class
	typedef shared_ptr<StaticGameObject3D> p_StaticGameObject3D;
}
