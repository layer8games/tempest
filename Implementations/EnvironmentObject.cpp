#include <Engine/EnvironmentObject.h>

namespace KillerEngine
{
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
	EnvironmentObject::EnvironmentObject(void)
	{
		GameObject2D::SetSprite(std::shared_ptr<Sprite>(new SqrSprite()));
		GameObject2D::SetID();
	}

	EnvironmentObject::EnvironmentObject(KM::Vector2& pos, F32 w, F32 h)
	{
		GameObject2D::SetSprite(std::shared_ptr<Sprite>(new SqrSprite()));
		GameObject2D::SetID();
		GameObject2D::SetDimensions(w, h);
		GameObject2D::SetPosition(pos);
	}

	EnvironmentObject::EnvironmentObject(KM::Vector2& pos, U32 textureID, F32 w, F32 h)
	{
		GameObject2D::SetSprite(std::shared_ptr<Sprite>(new SqrSprite()));
		GameObject2D::SetID();
		GameObject2D::SetDimensions(w, h);
		GameObject2D::SetPosition(pos);
		GameObject2D::SetTexture(textureID, 0.0f, 1.0f, 0.0f, 1.0f);
	}
}//end namespace