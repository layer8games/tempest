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
#include <Engine/ShaderManager.h>

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
	enum BufferData
	{
		VERTEX_BUFFER = 0,
		VERTEX_POS = 0,
		FRAGMENT_BUFFER = 1,
		FRAGMENT_POS = 2,
		TEX_COORD_BUFFER = 2,
		TEX_COORD_POS = 1,
		INDEX_BUFFER = 3,
		NORMAL_BUFFER = 4,
		NORMAL_POS = 3,
		NUM_VBO = 5
	};
	
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

		void MakeSprite(void);

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
//===== All Active =====
		inline const bool GetActive(void) const
		{
			return _activeUpdate && _activeRender;
		}

		inline void SetActive(bool state)
		{
			_activeUpdate = state;
			_activeRender = state;
		}

		inline void SetActive(void)
		{
			_activeUpdate = true;
			_activeRender = true;
		}

		inline void SetInactive(void)
		{
			_activeUpdate = false;
			_activeRender = false;
		}

//===== Active Update =====		
		inline const bool GetActiveUpdate(void) const
		{
			return _activeUpdate;
		}

		inline void SetActiveUpdate(bool state)
		{
			_activeUpdate = state;
		}

		inline void SetActiveUpdate(void)
		{
			_activeUpdate = true;
		}

		inline void SetInactiveUpdate(void)
		{
			_activeUpdate = false;
		}

//===== Active Render =====
		inline const bool GetActiveRender(void) const
		{
			return _activeRender;
		}

		inline void SetActiveRender(bool state)
		{
			_activeRender = state;
		}

		inline void SetActiveRender(void)
		{
			_activeRender = true;
		}

		inline void SetInactiveRender(void)
		{
			_activeRender = false;
		}

//===== Is Sprite =====
		inline bool IsSprite(void) const
		{
			return _isSprite;
		}

//===== ID =====
		inline const U32 GetID(void) const
		{
			return _ID;
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

		inline void SetPositionX(F32 xval)
		{
			_position[0] = xval;
		}

		inline void SetPositionY(F32 yVal)
		{
			_position[1] = yVal;
		}

		inline void SetPositionZ(F32 zVal)
		{
			_position[2] = zVal;
		}

		inline void AddScaledPosition(const KM::Vector pos, F32 scale)
		{
			_position.AddScaledVector(pos, scale);
		}

//===== Scale =====
		inline const KM::Vector& GetScale(void) const
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

//===== Color =====		
		inline void SetColor(const Color& col)
		{
			_color = col;
		}

		inline void SetColor(F32 red, F32 green, F32 blue)
		{
			_color[0] = red;
			_color[1] = green;
			_color[2] = blue;
		}

		inline const Color& GetColor(void) const
		{
			return _color;
		}

//===== Texture =====
		inline void SetTexture(shared_ptr<Texture> texture)
		{
			_texture = texture;
		}

		inline shared_ptr<Texture> GetTexture(void) const
		{
			return _texture;
		}

		inline void BindTexture(bool state=true)
		{
			_texture->Bind(state);
		}

//===== Shader =====
		inline const shared_ptr<Shader> GetShader(void) const
		{
			return _shader;
		}

		inline void SetShader(const shared_ptr<Shader> shader)
		{
			_shader = shader;
		}

		inline void LoadShader(std::vector<ShaderData> shaderData)
		{
			_shader->LoadShader(shaderData);
		}

		inline void UseShader(bool state=true)
		{
			_shader->Use(state);
		}

		inline void SetUniform(string name, const F32 val)
		{
			_shader->Use();
			_shader->SetUniform(name.c_str(), val);
		}

		inline void SetUniform(string name, const KM::Vector& vec)
		{
			_shader->Use();
			_shader->SetUniform(name.c_str(), vec);
		}

		inline void SetUniformVec3(string name, const KM::Vector& vec)
		{
			_shader->Use();
			_shader->SetUniformVec3(name.c_str(), vec);
		}

		inline void SetUniform(string name, const KM::Matrix& mat)
		{
			_shader->Use();
			_shader->SetUniform(name.c_str(), mat);
		}

		inline void SetUniformSampler(string name, S32 texSlot)
		{
			_shader->Use();
			_shader->SetUniformSampler(name.c_str(), texSlot);
		}

		inline void SetUniform(string name, const Color& col)
		{
			_shader->Use();
			_shader->SetUniform(name.c_str(), col);
		}

		inline void SetUniformVec3(string name, const Color& col)
		{
			_shader->Use();
			_shader->SetUniformVec3(name.c_str(), col);
		}

//===== NumVertices =====
		inline U32 GetNumVertices(void)
		{
			return _vertices.size();
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
		}

		inline void SetIndices(std::vector<U32> indices)
		{
			_indices = indices;
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

//===== VBO =====
		void BindVBO(BufferData buffer, bool state=true);

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

	private:
		std::vector<U32> _SplitU32(string text, char delim) const;
		
		std::vector<F32> _SplitF32(string text, char delim) const;

		std::vector<string> _SplitString(string text, char delim) const;

//==========================================================================================================================
//
//Data
//
//==========================================================================================================================		
		static U32				_nextID;
		
		std::vector<Vertex> 	_vertices;
		std::vector<U32> 		_indices;
		std::vector<F32> 		_uvList;
		KM::Vector				_position;
		KM::Vector 				_scale;
		Color 					_color;
		shared_ptr<Texture>		_texture;
		shared_ptr<Shader>		_shader;
		bool					_activeUpdate;
		bool					_activeRender;
		bool 					_isSprite;
		U32 					_ID;
		GLuint 					_vao;
		GLuint 					_vbo[NUM_VBO];
	};
}