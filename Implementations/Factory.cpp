#include "stdafx.h"
#include <Engine/Factory.h>
using namespace Tempest;

Factory::Factory(void)
{  }

Factory::~Factory(void)
{  }

p_StaticGameObject2D Factory::CreateStaticObject2D(const TM::Point2& pos, F32 scale, F32 pixelSize, U32 textureID)
{
    p_StaticGameObject2D obj = make_shared<StaticGameObject2D>();
    obj->SetPosition(pos);
    obj->SetDefaultPixelSize(pixelSize);
    obj->SetScale(scale);
    
    if(textureID != 0)
    {
        obj->SetTexture(TextureManager::Instance()->GetTexture(textureID));
    }

    return obj;
}

p_StaticGameObject3D Factory::CreateStaticObject3D(string filePath, U32 shaderID, const TM::Point3& pos, const TM::Vector3& scale, const TM::Vector3& pixelSize, U32 textureID)
{
    p_StaticGameObject3D obj = make_shared<StaticGameObject3D>();
    obj->SetPosition(pos);
    obj->SetScale(scale);
    obj->SetPixelScale(pixelSize);
    obj->SetMesh(make_shared<Mesh>());

    if(shaderID != 0)
    {
        obj->SetShader(ShaderManager::Instance()->GetShader(shaderID));
    }
    else
    {
        obj->SetShader(ShaderManager::Instance()->GetShader(DefaultShaderID::MODEL));
    }
    
    if(textureID != 0)
    {
        obj->SetTexture(TextureManager::Instance()->GetTexture(textureID));
    }

    obj->Init(filePath);

    return obj;
}