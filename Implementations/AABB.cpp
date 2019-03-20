#include <Engine/AABB.h>

using namespace KillerCollisions;
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

AABB::AABB(const KM::Point& center, F32 w, F32 h, F32 d)
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
	if(real_abs(_center[0] - other.GetCenter()[0]) > (_halfScale[x] + other.GetHalfWidth()))
	{
		return false;
	}

	if(real_abs(_center[1] - other.GetCenter()[1]) > (_halfScale[y] + other.GetHalfHeight()))
	{
		return false;
	}

	if(real_abs(_center[2] - other.GetCenter()[2]) > (_halfScale[z] + other.GetHalfDepth()))
	{
		return false;
	}

	return true;
}