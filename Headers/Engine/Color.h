/*========================================================================
A structure to hold basic colors for all Sprites to sent to OGL in order
to render things

There will be 4 values per color so that it can be sent to a vec4 in OGL
before it is used to actually control the colors of anything in the shader.
This is stored in an array for convience of passing the whole array out 
when the time comes. 

This is not free to use;
and cannot be used without the express permission
of KillerWave. 

Written by Maxwell Miller
========================================================================*/

#ifndef COLOR_H
#define COLOR_H

//=====Killer1 includes=====
#include <Engine/Atom.h>

namespace KillerEngine
{
	class Color 
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		Color(void);
		
		explicit Color(F32 col);

		Color(F32 red, F32 green, F32 blue);
		
		Color(F32 red, F32 green, F32 blue, F32 alpha);
		
		Color(const Color& c);

		~Color(void);

//==========================================================================================================================
//
//Operator overloads
//
//==========================================================================================================================
		Color& operator=(const Color& c) 
		{
			_red = c.GetRed();
			_green = c.GetGreen();
			_blue = c.GetBlue();
			_alpha = c.GetAlpha();

			return *this;
		}
		
//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		const F32* Get(void) const 
		{ 
			F32 val[] = { _red, _green, _blue, _alpha };
			return val; 
		}
		
		const F32 GetRed(void) const 
		{ 
			return _red; 
		}
		
		const F32 GetGreen(void) const 
		{ 
			return _green; 
		}
		
		const F32 GetBlue(void) const 
		{ 
			return _blue; 
		}
		
		const F32 GetAlpha(void) const 
		{ 
			return _alpha; 
		}

		void SetRed(const F32 r)   
		{ 
			_red = r; 
		}
		
		void SetGree(const F32 g)  
		{ 
			_green = g; 
		}
		
		void SetBlue(const F32 b)  
		{ 
			_blue = b; 
		}
		
		void SetAlpha(const F32 a) 
		{ 
			_alpha = a; 
		}

		void Set(F32 r, F32 g, F32 b)
		{
			_red = r;
			_green = g;
			_blue = b;
		}

	private:
		F32 _red;
		F32 _green;
		F32 _blue;
		F32 _alpha;

	};
}//End namespace
#endif