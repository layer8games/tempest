#include "stdafx.h"
#include "Engine/AABB.h"
using namespace TempestCollisions;

AABB::AABB(void)
:
_center(0.0f, 0.0f, 0.0f),
_halfScale(0.0f, 0.0f, 0.0f)
{  }

AABB::AABB(const TM::Point3& center, F32 w, F32 h, F32 d)
:
_center(center),
_halfScale(w / 2.0f, h / 2.0f, d / 2.0f)
{  }

AABB::~AABB(void)
{  }

bool AABB::TestCollision(const AABB& other) const
{
    if(real_abs(_center.GetX() - other.GetCenter().GetX()) > (_halfScale.GetX() + other.GetHalfWidth()))
    {
        return false;
    }

    if(real_abs(_center.GetY() - other.GetCenter().GetY()) > (_halfScale.GetY() + other.GetHalfHeight()))
    {
        return false;
    }

    if(real_abs(_center.GetZ() - other.GetCenter().GetZ()) > (_halfScale.GetZ() + other.GetHalfDepth()))
    {
        return false;
    }

    return true;
}

bool AABB::TestCollision(const TM::Point3& other) const
{
    if(real_abs(_center.GetX() - other.GetX()) > _halfScale.GetX())
    {
        return false;	
    }

    if(real_abs(_center.GetY() - other.GetY()) > _halfScale.GetY())
    {
        return false;
    }

    if(real_abs(_center.GetZ() - other.GetZ()) > _halfScale.GetZ())
    {
        return false;
    }
    
    return true;
}

void AABB::SetCenter(const TM::Point2& c)
{
    _center = c;
}

void AABB::SetCenter(const TM::Point3& c)
{
    _center = c;
}

void AABB::SetCenter(F32 x, F32 y, F32 z)
{
    _center.Set(x, y, z);
}

const TM::Point3& AABB::GetCenter(void) const
{
    return _center;
}

void AABB::SetHalfWidth(F32 width)
{
    _halfScale.SetX(width);
}

void AABB::SetWidth(F32 width)
{
    _halfScale.SetX(width / 2.0f);
}

F32 AABB::GetHalfWidth(void) const
{
    return _halfScale.GetX();
}

F32 AABB::GetWidth(void) const
{
    return _halfScale.GetX() * 2.0f;
}

void AABB::SetHalfHeight(F32 height)
{
    _halfScale.SetY(height);;
}

void AABB::SetHeight(F32 height)
{
    _halfScale.SetY(height / 2.0f);
}

F32 AABB::GetHalfHeight(void) const
{
    return _halfScale.GetY();
}

F32 AABB::GetHeight(void) const
{
    return _halfScale.GetY() * 2.0f;
}

void AABB::SetHalfDepth(F32 depth)
{
    _halfScale.SetZ(depth);
}

void AABB::SetDepth(F32 depth)
{
    _halfScale.SetZ(depth / 2.0f);
}

F32 AABB::GetHalfDepth(void) const
{
    return _halfScale.GetZ();
}

F32 AABB::GetDepth(void) const
{
    return _halfScale.GetZ() * 2.0f;
}

void AABB::SetHalfDimensions(F32 width, F32 height, F32 depth)
{
    _halfScale.Set(width, height, depth);
}

void AABB::SetHalfDimensions(const TM::Vector2& scale)
{
    _halfScale = scale;
}

void AABB::SetHalfDimensions(const TM::Vector3& scale)
{
    _halfScale = scale;
}

void AABB::SetDimensions(F32 width, F32 height, F32 depth)
{
    _halfScale.Set(width / 2.0f, height / 2.0f, depth / 2.0f);
}

void AABB::SetDimensions(const TM::Vector3& scale)
{
    _halfScale = scale / 2.0f;
}