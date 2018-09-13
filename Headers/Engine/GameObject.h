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
#include <stdlib.h>

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

		virtual void v_InitBuffers(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
		bool LoadOBJ(string filepath);

		void LoadMesh(string filepath);

		const KM::Matrix GetModelMatrix(void);

//==========================================================================================================================
//
//OpenGL Functions Wrappers
//
//==========================================================================================================================
		

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

//===== All Active =====
		inline const bool GetActive(void) const
		{
			return _active && _activeRender;
		}

		inline void SetActive(void)
		{
			_active = true;
			_activeRender = true;
		}

		inline void SetInactive(void)
		{
			_active = false;
			_activeRender = false;
		}

//===== Active Update =====		
		inline const bool GetActiveUpdate(void) const
		{
			return _active;
		}

		inline void SetActiveUpdate(void)
		{
			_active = true;
		}

		inline void SetInactiveUpdate(void)
		{
			_active = false;
		}

//===== Active Render =====
		inline const bool GetActiveRender(void)
		{
			return _activeRender;
		}

		inline void SetActiveRender(void)
		{
			_activeRender = true;
		}

		inline void SetInactiveRender(void)
		{
			_activeRender = false;
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

		inline void SetScale(F32 val)
		{
			_scale = val;
		}

		inline void SetScale(F32 xVal, F32 yVal)
		{
			_scale[0] = xVal;
			_scale[1] = yVal;
		}

		inline void SetScale(F32 xVal, F32 yVal, F32 zVal)
		{
			_scale[0] = xVal;
			_scale[1] = yVal;
			_scale[2] = zVal;	
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

		inline void SetShaderUniform(string name, Color col)
		{
			_shader.Use();
			_shader.SetUniform(name.c_str(), col);
		}

		inline void SetShaderUniform(string name, KM::Vector vec)
		{
			_shader.Use();
			_shader.SetUniform(name.c_str(), vec);
		}

		inline void SetShaderUniform(string name, KM::Matrix mat)
		{
			_shader.Use();
			_shader.SetUniform(name.c_str(), mat);
		}

//===== NumVertices =====
		inline S32 GetNumVertices(void)
		{
			return _numIndices;
		}

//===== Vertex =====
		inline void AddVertex(const Vertex&  vert)
		{
			_vertices.push_back(vert);
		}

		inline void SetVertices(std::vector<Vertex> vertices)
		{
			_vertices = vertices;
		}

		inline std::vector<Vertex> GetVertices(void) const
		{
			return _vertices;
		}

//===== Indices =====		
		inline void AddIndex(U32 index)
		{
			_indices.push_back(index);
			++_numIndices;
		}

		inline void SetIndices(std::vector<U32> indices)
		{
			_indices = indices;
			_numIndices = _indices.size();
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

//===== Uv List =====
		inline std::vector<F32> GetUVList(void) const
		{
			return _uvList;
		}

		inline void SetUVList(std::vector<F32> list)
		{
			_uvList = list;
		}

		inline void AddUV(F32 val)
		{
			_uvList.push_back(val);
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
		bool					_activeRender;
		bool 					_meshLoaded;
		KM::Vector				_position;
		KM::Vector 				_scale;
		S32						_numIndices;
		std::vector<Vertex> 	_vertices;
		std::vector<U32> 		_indices;
		GLuint 					_vao;
		GLuint 					_vbo[NUM_VBO];
		std::vector<F32> 		_uvList;

	};
}