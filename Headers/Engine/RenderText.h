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
#ifndef RENDER_TEXT_H
#define RENDER_TEXT_H

//=====Engine includes=====
#include <Engine/Atom.h>
#include <Engine/GameObject2D.h>
#include <Engine/Font.h>
#include <Engine/Sprite.h>
#include <Engine/Vector2.h>
#include <Engine/Color.h>

namespace KM = KillerMath;

//=====STL includes=====
#include <vector>
#include <memory>

namespace KillerEngine
{
	class RenderText : public GameObject2D
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		RenderText(void);

		RenderText(Font& font);
		
		RenderText(string text, Font& font);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
		void v_Update(void) 
		{  }

		void v_Render(void);

/* 		original version in case the new version breaks everything
		void v_SetPosition(KM::Vector2 pos)
		{
			GameObject2D::SetPositionNoSprite(pos);
			SetTextPosition(pos);
		}
*/

//==========================================================================================================================
//
//RenderText Functions
//
//==========================================================================================================================		
		void AddText(string text);

		void SetTextPosition(KM::Vector2& pos);

		void SetTextColor(Color& col);

		void SetWidthScaleFactor(F32 w) { _widthScaleFactor = w; }

		void SetHeightScaleFactor(F32 h) { _heightScaleFactor = h; }

		void SetScaleFactors(const F32 w, const F32 h) { _widthScaleFactor = w; _heightScaleFactor = h; }

		void SetFont(Font& font) { _font = font; }

		F32 GetTotalWidth(void) { return _totalWidth; }

		F32 GetTotalHeight(void) { return _totalHeight; }

		KM::Vector2& GetCenter(void) { return _center; }

	private:
		struct Character
		{
			KM::Vector2 position;
			F32 width;
			F32 height;
			Color color;
			Sprite sprite;
		};


		string _text;
		Font   _font;
		std::vector<Character> _characterList;
		F32 _widthScaleFactor;
		F32 _heightScaleFactor;
		F32 _totalWidth;
		F32 _totalHeight;
		KM::Vector2 _center;	
	};
}

#endif