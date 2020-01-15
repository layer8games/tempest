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
#include <Engine/Mesh.h>

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
	/// The GameObject may be the backbone of Tempest. This is the basic object that will exist in the game. It is the root of 
	/// all rendered and interactive objects in the games. It is not a manager. This is an abstract class, so it is meant to be
	/// full implemented as needed. This holds the generic ideas of what makes up the most basic type of Object in the game Level.
	class GameObject
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		/// Sets up initial values. Most of them are set to 0. Active is set to true.
		TEMPEST_API GameObject(void);

		/// Copies a GameObject.
		TEMPEST_API GameObject(const GameObject& obj);

		/// Deletes the buffers that are used for the shader. These should probably be moved. 
		TEMPEST_API virtual ~GameObject(void);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
		/// Abstract function. This update is called one per frame, if the object is registered with the GameObjectManager and is
		/// Update Active.
		virtual void v_Update(void)=0;

		/// Default Render will check if there is a texture attached to the Object, make the shader on the object active, and will
		/// send the vertices that have been added to the object to OpenGL using glDrawArrays. This is virtual because it can be 
		/// overloaded if this is not what you need for rendering.
		TEMPEST_API virtual void v_Render(void);

		TEMPEST_API void DefaultRender(void);

		/// Called when the Object is made active. Calls DefaultAwake. Can be overloaded if you need something different.		
		inline virtual void v_Awake(void)
		{
			DefaultAwake();
		}

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
		/// Calls _CalculateCachedData. The idea is that the data for the Object can be cached, and this updates that cache. 
		/// This has some issues since it is not always called. 
		TEMPEST_API void UpdateInternals(void);

		/// Returns the "view" matrix, the transform needed to get the object transformed into world space. This is used by opengl for
		/// rendering.
		inline const TM::Matrix4& GetModelMatrix(void) const
		{
			return _modelTOWorldCache;
		}

		//temporary idea. 
		//In Matrix4, add Translate vs Transform vs Rotate
		/// A temporary experiment meant to return the "view" matrix, with the rotations. This is a first attempt to make rotations 
		/// work, but it didn't really work out very well. Issue #51 should fix this. 
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
		/// Get the active state of the GameObject. Returns true if is active update and active render		
		inline const bool GetActive(void) const
		{
			return _activeUpdate && _activeRender;
		}

		/// Sets the active sate of the object. If either update or render is in active, v_Awake is called. Both update and rendering
		/// are set to active. 
		/// \param state is the new state, no default value.
		inline void SetActive(bool state)
		{
			if(!_activeUpdate || !_activeRender)
			{
				v_Awake();
			}
			
			_activeUpdate = state;
			_activeRender = state;
		}

		/// Sets update and render to active and calls v_Awake		
		inline void SetActive(void)
		{
			v_Awake();
			_activeUpdate = true;
			_activeRender = true;
		}

		/// Sets update and render to inactive.		
		inline void SetInactive(void)
		{
			_activeUpdate = false;
			_activeRender = false;
		}

//===== Active Update =====		
		/// Returns true if update is active. 		
		inline const bool GetActiveUpdate(void) const
		{
			return _activeUpdate;
		}

		/// Set active update state. v_Awake is not called.
		/// \param state is the new state for update. 
		inline void SetActiveUpdate(bool state)
		{
			_activeUpdate = state;
		}

		/// Set update to active. v_Awake is not called.		
		inline void SetActiveUpdate(void)
		{
			_activeUpdate = true;
		}

		/// Set update to not active. 		
		inline void SetInactiveUpdate(void)
		{
			_activeUpdate = false;
		}

//===== Active Render =====
		/// Returns true if render is active.		
		inline const bool GetActiveRender(void) const
		{
			return _activeRender;
		}

		/// Set a new state for render. v_Awake is not called.
		/// \param state is the new state for render.
		inline void SetActiveRender(bool state)
		{
			_activeRender = state;
		}

		/// Set render to active. v_Awake is not called.
		inline void SetActiveRender(void)
		{
			_activeRender = true;
		}

		/// Set render to not active.		
		inline void SetInactiveRender(void)
		{
			_activeRender = false;
		}

//===== ID =====
		/// Returns the ID for the GameObject.		
		inline const U32 GetID(void) const
		{
			return _ID;
		}
	
//===== Position =====
		/// Returns the current position of the GameObject in world space.		
		inline const TM::Point& GetPosition(void) const
		{
			return _position;
		}

		/// Set the position of the GameObject in world space. The bounding boxes center location is also updated.
		/// \param pos is the new position for the object and bounding box.
		inline void SetPosition(const TM::Point& pos)
		{
			_position = pos;
			_boundingBox.SetCenter(_position);
		}

		/// Set the x and y values of the GameObject in world space. The bounding box center is updated. 
		/// \param xVal is the new x offset.
		/// \param yVal is the new y offset.
		inline void SetPosition(F32 xVal, F32 yVal)
		{
			_position[0] = xVal;
			_position[1] = yVal;
			_boundingBox.SetCenter(_position);
		}

		/// Set the x, y and z values of the GameObject in world space. The bounding box center is updated. 
		/// \param xVal is the new x offset.
		/// \param yVal is the new y offset.
		/// \param zVal is the new z offset.
		inline void SetPosition(F32 xVal, F32 yVal, F32 zVal)
		{
			_position[x] = xVal;
			_position[y] = yVal;
			_position[z] = zVal;
			_boundingBox.SetCenter(_position);
		}

		/// Set just the x value of the GameObject in world space. Bounding box center is updated.
		/// \param xval is the new x offset.
		inline void SetPositionX(F32 xval)
		{
			_position[0] = xval;
			_boundingBox.SetCenter(_position);
		}

		/// Set just the y value of the GameObject in world space. Bounding box center is updated.
		/// \param yVal is the new y offset.		
		inline void SetPositionY(F32 yVal)
		{
			_position[1] = yVal;
			_boundingBox.SetCenter(_position);
		}

		/// Set just the z value of the GameObject in world space. Bounding box center is updated.
		/// \param zVal is the new z offset.
		inline void SetPositionZ(F32 zVal)
		{
			_position[2] = zVal;
			_boundingBox.SetCenter(_position);
		}

		/// Set the Position of the GameObject scaled by a factor. Vector4::AddScaledVector is called. Bounding Box is updated. 
		/// \param pos is the new position for the object.
		/// \param scale is the factor that the pos is scaled by.
		inline void AddScaledPosition(const TM::Vector4& pos, F32 scale)
		{
			_position.AddScaledVector(pos, scale);
			_boundingBox.SetCenter(_position);
		}

		/// Set the Position of the GameObject scaled by a factor. Vector3::AddScaledVector is called. Bounding Box is updated. 
		/// \param pos is the new position for the object.
		/// \param scale is the factor that the pos is scaled by.
		inline void AddScaledPosition(const TM::Vector3& pos, F32 scale)
		{
			_position.AddScaledVector(pos, scale);
			_boundingBox.SetCenter(_position);
		}

		/// Set the Position of the GameObject scaled by a factor. Point::AddScaledVector is called. Bounding Box is updated. 
		/// \param pos is the new position for the object.
		/// \param scale is the factor that the pos is scaled by.		
		inline void AddScaledPosition(const TM::Point& point, F32 scale)
		{
			_position.AddScaledPoint(point, scale);
			_boundingBox.SetCenter(_position);
		}

//===== Scale =====
		/// Return the current scale factor for the GameObject.		
		inline const TM::Vector3& GetScale(void) const
		{
			return _scale;
		}

		/// Sets a new scale factor for the GameObject. Bounding Box is updated.
		/// \param scale is set as the new scale. No matrix is updated.
		inline void SetScale(const TM::Vector3& scale)
		{
			_scale = scale;
			_boundingBox.SetHalfDimensions(_scale);
		}

		/// Set all values of the scale to a single value. Bounding Box is updated.
		inline void SetScale(F32 val)
		{
			_scale = val;
			_boundingBox.SetHalfDimensions(_scale);
		}

		/// Set x and y scale factors. Bounding Box is updated. 
		/// \pararm xVal is the new scale factor on the x axis.
		/// \pararm yVal is the new scale factor on the y axis.
		inline void SetScale(F32 xVal, F32 yVal)
		{
			_scale[0] = xVal;
			_scale[1] = yVal;
			_boundingBox.SetHalfDimensions(_scale);
		}

		/// Set x, y and z scale factors. Bounding Box is updated. 
		/// \pararm xVal is the new scale factor on the x axis.
		/// \pararm yVal is the new scale factor on the y axis.
		/// \pararm zVal is the new scale factor on the z axis.
		inline void SetScale(F32 xVal, F32 yVal, F32 zVal)
		{
			_scale[0] = xVal;
			_scale[1] = yVal;
			_scale[2] = zVal;
			_boundingBox.SetHalfDimensions(_scale);
		}

//===== Orientation =====
		/// Returns the current orientation of the GameObject		
		inline const TM::Quaternion& GetOrientation(void) const
		{
			return _orientation;
		}

		/// Set a new orientation for the GameObject.
		/// \param q is the new orienation.
		inline void SetOrientation(const TM::Quaternion& q)
		{
			_orientation = q;
		}

		/// Set the orienation of the GameObject to a single value
		/// \pararm val is the value all 4 components of the orientation will be set to.
		inline void SetOrientation(F32 val)
		{
			_orientation[0] = val;
			_orientation[1] = val;
			_orientation[2] = val;
			_orientation[3] = val;
		}

		/// Set the orientation of the GameObject without having to create a Quaternion
		/// \param wVal sets the w component.
		/// \param xVal sets the x component.
		/// \param yVal sets the y component.
		/// \param zVal sets the z component.
		inline void SetOrientation(F32 wVal, F32 xVal, F32 yVal, F32 zVal)
		{
			_orientation[0] = wVal;
			_orientation[1] = xVal;
			_orientation[2] = yVal;
			_orientation[3] = zVal;
		}

		/// Update to orientation by a Vector4 value scaled. This called Quaternion::AddScaledVector
		/// \param vec is a converted value to scale the orientation by. 
		/// \param scale is the value to scale the orientation by.
		inline void AddScaledOrientation(const TM::Vector4 vec, F32 scale)
		{
			_orientation.AddScaledVector(vec, scale);
		}

		/// Changes the length of the orientation to be 1.0. Calls Quaternion::Normalize.
		inline void NormalizeOrientation(void)
		{
			_orientation.Normalize();
		}

//===== Color =====		
		/// Change the color of the GameObject.
		/// \param col is the new color.
		inline void SetColor(const Color& col)
		{
			_color = col;
		}

		/// Change the color of the GameObject without having to create a Color object. Alpha is ommited.
		/// \param red is the value of red in the color, should range from 0.0f to 1.0f.
		/// \param green is the value of green in the color, should range from 0.0f to 1.0f.
		/// \param blue is the value of blue in the color, should range from 0.0f to 1.0f.
		inline void SetColor(F32 red, F32 green, F32 blue)
		{
			_color[0] = red;
			_color[1] = green;
			_color[2] = blue;
		}

		/// Return the color of the GameObject		
		inline const Color& GetColor(void) const
		{
			return _color;
		}

//===== AABB Bounding Volume =====
		/// Helper wrapper for AABB::TestCollission. This checks if the Bounding Box of another GameObject is overlapping this GameObject.
		/// Returns true if the bounding boxes overlap.
		/// \param other is the GameObject to test against.
		inline bool OverlapCheck(const shared_ptr<GameObject> other)
		{
			return _boundingBox.TestCollision(other->GetBounding());
		}

		/// Return the bounding boxe of this GameObject.		
		inline const TC::AABB& GetBounding(void) const
		{
			return _boundingBox;
		}

//===== Texture =====
		/// Change the texture of the GameObject. 
		/// \param texture is the new texture for the GameObject.
		inline void SetMeshTexture(shared_ptr<Texture> texture)
		{
			_mesh.SetTexture(texture);
		}

		/// Helper wrapper to call Texture::Bind on the texture that is saved on this GameObject.		
		inline void BindMeshTexture(bool state=true)
		{
			_mesh.BindTexture(state);
		}

//===== Mesh and Shader =====
		/// Call Mesh to get the number of vertices.
		inline U32 GetMeshNumVertices(void) const
		{
			return _mesh.GetNumVertices();
		}

		/// Returns the current shader for this GameObject.		
		inline const p_Shader GetMeshShader(void) const
		{
			return _mesh.GetShader();
		}

		/// Change the shader for this GameObject.		
		inline void SetMeshShader(const p_Shader shader)
		{
			_mesh.SetShader(shader);
		}

		/// Helper wrapper, calls Shader::LoadShader to initialize the Shader on this GameObject.
		/// \param shaderData is an array of programs to be compiled and added to the Shader.
		inline void LoadMeshShader(std::vector<ShaderData> shaderData)
		{
			_mesh.GetShader()->LoadShader(shaderData);
		}

		/// Helper wrapper, calls Shader::Use to set the current shader as active for OpenGL		
		inline void UseMeshShader(bool state=true)
		{
			_mesh.GetShader()->Use(state);
		}

		/// Helper wrapper, calls Shader::Use and Shader::SetUniform. 
		/// \param name is used to looked up if the uniform has been cached yet, and if it exists.
		/// \param val is the float to be passed into the uniform.
		inline void SetMeshShaderUniform(string name, const F32 val)
		{
			_mesh.GetShader()->Use();
			_mesh.GetShader()->SetUniform(name.c_str(), val);
		}

		/// Helper wrapper, calls Shader::Use and Shader::SetUniform. 
		/// \param name is used to looked up if the uniform has been cached yet, and if it exists.
		/// \param vec is the Vector4 to be passed into the uniform
		inline void SetUniform(string name, const TM::Vector4& vec)
		{
			_mesh.GetShader()->Use();
			_mesh.GetShader()->SetUniform(name.c_str(), vec);
		}

		/// Helper wrapper, calls Shader::Use and Shader::SetUniform. 
		/// \param name is used to looked up if the uniform has been cached yet, and if it exists.
		/// \param vec is the Vector3 to be passed into the uniform.
		inline void SetUniform(string name, const TM::Vector3& vec)
		{
			_mesh.GetShader()->Use();
			_mesh.GetShader()->SetUniform(name.c_str(), vec);
		}

		/// Helper wrapper, calls Shader::Use and Shader::SetUniform. 
		/// \param name is used to looked up if the uniform has been cached yet, and if it exists.
		/// \param point is passed as a Vector4 into the uniform.
		inline void SetUniform(string name, const TM::Point& point)
		{
			_mesh.GetShader()->Use();
			_mesh.GetShader()->SetUniform(name.c_str(), point);
		}

		/// Helper wrapper, calls Shader::Use and Shader::SetUniform. 
		/// \param name is used to looked up if the uniform has been cached yet, and if it exists.
		/// \param mat is passed into the uniform as a Matrix4
		inline void SetUniform(string name, const TM::Matrix4& mat)
		{
			_mesh.GetShader()->Use();
			_mesh.GetShader()->SetUniform(name.c_str(), mat);
		}

		/// Helper wrapper, calls Shader::Use and Shader::SetUniformSampler
		/// \param name is used to looked up if the uniform has been cached yet, and if it exists.
		/// \param texSlot is used to look up the needed sampler in the shader.
		inline void SetUniformSampler(string name, S32 texSlot)
		{
			_mesh.GetShader()->Use();
			_mesh.GetShader()->SetUniformSampler(name.c_str(), texSlot);
		}

		/// Helper wrapper, calls Shader::Use and Shader::SetUniform. 
		/// \param name is used to looked up if the uniform has been cached yet, and if it exists.
		/// \param col is passed into the uniform as a color4.
		inline void SetUniform(string name, const Color& col)
		{
			_mesh.GetShader()->Use();
			_mesh.GetShader()->SetUniform(name.c_str(), col);
		}

		/// Helper wrapper, calls Shader::Use and Shader::SetUniformVec3. 
		/// \param name is used to looked up if the uniform has been cached yet, and if it exists.
		/// \param col is passed into the shader, to be used as a color3
		inline void SetUniformVec3(string name, const Color& col)
		{
			_mesh.GetShader()->Use();
			_mesh.GetShader()->SetUniformVec3(name.c_str(), col);
		}	

	protected:
		/// Default code to be run when v_Awake is called.		
		TEMPEST_API void DefaultAwake(void);

	private:
		/// Creates a data cache of the model to world transformation matrix. This can help with objects that use their matrix a lot.		
		void _CalculateCachedData(void);

//==========================================================================================================================
//
//Data
//
//==========================================================================================================================		
		static U32				_nextID;				///< This is an early attempt to ensure that all ID as unique. This is a flawed approach.	
		TM::Matrix4 			_modelTOWorldCache;		///< Cache of the model to world transformation matrix. 
		TM::Point 				_position;				///< Position of the object in world space.
		TM::Vector3				_scale;					///< Scale of the object in world space.
		TM::Quaternion			_orientation;			///< Orientation of the object in world space. Untested.
		Color 					_color;					///< Color that should be used to tint the object. How it affects the object depends on what shader you are using.
		TC::AABB				_boundingBox;			///< Collision bounding box for the object. Is active and set up by default.
		Mesh					_mesh;
		bool					_activeUpdate;			///< State of the object in the update loop. If true, v_Update will be called. 
		bool					_activeRender;			///< State of the object in the render loop. If true, v_Render will be called.
		U32 					_ID;					///< ID should be unique, but this system needs to be changed.
		
	};//End class
	typedef shared_ptr<GameObject> p_GameObject;
}