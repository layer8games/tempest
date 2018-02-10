/*========================================================================
This class will hold all the data for a string of text that will be drawn
to the screen. It will use the font class and the texture manager to keep
track of all the character data and the texture for the font. 

It is considered a GameObject2D, and when adding it to the work it should
be treated as any other GameObject2D.

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#pragma once

//=====Engine includes=====
#include <Engine/Atom.h>
#include <Engine/GameObject2D.h>
#include <Engine/Font.h>
#include <Engine/Sprite.h>
#include <Engine/Vector2.h>
#include <Engine/RenderedCharacter.h>

namespace KM = KillerMath;

//=====STL includes=====
#include <vector>

namespace KillerEngine
{
	class RenderedText
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		RenderedText(void);

		explicit RenderedText(Font& font);
		
		RenderedText(string text, Font& font);

		//void Render(void);

/* 		original version in case the new version breaks everything
		void v_SetPosition(KM::Vector2 pos)
		{
			GameObject2D::SetPositionNoSprite(pos);
			SetTextPosition(pos);
		}
*/

//==========================================================================================================================
//
//RenderedText Functions
//
//==========================================================================================================================		
		void AddText(string text);

		void SetPosition(KM::Vector2& pos);

		//void SetTextColor(Color& col);

		void SetWidthScaleFactor(F32 w) 
		{ 
			_widthScaleFactor = w; 
		}

		void SetHeightScaleFactor(F32 h) 
		{ 
			_heightScaleFactor = h; 
		}

		void SetScaleFactors(const F32 w, const F32 h) 
		{ 
			_widthScaleFactor = w; 
			_heightScaleFactor = h; 
		}

		void SetFont(Font& font) 
		{ 
			_font = font; 
		}

		F32 GetTotalWidth(void) 
		{ 
			return _totalWidth; 
		}

		F32 GetTotalHeight(void) 
		{ 
			return _totalHeight; 
		}

		KM::Vector2& GetCenter(void) 
		{ 
			return _center; 
		}

		std::vector<std::shared_ptr<RenderedCharacter>> GetCharacterList(void)
		{
			return _characterList;
		}

	private:
		KM::Vector2 _pos;
		string _text;
		Font   _font;
		std::vector<shared_ptr<RenderedCharacter>> _characterList;
		F32 _widthScaleFactor;
		F32 _heightScaleFactor;
		F32 _totalWidth;
		F32 _totalHeight;
		KM::Vector2 _center;	
	};
}