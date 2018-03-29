#include <Engine/RenderedText.h>

using namespace KillerEngine;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================	
RenderedText::RenderedText(void) 
: 
_pos(0.0f),
_text(), 
_font(), 
_characterList(), 

_totalWidth(0), 
_totalHeight(0), 
_center(0.0f)
{  }

RenderedText::RenderedText(Font& font) 
: 
_text(), 
_font(font), 
_characterList(), 
_totalWidth(0), 
_totalHeight(0), 
_center(0.0f)
{  }

RenderedText::RenderedText(string text, Font& font) 
: 
_text(text), 
_font(font), 
_characterList(), 
_totalWidth(0), 
_totalHeight(0), 
_center(0.0f)
{
	AddText(_text);
}

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
/*	void RenderedText::v_Render(void)
{
	for(RenderedCharacter& character : _characterList)
	{
		//character.sprite.Render(KM::Vector2(character.xpos, character.ypos), character.width, character.height, character.color);
	}
}
*/
//==========================================================================================================================
//
//RenderedText Functions
//
//==========================================================================================================================
void RenderedText::AddText(string text)
{
	_characterList.clear();

	_text = text;

	F32 currentX = _pos.GetX();
	F32 currentY = _pos.GetY();


	for(char& c : text)
	{
		shared_ptr<RenderedCharacter> character{new RenderedCharacter()};

		shared_ptr<Sprite> sprite = _font.CreateCharacter(c);

		CharacterData data = sprite->GetCharData();

		character->SetPosition(KM::Vector2(currentX, currentY));

		currentX += static_cast<F32>(data.xadvance);

/*			
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
*/


		F32 totalCharWidth = data.width * _widthScaleFactor;
		F32 totalCharHeight = data.height * _heightScaleFactor;

		character->SetDimensions(totalCharWidth, totalCharHeight);

		_totalWidth += totalCharWidth;
		
		if(_totalHeight <= totalCharHeight)
		{
			_totalHeight = totalCharHeight;
		}

		character->SetSprite(sprite);

		_characterList.push_back(character);
	}

	_center = KM::Vector2(_totalWidth / 2.0f, _totalHeight / 2.0f);
}//End AddText

void RenderedText::SetPosition(KM::Vector2& pos)
{
	_pos = pos;;

	F32 currentX = _pos.GetX();
	F32 currentY = _pos.GetY();

	for(shared_ptr<RenderedCharacter> character : _characterList)
	{
		CharacterData data = character->GetSprite().GetCharData();

		character->SetPosition(KM::Vector2( currentX + static_cast<F32>(data.xoffset), currentY - static_cast<F32>(data.yoffset) ));

		currentX += static_cast<F32>(data.xadvance);// + static_cast<F32>(data.xoffset);
	}
}

/*	Not implemented yet in Sprite	
void RenderedText::SetTextColor(Color& col)
{
	for(RenderedCharacter& character : _characterList)
	{
		character.SetColor(col);
	}
}
*/	