#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Vertex.h>
#include <Engine/Shader.h>
#include <Engine/GameObject.h>

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
		TEMPEST_API virtual void v_Render(void);


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

		//===== Vertex =====
/// Manually add a single vertex to the GameObjects mesh.
/// \param vert is the vertice to manually add.
		inline void AddVertex(const Vertex& vert)
		{
			_vertices.push_back(vert);
		}

/// Set the vertices previously created for the GameObject.
/// \param vertices is an array of vertices that will act as the mesh for the GameObject.
		inline void SetVertices(std::vector<Vertex> vertices)
		{
			_vertices = vertices;
		}

/// Return the mesh of vertices the GameObject has.		
		inline std::vector<Vertex> GetVertices(void) const
		{
			return _vertices;
		}

		//===== Indices =====		
/// Manually add a single index for the mesh, used for rendering
/// \param index is added.
		inline void AddIndex(U32 index)
		{
			_indices.push_back(index);
		}

/// Set indices to be used in rendering. These are used as an optimization in rendering.
/// \param indices is an array of indices to be added.
		inline void SetIndices(std::vector<U32> indices)
		{
			_indices = indices;
		}

/// Return the array of indices used for the GameObject.		
		inline std::vector<U32> GetIndices(void) const
		{
			return _indices;
		}

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

//===== VBO =====
/// Bind the Vertex Buffer Object. This is needed before the vertices can be added to the buffer.
/// \param buffer contains the data to be sent into the buffer.
/// \param state is an optional value. This is currently unused.
		void BindVBO(BufferData buffer, bool state=true);

//===== Uv List =====
/// Return the UV index list saved for this object.		
		inline std::vector<F32> GetUVList(void) const
		{
			return _uvList;
		}

/// Change the UV index list for this object.
/// \param list is an array of UV's or this objects texture rendering.
		inline void SetUVList(std::vector<F32> list)
		{
			_uvList = list;
		}

/// Manually add a single UV to the UV list.
/// \param val is the single value to be added.
		inline void AddUV(F32 val)
		{
			_uvList.push_back(val);
		}

//===== Texture =====
/// Change the texture of the GameObject. 
/// \param texture is the new texture for the GameObject.
		inline void SetTexture(shared_ptr<Texture> texture)
		{
			_texture = texture;
		}

/// Return the current texture pointer for the GameObject.		
		inline shared_ptr<Texture> GetTexture(void) const
		{
			return _texture;
		}

		inline void BindTexture(bool state=true)
		{
			_texture->Bind(state);
		}

	private:
		p_GameObject			_gameObject;
		std::vector<Vertex> 	_vertices;				///< Array of vertices used for rendering. This is the mesh of the object.
		std::vector<U32> 		_indices;				///< Rendering optimization. An array of indices used to help render the mesh without duplicated vertices.
		std::vector<F32> 		_uvList;				///< Array of UV pair values, used to render a texture on the mesh.
		p_Shader				_shader;				///< Shader used for rendering. Should come from the ShaderManager. Set to null by default.
		shared_ptr<Texture>		_texture;				///< Texture used when rendering the object. Set to null by default.
		GLuint 					_vao;					///< Vertex Array Object, used in OpenGL. See OGL documentation for details.
		GLuint 					_vbo[NUM_VBO];			///< Vertex Buffer Object, used in OpenGL. See OGL documentation for details.

	};//end Class
	shared_ptr<Mesh> p_Mesh;
}