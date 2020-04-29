#pragma once

//===== Engine Includes =====
#include "stdafx.h"
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
    class GameObject2D
    {
    public:
        TEMPEST_API GameObject2D(void);

        TEMPEST_API GameObject2D(const GameObject2D& obj);

        TEMPEST_API virtual ~GameObject2D(void);

        TEMPEST_API void Init(void);
        
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
            return _modelToWorldCache;
        }

        inline const TM::Matrix4 GetModelMatrixRot(void) const
        {
            TM::Matrix4 mat = _modelToWorldCache;
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

        inline const TM::Point2& GetPosition(void) const
        {
            return _position;
        }

        inline void SetPosition(const TM::Point2& pos)
        {
            _position = pos;
            _boundingBox.SetCenter(_position);
        }

        inline void SetPosition(F32 xVal, F32 yVal)
        {
            _position.x = xVal;
            _position.y = yVal;
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

        inline void AddPosition(const TM::Point2& newPosition)
        {
            _position += newPosition;
        }

        inline void AddPosition(const TM::Vector2& newPosition)
        {
            _position += newPosition;
        }
        
        inline const TM::Vector2& GetScale(void) const
        {
            return _scale;
        }

        inline void SetScale(const TM::Vector2& scale)
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
            _scale.x = xVal;
            _scale.y = yVal;
            _boundingBox.SetHalfDimensions(_scale);
        }

        inline const real GetOrientation(void) const
        {
            return _orientation;
        }

        inline void SetOrientation(real angle)
        {
            _orientation = angle;
            _ClampOrientation();
        }

        inline void AddOrientation(real angle)
        {
            _orientation += angle;
            _ClampOrientation();
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

        inline bool OverlapCheck(const shared_ptr<GameObject2D> other)
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
            _shader->SetUniform("has_texture", true);
        }

        inline p_Texture GetTexture(void) const
        {
            return _texture;
        }

        inline void BindTexture(bool state=true)
        {
            _texture->Bind(state);
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

        p_Shader				_shader;				
        p_Mesh					_mesh;					
        TC::AABB				_boundingBox;			

    private:
        void _CalculateCachedData(void);

        inline void _ClampOrientation(void)
        {
            if(_orientation > 360.0f)
            {
                _orientation -= 360.0f;
            }
            else if(_orientation < -360.0f)
            {
                _orientation += 360.0f;
            }
        }

        static U32 _nextID;				
        TM::Matrix4	_modelToWorldCache;		
        TM::Point2 _position;				
        TM::Vector2	_scale;					
        real _orientation;			
        Color _color;					
        p_Texture _texture;				
        bool _activeUpdate;			
        bool _activeRender;			
        U32	_ID;					
    };//End class
    typedef shared_ptr<GameObject2D> p_GameObject2D;
}