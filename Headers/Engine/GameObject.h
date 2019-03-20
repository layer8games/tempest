#pragma once

//===== Engine Includes =====
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/Shader.h>
#include <Engine/Point.h>
#include <Engine/Vector3.h>
#include <Engine/Vector4.h>
#include <Engine/Matrix4.h>
#include <Engine/Color.h>
#include <Engine/Vertex.h>
#include <Engine/Quaternion.h>
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
		void UpdateInternals(void);

		bool LoadOBJ(string filepath);

		void LoadMesh(string filepath);

		void MakeSprite(void);

		const KM::Matrix4& GetModelMatrix(void) const
		{
			return _modelTOWorldCache;
		}

		//temporary idea. 
		//In Matrix4, add Translate vs Transform vs Rotate
		const KM::Matrix4 GetModelMatrixRot(void) const
		{
			KM::Matrix4 mat = _modelTOWorldCache; 
			mat.Translate(0.0f, 0.0f, 0.0f);
			return mat;
		}

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
		inline const KM::Point& GetPosition(void) const
		{
			return _position;
		}

		inline void SetPosition(const KM::Point& pos)
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

		inline void AddScaledPosition(const KM::Vector4& pos, F32 scale)
		{
			_position.AddScaledVector(pos, scale);
		}

		inline void AddScaledPosition(const KM::Point& point, F32 scale)
		{
			_position.AddScaledPoint(point, scale);
		}

//===== Scale =====
		inline const KM::Vector3& GetScale(void) const
		{
			return _scale;
		}

		inline void SetScale(const KM::Vector3& scale)
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

//===== Orientation =====
		inline const KM::Quaternion& GetOrientation(void) const
		{
			return _orientation;
		}

		inline void SetOrientation(const KM::Quaternion& q)
		{
			_orientation = q;
		}

		inline void SetOrientation(F32 wVal, F32 xVal, F32 yVal, F32 zVal)
		{
			_orientation[0] = wVal;
			_orientation[1] = xVal;
			_orientation[2] = yVal;
			_orientation[3] = zVal;
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

		inline void SetUniform(string name, const KM::Vector4& vec)
		{
			_shader->Use();
			_shader->SetUniform(name.c_str(), vec);
		}

		inline void SetUniform(string name, const KM::Vector3& vec)
		{
			_shader->Use();
			_shader->SetUniform(name.c_str(), vec);
		}

		inline void SetUniform(string name, const KM::Point& point)
		{
			_shader->Use();
			_shader->SetUniform(name.c_str(), point);
		}

		inline void SetUniform(string name, const KM::Matrix4& mat)
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

	protected:
		KM::Point& _AccessPosition(void)
		{
			return _position;
		}

		KM::Quaternion& _AccessOrientation(void)
		{
			return _orientation;
		}

	private:
		std::vector<U32> _SplitU32(string text, char delim) const;
		
		std::vector<F32> _SplitF32(string text, char delim) const;

		std::vector<string> _SplitString(string text, char delim) const;

		void _CalculateCachedData(void);

//==========================================================================================================================
//
//Data
//
//==========================================================================================================================		
		static U32				_nextID;
		
		std::vector<Vertex> 	_vertices;
		std::vector<U32> 		_indices;
		std::vector<F32> 		_uvList;
		KM::Matrix4 			_modelTOWorldCache;
		KM::Point				_position;
		KM::Vector3 			_scale;
		KM::Quaternion 			_orientation;
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