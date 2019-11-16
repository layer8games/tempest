#pragma once

//===== Killer1 includes =====
#include <Engine/Atom.h>

//===== STL includes =====
#include <cassert>

namespace Tempest
{
//==========================================================================================================================
//Documentations
//==========================================================================================================================
	/// A structure to hold basic colors for all Sprites to sent to OGL in order to render things
	
	/// There will be 4 values per color so that it can be sent to a vec4 in OGL before it is used to actually control the colors 
	/// of anything in the shader. This is stored in an array for convience of passing the whole array out 
	/// when the time comes.  

	/// Where values are set, they are required to be normalized, that is between 0.0f and 1.0f. This is because the colors need
	/// to be represented this for OpenGL. Asserts are used at compile time to make sure that this is true.
	class TEMPEST_API Color 
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
	/// Default Constructor. Sets Red Green and Blue to 0.0f, and Alpha to 1.0f 
		Color(void);
		
	/// Single Value Constructor. Sets Red, Green and Blue to value. The value needs to be between 0.0f and 1.0f. Alpha is set to
	/// 1.0f by default.
	/// \param col F32: value used to set RGB values.
		explicit Color(F32 col);

	/// Three value Constructor. Sets Red, Green and Blue accordingly. Values need to be between 0.0f and 1.0f. Alpha is set to 1.0f 
	/// by default.
	/// \param red F32: value for Red.
	/// \param green F32: value for Green.
	/// \param blue F32: value for Blue.
		Color(F32 red, F32 green, F32 blue);
		
	/// Four value Constructor. Sets Red, Green and Blue accordingly. Values need to be between 0.0f and 1.0f by default.
	/// \param red F32: value for Red.
	/// \param green F32: value for Green.
	/// \param blue F32: value for Blue. 
	/// \param alpha F32: value for Alpha.
		Color(F32 red, F32 green, F32 blue, F32 alpha);
		
	/// Copy constructor. Calls Color::GetRed Color::GetGreen Color::GetBlue Color::GetAlpha to set values. 
	/// \param c = Color&: color to copy
		Color(const Color& c);

	/// Default Constructor. Not implemented. 
		~Color(void);

//==========================================================================================================================
//
//Operator overloads
//
//==========================================================================================================================
		inline const F32& operator[](int i) const
		{
			return _data[i];
		}

		inline F32& operator[](int i)
		{
			return _data[i];
		}

		inline Color& operator=(const Color& c) 
		{
			_data[0] = c[0];
			_data[1] = c[1];
			_data[2] = c[2];
			_data[3] = c[3];

			return *this;
		}
		
//==========================================================================================================================
//
//Accessors
//
//========================================================================================================================== 
	/// Checks if the alpha channel should be considered for this Color. 
		inline bool HasAlpha(void) const
		{
			return _alpha;
		}

	/// Sets if the alpha channel should be considered for this Color.
	/// \param state is the new state that will be set. 
		inline void UseAlpha(bool state)
		{
			_alpha = state;
		}

	/// Creates and returns an array with the 4 color values in it as a pointer. 
		inline const F32* GetPointer(void) const 
		{ 
			return _data; 
		}

/// Set all values in the color to a single value.
/// \param val is the value to set rgb to.
		inline void Set(F32 val)
		{
			_data[0] = val;
			_data[1] = val;
			_data[2] = val;
		}

	private:
		bool _alpha;
		F32 _data[4];

	};
	typedef shared_ptr<Color> p_Color;
}//End namespace