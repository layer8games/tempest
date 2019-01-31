/*========================================================================
This class will hold all the data for a string of text that will be drawn
to the screen. It will use the font class and the texture manager to keep
track of all the character data and the texture for the font. 

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
/*!
	This class will hold all the data for a string of text that will be drawn
	to the screen. It will use the font class and the texture manager to keep
	track of all the character data and the texture for the font. 

	There are a lot of things that can be done to optimize this class and these ideas. It probably needs a second pass
	very badly. For example, AddText() creates as many Glyph characters as there are characters in the string that is 
	passed in. This means that there is no shared re-use of the Glyph. This is because each one needs a unique position.
	There could be some clever wasy to get around this using instancing, but this will require more work, and I wanted
	to just get the class working. 
*/
	class Text
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
/*!
	Default constructor. Sets scale and color to 1.0f, everything else to 0 or null.
*/
		Text(void);

/*!
	Default destructor. No function.
*/
		~Text(void);

//==========================================================================================================================
//
//Text Functions
//
//==========================================================================================================================		
/*!
	Updates the position of each Glyph in the Text.
	\param pos is the new position that will be used to start the update of each Glyph.
*/
		inline void SetPosition(const KM::Vector& pos)
		{
			_pos = pos;
			_UpdatePositions();
		}

/*! 
	 Updates the position of each Glyph in the Text.
	 \param x sets the first coordinate.
	 \param y sets the second coordinate.
*/
		void SetPosition(F32 x, F32 y)
		{
			_pos[0] = x;
			_pos[1] = y;
			_UpdatePositions();
		}

/*! 
	This does not so much add additional text to the Text as set's what string of Glpyhs will be set. This does incure the 
	cost of creating all of the Glyph characters in the Text. This creates a unique Glyph for each character in the Text. 
	\param text is the string that will be turned into Glyphs.  
*/
		void AddText(string text);

/*! 
	Sets the color of each Glyph in the Text.
	\param col is the Color each Glyph is set to.  
*/
		void SetTextColor(const Color& col);

/*! 
	A wrapper function that calls GameObject::SetUniform on each Glyph using the input. 
	\param name is the name of the uniform that will be set. 
	\param matrix is the transformation matrix to be used by each Glyph. 
*/
		void SetUniforms(string name, const KM::Matrix& matrix);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
/*! 
	Sets each Glyph to active state. 
*/
		inline void SetActive(void)
		{
			_active = true;
			_UpdateActive();
		}

/*! 
	Sets each Glyph to not active state. 
*/
		inline void SetInactive(void)
		{
			_active = false;
			_UpdateActive();
		}

/*! 
	Returns the active state of the Text, and by inference, each Glyph.
*/
		inline bool GetActive(void) const
		{
			return _active;
		}

/*! 
	Returns the total width of all the Glyphs including the xAdvance values. This means that this width represents how much
	screen space the Text is going to take up on the x axis. 
*/
		inline F32 GetWidth(void)
		{
			return _totalWidth;
		}

/*! 
	Sets the font for the Text and all of the Glyphs, if there are any. 
	\param font is the new Font that will be saved in this Text.
*/
		inline void SetFont(shared_ptr<Font> font)
		{
			_font = font;

			//Update Glyphs if there is already text
			if(_text.size() > 0)
			{
				AddText(_text);
			}
		}

/*! 
	Sets the font for the Text and all of the Glyphs, if there are any. 
	\param font is the new Font that will be saved in this Text.	 
*/
		inline void SetFont(Font& font) 
		{ 
			_font = shared_ptr<Font>(&font); 

			//Update Glyphs, if there are any
			if(_text.size() > 0)
			{
				AddText(_text);
			}
		}

/*! 
	Returns the font Text is using. 
*/
		inline const shared_ptr<Font> GetFont(void)
		{
			return _font;
		}

/*! 
	Returns all the Glyphs in the Text. Used for copying. 
*/
		std::vector<shared_ptr<Glyph>> GetCharacterList(void) const
		{
			return _characterList;
		}

/*! 
	Sets the scale of the Text and updates any Glyphs. Calls GameObject::SetScale()
	\param s is the Vector used as the scale.
*/
		inline void SetScale(const KM::Vector& s)
		{
			_scale = s;
			_UpdateScales();
		}

/*! 
	Returns the current scale of the Text. 
*/
		inline const KM::Vector& GetScale(void)
		{
			return _scale;
		}

/*! 
	 Sets the Color for the Text and each Glyph that has been added. 
	 \param c is the Color that will be used. 
*/
		inline void SetColor(const Color& c)
		{
			_color = c;
			_UpdateColors();
		}

/*! 
	 Sets the Color for the Text and each Glyph that has been added. 
	 \param r is the Red value that will be used. 
	 \param g is the Green value that will be used.
	 \param b is the Blue value that will be used. 
*/
		inline void SetColor(F32 r, F32 g, F32 b)
		{
			_color[0] = r;
			_color[1] = g;
			_color[2] = b;

			_UpdateColors();
		}

/*! 
	Returns the current Color of the Text. 
*/
		inline const Color& GetColor(void)
		{
			return _color;
		}

	private:
//==========================================================================================================================
//
//Private Functions
//
//==========================================================================================================================
/*! 
	Iterates over each Glyph calling GameObject::SetPosition() for each Glyph, updating the position, including the xAdvnace. 
*/
		void _UpdatePositions(void);

/*! 
	Iterates over each Glyph calling GameObject::SetActive() for each, using _active.
*/
		void _UpdateActive(void);

/*! 
	Iterates over each Glyph calling GameObject::SetScale() for each, using _scale.
*/
		void _UpdateScales(void);

/*! 
	Iterates over each Glyph calling GameObject::SetColor() for each, using _color. 
*/
		void _UpdateColors(void);

//==========================================================================================================================
//
//Data
//
//==========================================================================================================================
		bool 							_active;			///< Active state of Text and each Glyph.
		F32 							_totalWidth;		///< Total space the Text will take up on screen.
		KM::Vector 						_pos;				///< Position of the first Glyph in the Text.
		string 	   						_text;				///< The string used to generate each Glyph.
		shared_ptr<Font>				_font;				///< The Font used to generate each Glyph.
		std::vector<shared_ptr<Glyph>>	_characterList;		///< List of all generated Glyphs
		KM::Vector 						_scale;				///< The scaling factor used for each Glyph.
		Color 							_color;				///< The Color used for each Glyph.
	};
}