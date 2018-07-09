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

namespace KillerEngine
{
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
//Accessors
//
//==========================================================================================================================
		void SetVertexPath(string path)
		{
			_vertexPath = path;
		}

		void SetTesselationPath(string path)
		{
			_tessellationPath = path;
		}

		void SetGeometryPath(string path)
		{
			_geometryPath = path;
		}

		void SetFragmentPath(string path)
		{
			_fragmentPath = path;
		}

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
		static shared_ptr<Shader> Instance(void);

		void InitSpriteShader(void);

		void InitModelShader(void);

		void InitShader(void);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		GLuint GetSpriteShader(void);

		GLuint GetModelShader(void);

	private:
		static shared_ptr<Shader> _instance;
		GLuint 					  _spriteShader;
		GLuint 					  _modelShader;
		string 					  _vertexPath;
		string 					  _tessellationPath;
		string 					  _geometryPath;
		string 					  _fragmentPath;

	};//end Class
}//end Namespace
