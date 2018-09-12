#include <Engine/TextureManager.h>
#include <iostream>

using namespace KillerEngine;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
TextureManager::TextureManager(void) 
: 
_loadedTextures()
{  }

TextureManager::~TextureManager(void)
{
	_loadedTextures.clear();
}

//==========================================================================================================================
//
//Singleton Functions
//
//==========================================================================================================================
shared_ptr<TextureManager> TextureManager::_instance = NULL;

shared_ptr<TextureManager> TextureManager::Instance(void) 
{
	if(_instance == NULL) 
	{ 
		_instance = shared_ptr<TextureManager>(new TextureManager()); 
	}
	
	return _instance;
}

//====================================================================================================
//
//TextureManager Functions
//
//=====================================================================================================
void TextureManager::AddTexture(S32 id, const Texture& tex)
{
	_loadedTextures.insert({id, shared_ptr<Texture>(const_cast<Texture*>(&tex))});

	if(_loadedTextures.find(id) == _loadedTextures.end())
	{
		ErrorManager::Instance()->SetError(EC_TextureManager, "TextureManager::AddTexture Texture already loaded " + id);
	}
}

void TextureManager::AddTexture(S32 id, shared_ptr<Texture> tex)
{
	_loadedTextures.insert({id, tex});

	if(_loadedTextures.find(id) == _loadedTextures.end())
	{
		ErrorManager::Instance()->SetError(EC_TextureManager, "TextureManager::LoadTexture, Texture already loaded " + id);
	}
}

const shared_ptr<Texture> TextureManager::GetTexture(U32 id)
{ 
	if(_loadedTextures.find(id) == _loadedTextures.end())
	{
		ErrorManager::Instance()->SetError(EC_Engine, "TextureManager: Unable to find texture: " + std::to_string(id));
		return nullptr;
	}
	else
	{
		return _loadedTextures[id];	
	}		
}