#pragma once

//=====Killer includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/Matrix4.h>
#include <Engine/Vector4.h>
#include <Engine/Point3.h>
#include <Engine/Color.h>
#include <Engine/Timer.h>

#include <vector>

namespace TM = TempestMath;

namespace Tempest
{
    class Camera
    {
    public:
        TEMPEST_API Camera(void);

        TEMPEST_API virtual ~Camera(void);

        inline virtual void v_Rotate(void)
        {  }

        inline virtual void v_Update(void)
        {  }

        inline virtual void v_Move(const TM::Vector4& offset)
        {  }

        inline virtual void v_Move(F32 xVal, F32 yVal)
        {  }

        inline virtual void v_Move(F32 xVal, F32 yVal, F32 zVal)
        {  }
    
        TEMPEST_API void SetOrthographic(F32 left, F32 right, F32 bottom, F32 top, F32 nearPlane, F32 farPlane);
    
        TEMPEST_API void SetPerspective(F32 fov, F32 aspect, F32 nearPlane, F32 farPlane);
    
        TEMPEST_API void SetDefaultMatrix4(void);
    
        inline const virtual TM::Matrix4 GetViewMatrix4(void) const
        {
            return TM::Matrix4::LookAt(_position, _target, _up);
        }
    
        inline const TM::Matrix4& GetProjectionMatrix4(void) const
        {
            return _projection;
        }    
    
        inline void SetPosition(F32 x, F32 y)
        {
            _position.x = x;
            _position.y = y;

            _v_UpdateCameraVectors();
        }

        inline void SetPosition(F32 x, F32 y, F32 z)
        {
            _position.x = x;
            _position.y = y;
            _position.z = z;

            _v_UpdateCameraVectors();
        }

        inline void SetPosition(const TM::Point3& point)
        {
            _position = point;

            _v_UpdateCameraVectors();
        }
    
        inline void ScalePosition(F32 x, F32 y, F32 z, F32 scale)
        {
            _position.AddScaledPoint(TM::Point3(x, y, z), scale);

            _v_UpdateCameraVectors();
        }
    
        inline void ScalePosition(const TM::Point3& point, F32 scale)
        {
            _position.AddScaledPoint(point, scale);

            _v_UpdateCameraVectors();
        }
   
        inline const TM::Point3& GetPosition(void) const
        {
            return _position;
        }

        inline void SetTarget(const TM::Point3& target)
        {
            _target = target;
        }

        inline void SetTarget(F32 xVal, F32 yVal)
        {
            _target.x = xVal;
            _target.y = yVal;
            _target.z = 0.0f;
        }
    
        inline void SetTarget(F32 xVal, F32 yVal, F32 zVal)
        {
            _target.x = xVal;
            _target.y = yVal;
            _target.z = zVal;
        }
    
        inline const TM::Point3& GetTarget(void)
        {
            return _target;
        }

        inline void SetUpVector(F32 val)
        {
            _up.y = val;
        }

        inline void SetUpVector(F32 xVal, F32 yVal, F32 zVal)
        {
            _up.x = xVal;
            _up.y = yVal;
            _up.z = zVal;
        }

        inline void SetUpVector(const TM::Vector4& vec)
        {
            _up	 = vec;
        }
    
        inline const TM::Vector3& GetUpVector(void) const
        {
            return _up;
        }
    
        inline void SetLookVector(F32 val)
        {
            _look = val;
        }

        inline void SetLookVector(F32 xVal, F32 yVal)
        {
            _look.x = xVal;
            _look.y = yVal;
        }
    
        inline void SetLookVector(F32 xVal, F32 yVal, F32 zVal)
        {
            _look.x = xVal;
            _look.y = yVal;
            _look.z = zVal;
        }

        inline void SetLookVector(const TM::Vector4& vec)
        {
            _look = vec;
        }

        inline const TM::Vector3& GetLookVector(void) const
        {
            return _look;
        }

        inline void SetRightVector(F32 val)
        {
            _right = val;
        }

        inline void SetRightVector(F32 xVal, F32 yVal)
        {
            _right.x = xVal;
            _right.y = yVal;
        }
    
        inline void SetRightVector(F32 xVal, F32 yVal, F32 zVal)
        {
            _right.x = xVal;
            _right.y = yVal;
            _right.z = zVal;
        }

        inline void SetRightVector(const TM::Vector4& vec)
        {
            _right = vec;
        }

        inline const TM::Vector3& GetRightVector(void) const
        {
            return _right;
        }

        inline void SetMouseSensitivity(F32 val)
        {
            _mouseSensitivity = val;
        }

        inline F32 GetMouseSensitivity(void)
        {
            return _mouseSensitivity;
        }
    
        inline F32 GetYaw(void) const
        {
            return _yaw;
        }
    
        inline F32 GetPitch(void) const
        {
            return _pitch;
        }

        inline void SetFOV(F32 val)
        {
            _fov = val;
        }

        inline F32 GetFOV(void) const
        {
            return _fov;
        }

    private:
        Color _bgColor;				
        TM::Matrix4 _projection;				
        
    protected:
        inline virtual void _v_UpdateCameraVectors(void)
        {
            DefaultUpdateCameraVectors();
        }

        TEMPEST_API void DefaultUpdateCameraVectors(void);
        
        TM::Point3 _position;				
        TM::Point3 _target;				
        TM::Vector3 _worldUp;			
        TM::Vector3 _up;					
        TM::Vector3 _look;					
        TM::Vector3 _right;					
        TM::Point3 _currentMouseCoords;	
        TM::Point3 _lastMouseCoords;		
        F32 _mouseSensitivity;		
        F32 _yaw;					
        F32 _pitch;					
        F32 _deltaYaw;				
        F32 _deltaPitch;			
        F32 _fov;					
    };//end Camera
    typedef shared_ptr<Camera> p_Camera;
}//end namespace