#include "stdafx.h"
#include <Engine/Steering2D.h>
using namespace Tempest;

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Steering2D::Steering2D(void)
{  }

Steering2D::~Steering2D(void)
{  }

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
real Steering2D::GetNewOrientation(real currentOrientation, const TM::Vector2& velocity)
{
    if(velocity.SqrMagnitude() > 0.0f)
    {
        real orienationInRadians = real_atan2(-velocity.GetX(), velocity.GetY());
        return DEGREE(orienationInRadians);
    }
    else
    {
        return currentOrientation;
    }
}
