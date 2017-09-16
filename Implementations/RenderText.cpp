#include <Engine/RenderText.h>
#include <iostream>

namespace KillerEngine
{
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================	
	RenderText::RenderText(void) : _text(), _font(), _characterList(), _totalWidth(0), _totalHeight(0), _center(0.0f)
	{  }

	RenderText::RenderText(Font& font) : _text(), _font(font), _characterList(), _totalWidth(0), _totalHeight(0), _center(0.0f)
	{  }

	RenderText::RenderText(string text, Font& font) : _text(text), _font(font), _characterList(), _totalWidth(0), _totalHeight(0), _center(0.0f)
	{
		AddText(_text);
	}

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
	void RenderText::v_Render(void)
	{
		for(Character character : _characterList)
		{
			character.sprite.Render(KM::Vector2(character.xpos, character.ypos), character.width, character.height, character.color);
		}
	}

//==========================================================================================================================
//
//RenderText Functions
//
//==========================================================================================================================
	void RenderText::AddText(string text)
	{
		_characterList.clear();

		_text = text;

		F32 currentX = GameObject2D::GetPosition().GetX();
		F32 currentY = GameObject2D::GetPosition().GetY();

		Texture& texture = TextureManager::Instance()->GetTexture(_font.GetTextureID());


		for(char& c : text)
		{
			Character character;

			std::shared_ptr<Sprite> sprite = _font.CreateCharacter(c);

			CharacterData data = sprite->GetCharData();

			F32 xOffset = static_cast<F32>(data.xoffset) / 2.0f;
			F32 yOffset = static_cast<F32>(data.yoffset) / 2.0f;

			character.xpos = currentX + xOffset; 
			character.ypos = currentY - yOffset;

			currentX += static_cast<F32>(data.xadvance * _widthScaleFactor);

			F32 charWidth  	  = static_cast<F32>(data.width);
			F32 charHeight 	  = static_cast<F32>(data.height);
			F32 charX 	 	  = static_cast<F32>(data.x);
			F32 charY 	 	  = static_cast<F32>(data.y);
			F32 textureWidth  = static_cast<F32>(texture.GetWidth());
			F32 textureHeight = static_cast<F32>(texture.GetHeight());

			F32 rightCoord   = (charX / textureWidth);
			F32 topCoord    = charY / textureHeight;
			F32 leftCoord  = rightCoord + charWidth / textureWidth;
			F32 bottomCoord = topCoord + charHeight / textureHeight;

			//std::cout << "Top=" << topCoord << "\nBottom=" << bottomCoord << "\nrRight=" << rightCoord << "\nLeft=" << leftCoord << "\n";

			sprite->SetTexture(texture.GetID(), topCoord, bottomCoord, rightCoord, leftCoord);
			sprite->SetCharData(data);

			F32 totalCharWidth = charWidth * _widthScaleFactor;
			F32 totalCharHeight = charHeight * _heightScaleFactor;

			character.width = totalCharWidth;
			character.height = totalCharHeight;

			_totalWidth += totalCharWidth;
			
			if(_totalHeight <= totalCharHeight)
			{
				_totalHeight = totalCharHeight;
			}

			character.sprite = sprite;

			_characterList.push_back(character);
		}

		_center = KM::Vector2(_totalWidth / 2.0f, _totalHeight / 2.0f);
	}//End AddText

	void RenderText::SetTextPosition(KM::Vector2& pos)
	{
		GameObject2D::SetPosition(pos);

		F32 currentX = GameObject2D::GetPosition().GetX();
		F32 currentY = GameObject2D::GetPosition().GetY();

		for(auto i = _characterList.begin(); i != _characterList.end(); ++i)
		{
			F32 xOffset = static_cast<F32>((*i).sprite.GetCharData().xoffset) / 2.0f;
			F32 yOffset = static_cast<F32>((*i).sprite.GetCharData().yoffset) / 2.0f;

			(*i).xpos = currentX + xOffset;
			(*i).ypos = currentY - yOffset;

			currentX += static_cast<F32>((*i).sprite.GetCharData().xadvance) * _widthScaleFactor;
		}
	}

	void RenderText::SetTextColor(Color& col)
	{
		for(Character character : _characterList)
		{
			character.color = col;
		}
	}

}//End Namespace