#include <Engine/Texture.h>

using namespace KillerEngine;

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Texture::Texture(void) 
: 
_handle(0), 
_width(0), 
_height(0) 
{  }

Texture::Texture(GLuint id, S32 width, S32 height)
: 
_handle(id), 
_width(width), 
_height(height) 
{  }

Texture::Texture(const Texture& T)
: 
_handle(T.GetHandle()), 
_width(T.GetWidth()), 
_height(T.GetHeight()) 
{  }

Texture::Texture(const Texture* T)
: 
_handle(T->GetHandle()), 
_width(T->GetWidth()), 
_height(T->GetHeight()) 
{  }

Texture::~Texture(void)
{  }

//==========================================================================================================================
//
//Operator Overloads
//
//==========================================================================================================================	
Texture& Texture::operator=(const Texture& T) 
{
	_handle = T.GetHandle();
	_width  = T.GetWidth();
	_height = T.GetHeight();

	return *this;
}

Texture& Texture::operator=(Texture* T)
{
	_handle = T->GetHandle();
	_width  = T->GetWidth();
	_height = T->GetHeight();

	return *this;
}

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
void Texture::LoadTexture(string filePath)
{
	//add call to texture manager here to see if an id is found.

	unsigned char* imageData = SOIL_load_image(filePath.c_str(), &_width, &_height, 0, SOIL_LOAD_RGBA);

	if(imageData == 0)
	{
		ErrorManager::Instance()->SetError(EC_TextureManager, "Texture::LoadTexture -> SOIL_load_image call failed to load " + filePath);
	}
	else
	{
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);


	}
}