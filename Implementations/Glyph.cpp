#include <Engine/Glyph.h>

using namespace Tempest;

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Glyph::Glyph(void) 
:
_character(),
_characterData()
{  }

Glyph::Glyph(const Glyph& glyph)
:
GameObject2D(glyph),
_character(glyph.GetCharacter()),
_characterData(glyph.GetCharacterData())
{  }

Glyph::~Glyph(void)
{  }

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
void Glyph::Init(void)
{
    GameObject2D::Init();
    SetShader(ShaderManager::Instance()->GetShader(GLYPH));
}