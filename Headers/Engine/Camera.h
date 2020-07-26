#pragma once

//=====Engin includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/Matrix4.h>
#include <Engine/Vector4.h>
#include <Engine/Point3.h>
#include <Engine/Color.h>
#include <Engine/Timer.h>
#include <Engine/Driver.h>

#include <vector>

namespace TM = TempestMath;

namespace Tempest
{
    class Camera
    {
    public:
        TEMPEST_API Camera(void);

        TEMPEST_API virtual ~Camera(void);

        TEMPEST_API virtual void v_Rotate(void);

        TEMPEST_API virtual void v_Update(void);

        TEMPEST_API virtual void v_Move(const TM::Vector3& offset);
    
        TEMPEST_API void SetOrthographic(void);

        TEMPEST_API void SetOrthographic(F32 left, F32 right, F32 bottom, F32 top, F32 nearPlane, F32 farPlane);
    
        TEMPEST_API void SetPerspective(void);
        
        TEMPEST_API void SetPerspective(F32 fov, F32 aspect, F32 nearPlane, F32 farPlane);
    
        TEMPEST_API const TM::Matrix4& GetViewMatrix(void) const;

        TEMPEST_API const TM::Matrix4& GetProjectionMatrix(void) const;
    
        TEMPEST_API void SetPosition(F32 x, F32 y);

        TEMPEST_API void SetPosition(F32 x, F32 y, F32 z);

        TEMPEST_API void SetPosition(const TM::Point3& point);
    
        TEMPEST_API void ScalePosition(F32 x, F32 y, F32 z, F32 scale);
    
        TEMPEST_API void ScalePosition(const TM::Point3& point, F32 scale);
   
        TEMPEST_API const TM::Point3& GetPosition(void) const;

        TEMPEST_API void SetTargetPosition(const TM::Point3& target);
    
        TEMPEST_API const TM::Point3& GetTarget(void) const;
        
        TEMPEST_API void SetUpDirection(const TM::Vector3& vec);
    
        TEMPEST_API const TM::Vector3& GetUpDirection(void) const;

        TEMPEST_API void SetLookDirection(const TM::Vector3& vec);
        
        TEMPEST_API const TM::Vector3& GetLookDirection(void) const;

        TEMPEST_API void SetRightDirection(const TM::Vector3& vec);

        TEMPEST_API const TM::Vector3& GetRightVector(void) const;

        TEMPEST_API void SetMouseSensitivity(F32 val);

        TEMPEST_API F32 GetMouseSensitivity(void) const;
    
        TEMPEST_API F32 GetYaw(void) const;
    
        TEMPEST_API F32 GetPitch(void) const;

        TEMPEST_API void SetFOV(F32 val);

        TEMPEST_API F32 GetFOV(void) const;

    protected:
        TEMPEST_API virtual void _v_UpdateCameraVectors(void);
        
        TEMPEST_API void _DefaultUpdateCameraVectors(void);

        TEMPEST_API void _UpdateLookMatrix(void);
        
        TM::Matrix4 _projectionMatrix;
        TM::Matrix4 _lookAtMatrix;
        TM::Point3 _position;
        TM::Point3 _target;
        TM::Point3 _currentMouseCoords;
        TM::Point3 _lastMouseCoords;
        TM::Vector3 _worldUp;
        TM::Vector3 _up;
        TM::Vector3 _lookDirection;
        TM::Vector3 _right;
        Color _bgColor;
        F32 _mouseSensitivity;
        F32 _yaw;
        F32 _pitch;
        F32 _deltaYaw;
        F32 _deltaPitch;
        F32 _fov;

    };//end Camera
    typedef shared_ptr<Camera> p_Camera;
}//end namespace