#pragma once

#include "stdafx.h"
#include "Engine/Atom.h"
#include "Engine/BufferData.h"
#include "Engine/ErrorManager.h"
#include "Engine/Vertex.hpp"
#include "Engine/Vector4.h"

namespace TM = TempestMath;

#include "rapidxml.hpp"

#include "vector"
#include "fstream"
#include "sstream"
#include "algorithm"
#include "regex"
#include "stdlib.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

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

        TEMPEST_API GLuint GetVAO(void) const;

        TEMPEST_API void BindVAO(bool state=true);

        TEMPEST_API void BindVBO(BufferData buffer);

        TEMPEST_API U32 GetNumVertices(void);

        TEMPEST_API void AddVertex(const Vertex vert);

        TEMPEST_API void SetVertices(std::vector<Vertex> vertices);

        TEMPEST_API std::vector<Vertex> GetVertices(void) const;
        
        TEMPEST_API void AddIndex(U32 index);

        TEMPEST_API void SetIndices(std::vector<U32> indices);

        TEMPEST_API std::vector<U32> GetIndices(void) const;

        TEMPEST_API std::vector<F32> GetUVList(void) const;

        TEMPEST_API void SetUVList(std::vector<F32> list);

        TEMPEST_API void AddUV(F32 val);

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
