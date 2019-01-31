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
/*!
	The Texture class is used to save and hold information about a texture that has already been loaded into memory. It used
	the SOIL library to save the Texture data into OpenGL, along with several wrappers to work with that data. 
*/
	class Texture 
	{
	public:	
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================		
/*!
	Sets all values to 0 by default.
*/
		Texture(void);

/*!
	Calls LoadTexture to set up Texture at creation
	\param filePath is used to generate Texture.
*/
		explicit Texture(string filePath);

/*!
	Sets values up based on existing data. 
	\param id is an existing OpenGL handle that can be used. 
	\param width is the total width in pixels of the Texture. 
	\param height is the total height in pixels of the Texture.
*/
		Texture(GLuint id, S32 width, S32 height);

/*!
	Copy from T into Texture. 
	\param T is the texture to copy by ref.
*/
		Texture(const Texture& T);

/*!
	Copy from T into Texture. 
	\param T is the pointer to copy. 
*/
		Texture(const Texture* T);

/*!
	Calls glDeleteTextures to clean up memory.
*/
		~Texture(void);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
/*!
	Returns the handle to the OpenGL memory of the Texture.
*/
		inline GLuint GetHandle(void) const
		{
			return _handle;
		}

/*!
	Sets the handle to a new OpenGL memory handle. 
	\param h is the new OpenGL handle ID to use.
*/
		inline void SetHandle(GLuint h)
		{
			_handle = h;
		}

/*!
	Returns the Width of the Texture. 
*/
		inline S32 GetWidth(void) const 
		{ 
			return _width; 
		}

/*!
	Sets the width of the Texture. Use with care! This is not a value that can just be scaled at random.
	\param w is the new width. 
*/
		inline void SetWidth(S32 w)
		{
			_width = w;
		}

/*!
	Returns the height of the Texture.
*/
		inline S32 GetHeight(void) const 
		{ 
			return _height; 
		}

/*!
	Sets the height of the Texture. Use with care! This is not a value that can just be scaled at random. 
	\param h is the new height.
*/
		inline void SetHeight(S32 h)
		{
			_height = h;
		}

//==========================================================================================================================
//
//Operator Overload
//
//==========================================================================================================================
/*!
	Assignment from ref. Copies all data as expected. 
	\param T is the ref to copy. 
*/
		Texture& operator=(const Texture& T);

/*!
	Assignment from pointer. Copies all data as expected. 
	\param T is the pointer to copy. 
*/
		Texture& operator=(const Texture* T);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
/*!
	Uses SOIL to generate and save a Texture. SOIL will load the data needed, then OpenGL is used to set up an handle to the
	memory in the GPU for the Texture to be used later. 
	\param filePath is the path on the hardrive to image to Open. This is relative to your working directory. 
	\param generateMipMaps allows you to control if OpenGL performs the operations needed to create mipmaps. True by default. 
*/
		void LoadTexture(string filePath, bool generateMipMaps=true);

/*!
	Binds or Unbinds the Texture to the designated texUnit in OpenGL.
	\param state controls if we are binding or unbinding. True (default) means binding, false means unbinding.
	\param texUnit specifies which texUnit gets the Texture in OpenGL, if you are using multiple textures on a single object. 0 by default. 
*/
		void Bind(bool state=true, GLuint texUnit=0) const;

/*!
	Unbinds the Texture from OpenGL.
*/
		void UnBind(void) const;

	private:	
		GLuint _handle;  ///< ID used by OpenGL as handle to the memory this Texture takes up on the GPU.
		S32    _width;   ///< Width of the Texture. Not currently used for anything. Storing just for record keeping I guess. 
		S32    _height;  ///< Height of the Texture. Not currently used for anything. Storing just for record keeping.
		
	};

}