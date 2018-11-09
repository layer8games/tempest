#include <Engine/Font.h>
#include <iostream>

using namespace KillerEngine;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
Font::Font(void) 
:
_numCharacters(128),
_fontSize(0),
_fontName(), 
_characterGlyphs()
{  }

Font::Font(const Font& f)
:
_numCharacters(f.GetNumCharacters()),
_fontSize(f.GetSize()),
_fontName(f.GetName()),
_characterGlyphs(f.GetAllCharacterGlyphs())
{  }

Font::Font(const Font* f)
:
_numCharacters(f->GetNumCharacters()),
_fontName(f->GetName()),
_characterGlyphs(f->GetAllCharacterGlyphs())
{  }

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
void Font::InitFont(string fontName, string filePath, U32 fontSize)
{
 	_fontSize = fontSize;
 	_fontName = fontName;

 	S32 error;
	FT_Library ft;
	error = FT_Init_FreeType(&ft);
	if(error != 0) 
	{
		ErrorManager::Instance()->SetError(FREETYPE, "Font::InitFont failed to init FT_Library with Error Code: " + error);
	}

	FT_Face face;
	error = FT_New_Face(ft, filePath.c_str(), 0, &face);
	if(error != 0)
	{
		ErrorManager::Instance()->SetError(FREETYPE, "Font::InitFont failed to init FT_Face with Error Code: " + error);
		std::cout << "Error: " << error << std::endl;
	}

	error = FT_Set_Pixel_Sizes(face, 0, fontSize);
	if(error != 0)
	{
		ErrorManager::Instance()->SetError(FREETYPE, "Font::InitFont cannot set pixel sizes with Error Code: " + error);
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 

	char c = 0;
	for(int i = 0; i < _numCharacters; ++i)
	{
		error = FT_Load_Char(face, c, FT_LOAD_RENDER);
		if(error != 0)
		{
			ErrorManager::Instance()->SetError(FREETYPE, "Font::InitFont failed to load Glyph for " + c);
			continue;
		}
		
		shared_ptr<Texture> texture(new Texture());
		CharacterData data{};
		Glyph glyph{};

		data.width = face->glyph->bitmap.width;
		data.height = face->glyph->bitmap.rows;
		data.bearingX = face->glyph->bitmap_left;
		data.bearingY = face->glyph->bitmap_top;
		data.xAdvance = face->glyph->advance.x >> 6;

		//Make texture
		GLuint textureHandle;
		glGenTextures(1, &textureHandle);
		glBindTexture(GL_TEXTURE_2D, textureHandle);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			data.width,
			data.height,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);

		texture->SetHandle(textureHandle);
		texture->SetWidth(data.width);
		texture->SetHeight(data.height);

		data.texture = texture;

		_characterGlyphs.insert({c, data});

		glBindTexture(GL_TEXTURE_2D, 0);

		++c;
	}

	error = FT_Done_Face(face);
	if(error != 0)
	{
		ErrorManager::Instance()->SetError(FREETYPE, "Font::InitFont failed to release face");
	}

	error = FT_Done_FreeType(ft);
	if(error != 0)
	{
		ErrorManager::Instance()->SetError(FREETYPE, "Font::InitFont failed to release FreeType Library");
	}
}//InitFont

//==========================================================================================================================
//
//Operator Overloads
//
//==========================================================================================================================
Font& Font::operator=(const Font& font)
{
	_fontName = font.GetName();
	_fontSize = font.GetSize();
	_characterGlyphs = font.GetAllCharacterGlyphs();

	return *this;
}

Font& Font::operator=(const Font* font)
{
	_fontName = font->GetName();
	_fontSize = font->GetSize();
	_characterGlyphs = font->GetAllCharacterGlyphs();

	return *this;
}