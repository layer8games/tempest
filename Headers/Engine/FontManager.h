#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/Font.h>
#include <Engine/ErrorManager.h>

//===== STL includes =====
#include <map>

namespace Tempest
{
    class FontManager
    {
    public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
        TEMPEST_API ~FontManager(void);

//==========================================================================================================================
//
//Fucntions
//
//==========================================================================================================================
        TEMPEST_API static shared_ptr<FontManager> Instance(void);

        TEMPEST_API void LoadFont(U32 id, string fontName, string filePath, U32 size);

        TEMPEST_API void AddFont(U32 id, shared_ptr<Font> font);

        TEMPEST_API void AddFont(U32 id, Font& font);

        TEMPEST_API shared_ptr<Font> GetFont(U32 id);

    protected:
//==========================================================================================================================
//Constructor
//==========================================================================================================================
        FontManager(void);
//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
    private:
        static shared_ptr<FontManager>  _instance;
        std::map<U32, shared_ptr<Font>> _loadedFonts;
        
    };//end Class
}//end Namespace
