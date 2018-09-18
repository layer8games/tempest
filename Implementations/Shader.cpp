#include <Engine/Shader.h>
#include <iostream>

using namespace KillerEngine;
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Shader::Shader(void)
:
_uniformLocations(),
_shaderProgram(0)
{
	_shaderProgram = glCreateProgram();
}

Shader::~Shader(void)
{
	glUseProgram(0);
	glDeleteProgram(_shaderProgram);
}

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
void Shader::LoadShader(std::vector<ShaderData> shaders)
{
	if(shaders.size() > 5)
	{
		ErrorManager::Instance()->SetError(EC_OpenGL_Shader, "Shader::LoadShader. Too many shaders passed to function. Max of 5 allowed, sent = " + shaders.size());
		return;
	}

	GLuint vertexProgram, fragmentProgram = 0;
	GLint shaderSize;

	for(auto i : shaders)
	{
		if(i.type == VERTEX)
		{
			vertexProgram = glCreateShader(GL_VERTEX_SHADER);
			string vertexString = _GetFileString(i.filePath);
			const GLchar* vertexSource = vertexString.c_str();
			shaderSize = vertexString.size();

			glShaderSource(vertexProgram, 1, &vertexSource, (GLint*)&shaderSize);
			glCompileShader(vertexProgram);

			if(!_CheckCompileErrors(vertexProgram))
			{
				glDeleteProgram(vertexProgram);
				return;
			}
		} 
		else if(i.type == FRAGMENT)
		{
			fragmentProgram = glCreateShader(GL_FRAGMENT_SHADER);
			string fragmentString = _GetFileString(i.filePath);
			const GLchar* fragmentSource = fragmentString.c_str();
			shaderSize = fragmentString.size();

			glShaderSource(fragmentProgram, 1, &fragmentSource, (GLint*)&shaderSize);
			glCompileShader(fragmentProgram);
			
			if(!_CheckCompileErrors(fragmentProgram))
			{
				glDeleteProgram(fragmentProgram);
				return;
			}
		}
		else  
		{
			ErrorManager::Instance()->SetError(EC_OpenGL_Shader, "Shader::LoadShader; No such shader type " + i.type);	
		}
	}

	glAttachShader(_shaderProgram, vertexProgram);
	glAttachShader(_shaderProgram, fragmentProgram);
	glLinkProgram(_shaderProgram);

	//===== Error checking =====
	GLint isLinked = 0; 
	glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &isLinked);

	if(isLinked == GL_FALSE)
	{
		GLint length = 0;
		glGetProgramiv(_shaderProgram, GL_INFO_LOG_LENGTH, &length);

		//The length includes the NULL character
		string errorLog(length, ' ');
		glGetProgramInfoLog(_shaderProgram, length, &length, &errorLog[0]);

		ErrorManager::Instance()->SetError(EC_OpenGL_Shader, "Compile Error in shader\n" + errorLog);

		//The program is useless now. So delete it.
		glDeleteProgram(_shaderProgram);
	}

	//===== clean up =====
	glDeleteProgram(vertexProgram);
	glDeleteProgram(fragmentProgram);
}

void Shader::Use(bool state)
{
	if(state) 
	{
		glUseProgram(_shaderProgram);
	}
	else
	{
		glUseProgram(0);
	}
}

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
void Shader::SetUniform(const GLchar* name, const F32 val)
{
	GLuint location = _GetUniformLocation(name);
	glUniform1f(location, val);
}

void Shader::SetUniform(const GLchar* name, Color col)
{
	GLuint location = _GetUniformLocation(name);
	glUniform4f(location, col.GetRed(), col.GetGreen(), col.GetBlue(), col.GetAlpha());
}

void Shader::SetUniform(const GLchar* name, KM::Vector vec)
{
	GLuint location = _GetUniformLocation(name);
	glUniform4f(location, vec[0], vec[1], vec[2], vec[3]);
}

void Shader::SetUniform(const GLchar* name, KM::Matrix mat)
{
	GLuint location = _GetUniformLocation(name);
	glUniformMatrix4fv(location, 1, GL_FALSE, &mat.GetElems()[0]);
}

void Shader::SetUniformSampler(const GLchar* name, S32 texSlot)
{
	glActiveTexture(GL_TEXTURE0 + texSlot);

	GLuint location = _GetUniformLocation(name);

	glUniform1i(location, texSlot);	
}

//==========================================================================================================================
//
//Operator overloads
//
//==========================================================================================================================
Shader& Shader::operator=(const Shader& shader)
{
	//_uniformLocations = shader.GetUniformLocations();
	_shaderProgram = shader.GetProgram();

	return *this;
}

//==========================================================================================================================
//
//Private Functions
//
//==========================================================================================================================
string Shader::_GetFileString(string path)
{
	std::ifstream file {};
	std::stringstream shaderData;

	file.open(path.c_str());

	if(!file.is_open())
	{
		ErrorManager::Instance()->SetError(EC_OpenGL_Shader, "Unable to open file path to shader: " + path);
	}

	shaderData << file.rdbuf();

	file.close();

	return shaderData.str();
}

bool Shader::_CheckCompileErrors(GLuint shader)
{
	GLint status = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	
	if(status == GL_FALSE)
	{
		GLint length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

		//The length includes the NULL character
		string errorLog(length, ' ');	
		glGetProgramInfoLog(shader, length, &length, &errorLog[0]);

		ErrorManager::Instance()->SetError(EC_OpenGL_Shader, "Compile Error in shader\n" + errorLog);

		return false;
	}

	return true;
}

GLuint Shader::_GetUniformLocation(const GLchar* name)
{
	auto it = _uniformLocations.find(name);

	if(it == _uniformLocations.end())
	{
		//this use. Make current program active if it is not.
		Use();
		_uniformLocations[name] = glGetUniformLocation(_shaderProgram, name);
	}

	return _uniformLocations[name];
}