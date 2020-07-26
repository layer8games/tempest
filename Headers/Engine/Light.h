#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/Color.h>
#include <Engine/Vector3.h>

namespace TM = TempestMath;


namespace Tempest
{
    class Light
    {
    public:
        Light(void);

        ~Light(void);



    private:
        Color _ambientColor;
        TM::Vector3 _position;
        F32 _specularFactor;
        F32 _specularShine;

    };//end Class
    typedef shared_ptr<Light> p_Light;
}
