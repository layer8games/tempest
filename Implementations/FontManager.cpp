#include "stdafx.h"
#include <Engine/FontManager.h>
using namespace Tempest;

shared_ptr<FontManager> FontManager::_instance = nullptr;
FontManager::FontManager(void)
:
_loadedFonts()
{  }

FontManager::~FontManager(void)
{  }


shared_ptr<FontManager> FontManager::Instance(void)
{
    if(_instance == nullptr)
    {
        _instance = shared_ptr<FontManager>(new FontManager());
    }

    return _instance;
}

void FontManager::LoadFont(U32 id, string fontName, string filePath, U32 size)
{
    if(_loadedFonts.find(id) != _loadedFonts.end())
    {
        //Font already loaded -> Consider throwing an error
        return;
    }

    shared_ptr<Font> font (new Font());
    font->Init(fontName, filePath, size);

    _loadedFonts.insert({id, font});

    if(_loadedFonts.find(id) == _loadedFonts.end())
    {
        ErrorManager::Instance()->SetError(ENGINE, "FontManager::LoadFont: Unable to load font. Name = " + fontName);
    }
}

//==========================================================================================================================
//AddFont
//==========================================================================================================================
void FontManager::AddFont(U32 id, shared_ptr<Font> font)
{
    if(_loadedFonts.find(id) != _loadedFonts.end())
    {
        //Font already loaded -> Consider throwing an error
        return;
    }

    _loadedFonts.insert({id, font});

    if(_loadedFonts.find(id) == _loadedFonts.end())
    {
        ErrorManager::Instance()->SetError(ENGINE, "FontManager::LoadFont: Unable to load font. Name = " + font->GetName());
    }
}

void FontManager::AddFont(U32 id, Font& font)
{
    if(_loadedFonts.find(id) != _loadedFonts.end())
    {
        //Font already loaded -> Consider throwing an error
        return;
    }

    shared_ptr<Font> fontPTR (&font);
    
    _loadedFonts.insert({id, fontPTR});

    if(_loadedFonts.find(id) == _loadedFonts.end())
    {
        ErrorManager::Instance()->SetError(ENGINE, "FontManager::LoadFont: Unable to load font. Name = " + fontPTR->GetName());
    }
}

shared_ptr<Font> FontManager::GetFont(U32 id)
{
    if(_loadedFonts.find(id) == _loadedFonts.end())
    {
        ErrorManager::Instance()->SetError(ENGINE, "FontManager::GetFont: No such font, " + id);
        return nullptr;
    }

    return _loadedFonts[id];
}