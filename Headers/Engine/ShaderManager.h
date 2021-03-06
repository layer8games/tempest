#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/Shader.h>
#include <Engine/ErrorManager.h>
#include <Engine/Color.h>

//===== STL Includes =====
#include <map>
#include <vector>

namespace Tempest
{
    enum TEMPEST_API DefaultShaderID
    {
        SPRITE = 0,
        GLYPH = 1,
        MODEL = 2
    };

    class ShaderManager
    {
    public:
        TEMPEST_API ~ShaderManager(void);

        TEMPEST_API static shared_ptr<ShaderManager> Instance(void);

        TEMPEST_API void AddShader(U32 id, p_Shader shader);

        TEMPEST_API void LoadShader(U32 id, std::vector<ShaderData> data);

        TEMPEST_API p_Shader GetShader(U32 id);

        TEMPEST_API p_Shader LoadShader(U32 id, string vertexFilepath, string fragmentFilepath);

        template <class T>
        inline void SetAllUniforms(string name, const T& type)
        {
            for(auto i : _loadedShaders)
            {
                i.second->SetUniform(name, type);
            }
        }

        TEMPEST_API void SetAllUnformsColorAsVec3(string name, const Color& color);

    protected:
        ShaderManager(void);

    private:
        void _LoadDefaultShaders(void);
        
        static shared_ptr<ShaderManager>  _instance;	
        std::map<U32, shared_ptr<Shader>> _loadedShaders;
    };//end Class
}//end Namespace
