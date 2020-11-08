#pragma once

#include "stdafx.h"
#include "Engine/Atom.h"
#include "Engine/Vector3.h"

namespace TM = TempestMath;

namespace TempestCollisions
{
    class AABB
    {
    public:
        TEMPEST_API AABB(void);

        TEMPEST_API AABB(const TM::Point3& center, F32 w, F32 h, F32 d);
        
        TEMPEST_API ~AABB(void);

        TEMPEST_API bool TestCollision(const AABB& other) const;
        
        TEMPEST_API bool TestCollision(const TM::Point3& other) const;

        TEMPEST_API void SetCenter(const TM::Point2& c);

        TEMPEST_API void SetCenter(const TM::Point3& c);

        TEMPEST_API void SetCenter(F32 x, F32 y, F32 z);

        TEMPEST_API const TM::Point3& GetCenter(void) const;

        TEMPEST_API void SetHalfWidth(F32 w);

        TEMPEST_API void SetWidth(F32 w);

        TEMPEST_API F32 GetHalfWidth(void) const;

        TEMPEST_API F32 GetWidth(void) const;

        TEMPEST_API void SetHalfHeight(F32 h);

        TEMPEST_API void SetHeight(F32 h);

        TEMPEST_API F32 GetHalfHeight(void) const;

        TEMPEST_API F32 GetHeight(void) const;

        TEMPEST_API void SetHalfDepth(F32 d);

        TEMPEST_API void SetDepth(F32 d);

        TEMPEST_API F32 GetHalfDepth(void) const;

        TEMPEST_API F32 GetDepth(void) const;

        TEMPEST_API void SetHalfDimensions(F32 w, F32 h, F32 d);

        TEMPEST_API void SetHalfDimensions(const TM::Vector2& scale);

        TEMPEST_API void SetHalfDimensions(const TM::Vector3& scale);

        TEMPEST_API void SetDimensions(F32 w, F32 h, F32 d);

        TEMPEST_API void SetDimensions(const TM::Vector3& scale);

    private:
        TM::Point3 _center;
        TM::Vector3 _halfScale;

    };//end Class
    typedef shared_ptr<AABB> p_AABB;
}//end Namespace
