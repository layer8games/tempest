#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/Vector4.h>

namespace TM = TempestMath;

namespace TempestPhysics
{
    class Contact
    {
    public:
        TEMPEST_API Contact(void);

        TEMPEST_API ~Contact(void);

    private:
        TM::Vector4 _contactPoint;
        TM::Vector4 _collissionNormal;
        real _penetrationDepth;
        real _collissionRestitution;
        real _friction;  
    };//end Class
    typedef shared_ptr<Contact> p_Contact;
}//end Namespace
