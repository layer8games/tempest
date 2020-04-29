#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/Camera.h>
#include <Engine/Vector4.h>
#include <Engine/Controller.h>

namespace TM = TempestMath;

namespace Tempest
{
/// A classic Orbital camera. This is similar to the camera used in a lot of 3rd person games, like World of Warcraft. A 
/// Point in space is set, and the camera will then move around that point in a circle. This includes the ability to get
/// closer to and further from that point. 
/// ToDO: Need to make the Target a param that can be updated.
    class OrbitCamera : public Camera
    {
    public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
/// Sets the initial radius to be 10.0f, the minRadius to be 2.0f and the maxRadius to be 80.0f
        TEMPEST_API OrbitCamera(void);

/// No implementation.
        TEMPEST_API ~OrbitCamera(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================		
/// Uses the updated values of the camera to perform the rotation.
        TEMPEST_API virtual void v_Rotate(void) final;

/// Called once per frame, uses the Base Camera to get the updated mouse coords, updates rotational values to match.
        TEMPEST_API virtual void v_Update(void) final;

        //to test later
        //If you use this, make sure to comment out the Vector4 update 
        //in the implementation
/*
        inline const virtual TM::Matrix4 GetViewMatrix4(void)
        {
            return TM::Matrix4::FPSView(_position, _yaw, _pitch);
        }
*/
/// Uses the base Camera to orbit around the set point.
        TEMPEST_API void Orbit(void);

/// Moves the Camera closer to or further away from the target, based on the value of the radius.
        TEMPEST_API void Zoom(void);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================		
        //ToDO: Make the min and max member vairables
        //that can be changed per instance
/// Updates the radius of the Camera. 
/// \param val is the new radius. It will be clamped to min and max.
        inline void SetRadius(F32 val)
        {
            _radius = REAL_CLAMP(val, _minRadius, _maxRadius);
        }

/// Sets the minimum possible Radius. 
/// \param val is the new min radius.
        inline void SetMinRadius(F32 val)
        {
            _minRadius = val;
        }

/// Return the current min radius. 
        inline F32 GetMinRadius(void)
        {
            return _minRadius;
        }

/// Sets the new maximum radius.
/// \param val is the new max radius. 
        inline void SetMaxRaidus(F32 val)
        {
            _maxRadius = val;
        }

/// Returns the current max radius. 
        inline F32 GetMaxRadius(void)
        {
            return _maxRadius;
        }

    private:
/// Updates the Camera vectors, used in Rotate and Orbit.
        virtual void _v_UpdateCameraVectors(void);
//==========================================================================================================================
//
//Data
//
//==========================================================================================================================		
        F32 _radius;		/// Distance of the view port from the target.
        F32 _minRadius;		/// Min radius.
        F32 _maxRadius;		/// Max radius.

    };//end OrbitCamera
    typedef shared_ptr<OrbitCamera> p_OrbitCamera;
}//end Namespace
