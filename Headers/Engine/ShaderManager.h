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

	class TEMPEST_API ShaderManager
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

		void AddShader(U32 id, shared_ptr<Shader> shader);

		void LoadShader(U32 id, std::vector<ShaderData> data);

		shared_ptr<Shader> GetShader(U32 id);

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
