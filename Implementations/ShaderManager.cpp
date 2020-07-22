#include "stdafx.h"
#include <Engine/ShaderManager.h>
using namespace Tempest;

shared_ptr<ShaderManager> ShaderManager::_instance = nullptr;
ShaderManager::ShaderManager(void)
:
_loadedShaders()
{
    //TODO: This needs re-thought out. It wont work in Game Projects
    _LoadDefaultShaders();
}

ShaderManager::~ShaderManager(void)
{  }


shared_ptr<ShaderManager> ShaderManager::Instance(void) 
{
    if(_instance == nullptr) 
    { 
        _instance = shared_ptr<ShaderManager>(new ShaderManager()); 
    }
    
    return _instance;
}


void ShaderManager::AddShader(U32 id, p_Shader shader)
{
    _loadedShaders.insert({id, shader});

    if(_loadedShaders.find(id) == _loadedShaders.end())
    {
        ErrorManager::Instance()->SetError(ENGINE, "ShaderManager::AddShader unable to Added shader");
    }
}

void ShaderManager::LoadShader(U32 id, std::vector<ShaderData> data)
{
    if(_loadedShaders.find(id) != _loadedShaders.end())
    {
        //NO error for now. This allows calls to load shader to be set in an object, without loading a shader more than 
        //once.
        //ErrorManager::Instance()->SetError(ENGINE, "ShaderManager::LoadShader Shader already loaded. ID = " + id);
        return;
    }

    p_Shader shader(new Shader());
    shader->LoadShader(data);

    _loadedShaders.insert({id, shader});

    if(_loadedShaders.find(id) == _loadedShaders.end())
    {
        ErrorManager::Instance()->SetError(ENGINE, "ShaderManager::LoadShader Unable to create and added shader");
    }
}

p_Shader ShaderManager::GetShader(U32 id)
{
    if(_loadedShaders.find(id) != _loadedShaders.end())
    {
        return _loadedShaders[id];
    }
    else
    {
        ErrorManager::Instance()->SetError(ENGINE, "ShaderManager::GetShader No such Shader! ID = " + id);
        return nullptr;
    }
}

p_Shader ShaderManager::LoadShader(U32 id, string vertexFilepath, string fragmentFilepath)
{
    p_Shader shader(new Shader());
    std::vector<ShaderData> shaderData;
    ShaderData vs;
    ShaderData fs;

    vs.filePath = vertexFilepath;
    vs.type = ShaderType::VERTEX;
    shaderData.push_back(vs);

    fs.filePath = fragmentFilepath;
    fs.type = ShaderType::FRAGMENT;
    shaderData.push_back(fs);

    shader->LoadShader(shaderData);

    AddShader(id, shader);

    return shader;
}

void ShaderManager::_LoadDefaultShaders(void)
{
    LoadShader(SPRITE, "./Assets/Shaders/default_sprite_vertex.glsl", "./Assets/Shaders/default_sprite_fragment.glsl");

    LoadShader(GLYPH, "./Assets/Shaders/glyph_vertex.glsl", "./Assets/Shaders/glyph_fragment.glsl");

    LoadShader(MODEL, "./Assets/Shaders/default_model_vertex.glsl", "./Assets/Shaders/default_model_fragment.glsl");
}