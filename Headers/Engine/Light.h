#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/Color.h>
#include <Engine/Vector3.h>
#include <Engine/ShaderManager.h>

namespace TM = TempestMath;


namespace Tempest
{
    class Light
    {
    public:
        TEMPEST_API Light(void);

        TEMPEST_API ~Light(void);

        TEMPEST_API void SetAmbientColor(const Color& color);

        TEMPEST_API void SetPosition(const TM::Vector3& pos);

        TEMPEST_API void SetSpecularFactor(F32 factor);

        TEMPEST_API void SetSpecularShine(F32 factor);

    private:
        Color _ambientColor;
        TM::Vector3 _position;
        F32 _specularFactor;
        F32 _specularShine;

    };//end Class
    typedef shared_ptr<Light> p_Light;
}
