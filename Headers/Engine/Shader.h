/*========================================================================
A manager class that will control the compiled shaders for OpenGL. It could
be abstrated out to also include directx, if support is ever added. 

It will act as a factory class, compiling and creating shaders. It has several
default shaders, which should be shared amoung common objects, such as the 
sprites or model primitiives. 

It can also return an abritrary shader that does not get saved by the class
over all. This function acts as a wrapper around the calls needed to complile
GLSL shaders. 

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/Color.h>
#include <Engine/Vector.h>
#include <Engine/Matrix.h>

namespace KM = KillerMath;

//=====STL includes=====
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

using std::map;

namespace KillerEngine
{
	enum ShaderType
	{
		VERTEX,
		FRAGMENT
	};

	struct ShaderData
	{
		string filePath;
		ShaderType type;
	};

	class Shader
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		Shader(void);

		~Shader(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
		//void InitSpriteShader(void);

		//void InitModelShader(void);

		//GLuint CreateShader(void);

		void LoadShader(std::vector<ShaderData> shaders);

		void Use(bool state=true);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================		

		void SetUniform(const GLchar* name, Color col);

		void SetUniform(const GLchar* name, KM::Vector vec);

		void SetUniform(const GLchar* name, KM::Matrix mat);

		inline GLuint GetProgram(void) const
		{
			return _shaderProgram;
		}

		inline void SetProgram(GLuint program)
		{
			_shaderProgram = program;
		}

		inline map<string, GLuint> GetUniformLocations(void) const
		{
			return _uniformLocations;
		}

		inline void SetUniformLocations(map<string, GLuint> uniforms)
		{
			_uniformLocations = uniforms;
		}

//==========================================================================================================================
//
//Operator Overloads
//
//==========================================================================================================================		
		Shader& operator=(const Shader& shader);
	
	private:
//==========================================================================================================================
//
//Private Functions
//
//==========================================================================================================================
		string _GetFileString(string path);
		
		bool _CheckCompileErrors(GLuint shader);

		GLuint _GetUniformLocation(const GLchar* name);
			
//==========================================================================================================================
//Data
//==========================================================================================================================			
		map<string, GLuint> 	_uniformLocations;
		GLuint 					_shaderProgram;

	};//end Class
}//end Namespace
