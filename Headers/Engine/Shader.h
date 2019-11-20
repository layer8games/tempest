#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/Color.h>
#include <Engine/Vector4.h>
#include <Engine/Vector3.h>
#include <Engine/Point.h>
#include <Engine/Matrix4.h>
#include <Engine/Texture.h>

namespace TM = TempestMath;

//=====STL includes=====
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

using std::map;

namespace Tempest
{ 
///	Helper struct to hold the type of shader contained. Allows for functions to be able to build Shaders dynamically. 
	enum  ShaderType
	{
		VERTEX,
		FRAGMENT
	};

///	All data needed to be able to compile a shader. Filepath is the path to the code file on the hard drive, type is
///	the type of compiler needed by OpenGL. 
///	\param filePath is the path to the specific shader on the hard drive. This will be the source code for one shader 
///	stage, ie a vertex shader source file. 
///	\param type is the type of shader this file path is, ie VERTEX for a vertext shader file.
	struct ShaderData
	{
		string filePath;
		ShaderType type;
	};

///	A manager class that will control the compiled shaders for OpenGL. It could be abstrated out to also include directx, 
///	if support is ever added. 
///	It will act as a factory class, compiling and creating shaders. It has several default shaders, which should be shared 
///	amoung common objects, such as the sprites or model primitiives. 
///	It can also return an abritrary shader that does not get saved by the class over all. This function acts as a wrapper 
///	around the calls needed to complile GLSL shaders.  
	class Shader
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
///	Initializes the Uniform Locations and sets the shader handle to 0. 
		TEMPEST_API Shader(void);

///	Sets the GL Program to 0, deletes the shader from OpenGL. 
		TEMPEST_API ~Shader(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
///	Takes in a list of ShaderData, looping over it to compile each shader, then link them together. 
///	\param shaders is the list of shaders that will be compiled and linked.  
		TEMPEST_API void LoadShader(std::vector<ShaderData> shaders);
 
///	Wrapper aroudn glUseProgram. Sets this shader to be active in OpenGL for rendering. 
///	\param state is an optional flag. True = set to active, false = set inactive, this is done by calling glUseProgram(0). 
		TEMPEST_API void Use(bool state=true);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================		 
///	Helper function to set a uniform in the shader. Wrapper around glUniform1f.
///	\param name is the name of the uniform in the shader. 
///	\param val is the value to pass into the shader.  
		TEMPEST_API void SetUniform(const GLchar* name, const F32 val);

///	 Helper function to set a uniform in the shader. Wrapper around glUniform4f.
///	 \param naem is the name of the uniform in the shader. 
///	 \param vec is the KillerMath::Vector4 to pass along into the shader. x, y, z and w will be passed into the shader. 
		TEMPEST_API void SetUniform(const GLchar* name, const TM::Vector4& vec);

///	Helper function to set a uniform in the shader. Wrapper around glUniform3f.
///	\param name is the name of the uniform in the shader. 
///	\param vec is the KillerMath::Vector3 to pass into the shader. x, y and z will be passed into the shader.
		TEMPEST_API void SetUniform(const GLchar* name, const TM::Vector3& vec);

///	Helper function to set a uniform in the shader. Wrapper around glUniform3f.
///	\param name is the name of the uniform in the shader. 
///	\param point is the KillerMath::Point to pass into the shader. x, y, z and w will be passed into the shader.
		TEMPEST_API void SetUniform(const GLchar* name, const TM::Point& point);

///	Helper function to set a uniform in the shader. Wrapper around glUniformMatrix44fv.
///	\param name is the name of the uniform in the shader.
///	\param mat is the KillerMath::Matrix4 to pass into the shader. All 16 values will be passed in.
		TEMPEST_API void SetUniform(const GLchar* name, TM::Matrix4 mat);
 
///	 Helper function to set a uniform in the shader. This is used to activate more than one texture in the shader. The 
///	 default is to set all textures to slot 0, this allows for multiple slots to be set. Wrapper around glActiveTexture 
///	 and glUniform1i.
///	\param name is the name of the uniform in the shader.
///	\param texSlot is the index Texture slot to activate. 
		TEMPEST_API void SetUniformSampler(const GLchar* name, S32 texSlot);

///	Helper function to set a uniform in the shader. Wrapper around glUniform4f. Sets the r,g,b and a.
///	\param name is the name of the uniform in the shader. 
///	\param col is the Color to set in the shader.
		TEMPEST_API void SetUniform(const GLchar* name, const Color& col);
 
///	 Helper function to set a uniform in the shader. Wrapper around glUniform3f. Sets the r, g, and b.
///	\param name is the name of the uniform in the shader. 
///	\param col is the Color to set in the shader.
		TEMPEST_API void SetUniformVec3(const GLchar* name, const Color& col);

		inline GLuint GetProgram(void) const
		{
			return _shaderProgram;
		}

///	Manually set the OpenGL program handle. Used for copying the shader.
///	\param program is the new handle to set.  
		inline void SetProgram(GLuint program)
		{
			_shaderProgram = program;
		}

///	Returns all cached uniform locations in this shader. 
		inline map<string, GLuint> GetUniformLocations(void) const
		{
			return _uniformLocations;
		}
 
///	Manually set cache of uniform locations. Used for copying.  
		inline void SetUniformLocations(map<string, GLuint> uniforms)
		{
			_uniformLocations = uniforms;
		}

//==========================================================================================================================
//
//Operator Overloads
//
//==========================================================================================================================		
///	Copy assignment operator. Copies both the shader handle from OpenGL and the cached shader locations.  
		TEMPEST_API Shader& operator=(const Shader& shader);
	
	private:
//==========================================================================================================================
//
//Private Functions
//
//==========================================================================================================================
///	Converts the contends of a file into a flat string. Used for getting a pointer to all the characters to be passed to 
///	OpenGL later for compilation of shaders. 
///	\param path is the path to the file to convert into a string.  
		string _GetFileString(string path);
		
///	Calls to OpenGL, checking for any errors in the compilation of the shader.  
		bool _CheckCompileErrors(GLuint shader);

///	Checks if there is a cached location with name yet. If not, it tries to find one with that name, and caches it. There is
///	no error checking yet, if you send it a name that doesn't exists, it will die with a compiler error. 
///	\param name is the name of the location to check for and/or cache and return. 
		GLuint _GetUniformLocation(const GLchar* name);
			
//==========================================================================================================================
//Data
//==========================================================================================================================			
		map<string, GLuint> 	_uniformLocations;		///< Cached database of uniform locations, keyd with the name. 
		GLuint 					_shaderProgram;			///< Handle to compiled shader program in OpenGL

	};//end Class
	typedef shared_ptr<Shader> p_Shader;
}//end Namespace
