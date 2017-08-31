#include <Engine/GameObject2D.h>

namespace KillerEngine 
{
	U32 GameObject2D::_nextID = 1;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
	GameObject2D::GameObject2D(void) : _ID(0), _active(true), _sprite(NULL), _position(0), _velocity(0), _acceleration(0)
	{
		SetID();
	}

	GameObject2D::~GameObject2D(void)
	{  }

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
//===== Dimensions =====	
	const F32 GameObject2D::GetWidth(void)
	{
		if(!_sprite)
		{
			ErrorManager::Instance()->SetError(EC_GameObject, "GameObject2D::GetWidth => Sprite not set when call to sprite was made.");
			return NULL;
		}

		return _sprite->GetWidth();
	}

	void GameObject2D::SetWidth(F32 w)
	{
		if(!_sprite)
		{
			ErrorManager::Instance()->SetError(EC_GameObject, "GameObject2D::SetWidth => Sprite not set when call to sprite was made.");
			return;
		}

		return _sprite->SetWidth(w);
	}

	const F32 GameObject2D::GetHeight(void)
	{
		if(!_sprite)
		{
			ErrorManager::Instance()->SetError(EC_GameObject, "GameObject2D::GetHeight => Sprite not set when call to sprite was made.");
			return NULL;
		}

		return _sprite->GetHeight();
	}

	void GameObject2D::SetHeight(F32 h)
	{
		if(!_sprite)
		{
			ErrorManager::Instance()->SetError(EC_GameObject, "GameObject2D::SetHeight => Sprite not set when call to sprite was made.");
			return;
		}

		return _sprite->SetHeight(h);
	}

	void GameObject2D::SetDimensions(F32 w, F32 h)
	{
		if(!_sprite)
		{
			ErrorManager::Instance()->SetError(EC_GameObject, "GameObject2D::SetDimensions => Sprite not set when call to sprite was made.");
			return;
		}

		return _sprite->SetDimensions(w, h);
	}

//===== Color =====
	const Color& GameObject2D::GetColor(void)
	{
		if(!_sprite)
		{
			ErrorManager::Instance()->SetError(EC_GameObject, "GameObject2D::GetColor => Sprite not set when call to sprite was made.");
			return _sprite->GetColor();
		}

		return _sprite->GetColor();
	}

	void GameObject2D::SetColor(Color& col)
	{
		if(!_sprite)
		{
			ErrorManager::Instance()->SetError(EC_GameObject, "GameObject2D::SetColor => Sprite not set when call to sprite was made.");
			return;
		}

		_sprite->SetColor(col);
	}

	void GameObject2D::SetColor(F32 red, F32 blue, F32 green)
	{
		if(!_sprite)
		{
			ErrorManager::Instance()->SetError(EC_GameObject, "GameObject2D::SetColor => Sprite not set when call to sprite was made.");
			return;
		}

		_sprite->SetColor(Color(red, blue, green));
	}

//===== Texture =====
	const U32 GameObject2D::GetTextureID(void)
	{
		if(!_sprite)
		{
			ErrorManager::Instance()->SetError(EC_GameObject, "GameObject2D::GetTextureID => Sprite not set when call to sprite was made.");
			return NULL;
		}

		return _sprite->GetTextureID();
	}

	void GameObject2D::SetTexture(U32 id, const F32 top, const F32 bottom, const F32 right, const F32 left)
	{
		if(!_sprite)
		{
			ErrorManager::Instance()->SetError(EC_GameObject, "GameObject2D::SetTexture => Sprite not set when call to sprite was made.");
			return;
		}

		_sprite->SetTexture(id, top, bottom, right, left);
	}

	void GameObject2D::SetTexture(U32 id)
	{
		if(!_sprite)
		{
			ErrorManager::Instance()->SetError(EC_GameObject, "GameObject2D::SetTexture => Sprite not set when call to sprite was made.");
			return;
		}

		_sprite->SetTexture(id, 0.0f, 1.0f, 0.0f, 1.0f);
	}
//===== Sprite =====
	const std::shared_ptr<Sprite> GameObject2D::GetSprite(void)
	{
		if(!_sprite)
		{
			ErrorManager::Instance()->SetError(EC_GameObject, "GameObject2D::GetSprite => Sprite not set when call to sprite was made.");
			return NULL;
		}

		return _sprite;
	}

	void GameObject2D::RenderSprite(void)
	{
		if(!_sprite)
		{
			ErrorManager::Instance()->SetError(EC_GameObject, "GameObject2D::RenderSprite => Sprite not set when call to sprite was made.");
			return;
		}

		_sprite->v_RenderSprite();
	}
}