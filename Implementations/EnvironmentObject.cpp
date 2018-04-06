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

EnvironmentObject::EnvironmentObject(const KM::Vector2& pos, U32 textureID, F32 w, F32 h)
{
	GameObject2D::SetDimensions(w, h);
	GameObject2D::SetPosition(pos);
	GameObject2D::SetTexture(textureID, 0.0f, 1.0f, 0.0f, 1.0f);
}

EnvironmentObject::~EnvironmentObject(void)
{  }

void EnvironmentObject::v_Update(void)
{  }