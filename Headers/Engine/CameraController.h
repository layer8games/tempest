#pragma once
//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/Camera.h>
#include <Engine/Matrix4.h>
#include <Engine/ErrorManager.h>

namespace TM = TempestMath;

#include <map>

namespace Tempest
{
    class CameraController
    {
    public:
        TEMPEST_API ~CameraController(void);

        TEMPEST_API static shared_ptr<CameraController> Instance(void);

        TEMPEST_API void UpdateCamera(void);

        TEMPEST_API const TM::Matrix4& GetProjectionMatrix(void);

        TEMPEST_API const TM::Matrix4& GetViewMatrix(void);

        TEMPEST_API void SetCamera(Camera* camera);

        TEMPEST_API void SetOrthographicCamera(void);

    protected:
        TEMPEST_API CameraController(void);

    private:
        void _CheckCamera(void);

        static shared_ptr<CameraController> _instance;
        Camera* _camera;
    };//end Class
    typedef shared_ptr<CameraController> p_CameraController;
}
