#include <Engine/EnvironmentObject.h>

using namespace KillerEngine;

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
EnvironmentObject::EnvironmentObject(void)
{  }

EnvironmentObject::EnvironmentObject(const KM::Vector2& pos, F32 w, F32 h)
{
	GameObject2D::SetDimensions(w, h);
	GameObject2D::SetPosition(pos);
}

EnvironmentObject::~EnvironmentObject(void)
{  }