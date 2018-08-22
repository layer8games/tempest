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
namespace KM = KillerMath;

#include <Extern/rapidxml.hpp>

//===== STL inludes =====
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <regex>

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

		virtual ~GameObject(void);

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
		void LoadMesh(string filepath);

		inline void AddVertex(const Vertex&  vert)
		{
			_vertices.push_back(vert);
		}

		inline void AddIndex(U32 index)
		{
			_indices.push_back(index);
			++_numIndices;
		}

		inline void SetIndices(std::vector<U32> indices)
		{
			_indices = indices;
			_numIndices = indices.size();
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

		inline void AddScaledPosition(const KM::Vector pos, F32 scale)
		{
			_position.AddScaledVector(pos, scale);
		}

//===== Scale =====
		inline const KM::Vector& GetScale(void)
		{
			return _scale;
		}

		inline void SetScale(const KM::Vector& scale)
		{
			_scale = scale;
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

		inline void LoadShader(std::vector<ShaderData> shaderData)
		{
			_shader.LoadShader(shaderData);
		}

		inline void UseShader(void)
		{
			_shader.Use();
		}

//===== NumVertices =====
		inline S32 GetNumVertices(void)
		{
			return _numIndices;
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

	protected:
		Shader _shader;

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

		std::vector<U32> _SplitU32(string text, char delim) const;
		
		std::vector<F32> _SplitF32(string text, char delim) const;

//==========================================================================================================================
//
//Data
//
//==========================================================================================================================		
		static U32				_nextID;
		U32 					_ID;
		bool					_active;
		KM::Vector				_position;
		KM::Vector 				_scale;
		S32						_numIndices;
		std::vector<Vertex> 	_vertices;
		std::vector<U32> 		_indices;
		GLuint 					_vao;
		GLuint 					_vbo[NUM_VBO];

	};
}