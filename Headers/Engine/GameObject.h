#pragma once

//===== Engine Includes =====
#include <Engine/Atom.h>
#include <Engine/Shader.h>
#include <Engine/Vector.h>
#include <Engine/Matrix.h>
#include <Engine/Color.h>
#include <Engine/Vertex.h>

//===== STL inludes =====
#include <vector>;

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
		inline void AddVertex(const Vertex&  vert);
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
		inline const Texture& GetTexture(void) const
		{
			return _texture;
		}

		inline void SetTexture(const Texture& tex)
		{
			_texture = tex;
		}

		inline const Shader& GetShader(void) const
		{
			return _shader;
		}

		inline void SetShader(const Shader& shader)
		{
			_shader = shader;
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
		static U32				_nextID = 0;
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