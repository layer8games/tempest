#pragma once

//===== Killer1 includes =====
#include <Engine/Atom.h>

//===== STL includes =====
#include <cassert>

namespace KillerEngine
{
//==========================================================================================================================
//Documentations
//==========================================================================================================================
/*! A structure to hold basic colors for all Sprites to sent to OGL in order to render things

	There will be 4 values per color so that it can be sent to a vec4 in OGL before it is used to actually control the colors 
	of anything in the shader. This is stored in an array for convience of passing the whole array out 
	when the time comes.  

	Where values are set, they are required to be normalized, that is between 0.0f and 1.0f. This is because the colors need
	to be represented this for OpenGL. Asserts are used at compile time to make sure that this is true. */
	class Color 
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
/*! Default Constructor. Sets Red Green and Blue to 0.0f, and Alpha to 1.0f */		
		Color(void);
		
/*! Single Value Constructor. Sets Red, Green and Blue to value. The value needs to be between 0.0f and 1.0f. Alpha is set to 
	1.0f by default.
	\param col F32: value used to set RGB values. */		
		explicit Color(F32 col);

/*! Three value Constructor. Sets Red, Green and Blue accordingly. Values need to be between 0.0f and 1.0f. Alpha is set to 1.0f 
	by default.
	\param red F32: value for Red.
	\param green F32: value for Green.
	\param blue F32: value for Blue. */		
		Color(F32 red, F32 green, F32 blue);
		
/*! Four value Constructor. Sets Red, Green and Blue accordingly. Values need to be between 0.0f and 1.0f by default.
	\param red F32: value for Red.
	\param green F32: value for Green.
	\param blue F32: value for Blue. 
	\param alpha F32: value for Alpha. */		
		Color(F32 red, F32 green, F32 blue, F32 alpha);
		
/*! Copy constructor. Calls Color::GetRed Color::GetGreen Color::GetBlue Color::GetAlpha to set values. 
	\param c = Color&: color to copy*/
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
/*! Creates and returns an array with the 4 color values in it as a pointer. */
		inline const F32* Get(void) const 
		{ 
			F32 val[] = { _red, _green, _blue, _alpha };
			return val; 
		}
		
/*! Returns the Red color value. */		
		inline const F32 GetRed(void) const 
		{ 
			return _red; 
		}
		
/*! Returns the Green color value. */		
		inline const F32 GetGreen(void) const 
		{ 
			return _green; 
		}
		
/*! Returns the Blue color value. */		
		inline const F32 GetBlue(void) const 
		{ 
			return _blue; 
		}
		
/*! Returns the Alpha color value. */		
		inline const F32 GetAlpha(void) const 
		{ 
			return _alpha; 
		}

/*! Sets the Red Color value.
	\params r F32: new value for Red. */
		inline void SetRed(const F32 r)   
		{ 
			assert(r >= 0.0f && r <= 1.0f);
			_red = r; 
		}
		
/*! Sets the Green Color value.
	\params r F32: new value for Green. */		
		inline void SetGreen(const F32 g)  
		{ 
			assert(g >= 0.0f && g <= 1.0f);
			_green = g; 
		}
		
/*! Sets the Blue Color value.
	\params r F32: new value for Blue. */		
		inline void SetBlue(const F32 b)  
		{ 
			assert(b >= 0.0f && b <= 1.0f);
			_blue = b; 
		}
		
/*! Sets the Alpha Color value.
	\params r F32: new value for Alpha. */		
		inline void SetAlpha(const F32 a) 
		{ 
			assert(a >= 0.0f && a <= 1.0f);
			_alpha = a; 
		}

/*! Sets Red Green and Blue color values at the same time. This value should be between 0.0 and 1.0
	\param r F32: Red value.
	\param g F32: Green value.
	\param b F32: Blue value. */		
		void Set(F32 r, F32 g, F32 b);

	private:
		F32 _red;	///< Red Value
		F32 _green;	///< Green Value
		F32 _blue;	///< Blue Value
		F32 _alpha;	///< Alpha Value

	};
}//End namespace