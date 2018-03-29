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
_currentTextureID(0) 
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

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
void TextureManager::SetCurrentTextureID(U32 tID)
{ 
	_currentTextureID = tID; 
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _loadedTextures[tID]->GetID());
}

//====================================================================================================
//
//TextureManager Functions
//
//=====================================================================================================
void TextureManager::LoadTexture(string path, U32 id, S32 width, S32 height) 
{
	if(_loadedTextures.find(id) != _loadedTextures.end())
	{
		ErrorManager::Instance()->SetError(EC_TextureManager, "Texture already loaded " + path);
		return;
	}

	unsigned char* image = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);

	if(image == 0) 
	{
		string errorMessage = string("SOIL_load_image failed to load image: ") + path;
		ErrorManager::Instance()->SetError(EC_TextureManager, errorMessage);
	}
	
	else 
	{
		GLuint glTexture;
		glGenTextures(1, &glTexture);
		glBindTexture(GL_TEXTURE_2D, glTexture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D( GL_TEXTURE_2D,		//target
					  0,					//first mipmap level
					  GL_RGBA,				//internal format
					  width, height,		//dimensions of texture
					  0,					//border
					  GL_RGBA,				//format
					  GL_UNSIGNED_BYTE,		//type
					  image 				//image data from SOIL
					 );
		glGenerateMipmap(GL_TEXTURE_2D);

		shared_ptr<Texture> newTexture{new Texture(glTexture, width, height)};

		_loadedTextures.insert(std::map<U32, shared_ptr<Texture>>::value_type(id, newTexture));

		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0);

	}
}

shared_ptr<Texture> TextureManager::GetTexture(U32 id)
{ 
	if(_loadedTextures.find(id) == _loadedTextures.end())
	{
		ErrorManager::Instance()->SetError(EC_KillerEngine, "TextureManager: Unable to find texture: " + std::to_string(id));
		return nullptr;
	}
	else
	{
		return _loadedTextures.find(id)->second; 	
	}		
}