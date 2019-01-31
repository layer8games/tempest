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
/*! 
	The TextureManager is a singleton class that will control when and how all textures are added to memory from the disc. 
	SOIL is the library used to actually load the images from the hard drive and use the image data to create the texture.
	Once a Texture is created, it can be accessed by ID to copy a pointer to the Texture. This means that each Texture can
	be shared between multiple objects. 
*/
	class TextureManager
	{
	public:
//==========================================================================================================================
//
//Constructor
//
//==========================================================================================================================
/*! 
	Clears all of the saved Textures. 
*/
		~TextureManager(void);
//==========================================================================================================================
//
//Singleton Functions
//
//==========================================================================================================================
/*! 
	Singleton function. Returns the global pointer to the TextureManager. 
*/
		static shared_ptr<TextureManager> Instance(void);
		
//==========================================================================================================================
//
//TextureManager Functions
//
//==========================================================================================================================
/*! 
	Creates a new Texture using the Texture::Texture(string) constructor. Saves by calling AddTexture.
	\param filePath is the path to the image on the hard drive. 
*/
		void LoadTexture(U32 id, string filePath);

/*! 
	Adds a Texture to manager. ID will be used to call it back. 
	\tex is the Texture to add. It is converted into a shared_ptr<Texture>. 
*/
		void AddTexture(U32 id, const Texture& tex);

/*! 
	Adds a pointer to a Texture into the manager. ID will be used to call it back.
	\param tex is the shared pointer to add.  
*/
		void AddTexture(U32 id, shared_ptr<Texture> tex);
		
/*! 
	Returns the Texture pointer stored with ID.
	\param id is the Texture id that you wish to return. Used as a key in a map. 
*/
		const shared_ptr<Texture> GetTexture(U32 id);

	protected:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================		
/*! 
	Calls default, empty constructor on map. 
*/
		TextureManager(void);
		
	private:
		static shared_ptr<TextureManager> _instance;			///< Pointer to self used as global data in Singleton pattern
		map<U32, shared_ptr<Texture>> 	  _loadedTextures;		///< Database of all added Texture pointers that can be accessed.

	};
}//End namespace