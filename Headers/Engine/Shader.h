#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/Color.h>
#include <Engine/Point2.h>
#include <Engine/Point3.h>
#include <Engine/Vector3.h>
#include <Engine/Vector4.h>
#include <Engine/Matrix4.h>
#include <Engine/Texture.h>

namespace TM = TempestMath;

//=====STL includes=====
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

//===== OpenGL includes =====
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using std::map;

namespace Tempest
{ 
    enum  ShaderType
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
        TEMPEST_API Shader(void);

        TEMPEST_API ~Shader(void);

        TEMPEST_API void LoadShader(std::vector<ShaderData> shaders);
 
        TEMPEST_API void Use(bool state=true);
         
        TEMPEST_API void SetUniform(string name, const F32 val);

        TEMPEST_API void SetUniform(string name, const TM::Vector4& vec);

        TEMPEST_API void SetUniform(string name, const TM::Vector3& vec);

        TEMPEST_API void SetUniform(string name, const TM::Point2& point);
        
        TEMPEST_API void SetUniform(string name, const TM::Point3& point);

        TEMPEST_API void SetUniform(string name, const TM::Matrix4& mat);
 
        TEMPEST_API void SetUniformSampler(string name, S32 texSlot);

        TEMPEST_API void SetUniform(string name, const Color& col);
 
        TEMPEST_API void SetUniformColorAsVec3(string name, const Color& col);

        TEMPEST_API GLuint GetProgram(void) const;

        TEMPEST_API void SetProgram(GLuint program);

        TEMPEST_API map<string, GLuint> GetUniformLocations(void) const;
 
        TEMPEST_API void SetUniformLocations(map<string, GLuint> uniforms);
    
        TEMPEST_API Shader& operator=(const Shader& shader);
    
    private:
        string _GetFileString(string path);
        
        bool _CheckCompileStatus(GLuint shader);

        void _CheckLinkStatus(void);

        GLuint _GetUniformLocation(const GLchar* name);
                    
        map<string, GLuint> 	_uniformLocations;
        GLuint 					_shaderProgram;	

    };//end Class
    typedef shared_ptr<Shader> p_Shader;
}//end Namespace
