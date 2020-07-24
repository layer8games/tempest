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
       
        TEMPEST_API virtual ~GameObject3D(void);
        
        TEMPEST_API void Init(string filepath);

        TEMPEST_API void Init(string filepath, U32 shaderID);
        
        virtual void v_Update(void)=0;

        TEMPEST_API virtual void v_Render(void);

        TEMPEST_API virtual void v_Awake(void);

        TEMPEST_API virtual void v_OnEvent(Event event);

        TEMPEST_API virtual void v_OnCollide(U32 otherObjectID);

        TEMPEST_API void UpdateInternals(void);

        TEMPEST_API const TM::Matrix4& GetModelMatrix(void) const;

        TEMPEST_API const TM::Matrix4 GetModelMatrixRot(void) const;
        
        TEMPEST_API const string GetName(void) const;

        TEMPEST_API void SetName(string name);

        TEMPEST_API p_Mesh GetMesh(void) const;

        TEMPEST_API void SetMesh(p_Mesh mesh);

        TEMPEST_API Level* GetLevel(void) const;

        TEMPEST_API void SetLevel(Level* level);

        TEMPEST_API bool GetActiveUpdate(void) const;

        TEMPEST_API void SetActiveUpdate(bool state);

        TEMPEST_API bool GetActiveRender(void) const;

        TEMPEST_API void SetActiveRender(bool state);
    
        TEMPEST_API const TM::Point3& GetPosition(void) const;

        TEMPEST_API void SetPosition(const TM::Point3& pos);

        TEMPEST_API void SetPosition(const TM::Vector3& pos);

        TEMPEST_API void SetPosition(F32 xVal, F32 yVal, F32 zVal);

        TEMPEST_API void AddScaledPosition(const TM::Vector4& pos, F32 scale);

        TEMPEST_API void AddScaledPosition(const TM::Vector3& pos, F32 scale);

        TEMPEST_API void AddScaledPosition(const TM::Point3& point, F32 scale);

        TEMPEST_API void SetPixelScale(const TM::Vector3& size);

        TEMPEST_API const TM::Vector3& GetPixelScale(void) const;
        
        TEMPEST_API const TM::Vector3& GetScale(void) const;

        TEMPEST_API void SetScale(const TM::Vector3& scale);

        TEMPEST_API void SetScale(F32 val);

        TEMPEST_API void SetScale(F32 xVal, F32 yVal, F32 zVal);

        TEMPEST_API const TM::Quaternion& GetOrientation(void) const;

        TEMPEST_API void SetOrientation(const TM::Quaternion& q);

        TEMPEST_API void SetOrientation(const TM::Vector3& vec);

        TEMPEST_API void SetOrientation(real yaw, real pitch, real roll);

        TEMPEST_API void AddOrientation(const TM::Vector3& vec);

        TEMPEST_API void AddOrientation(real yaw, real pitch, real roll);

        TEMPEST_API void NormalizeOrientation(void);

        TEMPEST_API void SetColor(const Color& col);

        TEMPEST_API void SetColor(F32 red, F32 green, F32 blue);

        TEMPEST_API const Color& GetColor(void) const;
        
        TEMPEST_API bool OverlapCheck(const shared_ptr<GameObject3D> other);
        
        TEMPEST_API const TC::AABB& GetBounding(void) const;

        TEMPEST_API void SetTexture(p_Texture texture);

        TEMPEST_API p_Texture GetTexture(void) const;

        TEMPEST_API void BindTexture(bool state=true);

        TEMPEST_API const p_Shader GetShader(void) const;

        TEMPEST_API void SetShader(const p_Shader shader);


    protected:
        TEMPEST_API void DefaultAwake(void);

        TEMPEST_API void DefaultRender(void);

        TEMPEST_API void DefaultUpdate(void);

        string _name;
        p_Shader _shader;
        p_Mesh _mesh;
        Level* _level;
        TC::AABB _boundingBox;

    private:
        void _CalculateCachedData(void);

        bool _activeUpdate;
        bool _activeRender;
        TM::Matrix4	_modelToWorldCache;
        TM::Vector3 _scale;
        TM::Vector3 _pixelScale;
        TM::Point3 _position;
        TM::Quaternion _orientation;
        Color _color;
        p_Texture _texture;
    };//End class
    typedef shared_ptr<GameObject3D> p_GameObject3D;
}