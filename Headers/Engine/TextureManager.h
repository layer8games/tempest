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
#pragma once
//=====Killer1 includes=====
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/Texture.h>

//=====STL includes=====
#include <map>
using std::map;

namespace KillerEngine 
{

	class TextureManager
	{
	public:
//==========================================================================================================================
//
//Constructor
//
//==========================================================================================================================
		~TextureManager(void);
//==========================================================================================================================
//
//Singleton Functions
//
//==========================================================================================================================
		static shared_ptr<TextureManager> Instance(void);
		
//==========================================================================================================================
//
//TextureManager Functions
//
//==========================================================================================================================
		void AddTexture(S32 id, const Texture& tex);

		void AddTexture(S32 id, shared_ptr<Texture> tex);
		
		const shared_ptr<Texture> GetTexture(U32 id);

	protected:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================		
		TextureManager(void);
		
	private:
		static shared_ptr<TextureManager> _instance;
		map<S32, shared_ptr<Texture>> 	  _loadedTextures;

	};
}//End namespace