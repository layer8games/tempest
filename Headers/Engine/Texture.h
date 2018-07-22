/*=========================================================================
The Texture struct is used to save and hold information about a texture that
has already been loaded into memory. It is there to save the GLUINT ID that 
is returned from DevIL that represents the saved texture that is fully loaded
into memory. 


This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
=========================================================================*/
#pragma once

//=====Killer1 includes=====
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>

//===== Image Library =====
#include <SOIL/SOIL.h>

namespace KillerEngine 
{

	class Texture 
	{
	public:	
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================		
		Texture(void);

		Texture(GLuint id, S32 width, S32 height);

		Texture(const Texture& T);

		Texture(const Texture* T);

		~Texture(void);

//==========================================================================================================================
//
//Accessors
//
// most of this will go. 
//==========================================================================================================================
		inline GLuint GetHandle(void) const
		{
			return _handle;
		}

		inline S32 GetWidth(void) const 
		{ 
			return _width; 
		}

		inline void SetWidth(S32 w) 
		{ 
			_width = w; 
		}

		inline S32 GetHeight(void) const 
		{ 
			return _height; 
		}

		inline void SetHeight(S32 h) 
		{ 
			_height = h; 
		}

//==========================================================================================================================
//
//Operator Overload
//
//==========================================================================================================================
		Texture& operator=(const Texture& T);

		Texture& operator=(const Texture* T);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
		void LoadTexture(string filePath, bool generateMipMaps=true);

		void Bind(GLuint texUnit=0);

	private:	
		GLuint _handle; // keep but change into handle for new texture. 
		S32    _width; // not needed. Only keep if you use SOIL, and you think it is something that may be useful to save. 
		S32    _height; // not needed. Same
		
	};

}