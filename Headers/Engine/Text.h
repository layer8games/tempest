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
#include <Engine/Glyph.h>

namespace KM = KillerMath;

//=====STL includes=====
#include <vector>

namespace KillerEngine
{
	class Text
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		Text(void);

		explicit Text(const Font& font);
		
		Text(const Font& font, string text);

		Text(const Font& font, string text, const KM::Vector& pos);

		~Text(void);

//==========================================================================================================================
//
//Text Functions
//
//==========================================================================================================================		
		void SetPosition(const KM::Vector& pos);

		void AddText(string text);

		//void SetTextColor(const Color& col);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================

		inline void SetFont(const Font& font) 
		{ 
			_font = font; 
		}

		inline const Font GetFont(void)
		{
			return _font;
		}

		std::vector<std::shared_ptr<Glyph>> GetCharacterList(void)
		{
			return _characterList;
		}

		inline void SetWidth(F32 w) 
		{ 
			_width = w; 
		}

		inline F32 GetWidth(void) const
		{ 
			return _width; 
		}

		inline void SetHeight(F32 h) 
		{ 
			_height = h; 
		}

		inline F32 GetHeight(void) const
		{ 
			return _height; 
		}

		inline const KM::Vector& GetCenter(void) const
		{ 
			return _center; 
		}

		inline void SetScale(const KM::Vector& s)
		{
			_scale = s;
		}

		inline const KM::Vector& GetScale(void)
		{
			return _scale;
		}

	private:
		KM::Vector 						_pos;
		string 	   						_text;
		Font   	   						_font;
		std::vector<shared_ptr<Glyph>> 	_characterList;
		F32 							_width;
		F32 							_height;
		KM::Vector 						_center;
		KM::Vector 						_scale;
	};
}