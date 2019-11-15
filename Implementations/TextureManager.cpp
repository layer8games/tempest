#include <Engine/TextureManager.h>
#include <iostream>

using namespace Tempest;

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
	p_Texture texture = make_shared<Texture>(filePath);
	AddTexture(id, texture);
}

void TextureManager::AddTexture(U32 id, const Texture& tex)
{
	_loadedTextures.insert({id, p_Texture(const_cast<Texture*>(&tex))});

	if(_loadedTextures.find(id) == _loadedTextures.end())
	{
		ErrorManager::Instance()->SetError(TEXTURE_MANAGER, "TextureManager::AddTexture Texture already loaded " + id);
	}
}

void TextureManager::AddTexture(U32 id, p_Texture tex)
{
	_loadedTextures.insert({id, tex});

	if(_loadedTextures.find(id) == _loadedTextures.end())
	{
		ErrorManager::Instance()->SetError(TEXTURE_MANAGER, "TextureManager::LoadTexture, Texture already loaded " + id);
	}
}

void TextureManager::RemoveTexture(U32 id)
{
	if(_loadedTextures.find(id) != _loadedTextures.end())
	{
		_loadedTextures.erase(id);
	}
}

const p_Texture TextureManager::GetTexture(U32 id)
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