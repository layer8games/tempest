#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/Steering2D.h>

namespace Tempest
{
    class KinematicSeek : public Steering2D
    {
    public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
        TEMPEST_API KinematicSeek(void);

        TEMPEST_API ~KinematicSeek(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
        TEMPEST_API SteeringOutput2D v_GetSteering(void) final;

    private:
        real _maxSpeed;


    };//end Class
    typedef shared_ptr<KinematicSeek> p_KinematicSeek;
}
