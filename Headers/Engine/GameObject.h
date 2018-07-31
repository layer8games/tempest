#pragma once

//===== Engine Includes =====
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/Shader.h>
#include <Engine/Vector.h>
#include <Engine/Matrix.h>
#include <Engine/Color.h>
#include <Engine/Vertex.h>
#include <Engine/Texture.h>

//===== STL inludes =====
#include <vector>

namespace KM = KillerMath;

namespace KillerEngine
{
	class GameObject
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		GameObject(void);

		GameObject(const GameObject& obj);

		~GameObject(void);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
		virtual void v_Update(void)=0;

		virtual void v_Render(void);

		virtual void v_InitVertexData(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
		inline void AddVertex(const Vertex&  vert)
		{
			_vertices.push_back(vert);
		}

		inline void AddIndex(U32 index)
		{
			_indices.push_back(index);
		}

		inline void SetIndices(std::vector<U32> indices)
		{
			_indices = indices;
		}


//==========================================================================================================================
//
//OpenGL Functions Wrappers
//
//==========================================================================================================================
		inline void BindVAO(void)
		{
			glBindVertexArray(_vao);
		}

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
//===== ID =====
		inline const U32 GetID(void) const
		{
			return _ID;
		}

//===== Active =====
		inline const bool GetActive(void) const
		{
			return _active;
		}

		inline void SetActive(void)
		{
			_active = true;
		}

		inline void SetInactive(void)
		{
			_active = false;
		}

//===== Position =====
		inline const KM::Vector& GetPosition(void) const
		{
			return _position;
		}

		inline void SetPosition(const KM::Vector& pos)
		{
			_position = pos;
		}

		inline void SetPosition(F32 x, F32 y)
		{
			_position[0] = x;
			_position[1] = y;
		}

		inline void SetPosition(F32 x, F32 y, F32 z)
		{
			_position[0] = x;
			_position[1] = y;
			_position[2] = z;
		}

//===== Shader =====
		inline const Shader& GetShader(void) const
		{
			return _shader;
		}

		inline void SetShader(const Shader& shader)
		{
			_shader = shader;
		}

//===== Texture =====
		inline const Texture& GetTexture(void) const
		{
			return _texture;
		}

		inline void SetTexture(const Texture& tex)
		{
			_texture = tex;
		}

//===== Vertex and Index =====
		inline std::vector<Vertex> GetVertices(void) const
		{
			return _vertices;
		}

		inline std::vector<U32> GetIndices(void) const
		{
			return _indices;
		}

//===== VAO =====
		inline GLuint GetVAO(void) const
		{
			return _vao;
		}

	private:
		enum BufferData
		{
			VERTEX_BUFFER = 0,
			VERTEX_POS = 0,
			FRAGMENT_BUFFER = 1,
			FRAGMENT_POS = 2,
			TEX_COORD_BUFFER = 2,
			TEX_COORD_POS = 1,
			INDEX_BUFFER = 3,
			NUM_VBO = 4
		};

//==========================================================================================================================
//
//Data
//
//==========================================================================================================================		
		static U32				_nextID;
		U32 					_ID;
		bool					_active;
		KM::Vector				_position;
		Shader 					_shader;
		Texture 				_texture;
		std::vector<Vertex> 	_vertices;
		std::vector<U32> 		_indices;
		GLuint 					_vao;
		GLuint 					_vbo[NUM_VBO];

	};
}