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

//=====OGL includes=====
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/wglext.h>

//=====OGL includes=====


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
		GLuint _id;
		S32    _width;
		S32    _height;
		
	};

}