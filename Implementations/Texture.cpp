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
void Texture::LoadTexture(string filePath, bool generateMipMaps)
{
	//add call to texture manager here to see if an id is found.

	unsigned char* imageData = SOIL_load_image(filePath.c_str(), &_width, &_height, 0, SOIL_LOAD_RGBA);

	if(imageData == 0)
	{
		ErrorManager::Instance()->SetError(EC_TextureManager, "Texture::LoadTexture -> SOIL_load_image call failed to load " + filePath);
	}
	else
	{
		glGenTextures(1, &_handle);
		glBindTexture(GL_TEXTURE_2D, _handle);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//Args: target texture type, level of details (mipmaps), Internal format, dimensions, width of the border, resulting format, data type, image data
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

		if(generateMipMaps)
		{
			glGenerateMipMap(GL_TEXTURE_2D);
		}

		SOIL_free_image_data(imageData);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}