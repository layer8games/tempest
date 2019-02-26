#include <Engine/EnvironmentObject.h>

using namespace KillerEngine;

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
EnvironmentObject::EnvironmentObject(void)
{  }

EnvironmentObject::EnvironmentObject(const KM::Vector4& pos, F32 w, F32 h)
{
	GameObject::SetPosition(pos);
}

EnvironmentObject::~EnvironmentObject(void)
{  }