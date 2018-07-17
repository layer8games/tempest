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

//=====STL includes=====
#include <vector>
#include <fstream>
#include <sstream>

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

		void Use(void);

	private:
		string _GetFileString(string path);
		bool _CheckCompileErrors(GLuint shader);

		GLuint _shaderProgram;

	};//end Class
}//end Namespace
