/*=========================================================================
The TextureManager is a singleton class that will controll when and how all
textures are added to memory from the disc. In order to make this process 
as easy as possible the functions written to control how this works uses
the DevIL library. See http://openil.sourceforge.net/about.php for details.

SOIL is the library used to actually load the images from the hard drive 
and use the image data to create the OGL texture.  

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
=========================================================================*/
#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

//=====Killer1 includes=====
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/Texture.hpp>

//=====STL includes=====
#include <map>
using std::map;


//=====SOIL includes=====
#include <SOIL/SOIL.h>

//=====OGL includes=====
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/wglext.h>

namespace KillerEngine 
{

	class TextureManager
	{
	public:
//==========================================================================================================================
//
//Singleton Functions
//
//==========================================================================================================================
		static TextureManager* Instance(void);
		
		void ShutDown(void);
		
//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		U32 GetCurrentTextureID(void) { return _currentTextureID; }
		
		void SetCurrentTextureID(U32 textureId); 


//==========================================================================================================================
//
//TextureManager Functions
//
//==========================================================================================================================
		void LoadTexture(string path, U32 id, S32 width, S32 height);
		
		Texture& GetTexture(U32 id) { return _loadedTextures.find(id)->second; }


	protected:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================		
		TextureManager(void): _currentTextureID(0) {  }
		
		~TextureManager(void) {  }

	private:
		static TextureManager* _instance;
		U32 			   	   _currentTextureID;
		map<U32, Texture>      _loadedTextures;

	};
}//End namespace

#endif