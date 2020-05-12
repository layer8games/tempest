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
#include <Engine/Level.h>

namespace TM = TempestMath;
namespace TC = TempestCollisions;

namespace Tempest
{
    class Level;

    class GameObject2D
    {
    public:
        TEMPEST_API GameObject2D(void);

        TEMPEST_API virtual ~GameObject2D(void);

        TEMPEST_API void Init(void);
        
        virtual void v_Update(void)=0;

        TEMPEST_API virtual void v_Render(void);
        
        TEMPEST_API virtual void v_Awake(void);
       
        void v_OnEvent(Event event)
        {  }
       
        TEMPEST_API void UpdateInternals(void);
        
        TEMPEST_API const TM::Matrix4& GetModelMatrix(void) const;

        TEMPEST_API const TM::Matrix4 GetModelMatrixRot(void) const;
        
        TEMPEST_API const bool GetActive(void) const;
        
        TEMPEST_API void SetActive(bool state);
        
        TEMPEST_API void SetActive(void);
        
        TEMPEST_API void SetInactive(void);
        
        TEMPEST_API const bool GetActiveUpdate(void) const;
        
        TEMPEST_API void SetActiveUpdate(bool state);
        
        TEMPEST_API void SetActiveUpdate(void);
        
        TEMPEST_API void SetInactiveUpdate(void);

        TEMPEST_API const bool GetActiveRender(void) const;

        TEMPEST_API void SetActiveRender(bool state);

        TEMPEST_API void SetActiveRender(void);

        TEMPEST_API void SetInactiveRender(void);

        TEMPEST_API U32 GetID(void) const;

        TEMPEST_API void SetName(string name);

        TEMPEST_API string GetName(void) const;

        TEMPEST_API const TM::Point2& GetPosition(void) const;

        TEMPEST_API void SetPosition(const TM::Point2& pos);

        TEMPEST_API void SetPosition(F32 xVal, F32 yVal);

        TEMPEST_API void SetPositionX(F32 xval);

        TEMPEST_API void SetPositionY(F32 yVal);

        TEMPEST_API void AddPosition(const TM::Point2& newPosition);

        TEMPEST_API void AddPosition(const TM::Vector2& newPosition);
        
        TEMPEST_API void SetDefaultPixelSize(F32 scale);
        
        TEMPEST_API const TM::Vector2& GetScaleInPixels(void) const;

        TEMPEST_API F32 GetScale(void) const;

        TEMPEST_API void SetScaleInPixels(const TM::Vector2& scale);

        TEMPEST_API void SetScaleInPixels(F32 xVal, F32 yVal);

        TEMPEST_API void SetScale(F32 val);

        TEMPEST_API real GetOrientation(void) const;

        TEMPEST_API void SetOrientation(real angle);

        TEMPEST_API void AddOrientation(real angle);

        TEMPEST_API void SetColor(const Color& col);

        TEMPEST_API void SetColor(F32 red, F32 green, F32 blue);

        TEMPEST_API const Color& GetColor(void) const;

        TEMPEST_API bool OverlapCheck(const shared_ptr<GameObject2D> other);

        TEMPEST_API const TC::AABB& GetBounding(void) const;

        TEMPEST_API void SetTexture(p_Texture texture);

        TEMPEST_API void SetLevel(Level* level);

        TEMPEST_API p_Texture GetTexture(void) const;

        TEMPEST_API void BindTexture(bool state=true);

        TEMPEST_API const p_Shader GetShader(void) const;

        TEMPEST_API void SetShader(const p_Shader shader);

        TEMPEST_API void SetMesh(p_Mesh mesh);

    protected:
        TEMPEST_API void DefaultAwake(void);

        TEMPEST_API void DefaultRender(void);

        TEMPEST_API void DefaultUpdate(void);

        string _name;
        p_Shader _shader;				
        p_Mesh _mesh;					
        Level* _level;
        TM::Point2 _position;				
        TC::AABB _boundingBox;			

    private:
        void _CalculateCachedData(void);

        void _ClampOrientation(void);

        static U32 _nextID;
        F32 _defaultPixelSize;
        F32 _scale;
        TM::Matrix4	_modelToWorldCache;		
        TM::Vector2	_scaleInPixels;					
        real _orientation;			
        Color _color;					
        p_Texture _texture;				
        bool _activeUpdate;			
        bool _activeRender;			
        U32	_ID;					
    };//End class
    typedef shared_ptr<GameObject2D> p_GameObject2D;
}