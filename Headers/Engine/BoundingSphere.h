#pragma once

#include "stdafx.h"
#include "Engine/Atom.h"
#include "Engine/Vector3.h"

namespace TM = TempestMath;

namespace TempestCollisions
{
    class BoundingSphere
    {

    public:
        TEMPEST_API BoundingSphere(void);

        TEMPEST_API BoundingSphere(const TM::Point3& center, real radius);

        TEMPEST_API BoundingSphere(const BoundingSphere& one, const BoundingSphere& two);

        TEMPEST_API ~BoundingSphere(void);

        TEMPEST_API bool TestCollision(const BoundingSphere& other) const;

        TEMPEST_API real GetGrowth(BoundingSphere& other) const;

        TEMPEST_API real GetSize(void) const;

        TEMPEST_API void SetCenter(const TM::Point3& pos);

        TEMPEST_API void SetCenter(F32 x, F32 y, F32 z);

        TEMPEST_API const TM::Point3& GetCenter(void) const;

        TEMPEST_API void SetRadius(real r);

        TEMPEST_API real GetRadius(void) const;

    private:
        TM::Point3 _center; 
        real _radius;

    };//end Class
    typedef shared_ptr<BoundingSphere> p_BoundingSphere;
}//end Namespace
