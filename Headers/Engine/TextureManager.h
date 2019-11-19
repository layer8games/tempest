#pragma once
//=====Killer1 includes=====
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/Texture.h>

//=====STL includes=====
#include <map>
using std::map;

namespace Tempest 
{
///	The TextureManager is a singleton class that will control when and how all textures are added to memory from the disc. 
///	SOIL is the library used to actually load the images from the hard drive and use the image data to create the texture.
///	Once a Texture is created, it can be accessed by ID to copy a pointer to the Texture. This means that each Texture can
///	be shared between multiple objects. 
	class TEMPEST_API TextureManager
	{
	public:
//==========================================================================================================================
//
//Constructor
//
//==========================================================================================================================
///	Clears all of the saved Textures. 
		~TextureManager(void);
//==========================================================================================================================
//
//Singleton Functions
//
//==========================================================================================================================
///	Singleton function. Returns the global pointer to the TextureManager. 
		static shared_ptr<TextureManager> Instance(void);
		
//==========================================================================================================================
//
//TextureManager Functions
//
//==========================================================================================================================
///	Creates a new Texture using the Texture::Texture(string) constructor. Saves by calling AddTexture.
///	\param filePath is the path to the image on the hard drive. 
		void LoadTexture(U32 id, string filePath);

///	Adds a Texture to manager. ID will be used to call it back. 
///	\param id is the id the Texture will be registered with
/// \param tex is the Texture that will be cached.
		void AddTexture(U32 id, const Texture& tex);

///	Adds a pointer to a Texture into the manager. ID will be used to call it back.
///	\param tex is the shared pointer to add.  
		void AddTexture(U32 id, p_Texture tex);

/// Remove the Texture with the given ID
/// \param id is the ID of the registered Texture
		void RemoveTexture(U32 id);
		
///	Returns the Texture pointer stored with ID.
///	\param id is the Texture id that you wish to return. Used as a key in a map. 
		const p_Texture GetTexture(U32 id);

	protected:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================		
///	Calls default, empty constructor on map. 
		TextureManager(void);
		
	private:
		static shared_ptr<TextureManager> _instance;			///< Pointer to self used as global data in Singleton pattern
		map<U32, p_Texture> 			 _loadedTextures;		///< Database of all added Texture pointers that can be accessed.

	};
}//End namespace