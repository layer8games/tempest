#include <Engine/Color.h>

using namespace KillerEngine;
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Color::Color(void) 
: 
_data{0.0f, 0.0f, 0.0f, 1.0f}
{  }

Color::Color(F32 col)
: 
_data{col, col, col, 1.0f}
{  }

Color::Color(F32 red, F32 green, F32 blue)
: 
_data{red, green, blue, 1.0f}
{  }

Color::Color(F32 red, F32 green, F32 blue, F32 alpha)
: 
_data{red, green, blue, alpha}
{  }

Color::Color(const Color& c) 
: 
_data{c[0], c[1], c[2], c[3]}
{  }

Color::~Color(void)
{  }