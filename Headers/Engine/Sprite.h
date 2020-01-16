#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Mesh.h>
#include <Engine/ShaderManager.h>


namespace Tempest
{
	class Sprite : public Mesh
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		Sprite(void);

		~Sprite(void);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
		TEMPEST_API void v_Render(const TM::Matrix4& modelMatrix);

		TEMPEST_API void v_InitBuffers(void);

	private:

	};//end Class
}