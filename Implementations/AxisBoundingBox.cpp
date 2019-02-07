#include <Engine/AxisBoundingBox.h>

using namespace KillerCollisions;
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
AxisBoundingBox::AxisBoundingBox(void)
:
_center(0.0f, 0.0f, 0.0f, 0.0f),
_halfWidth(0.0f),
_halfHeight(0.0f),
_halfDepth(0.0f)
{  }

AxisBoundingBox::AxisBoundingBox(const KM::Vector& center, F32 w, F32 h, F32 d)
:
_center(center),
_halfWidth(w),
_halfHeight(h),
_halfDepth(d)
{  }

AxisBoundingBox::~AxisBoundingBox(void)
{  }

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
bool AxisBoundingBox::TestCollision(const AxisBoundingBox& other) const
{
	if(real_abs(_center[0] - other.GetCenter()[0]) > _halfWidth + other.GetHalfWidth())
	{
		return false;
	}

	if(real_abs(_center[1] - other.GetCenter()[1] > _halfHeight + other.GetHalfHeight()))
	{
		return false;
	}

	if(real_abs(_center[3] - other.GetCenter()[3] > _halfDepth + other.GetHalfDepth()))
	{
		return false;
	}

	return true;
}