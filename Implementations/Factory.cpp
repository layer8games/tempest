#include "stdafx.h"
#include <Engine/Factory.h>

using namespace Tempest;

Factory::Factory(void)
{  }

Factory::~Factory(void)
{  }

p_StaticGameObject2D Factory::CreateStaticObject(const TM::Point2& pos, F32 scale, F32 pixelSize, U32 textureID)
{
    p_StaticGameObject2D obj = make_shared<StaticGameObject2D>();
    obj->SetPosition(pos);
    obj->SetTexture(TextureManager::Instance()->GetTexture(textureID));
    obj->SetDefaultPixelSize(pixelSize);
    obj->SetScale(scale);

    return obj;
}