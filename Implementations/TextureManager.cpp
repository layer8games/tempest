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
shared_ptr<TextureManager> TextureManager::_instance = nullptr;

shared_ptr<TextureManager> TextureManager::Instance(void) 
{
	if(_instance == nullptr) 
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
void TextureManager::LoadTexture(U32 id, string filePath)
{
	shared_ptr<Texture> texture(new Texture(filePath));
	AddTexture(id, texture);
}

void TextureManager::AddTexture(U32 id, const Texture& tex)
{
	_loadedTextures.insert({id, shared_ptr<Texture>(const_cast<Texture*>(&tex))});

	if(_loadedTextures.find(id) == _loadedTextures.end())
	{
		ErrorManager::Instance()->SetError(TEXTURE_MANAGER, "TextureManager::AddTexture Texture already loaded " + id);
	}
}

void TextureManager::AddTexture(U32 id, shared_ptr<Texture> tex)
{
	_loadedTextures.insert({id, tex});

	if(_loadedTextures.find(id) == _loadedTextures.end())
	{
		ErrorManager::Instance()->SetError(TEXTURE_MANAGER, "TextureManager::LoadTexture, Texture already loaded " + id);
	}
}

const shared_ptr<Texture> TextureManager::GetTexture(U32 id)
{ 
	if(_loadedTextures.find(id) == _loadedTextures.end())
	{
		ErrorManager::Instance()->SetError(ENGINE, "TextureManager: Unable to find texture: " + std::to_string(id));
		return nullptr;
	}
	else
	{
		return _loadedTextures[id];	
	}		
}