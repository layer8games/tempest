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
_width(0), 
_height(0), 
_center(0.0f),
_scale(1.0f, 1.0f)
{  }

RenderedText::RenderedText(const Font& font) 
: 
_pos(0.0f),
_text(), 
_font(font), 
_characterList(), 
_width(0), 
_height(0), 
_center(0.0f),
_scale(1.0f, 1.0f)
{  }

RenderedText::RenderedText(const Font& font, string text) 
:
_pos(0.0f), 
_text(text), 
_font(font), 
_characterList(), 
_width(0), 
_height(0), 
_center(0.0f),
_scale(1.0f, 1.0f)
{
	AddText(_text);
}

RenderedText::RenderedText(const Font& font, string text, const KM::Vector& pos)
:
_pos(pos),
_text(text), 
_font(font), 
_characterList(), 
_width(0), 
_height(0), 
_center(0.0f),
_scale(1.0f, 1.0f)
{
	AddText(_text);
}

RenderedText::~RenderedText(void)
{  }

//==========================================================================================================================
//
//RenderedText Functions
//
//==========================================================================================================================
void RenderedText::AddText(string text)
{
/*
	_characterList.clear();

	_text = text;

	F32 currentX = _pos.GetX();
	F32 currentY = _pos.GetY();


	for(char& c : text)
	{
		shared_ptr<RenderedCharacter> character{new RenderedCharacter()};

		shared_ptr<Sprite> sprite = _font.CreateCharacter(c);

		CharacterData data = sprite->GetCharData();

		character->SetPosition(KM::Vector(currentX, currentY));

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



		F32 totalCharWidth = data.width * _widthScaleFactor;
		F32 totalCharHeight = data.height * _heightScaleFactor;

		character->SetDimensions(totalCharWidth, totalCharHeight);

		_width += totalCharWidth;
		
		if(_height <= totalCharHeight)
		{
			_height = totalCharHeight;
		}

		character->SetSprite(sprite);

		_characterList.push_back(character);
	}

	_center = KM::Vector(_width / 2.0f, _height / 2.0f);
*/
}//End AddText

void RenderedText::SetPosition(const KM::Vector& pos)
{
/*
	_pos = pos;;

	F32 currentX = _pos.GetX();
	F32 currentY = _pos.GetY();

	for(shared_ptr<RenderedCharacter> character : _characterList)
	{
		CharacterData data = character->GetSprite().GetCharData();

		character->SetPosition(KM::Vector( currentX + static_cast<F32>(data.xoffset), currentY - static_cast<F32>(data.yoffset) ));

		currentX += static_cast<F32>(data.xadvance);// + static_cast<F32>(data.xoffset);
	}
*/	
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