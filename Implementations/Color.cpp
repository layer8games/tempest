#include <Engine/Color.h>

using namespace KillerEngine;
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Color::Color(void) 
: 
_red(0.0f), 
_green(0.0f), 
_blue(0.0f), 
_alpha(1.0f)
{  }

Color::Color(F32 col)
: 
_red(col), 
_green(col), 
_blue(col), 
_alpha(1.0f)
{
	assert(col >= 0.0f && col <= 1.0f);
}

Color::Color(F32 red, F32 green, F32 blue)
: 
_red(red), 
_green(green), 
_blue(blue), 
_alpha(1.0f)
{
	assert(red >= 0.0f && red <= 1.0f);
	assert(green >= 0.0f && green <= 1.0f);
	assert(blue >= 0.0f && blue <= 1.0f);
}

Color::Color(F32 red, F32 green, F32 blue, F32 alpha)
: 
_red(red), 
_green(green), 
_blue(blue), 
_alpha(alpha)
{
	assert(red >= 0.0f && red <= 1.0f);
	assert(green >= 0.0f && green <= 1.0f);
	assert(blue >= 0.0f && blue <= 1.0f);
	assert(alpha >= 0.0f && alpha <= 1.0f);
}

Color::Color(const Color& c) 
: 
_red(c.GetRed()), 
_green(c.GetGreen()), 
_blue(c.GetBlue()), 
_alpha(c.GetAlpha())
{  }

Color::~Color(void)
{  }

//==========================================================================================================================
//
//Color Funtions
//
//==========================================================================================================================
void Color::Set(F32 r, F32 g, F32 b)
{
	assert(r >= 0.0f && r <= 1.0f);
	assert(g >= 0.0f && g <= 1.0f);
	assert(b >= 0.0f && b <= 1.0f);
	
	_red = r;
	_green = g;
	_blue = b;
}