#include <Engine/Color.h>

using namespace Tempest;
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Color::Color(void) 
:
_alpha(true),
_data{0.0f, 0.0f, 0.0f, 1.0f}
{  }

Color::Color(F32 col)
:
_alpha(true),
_data{col, col, col, 1.0f}
{  }

Color::Color(F32 red, F32 green, F32 blue)
:
_alpha(true),
_data{red, green, blue, 1.0f}
{  }

Color::Color(F32 red, F32 green, F32 blue, F32 alpha)
: 
_alpha(true),
_data{red, green, blue, alpha}
{  }

Color::Color(const Color& c) 
: 
_alpha(c.HasAlpha()),
_data{c[0], c[1], c[2], c[3]}
{  }

Color::~Color(void)
{  }