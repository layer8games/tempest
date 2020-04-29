#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/GameObject2D.h>
#include <Engine/Vector4.h>
#include <Engine/Texture.h>
#include <Engine/CharacterData.h>
#include <Engine/Color.h>
#include <Engine/Matrix4.h>
#include <Engine/ShaderManager.h>

namespace TM = TempestMath;

namespace Tempest
{
    class Glyph : public GameObject2D
    {
    public:
        TEMPEST_API Glyph(void);

        TEMPEST_API Glyph(const Glyph& glyph);

        TEMPEST_API ~Glyph(void);

        void v_Update(void) final
        {
            DefaultUpdate();
        }

        TEMPEST_API void Init(void);

        inline void SetCharacter(char character, shared_ptr<Texture> tex, const CharacterData& characterData)
        {
            _character = character;
            SetTexture(tex);
            _characterData = characterData;
        }

        inline void SetCharacter(char character, const CharacterData& characterData)
        {
            _character = character;
            _characterData = characterData;
        }

        inline char GetCharacter(void) const
        {
            return _character;
        }

        inline CharacterData GetCharacterData(void) const
        {
            return _characterData;
        }

    private:
        char _character;		
        CharacterData _characterData;	
    };//end Class
    typedef shared_ptr<Glyph> p_Glyph;
}//end Namespace