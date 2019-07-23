#include <Engine/ShaderManager.h>

using namespace KillerEngine;
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
ShaderManager::ShaderManager(void)
:
_loadedShaders()
{
	//TODO: This needs re-thought out. It wont work in Game Projects
	_LoadDefaultShaders();
}

ShaderManager::~ShaderManager(void)
{  }

//==========================================================================================================================
//
//Singleton Function
//
//==========================================================================================================================
shared_ptr<ShaderManager> ShaderManager::_instance = nullptr;

shared_ptr<ShaderManager> ShaderManager::Instance(void) 
{
	if(_instance == nullptr) 
	{ 
		_instance = shared_ptr<ShaderManager>(new ShaderManager()); 
	}
	
	return _instance;
}

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
void ShaderManager::AddShader(U32 id, shared_ptr<Shader> shader)
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

	shared_ptr<Shader> shader(new Shader());
	shader->LoadShader(data);

	_loadedShaders.insert({id, shader});

	if(_loadedShaders.find(id) == _loadedShaders.end())
	{
		ErrorManager::Instance()->SetError(ENGINE, "ShaderManager::LoadShader Unable to create and added shader");
	}
}

shared_ptr<Shader> ShaderManager::GetShader(U32 id)
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

//==========================================================================================================================
//
//Private Functions
//
//==========================================================================================================================
void ShaderManager::_LoadDefaultShaders(void)
{
	//===== Add Sprite Shader =====
	shared_ptr<Shader> spriteShader(new Shader());
	std::vector<ShaderData> shaderData;
	ShaderData vs;
	ShaderData fs;
	
	vs.filePath = "../Assets/Shaders/Default/sprite_vertex.glsl";
	vs.type = ShaderType::VERTEX;
	shaderData.push_back(vs);

	fs.filePath = "../Assets/Shaders/Default/sprite_fragment.glsl";
	fs.type = ShaderType::FRAGMENT;
	shaderData.push_back(fs);

	spriteShader->LoadShader(shaderData);

	AddShader(SPRITE, spriteShader);

	//===== Add Glyph Shader =====
	shared_ptr<Shader> glyphShader(new Shader());
	shaderData.clear();

	vs.filePath = "../Assets/Shaders/Default/glyph_vertex.glsl";
	vs.type = ShaderType::VERTEX;
	shaderData.push_back(vs);

	fs.filePath = "../Assets/Shaders/Default/glyph_fragment.glsl";
	fs.type = ShaderType::FRAGMENT;
	shaderData.push_back(fs);

	glyphShader->LoadShader(shaderData);

	AddShader(GLYPH, glyphShader);
}