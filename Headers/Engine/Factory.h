#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/GameObject2D.h>
#include <Engine/StaticGameObject2D.h>
#include <Engine/GameObject3D.h>
#include <Engine/StaticGameObject3D.h>
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

        TEMPEST_API virtual p_GameObject2D v_Create2D(string type, const TM::Point2& pos, F32 scale, F32 pixelSize, U32 textureID)=0;

        TEMPEST_API virtual p_GameObject3D v_Create3D(string type, const TM::Point3& pos, F32 scale, F32 pixelSize, U32 textureID)=0;

        TEMPEST_API p_StaticGameObject2D CreateStaticObject2D(const TM::Point2& pos, F32 scale, F32 pixelSize, U32 textureID);

        TEMPEST_API p_StaticGameObject3D CreateStaticObject3D(string filePath, const TM::Point3& pos, const TM::Vector3& scale, const TM::Vector3& pixelSize, U32 textureID);

    private:

    };//end Class
    typedef shared_ptr<Factory> p_Factory;
}
