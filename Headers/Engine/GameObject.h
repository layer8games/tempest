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
#include <Engine/AABB.h>

namespace TM = TempestMath;
namespace TC = TempestCollisions;

#include <rapidxml.hpp>

//===== STL inludes =====
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <regex>
#include <stdlib.h>

namespace Tempest
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
	
	class TEMPEST_API GameObject
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

		inline virtual void v_Awake(void)
		{
			DefaultAwake();
		}

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
		void InitOGL(void);

		void UpdateInternals(void);

		bool LoadOBJ(string filepath);

		void LoadMesh(string filepath);

		void MakeSprite(void);

		inline const TM::Matrix4& GetModelMatrix(void) const
		{
			return _modelTOWorldCache;
		}

		//temporary idea. 
		//In Matrix4, add Translate vs Transform vs Rotate
		inline const TM::Matrix4 GetModelMatrixRot(void) const
		{
			TM::Matrix4 mat = _modelTOWorldCache; 
			mat.SetTranslate(0.0f, 0.0f, 0.0f);
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
			if(!_activeUpdate || !_activeRender)
			{
				v_Awake();
			}
			
			_activeUpdate = state;
			_activeRender = state;
		}

		inline void SetActive(void)
		{
			v_Awake();
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
		inline const TM::Point& GetPosition(void) const
		{
			return _position;
		}

		inline void SetPosition(const TM::Point& pos)
		{
			_position = pos;
			_boundingBox.SetCenter(_position);
		}

		inline void SetPosition(F32 xVal, F32 yVal)
		{
			_position[0] = xVal;
			_position[1] = yVal;
			_boundingBox.SetCenter(_position);
		}

		inline void SetPosition(F32 xVal, F32 yVal, F32 zVal)
		{
			_position[x] = xVal;
			_position[y] = yVal;
			_position[z] = zVal;
			_boundingBox.SetCenter(_position);
		}

		inline void SetPositionX(F32 xval)
		{
			_position[0] = xval;
			_boundingBox.SetCenter(_position);
		}

		inline void SetPositionY(F32 yVal)
		{
			_position[1] = yVal;
			_boundingBox.SetCenter(_position);
		}

		inline void SetPositionZ(F32 zVal)
		{
			_position[2] = zVal;
			_boundingBox.SetCenter(_position);
		}

		inline void AddScaledPosition(const TM::Vector4& pos, F32 scale)
		{
			_position.AddScaledVector(pos, scale);
			_boundingBox.SetCenter(_position);
		}

		inline void AddScaledPosition(const TM::Vector3& pos, F32 scale)
		{
			_position.AddScaledVector(pos, scale);
			_boundingBox.SetCenter(_position);
		}

		inline void AddScaledPosition(const TM::Point& point, F32 scale)
		{
			_position.AddScaledPoint(point, scale);
			_boundingBox.SetCenter(_position);
		}

//===== Scale =====
		inline const TM::Vector3& GetScale(void) const
		{
			return _scale;
		}

		inline void SetScale(const TM::Vector3& scale)
		{
			_scale = scale;
			_boundingBox.SetHalfDimensions(_scale);
		}

		inline void SetScale(F32 val)
		{
			_scale = val;
			_boundingBox.SetHalfDimensions(_scale);
		}

		inline void SetScale(F32 xVal, F32 yVal)
		{
			_scale[0] = xVal;
			_scale[1] = yVal;
			_boundingBox.SetHalfDimensions(_scale);
		}

		inline void SetScale(F32 xVal, F32 yVal, F32 zVal)
		{
			_scale[0] = xVal;
			_scale[1] = yVal;
			_scale[2] = zVal;
			_boundingBox.SetHalfDimensions(_scale);
		}

//===== Orientation =====
		inline const TM::Quaternion& GetOrientation(void) const
		{
			return _orientation;
		}

		inline void SetOrientation(const TM::Quaternion& q)
		{
			_orientation = q;
		}

		inline void SetOrientation(F32 val)
		{
			_orientation[0] = val;
			_orientation[1] = val;
			_orientation[2] = val;
			_orientation[3] = val;
		}

		inline void SetOrientation(F32 wVal, F32 xVal, F32 yVal, F32 zVal)
		{
			_orientation[0] = wVal;
			_orientation[1] = xVal;
			_orientation[2] = yVal;
			_orientation[3] = zVal;
		}

		inline void AddScaledOrientation(const TM::Vector4 vec, F32 scale)
		{
			_orientation.AddScaledVector(vec, scale);
		}

		inline void NormalizeOrientation(void)
		{
			_orientation.Normalize();
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

		inline void SetColor(F32 val)
		{
			_color[0] = val;
			_color[1] = val;
			_color[2] = val;
		}

		inline const Color& GetColor(void) const
		{
			return _color;
		}

//===== AABB Bounding Volume =====
		inline bool OverlapCheck(const shared_ptr<GameObject> other)
		{
			return _boundingBox.TestCollision(other->GetBounding());
		}

		inline const TC::AABB& GetBounding(void) const
		{
			return _boundingBox;
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

		inline void SetUniform(string name, const TM::Vector4& vec)
		{
			_shader->Use();
			_shader->SetUniform(name.c_str(), vec);
		}

		inline void SetUniform(string name, const TM::Vector3& vec)
		{
			_shader->Use();
			_shader->SetUniform(name.c_str(), vec);
		}

		inline void SetUniform(string name, const TM::Point& point)
		{
			_shader->Use();
			_shader->SetUniform(name.c_str(), point);
		}

		inline void SetUniform(string name, const TM::Matrix4& mat)
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
		void DefaultAwake(void);

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
		TM::Matrix4 			_modelTOWorldCache;		
		TM::Point 				_position;
		TM::Vector3				_scale;
		TM::Quaternion			_orientation;
		Color 					_color;
		TC::AABB				_boundingBox;
		shared_ptr<Texture>		_texture;
		shared_ptr<Shader>		_shader;
		bool					_activeUpdate;
		bool					_activeRender;
		bool 					_isSprite;
		U32 					_ID;
		GLuint 					_vao;
		GLuint 					_vbo[NUM_VBO];
	};//End class
	typedef shared_ptr<GameObject> p_GameObject;
}