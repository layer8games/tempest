#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/BufferData.h>
#include <Engine/ErrorManager.h>
#include <Engine/Vertex.hpp>
#include <Engine/Point4.h>

namespace TM = TempestMath;

#include <rapidxml.hpp>

//===== STL inludes =====
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <regex>
#include <stdlib.h>

//===== OpenGL Includes =====
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Tempest
{
    class Mesh
    {
    public:
        TEMPEST_API Mesh(void);

        TEMPEST_API Mesh(const Mesh& mesh);

        TEMPEST_API virtual ~Mesh(void);

        TEMPEST_API virtual void v_Render(void);

        TEMPEST_API void DefaultRender(void);

        TEMPEST_API void InitOpenGLData(void);

        TEMPEST_API bool LoadOBJ(string filepath);

        TEMPEST_API void LoadMesh(string filepath);

        inline GLuint GetVAO(void) const
        {
            return _vao;
        }

        inline void BindVAO(bool state=true)
        {
            if(state)
            {
                glBindVertexArray(_vao);
            }
            else
            {
                glBindVertexArray(0);
            }
        }

        void BindVBO(BufferData buffer);

        inline U32 GetNumVertices(void)
        {
            return _vertices.size();
        }

        inline void AddVertex(const Vertex vert)
        {
            _vertices.push_back(vert);
        }

        inline void SetVertices(std::vector<Vertex> vertices)
        {
            _vertices = vertices;
        }

        inline std::vector<Vertex> GetVertices(void) const
        {
            return _vertices;
        }
        
        inline void AddIndex(U32 index)
        {
            _indices.push_back(index);
        }

        inline void SetIndices(std::vector<U32> indices)
        {
            _indices = indices;
        }

        inline std::vector<U32> GetIndices(void) const
        {
            return _indices;
        }

        inline std::vector<F32> GetUVList(void) const
        {
            return _uvList;
        }

        inline void SetUVList(std::vector<F32> list)
        {
            _uvList = list;
        }

        inline void AddUV(F32 val)
        {
            _uvList.push_back(val);
        }

    private:
        std::vector<U32> _SplitU32(string text, char delim) const;

        std::vector<F32> _SplitF32(string text, char delim) const;

        std::vector<string> _SplitString(string text, char delim) const;

        std::vector<Vertex> _vertices;
        std::vector<U32> _indices;
        std::vector<F32> _uvList;
        GLuint _vao;
        GLuint _vbo[NUM_VBO];

    };//end Class
    typedef shared_ptr<Mesh> p_Mesh;
}//end namespace
