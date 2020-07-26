#include "stdafx.h"
#include <Engine/Shader.h>
using namespace Tempest;

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

void Shader::LoadShader(std::vector<ShaderData> shaders)
{
    if(shaders.size() > 5)
    {
        ErrorManager::Instance()->SetError(SHADER, "Shader::LoadShader. Too many shaders passed to function. Max of 5 allowed, sent = " + shaders.size());
        return;
    }

    GLuint vertexProgram = 0; 
    GLuint fragmentProgram = 0;
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

            if(!_CheckCompileStatus(vertexProgram))
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
            
            if(!_CheckCompileStatus(fragmentProgram))
            {
                glDeleteProgram(fragmentProgram);
                return;
            }
        }
        else  
        {
            ErrorManager::Instance()->SetError(SHADER, "Shader::LoadShader; No such shader type " + i.type);	
        }
    }

    glAttachShader(_shaderProgram, vertexProgram);
    glAttachShader(_shaderProgram, fragmentProgram);
    glLinkProgram(_shaderProgram);

    _CheckLinkStatus();

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

void Shader::SetUniform(string name, const F32 val)
{
    Use();
    GLuint location = _GetUniformLocation(name.c_str());
    glUniform1f(location, val);
}

void Shader::SetUniform(string name, const TM::Vector4& vec)
{
    Use();
    GLuint location = _GetUniformLocation(name.c_str());
    glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
}

void Shader::SetUniform(string name, const TM::Vector3& vec)
{
    Use();
    GLuint location = _GetUniformLocation(name.c_str());
    glUniform3f(location, vec.x, vec.y, vec.z);
}

void Shader::SetUniform(string name, const TM::Point2& point)
{
    Use();
    GLuint location = _GetUniformLocation(name.c_str());
    glUniform2f(location, point.x, point.y);
}

void Shader::SetUniform(string name, const TM::Point3& point)
{
    Use();
    GLuint location = _GetUniformLocation(name.c_str());
    glUniform3f(location, point.x, point.y, point.z);
}

void Shader::SetUniform(string name, const TM::Matrix4& mat)
{
    Use();
    GLuint location = _GetUniformLocation(name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, &mat.GetElems()[0]);
}

void Shader::SetUniformSampler(string name, S32 texSlot)
{
    Use();
    glActiveTexture(GL_TEXTURE0 + texSlot);

    GLuint location = _GetUniformLocation(name.c_str());

    glUniform1i(location, texSlot);	
}

void Shader::SetUniform(string name, const Color& col)
{
    Use();
    if(col.HasAlpha())
    {
        GLuint location = _GetUniformLocation(name.c_str());
        glUniform4f(location, col[0], col[1], col[2], col[3]);	
    }
    else
    {
        GLuint location = _GetUniformLocation(name.c_str());
        glUniform3f(location, col[0], col[1], col[2]);	
    }
}

void Shader::SetUniformColorAsVec3(string name, const Color& col)
{
    Use();
    GLuint location = _GetUniformLocation(name.c_str());
    glUniform3f(location, col[0], col[1], col[2]);
}

GLuint Shader::GetProgram(void) const
{
    return _shaderProgram;
}

void Shader::SetProgram(GLuint program)
{
    _shaderProgram = program;
}

map<string, GLuint> Shader::GetUniformLocations(void) const
{
    return _uniformLocations;
}
 
void Shader::SetUniformLocations(map<string, GLuint> uniforms)
{
    _uniformLocations = uniforms;
}

Shader& Shader::operator=(const Shader& shader)
{
    _shaderProgram = shader.GetProgram();

    return *this;
}

string Shader::_GetFileString(string path)
{
    std::ifstream file {};
    std::stringstream shaderData;

    file.open(path.c_str());

    if(!file.is_open())
    {
        ErrorManager::Instance()->SetError(SHADER, "Unable to open file path to shader: " + path);
    }

    shaderData << file.rdbuf();

    file.close();

    return shaderData.str();
}

bool Shader::_CheckCompileStatus(GLuint shader)
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

        ErrorManager::Instance()->SetError(SHADER, "Compile Error in shader\n" + errorLog);

        return false;
    }

    return true;
}

void Shader::_CheckLinkStatus(void)
{
    GLint isLinked = 0; 
    glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &isLinked);

    if(isLinked == GL_FALSE)
    {
        GLint length = 0;
        glGetProgramiv(_shaderProgram, GL_INFO_LOG_LENGTH, &length);

        //The length includes the NULL character
        string errorLog(length, ' ');
        glGetProgramInfoLog(_shaderProgram, length, &length, &errorLog[0]);

        ErrorManager::Instance()->SetError(SHADER, "Compile Error in shader\n" + errorLog);

        glDeleteProgram(_shaderProgram);
    }
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