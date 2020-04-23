#pragma once

//=====Engine Includes=====
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
///	A sprite based UI character to be rendered at run time. It gets its data from a Font, which informs it of its size and
///	its texture. 
    class Glyph : public GameObject2D
    {
    public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
///	No special behavior.
        TEMPEST_API Glyph(void);

///	Copies data from getters. 
        TEMPEST_API Glyph(const Glyph& glyph);

///	No special behavior.
        TEMPEST_API ~Glyph(void);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
///	Needed virtual function from GameObject. Empty implementation.
        void v_Update(void) final
        {
            DefaultUpdate();
        }


///	Initializes the Glyph as a sprite, sets Glyph shader. 
        TEMPEST_API void Init(void);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
///	Sets up the CharacterData that the Glyph will represent.
///	\param character is the raw character this Glyph is.
///	\param tex is the Texture from the Font used to draw the character Glyph.
///	\param characterData comes from the Font and stores various data the character need.
        inline void SetCharacter(char character, shared_ptr<Texture> tex, const CharacterData& characterData)
        {
            _character = character;
            SetTexture(tex);
            _characterData = characterData;
        }

///	Partial set up of the Glyph CharacterData.
///	\param character is the raw character this Glyph is.
///	\param characterData comes from the Font and stores various data the character needs.
        inline void SetCharacter(char character, const CharacterData& characterData)
        {
            _character = character;
            _characterData = characterData;
        }

///	Returns the raw character.
        inline char GetCharacter(void) const
        {
            return _character;
        }

///	Returns the CharacterData for the Glyph.
        inline CharacterData GetCharacterData(void) const
        {
            return _characterData;
        }

    private:
//==========================================================================================================================
//
//Data
//
//==========================================================================================================================
        char 		  _character;		///< Raw character that the Glyph represents on screen.
        CharacterData _characterData;	///< Various data needed to render and position the Glyph.
    };//end Class

    typedef shared_ptr<Glyph> p_Glyph;
}//end Namespace