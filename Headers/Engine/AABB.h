#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/Point3.h>
#include <Engine/Vector3.h>

namespace TM = TempestMath;

namespace TempestCollisions
{
    class AABB
    {
    public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
        TEMPEST_API AABB(void);

        TEMPEST_API AABB(const TM::Point3& center, F32 w, F32 h, F32 d);
        
        TEMPEST_API ~AABB(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
        TEMPEST_API bool TestCollision(const AABB& other) const;
        
        TEMPEST_API bool TestCollision(const TM::Point3& other) const;

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
        inline void SetCenter(const TM::Point2& c)
        {
            _center = c;
        }

        inline void SetCenter(const TM::Point3& c)
        {
            _center = c;
        }

        inline void SetCenter(F32 x, F32 y, F32 z)
        {
            _center.x = x;
            _center.y = y;
            _center.z = z;
        }

        inline const TM::Point3& GetCenter(void) const
        {
            return _center;
        }

        inline void SetHalfWidth(F32 w)
        {
            _halfScale.x = w;
        }

        inline void SetWidth(F32 w)
        {
            _halfScale.x = w / 2.0f;
        }

        inline F32 GetHalfWidth(void) const
        {
            return _halfScale.x;
        }

        inline F32 GetWidth(void) const
        {
            return _halfScale.x * 2.0f;
        }

        inline void SetHalfHeight(F32 h)
        {
            _halfScale.y = h;
        }

        inline void SetHeight(F32 h)
        {
            _halfScale.y = h / 2.0f;
        }

        inline F32 GetHalfHeight(void) const
        {
            return _halfScale.y;
        }

        inline F32 GetHeight(void) const
        {
            return _halfScale.y * 2.0f;
        }

        inline void SetHalfDepth(F32 d)
        {
            _halfScale.z = d;
        }

        inline void SetDepth(F32 d)
        {
            _halfScale.z = d / 2.0f;
        }

        inline F32 GetHalfDepth(void) const
        {
            return _halfScale.z;
        }

        inline F32 GetDepth(void) const
        {
            return _halfScale.z * 2.0f;
        }

        inline void SetHalfDimensions(F32 w, F32 h, F32 d)
        {
            _halfScale.x = w;
            _halfScale.y = h;
            _halfScale.z = d;
        }

        inline void SetHalfDimensions(const TM::Vector2& scale)
        {
            _halfScale.x = scale.x;
            _halfScale.y = scale.y;
            _halfScale.z = 0.0f;
        }

        inline void SetHalfDimensions(const TM::Vector3& scale)
        {
            _halfScale = scale;
        }

        inline void SetDimensions(F32 w, F32 h, F32 d)
        {
            _halfScale.x = w / 2.0f;
            _halfScale.y = h / 2.0f;
            _halfScale.z = d / 2.0f;
        }

        inline void SetDimensions(const TM::Vector3& scale)
        {
            _halfScale = scale / 2.0f;
        }

    private:
        TM::Point3   _center;		
        TM::Vector3 _halfScale;		
        
    };//end Class
    typedef shared_ptr<AABB> p_AABB;
}//end Namespace
