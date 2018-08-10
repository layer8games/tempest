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
#include <Engine/GameObject.h>
#include <Engine/Font.h>
#include <Engine/Vector.h>
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

		explicit RenderedText(const Font& font);
		
		RenderedText(string text, const Font& font);

		~RenderedText(void);

//==========================================================================================================================
//
//RenderedText Functions
//
//==========================================================================================================================		
		void AddText(string text);

		void SetPosition(const KM::Vector& pos);

		//void SetTextColor(const Color& col);

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

		void SetFont(const Font& font) 
		{ 
			_font = font; 
		}

		F32 GetTotalWidth(void) const
		{ 
			return _totalWidth; 
		}

		F32 GetTotalHeight(void) const
		{ 
			return _totalHeight; 
		}

		const KM::Vector& GetCenter(void) const
		{ 
			return _center; 
		}

		std::vector<std::shared_ptr<RenderedCharacter>> GetCharacterList(void)
		{
			return _characterList;
		}

	private:
		KM::Vector _pos;
		string _text;
		Font   _font;
		std::vector<shared_ptr<RenderedCharacter>> _characterList;
		F32 _widthScaleFactor;
		F32 _heightScaleFactor;
		F32 _totalWidth;
		F32 _totalHeight;
		KM::Vector _center;	
	};
}