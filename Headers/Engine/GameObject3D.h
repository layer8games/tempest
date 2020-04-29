#pragma once

//===== Engine Includes =====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/Shader.h>
#include <Engine/Point3.h>
#include <Engine/Vector3.h>
#include <Engine/Vector4.h>
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
    class GameObject3D
    {
    public:
        TEMPEST_API GameObject3D(void);
        
        TEMPEST_API GameObject3D(const GameObject3D& obj);
       
        TEMPEST_API virtual ~GameObject3D(void);
        
        virtual void v_Update(void)=0;

        inline virtual void v_Render(void)
        {
            DefaultRender();
        }

        inline virtual void v_Awake(void)
        {
            DefaultAwake();
        }

        virtual void v_OnEvent(Event event)
        {  }

        TEMPEST_API void UpdateInternals(void);

        inline const TM::Matrix4& GetModelMatrix(void) const
        {
            return _modelTOWorldCache;
        }

        inline const TM::Matrix4 GetModelMatrixRot(void) const
        {
            TM::Matrix4 mat = _modelTOWorldCache; 
            mat.SetTranslate(0.0f, 0.0f, 0.0f);
            return mat;
        }
        
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

        inline const U32 GetID(void) const
        {
            return _ID;
        }
    
        inline const TM::Point3& GetPosition(void) const
        {
            return _position;
        }

        inline void SetPosition(const TM::Point3& pos)
        {
            _position = pos;
            _boundingBox.SetCenter(_position);
        }

        inline void SetPosition(F32 xVal, F32 yVal, F32 zVal)
        {
            _position.x = xVal;
            _position.y = yVal;
            _position.z = zVal;
            _boundingBox.SetCenter(_position);
        }

        inline void SetPositionX(F32 xval)
        {
            _position.x = xval;
            _boundingBox.SetCenter(_position);
        }

        inline void SetPositionY(F32 yVal)
        {
            _position.y = yVal;
            _boundingBox.SetCenter(_position);
        }

        inline void SetPositionZ(F32 zVal)
        {
            _position.z = zVal;
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

        inline void AddScaledPosition(const TM::Point3& point, F32 scale)
        {
            _position.AddScaledPoint(point, scale);
            _boundingBox.SetCenter(_position);
        }

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

        inline void SetScale(F32 xVal, F32 yVal, F32 zVal)
        {
            _scale.x = xVal;
            _scale.y = yVal;
            _scale.z = zVal;
            _boundingBox.SetHalfDimensions(_scale);
        }

        inline const TM::Quaternion& GetOrientation(void) const
        {
            return _orientation;
        }

        inline void SetOrientation(const TM::Quaternion& q)
        {
            _orientation = q;
        }

        inline void SetOrientation(const TM::Vector3& vec)
        {
            _orientation.RotateByEuler(vec);
        }

        inline void SetOrientation(real yaw, real pitch, real roll)
        {
            _orientation.RotateByEuler(yaw, pitch, roll);
        }

        inline void AddOrientation(const TM::Vector3& vec)
        {
            _orientation.AddEuler(vec);
        }

        inline void AddOrientation(real yaw, real pitch, real roll)
        {
            _orientation.AddEuler(yaw, pitch, roll);
        }

        inline void NormalizeOrientation(void)
        {
            _orientation.Normalize();
        }

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

        inline bool OverlapCheck(const shared_ptr<GameObject3D> other)
        {
            return _boundingBox.TestCollision(other->GetBounding());
        }

        inline const TC::AABB& GetBounding(void) const
        {
            return _boundingBox;
        }

        inline void SetTexture(p_Texture texture)
        {
            _texture = texture;
            
            if(_shader != nullptr)
            {
                _shader->SetUniform("has_texture", true);
            }
        }

        inline p_Texture GetTexture(void) const
        {
            return _texture;
        }

        inline void BindTexture(bool state=true)
        {
            if(_texture != nullptr)
            {
                _texture->Bind(state);
            }
        }

        inline const p_Shader GetShader(void) const
        {
            return _shader;
        }

        inline void SetShader(const p_Shader shader)
        {
            _shader = shader;
        }

        inline void SetMesh(p_Mesh mesh)
        {
            _mesh = mesh;
        }

    protected:
        TEMPEST_API void DefaultAwake(void);

        TEMPEST_API void DefaultRender(void);

        TEMPEST_API void DefaultUpdate(void);

        p_Shader _shader;				
        p_Mesh _mesh;					
        TC::AABB _boundingBox;			

    private:
        void _CalculateCachedData(void);

        static U32 _nextID;				
        TM::Matrix4	_modelTOWorldCache;		
        TM::Point3 _position;				
        TM::Vector3 _scale;					
        TM::Quaternion _orientation;			
        Color _color;					
        p_Texture _texture;				
        bool _activeUpdate;			
        bool _activeRender;			
        U32 _ID;					
    };//End class
    typedef shared_ptr<GameObject3D> p_GameObject3D;
}