#include <Engine/Glyph.h>

using namespace KillerEngine;

//==========================================================================================================================
//Static Init
//==========================================================================================================================
	static U32 _nextID = 1;
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Glyph::Glyph(void) 
:
_character(),
_texture(),
_characterData()
{  }

Glyph::~Glyph(void)
{  }

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
void Glyph::v_Render(void)
{
	GameObject::_shader.Use(true);
	GameObject::_shader.SetUniform("model", GameObject::GetModelMatrix());

	_texture.Bind();
	
	GameObject::BindVAO(true);

	glDrawArrays(GL_TRIANGLES, 0, GameObject::GetNumVertices());

	_texture.UnBind();
	GameObject::_shader.Use(false);
	GameObject::BindVAO(false);
}

void Glyph::v_InitBuffers(void)
{
	
}