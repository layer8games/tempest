#include "stdafx.h"
#include <Engine/CameraController.h>

using namespace Tempest;

p_CameraController CameraController::_instance = nullptr;
CameraController::CameraController(void)
    :
    _camera(nullptr)
{  }

CameraController::~CameraController(void)
{
    if(_camera != nullptr)
    {
        //delete _camera;
    }
}

p_CameraController CameraController::Instance(void)
{
    if(_instance == nullptr)
    {
        _instance = shared_ptr<CameraController>(new CameraController());
    }
    return _instance;
}

void CameraController::UpdateCamera(void)
{
   _CheckCamera();
   _camera->v_Update();
}

const TM::Matrix4& CameraController::GetProjectionMatrix(void)
{
    _CheckCamera();
    return _camera->GetProjectionMatrix();
}

const TM::Matrix4& CameraController::GetViewMatrix(void)
{
    _CheckCamera();
    return _camera->GetViewMatrix();
}

void CameraController::SetCamera(Camera* camera)
{
    _camera = camera;
}

void CameraController::SetOrthographicCamera(void)
{
    Camera* camera = new Camera();
    camera->SetOrthographic();

    _camera = camera;
}

void CameraController::_CheckCamera(void)
{
    if(_camera == nullptr)
    {
        ErrorManager::Instance()->ThrowError(ENGINE, "CameraController::GetProjectionMatrix Camera not set!");
    }
}