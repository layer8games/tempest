#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Vertex.h>
#include <Engine/Shader.h>

//===== STL includes =====
#include <vector>

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
		Mesh(void);

		~Mesh(void);

	//==========================================================================================================================
	//
	//Functions
	//
	//==========================================================================================================================

	//==========================================================================================================================
	//
	//Accessors
	//
	//==========================================================================================================================
		inline p_Shader GetShader(void) const
		{
			return _shader;
		}

		inline void SetShader(p_Shader shader)
		{
			_shader = shader;
		}

		inline U32 GetNumVertices(void) const
		{
			return _vertices.size();
		}

	private:
		std::vector<Vertex> 	_vertices;				///< Array of vertices used for rendering. This is the mesh of the object.
		std::vector<U32> 		_indices;				///< Rendering optimization. An array of indices used to help render the mesh without duplicated vertices.
		std::vector<F32> 		_uvList;				///< Array of UV pair values, used to render a texture on the mesh.
		p_Shader				_shader;				///< Shader used for rendering. Should come from the ShaderManager. Set to null by default.
		GLuint 					_vao;					///< Vertex Array Object, used in OpenGL. See OGL documentation for details.
		GLuint 					_vbo[NUM_VBO];			///< Vertex Buffer Object, used in OpenGL. See OGL documentation for details.

	};//end Class
	shared_ptr<Mesh> p_Mesh;
}