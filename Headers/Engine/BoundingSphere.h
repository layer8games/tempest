#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/Point3.h>

namespace TM = TempestMath;

namespace TempestCollisions
{
    class BoundingSphere
    {

    public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
        TEMPEST_API BoundingSphere(void);

        TEMPEST_API BoundingSphere(const TM::Point3& center, real radius);

        TEMPEST_API BoundingSphere(const BoundingSphere& one, const BoundingSphere& two);

        TEMPEST_API ~BoundingSphere(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
        TEMPEST_API bool TestCollision(const BoundingSphere& other) const;

        TEMPEST_API real GetGrowth(BoundingSphere& other) const;

        inline real GetSize(void) const
        {
            return static_cast<real>(1.333333) * R_PI * _radius * _radius * _radius;
        }

//==========================================================================================================================
//
//Accessors
//
//========================================================================================================================== 
        inline void SetCenter(const TM::Point3& pos)
        {
            _center = pos;
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

        inline void SetRadius(real r)
        {
            _radius = r;
        }

        inline real GetRadius(void) const
        {
            return _radius;
        }

    private:
//==========================================================================================================================
//
//Data
//
//==========================================================================================================================	
        TM::Point3 _center; 	
        real 	  _radius;	

    };//end Class
    typedef shared_ptr<BoundingSphere> p_BoundingSphere;
}//end Namespace
