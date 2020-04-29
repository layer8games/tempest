#pragma once
//=====Killer1 includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/Texture.h>

//=====STL includes=====
#include <map>
using std::map;

namespace Tempest 
{
    class TextureManager
    {
    public:
        TEMPEST_API ~TextureManager(void);

        TEMPEST_API static shared_ptr<TextureManager> Instance(void);

        TEMPEST_API void LoadTexture(U32 id, string filePath);

        TEMPEST_API void AddTexture(U32 id, const Texture& tex);

        TEMPEST_API void AddTexture(U32 id, p_Texture tex);

        TEMPEST_API void RemoveTexture(U32 id);
        
        TEMPEST_API const p_Texture GetTexture(U32 id);

    protected:		
        TextureManager(void);
        
    private:
        static shared_ptr<TextureManager> _instance;	
        map<U32, p_Texture> _loadedTextures;
    };
}//End namespace