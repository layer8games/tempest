#include <Engine/Color.h>

namespace KillerEngine
{
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
	Color::Color(void) 
	{
		_red = _green= _blue = 0.0f;
		_alpha = 1.0f;
	}
	
	Color::Color(F32 col)	
	{
		_red = _green= _blue = col;
		_alpha = 1.0f;
	}

	Color::Color(F32 red, F32 green, F32 blue) 
	{
		_red = red;
		_green= green;
		_blue = blue;
		_alpha = 1.0f;
	}
	
	Color::Color(F32 red, F32 green, F32 blue, F32 alpha) 
	{
		_red = red;
		_green= green;
		_blue = blue;
		_alpha = alpha;
	}
	
	Color::Color(const Color& c) : _red(c.GetRed()), _green(c.GetGreen()), _blue(c.GetBlue()), _alpha(c.GetAlpha())
	{  }

	Color::~Color(void)
	{  }
}//end namespace