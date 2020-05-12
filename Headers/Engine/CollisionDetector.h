#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/GameObject2D.h>
#include <Engine/GameObjectManager.h>

namespace TE = Tempest;


namespace TempestCollisions
{
    class CollisionDetector
    {
    protected:
        TEMPEST_API CollisionDetector(void);
    public:
        TEMPEST_API ~CollisionDetector(void);

        TEMPEST_API static shared_ptr<CollisionDetector> Instance(void);

        TEMPEST_API void CheckVsDynamic(TE::p_GameObject2D& object);

    private:
        static shared_ptr<CollisionDetector> _instance;

    };//end Class
    typedef shared_ptr<CollisionDetector> p_CollisionDetector;
}
