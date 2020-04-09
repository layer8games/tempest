#pragma once

//===== Engine Includes =====
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/Shader.h>
#include <Engine/Point2.h>
#include <Engine/Vector2.h>
#include <Engine/Matrix4.h>
#include <Engine/Color.h>
#include <Engine/Quaternion.h>
#include <Engine/Texture.h>
#include <Engine/ShaderManager.h>
#include <Engine/AABB.h>
#include <Engine/Mesh.h>
#include <Engine/BufferData.h>
#include <Engine/Event.hpp>

namespace TM = TempestMath;
namespace TC = TempestCollisions;

namespace Tempest
{
    /// The GameObject2D may be the backbone of Tempest. This is the basic object that will exist in the game. It is the root of 
    /// all rendered and interactive objects in the games. It is not a manager. This is an abstract class, so it is meant to be
    /// full implemented as needed. This holds the generic ideas of what makes up the most basic type of Object in the game Level.
    class GameObject2D
    {
    public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
        /// Sets up initial values. Most of them are set to 0. Active is set to true.
        TEMPEST_API GameObject2D(void);

        /// Copies a GameObject2D.
        TEMPEST_API GameObject2D(const GameObject2D& obj);

        /// Deletes the buffers that are used for the shader. These should probably be moved. 
        TEMPEST_API virtual ~GameObject2D(void);

        TEMPEST_API void Init(void);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
        /// Abstract function. This update is called one per frame, if the object is registered with the GameObject2DManager and is
        /// Update Active.
        virtual void v_Update(void)=0;

        /// Default Render will check if there is a texture attached to the Object, make the shader on the object active, and will
        /// send the vertices that have been added to the object to OpenGL using glDrawArrays. This is virtual because it can be 
        /// overloaded if this is not what you need for rendering.
        inline virtual void v_Render(void)
        {
            DefaultRender();
        }

        /// Called when the Object is made active. Calls DefaultAwake. Can be overloaded if you need something different.		
        inline virtual void v_Awake(void)
        {
            DefaultAwake();
        }

        /// Handle an event that is passed to this object. This behavior is to be defined by each GameObject2D that is made. 
        /// The default behavior is to ignore the Event.
        virtual void v_OnEvent(Event event)
        {  }

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
        /// Get the active state of the GameObject2D. Returns true if is active update and active render		
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
        /// Returns the ID for the GameObject2D.		
        inline const U32 GetID(void) const
        {
            return _ID;
        }

//===== Position =====
        /// Returns the current position of the GameObject2D in world space.		
        inline const TM::Point2& GetPosition(void) const
        {
            return _position;
        }

        /// Set the position of the GameObject2D in world space. The bounding boxes center location is also updated.
        /// \param pos is the new position for the object and bounding box.
        inline void SetPosition(const TM::Point2& pos)
        {
            _position = pos;
            _boundingBox.SetCenter(_position);
        }

        /// Set the x and y values of the GameObject2D in world space. The bounding box center is updated. 
        /// \param xVal is the new x offset.
        /// \param yVal is the new y offset.
        inline void SetPosition(F32 xVal, F32 yVal)
        {
            _position[0] = xVal;
            _position[1] = yVal;
            _boundingBox.SetCenter(_position);
        }

        /// Set just the x value of the GameObject2D in world space. Bounding box center is updated.
        /// \param xval is the new x offset.
        inline void SetPositionX(F32 xval)
        {
            _position[0] = xval;
            _boundingBox.SetCenter(_position);
        }

        /// Set just the y value of the GameObject2D in world space. Bounding box center is updated.
        /// \param yVal is the new y offset.		
        inline void SetPositionY(F32 yVal)
        {
            _position[1] = yVal;
            _boundingBox.SetCenter(_position);
        }

        /// Set the Position of the GameObject2D scaled by a factor. Vector4::AddScaledVector is called. Bounding Box is updated. 
        /// \param pos is the new position for the object.
        /// \param scale is the factor that the pos is scaled by.
        inline void AddScaledPosition(const TM::Vector2& pos, F32 scale)
        {
            _position.AddScaledVector(pos, scale);
            _boundingBox.SetCenter(_position);
        }

        /// Set the Position of the GameObject2D scaled by a factor. Vector3::AddScaledVector is called. Bounding Box is updated. 
        /// \param pos is the new position for the object.
        /// \param scale is the factor that the pos is scaled by.
        inline void AddScaledPosition(const TM::Vector3& pos, F32 scale)
        {
            _position.AddScaledVector(pos, scale);
            _boundingBox.SetCenter(_position);
        }

        /// Set the Position of the GameObject2D scaled by a factor. Point::AddScaledVector is called. Bounding Box is updated. 
        /// \param pos is the new position for the object.
        /// \param scale is the factor that the pos is scaled by.		
        inline void AddScaledPosition(const TM::Point2& point, F32 scale)
        {
            _position.AddScaledPoint(point, scale);
            _boundingBox.SetCenter(_position);
        }

//===== Scale =====
        /// Return the current scale factor for the GameObject2D.		
        inline const TM::Vector2& GetScale(void) const
        {
            return _scale;
        }

        /// Sets a new scale factor for the GameObject2D. Bounding Box is updated.
        /// \param scale is set as the new scale. No matrix is updated.
        inline void SetScale(const TM::Vector2& scale)
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

//===== Orientation =====
        /// Returns the current orientation of the GameObject2D		
        inline const TM::Quaternion& GetOrientation(void) const
        {
            return _orientation;
        }

        /// Set a new orientation for the GameObject2D.
        /// \param q is the new orienation.
        inline void SetOrientation(const TM::Quaternion& q)
        {
            _orientation = q;
        }

        /// Set the orientation of the GameObject2D with an Euler Angle. The Vector3 is treated as 
        /// an Euler Angle in this context. 
        /// \param vec is the new orientation represent as an Euler Angle.
        inline void SetOrientation(const TM::Vector3& vec)
        {
            _orientation.RotateByEuler(vec);
        }

        /// Set the orientation of the GameObject2D with an Euler Angle.
        /// \param yaw
        /// \param pitch
        /// \param roll
        inline void SetOrientation(real yaw, real pitch, real roll)
        {
            _orientation.RotateByEuler(yaw, pitch, roll);
        }

        /// Add an Euler Angle to the current orientation. Vector3 is treated as an Euler Angle 
        /// in this context. 
        /// \param vec is an Euler Angle.
        inline void AddOrientation(const TM::Vector3& vec)
        {
            _orientation.AddEuler(vec);
        }

        /// Add an Euler Angle to the current orientation. 
        /// \param yaw
        /// \param pitch 
        /// \param roll
        inline void AddOrientation(real yaw, real pitch, real roll)
        {
            _orientation.AddEuler(yaw, pitch, roll);
        }

        /// Changes the length of the orientation to be 1.0. Calls Quaternion::Normalize.
        inline void NormalizeOrientation(void)
        {
            _orientation.Normalize();
        }

//===== Color =====		
        /// Change the color of the GameObject2D.
        /// \param col is the new color.
        inline void SetColor(const Color& col)
        {
            _color = col;
        }

        /// Change the color of the GameObject2D without having to create a Color object. Alpha is ommited.
        /// \param red is the value of red in the color, should range from 0.0f to 1.0f.
        /// \param green is the value of green in the color, should range from 0.0f to 1.0f.
        /// \param blue is the value of blue in the color, should range from 0.0f to 1.0f.
        inline void SetColor(F32 red, F32 green, F32 blue)
        {
            _color[0] = red;
            _color[1] = green;
            _color[2] = blue;
        }

        /// Return the color of the GameObject2D		
        inline const Color& GetColor(void) const
        {
            return _color;
        }

//===== AABB Bounding Volume =====
        /// Helper wrapper for AABB::TestCollission. This checks if the Bounding Box of another GameObject2D is overlapping this GameObject2D.
        /// Returns true if the bounding boxes overlap.
        /// \param other is the GameObject2D to test against.
        inline bool OverlapCheck(const shared_ptr<GameObject2D> other)
        {
            return _boundingBox.TestCollision(other->GetBounding());
        }

        /// Return the bounding boxe of this GameObject2D.		
        inline const TC::AABB& GetBounding(void) const
        {
            return _boundingBox;
        }

//===== Texture =====
        /// Change the texture of the GameObject2D. 
        /// \param texture is the new texture for the GameObject2D.
        inline void SetTexture(p_Texture texture)
        {
            _texture = texture;
            _shader->SetUniform("has_texture", true);
        }

        /// Return the current texture pointer for the GameObject2D.		
        inline p_Texture GetTexture(void) const
        {
            return _texture;
        }

        /// Helper wrapper to call Texture::Bind on the texture that is saved on this GameObject2D.		
        inline void BindTexture(bool state=true)
        {
            _texture->Bind(state);
        }

//===== Shader =====
        /// Returns the current shader for this GameObject2D.		
        inline const p_Shader GetShader(void) const
        {
            return _shader;
        }

        /// Change the shader for this GameObject2D.		
        inline void SetShader(const p_Shader shader)
        {
            _shader = shader;
        }

        //===== Mesh =====
        inline void SetMesh(p_Mesh mesh)
        {
            _mesh = mesh;
        }

    protected:
        /// Default code to be run when v_Awake is called.		
        TEMPEST_API void DefaultAwake(void);

        /// Default code to Render the Object.
        TEMPEST_API void DefaultRender(void);

        /// Default behavior that should be considered when calling Update on an GameObject2D. This calls UpdateInternals.
        TEMPEST_API void DefaultUpdate(void);

//==========================================================================================================================
//
//Protected Data
//
//==========================================================================================================================		
        p_Shader				_shader;				///< Shader used for rendering. Should come from the ShaderManager. Set to null by default.
        p_Mesh					_mesh;					///< Collection of vertices that make up the body of the rendered object.
        TC::AABB				_boundingBox;			///< Collision bounding box for the object. Is active and set up by default.

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
        TM::Point2 				_position;				///< Position of the object in world space.
        TM::Vector2				_scale;					///< Scale of the object in world space.
        TM::Quaternion			_orientation;			///< Orientation of the object in world space. Untested.
        Color 					_color;					///< Color that should be used to tint the object. How it affects the object depends on what shader you are using.
        p_Texture				_texture;				///< Texture used when rendering the object. Set to null by default.
        bool					_activeUpdate;			///< State of the object in the update loop. If true, v_Update will be called. 
        bool					_activeRender;			///< State of the object in the render loop. If true, v_Render will be called.
        U32 					_ID;					///< ID should be unique, but this system needs to be changed.
    };//End class
    typedef shared_ptr<GameObject2D> p_GameObject2D;
}