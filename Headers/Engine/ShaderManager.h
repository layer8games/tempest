#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Shader.h>
#include <Engine/ErrorManager.h>

//===== STL Includes =====
#include <map>
#include <vector>

namespace Tempest
{
	enum TEMPEST_API DefaultShaderID
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
		TEMPEST_API ~ShaderManager(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
		TEMPEST_API static shared_ptr<ShaderManager> Instance(void);

		TEMPEST_API void AddShader(U32 id, shared_ptr<Shader> shader);

		TEMPEST_API void LoadShader(U32 id, std::vector<ShaderData> data);

		TEMPEST_API shared_ptr<Shader> GetShader(U32 id);

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
