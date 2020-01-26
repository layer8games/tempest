#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>

namespace Tempest
{
	class Mesh
	{
	public:
	//==========================================================================================================================
	//
	//Constructors	 	
	//
	//==========================================================================================================================
		TEMPEST_API Mesh(void);

		TEMPEST_API Mesh(const Mesh& mesh);

		TEMPEST_API ~Mesh(void);

	//==========================================================================================================================
	//
	//Functions
	//
	//==========================================================================================================================
		TEMPEST_API virtual void v_Render(U32 count);

		TEMPEST_API void InitOpenGLData(void);

		//===== VAO =====
		/// Return the currently used Vertex Array Object for the GameObject. Used for rendering by OpenGL		
		inline GLuint GetVAO(void) const
		{
			return _vao;
		}

		/// The Vertex Array Object needs to be bound before OpenGL can render this object. This is what sets the vertices for
		/// this object on the video card. This is part of the magic.
		inline void BindVAO(bool state=true)
		{
			if(state)
			{
				glBindVertexArray(_vao);
			}
			else
			{
				glBindVertexArray(0);
			}
		}

	private:
		GLuint 					_vao;					///< Vertex Array Object, used in OpenGL. See OGL documentation for details.

	};//end Class
	typedef shared_ptr<Mesh> p_Mesh;
}//end namespace
