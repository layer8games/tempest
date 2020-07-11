#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/GameObject2D.h>
#include <Engine/StaticGameObject2D.h>
#include <Engine/TextureManager.h>
#include <Engine/Point2.h>

namespace TM = TempestMath;

namespace Tempest
{
    class Factory
    {
    public:
        TEMPEST_API Factory(void);

        TEMPEST_API virtual ~Factory(void);

        TEMPEST_API virtual p_GameObject2D v_Create2D(string type, const TM::Point2& pos, F32 scale, F32 pixelSize, U32 textureID) { return nullptr; };

        TEMPEST_API virtual p_GameObject3D v_Create3D(string type, const TM::Point3& pos, F32 scale, F32 pixelSize, U32 textureID) { return nullptr; };

        TEMPEST_API p_StaticGameObject2D CreateStaticObject(const TM::Point2& pos, F32 scale, F32 pixelSize, U32 textureID);

    private:

    };//end Class
    typedef shared_ptr<Factory> p_Factory;
}
