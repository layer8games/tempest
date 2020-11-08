#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include "Engine/Atom.h"
#include "Engine/Camera.h"

namespace Tempest
{
    class Camera2D : public Camera
    {
    public:
        TEMPEST_API Camera2D(void);

        TEMPEST_API ~Camera2D(void) final;

        TEMPEST_API void v_Move(const TM::Vector3& offset) final;
        
        TEMPEST_API void SetMoveSpeed(F32 val);

        TEMPEST_API F32 GetMoveSpeed(void);

    private:
        F32 _moveSpeed;

    };//end Class
    typedef shared_ptr<Camera2D> p_Camera2D;
}
