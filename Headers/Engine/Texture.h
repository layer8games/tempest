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
		GLuint GetID(void) const;

		void SetID(GLuint id);

		S32 GetWidth(void) const;

		void SetWidth(S32 w);

		S32 GetHeight(void) const;

		void SetHeight(S32 h);

//==========================================================================================================================
//
//Operator Overload
//
//==========================================================================================================================
		Texture& operator=(const Texture& T);

		Texture& operator=(Texture* T);

	private:	
		GLuint _id; // keep but change into handle for new texture. 
		S32    _width; // not needed. ONly keep if you use SOIL, and you think it is something that may be useful to save. 
		S32    _height; // not needed. Same
		
	};

}