#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Shader.h>
#include <Engine/ErrorManager.h>

//===== STL Includes =====
#include <map>
#include <vector>

namespace KillerEngine
{
	enum DefaultShaderID
	{
		SPRITE = 0,
		GLYPH = 1
	};

	class ShaderManager
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		~ShaderManager(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
		static shared_ptr<ShaderManager> Instance(void);

		void AddShader(U32 id, shared_ptr<Shader> shader)
		{
			_loadedShaders.insert({id, shader});

			if(_loadedShaders.find(id) == _loadedShaders.end())
			{
				ErrorManager::Instance()->SetError(ENGINE, "ShaderManager::AddShader unable to Added shader");
			}
		}

		void LoadShader(U32 id, std::vector<ShaderData> data);

		shared_ptr<Shader> GetShader(U32 id)
		{
			if(_loadedShaders.find(id) == _loadedShaders.end())
			{
				ErrorManager::Instance()->SetError(ENGINE, "ShaderManager::GetShader No such Shader! ID = " + id);
			}
			else
			{
				return _loadedShaders[id];
			}
		}

	protected:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		ShaderManager(void);

	private:
//==========================================================================================================================
//
//Private Functions
//
//==========================================================================================================================
		void _LoadDefaultShaders(void);
//==========================================================================================================================
//
//Data
//
//==========================================================================================================================		
		static shared_ptr<ShaderManager>  _instance;
		std::map<U32, shared_ptr<Shader>> _loadedShaders;
	};//end Class
}//end Namespace
