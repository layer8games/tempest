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
#include <Engine/Color.h>

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
		void Render(void);

		void SetPosition(const KM::Vector& pos);

		void SetPosition(F32 x, F32 y)
		{
			_pos[0] = x;
			_pos[1] = y;
		}

		void AddText(string text);

		void SetTextColor(const Color& col);

		void SetUniforms(string name, const KM::Matrix& matrix);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		inline void SetActive(void)
		{
			_active = true;
		}

		inline void SetInactive(void)
		{
			_active = false;
		}

		inline bool GetActive(void) const
		{
			return _active;
		}

		inline void SetFont(const Font& font) 
		{ 
			_font = font; 
		}

		inline const Font GetFont(void)
		{
			return _font;
		}

		std::vector<Glyph> GetCharacterList(void)
		{
			return _characterList;
		}

		//ToDO:: Scale needs to change each Glyph too
		inline void SetScale(const KM::Vector& s)
		{
			_scale = s;
		}

		inline const KM::Vector& GetScale(void)
		{
			return _scale;
		}

		inline void SetColor(const Color& c)
		{
			_color = c;
		}

		inline void SetColor(F32 r, F32 g, F32 b)
		{
			_color[0] = r;
			_color[1] = g;
			_color[2] = b;
		}

		inline const Color& GetColor(void)
		{
			return _color;
		}

	private:
//==========================================================================================================================
//
//Data
//
//==========================================================================================================================
		bool 							_active;
		KM::Vector 						_pos;
		string 	   						_text;
		Font   	   						_font;
		std::vector<Glyph>		 		_characterList;
		KM::Vector 						_scale;
		Color 							_color;
	};
}