#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/GameObject2D.h>
#include <Engine/Point2.h>

namespace TM = TempestMath;

namespace Tempest
{
    class Factory
    {
    public:
        TEMPEST_API Factory(void);

        TEMPEST_API virtual ~Factory(void);

        TEMPEST_API virtual p_GameObject2D v_Create(string type, const TM::Point2& pos, F32 scale, F32 pixelSize, U32 textureID)=0;

    private:

    };//end Class
    typedef shared_ptr<Factory> p_Factory;
}
