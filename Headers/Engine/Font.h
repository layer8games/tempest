#pragma once

//=====Engine includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/Texture.h>
#include <Engine/CharacterData.h>
#include <Engine/Glyph.h>
#include <Engine/ErrorManager.h>

//===== External =====
#include <ft2build.h>
#include FT_FREETYPE_H

//=====STL includes=====
#include <vector>
#include <map>
#include <list>

namespace Tempest
{
    class Font
    {
    public:
        typedef std::map<char, CharacterData> CharacterDataMap;

        TEMPEST_API Font(void);

        TEMPEST_API Font(const Font& f);

        TEMPEST_API Font(const Font* f);

        TEMPEST_API void Init(string fontName, string filePath, U32 fontSize);

        TEMPEST_API Font& operator=(const Font* font);

        TEMPEST_API Font& operator=(const Font& font);

        inline bool GetInitialized(void) const
        {
            return _initialized;
        }

        inline void SetNumCharacters(S32 num)
        {
            _numCharacters = num;
        }

        inline S32 GetNumCharacters(void) const
        {
            return _numCharacters;
        }

        inline void SetSize(U32 size)
        {
            _fontSize = size;
        }

        inline U32 GetSize(void) const
        {
            return _fontSize;
        }

        inline void SetName(string fontName)
        {
            _fontName = fontName; 
        }

        inline const string GetName(void) const
        {
            return _fontName; 
        }

        inline CharacterDataMap GetAllCharacterGlyphs(void) const
        { 
            return _characterGlyphs; 
        }

        inline CharacterData GetCharacterData(char c)
        {
            return _characterGlyphs[c];
        }

    private:	
        bool _initialized;		
        S32 _numCharacters;	
        U32 _fontSize;			
        string _fontName;			
        CharacterDataMap _characterGlyphs; 	
    };//End Font
    typedef shared_ptr<Font> p_Font;
}//End namespace