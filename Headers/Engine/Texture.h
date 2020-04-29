#pragma once

//=====Killer1 includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>

//===== Image Library =====
#include <SOIL/SOIL.h>

//===== OpenGL Includes =====
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Tempest 
{
    class Texture 
    {
    public:			
        TEMPEST_API Texture(void);

        TEMPEST_API explicit Texture(string filePath);

        TEMPEST_API Texture(GLuint id, S32 width, S32 height);

        TEMPEST_API Texture(const Texture& T);

        TEMPEST_API Texture(const Texture* T);

        TEMPEST_API ~Texture(void);

        inline GLuint GetHandle(void) const
        {
            return _handle;
        }

        inline void SetHandle(GLuint h)
        {
            _handle = h;
        }

        inline S32 GetWidth(void) const 
        { 
            return _width; 
        }

        inline void SetWidth(S32 w)
        {
            _width = w;
        }

        inline S32 GetHeight(void) const 
        { 
            return _height; 
        }

        inline void SetHeight(S32 h)
        {
            _height = h;
        }

        TEMPEST_API Texture& operator=(const Texture& T);

        TEMPEST_API Texture& operator=(const Texture* T);

        TEMPEST_API void LoadTexture(string filePath, bool generateMipMaps=true);

        TEMPEST_API void Bind(bool state=true, GLuint texUnit=0) const;

        TEMPEST_API void UnBind(void) const;

    private:	
        GLuint _handle;
        S32 _width; 
        S32 _height;
        
    };//End class
    typedef shared_ptr<Texture> p_Texture;
}//End namespace
