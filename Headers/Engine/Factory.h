#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/GameObject2D.h>
#include <Engine/Vector2.h>

namespace TM = TempestMath;

namespace Tempest
{
    class Factory
    {
    public:
        TEMPEST_API Factory(void);

        TEMPEST_API ~Factory(void);

        TEMPEST_API virtual p_GameObject2D Create(string type, const TM::Vector2& pos, U32 textureID)=0;

    private:

    };//end Class
    typedef shared_ptr<Factory> p_Factory;
}
