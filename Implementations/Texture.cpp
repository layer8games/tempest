#include <Engine/Texture.h>

using namespace KillerEngine;

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Texture::Texture(void) 
: 
_id(0), 
_width(0), 
_height(0) 
{  }

Texture::Texture(GLuint id, S32 width, S32 height)
: 
_id(id), 
_width(width), 
_height(height) 
{  }

Texture::Texture(const Texture& T)
: 
_id(T.GetID()), 
_width(T.GetWidth()), 
_height(T.GetHeight()) 
{  }

Texture::Texture(const Texture* T)
: 
_id(T->GetID()), 
_width(T->GetWidth()), 
_height(T->GetHeight()) 
{  }

Texture::~Texture(void)
{  }

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================

GLuint Texture::GetID(void) const 
{ 
	return _id; 
}

void Texture::SetID(GLuint id) 
{ 
	_id = id; 
}

S32 Texture::GetWidth(void) const 
{ 
	return _width; 
}

void Texture::SetWidth(S32 w) 
{ 
	_width = w; 
}

S32 Texture::GetHeight(void) const 
{ 
	return _height; 
}

void Texture::SetHeight(S32 h) 
{ 
	_height = h; 
}

//==========================================================================================================================
//
//Operator Overloads
//
//==========================================================================================================================	
Texture& Texture::operator=(const Texture& T) 
{
	_id     = T.GetID();
	_width  = T.GetWidth();
	_height = T.GetHeight();

	return *this;
}

Texture& Texture::operator=(Texture* T)
{
	_id     = T->GetID();
	_width  = T->GetWidth();
	_height = T->GetHeight();

	return *this;
}