#include <Engine/AABB.h>
#include <iostream>

using namespace TempestCollisions;
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
AABB::AABB(void)
:
_center(0.0f, 0.0f, 0.0f),
_halfScale(0.0f, 0.0f, 0.0f)
{  }

AABB::AABB(const TM::Point& center, F32 w, F32 h, F32 d)
:
_center(center),
_halfScale(w / 2.0f, h / 2.0f, d / 2.0f)
{  }

AABB::~AABB(void)
{  }

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
bool AABB::TestCollision(const AABB& other) const
{

	if(real_abs(_center[x] - other.GetCenter()[x]) > (_halfScale[x] + other.GetHalfWidth()))
	{
		return false;
	}

	if(real_abs(_center[y] - other.GetCenter()[y]) > (_halfScale[y] + other.GetHalfHeight()))
	{
		return false;
	}

	if(real_abs(_center[z] - other.GetCenter()[z]) > (_halfScale[z] + other.GetHalfDepth()))
	{
		return false;
	}

	return true;
}