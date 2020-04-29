#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/BufferData.h>
#include <Engine/ErrorManager.h>
#include <Engine/Vertex.h>
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
    //==========================================================================================================================
    //
    //Constructors	 	
    //
    //==========================================================================================================================
        TEMPEST_API Mesh(void);

        TEMPEST_API Mesh(const Mesh& mesh);

        TEMPEST_API virtual ~Mesh(void);

    //==========================================================================================================================
    //
    //Functions
    //
    //==========================================================================================================================
        TEMPEST_API virtual void v_Render(void);

        TEMPEST_API void DefaultRender(void);

        TEMPEST_API void InitOpenGLData(void);

        /// Loads a model from a wavefront object (.obj file). I would call this a hacked version of file processing, but it does work.		
        /// \param filepath is the path to the model to be loaded.
        TEMPEST_API bool LoadOBJ(string filepath);

        /// Loads model from a .dae file. This does not work at all. I have considered removing it completely. 
        /// \param filepath is the file to be loaded.
        TEMPEST_API void LoadMesh(string filepath);

        //===== VAO =====
        /// Return the currently used Vertex Array Object for the GameObject. Used for rendering by OpenGL		
        inline GLuint GetVAO(void) const
        {
            return _vao;
        }

        /// The Vertex Array Object needs to be bound before OpenGL can render this object. This is what sets the vertices for
        /// this object on the video card. This is part of the magic.
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

        //===== VBO =====
        /// Bind the Vertex Buffer Object. This is needed before the vertices can be added to the buffer.
        /// \param buffer contains the data to be sent into the buffer.
        /// \param state is an optional value. This is currently unused.
        void BindVBO(BufferData buffer);

        //===== NumVertices =====
        /// Return the number of vertices this GameObjects mesh has.		
        inline U32 GetNumVertices(void)
        {
            return _vertices.size();
        }

//===== Vertex =====
        /// Manually add a single vertex to the GameObjects mesh.
        /// \param vert is the vertice to manually add.
        inline void AddVertex(const Vertex& vert)
        {
            _vertices.push_back(vert);
        }

        /// Set the vertices previously created for the GameObject.
        /// \param vertices is an array of vertices that will act as the mesh for the GameObject.
        inline void SetVertices(std::vector<Vertex> vertices)
        {
            _vertices = vertices;
        }

        /// Return the mesh of vertices the GameObject has.		
        inline std::vector<Vertex> GetVertices(void) const
        {
            return _vertices;
        }

//===== Indices =====		
        /// Manually add a single index for the mesh, used for rendering
        /// \param index is added.
        inline void AddIndex(U32 index)
        {
            _indices.push_back(index);
        }

        /// Set indices to be used in rendering. These are used as an optimization in rendering.
        /// \param indices is an array of indices to be added.
        inline void SetIndices(std::vector<U32> indices)
        {
            _indices = indices;
        }

        /// Return the array of indices used for the GameObject.		
        inline std::vector<U32> GetIndices(void) const
        {
            return _indices;
        }

//===== Uv List =====
        /// Return the UV index list saved for this object.		
        inline std::vector<F32> GetUVList(void) const
        {
            return _uvList;
        }

        /// Change the UV index list for this object.
        /// \param list is an array of UV's or this objects texture rendering.
        inline void SetUVList(std::vector<F32> list)
        {
            _uvList = list;
        }

        /// Manually add a single UV to the UV list.
        /// \param val is the single value to be added.
        inline void AddUV(F32 val)
        {
            _uvList.push_back(val);
        }

    private:
        /// Helper function to split a list of numbers apart. This is intended to be used with a list of numbers separated by a 
        /// standard character, for instance, a list of space or comma separated numbers. The numbers are read as strings and
        /// converted into U32 types.
        /// \param text is string to break apart. It should be numbers separated by a common character.
        /// \param delim is the character that separates each number in list.
        std::vector<U32> _SplitU32(string text, char delim) const;

        /// Helper function to split a list of numbers apart. This is intended to be used with a list of numbers separated by a 
        /// standard character, for instance, a list of space or comma separated numbers. The numbers are read as strings and
        /// converted into F32 types.
        /// \param text is string to break apart. It should be numbers separated by a common character.
        /// \param delim is the character that separates each number in list. 		
        std::vector<F32> _SplitF32(string text, char delim) const;

        /// Helper function to split a list of numbers apart. This is intended to be used with a list of characters separated by a 
        /// standard character, for instance, a list of space or comma separated numbers. The numbers are read as strings and
        /// converted into string types.
        /// \param text is string to break apart. It should be characters separated by a common character.
        /// \param delim is the character that separates each number in list.		
        std::vector<string> _SplitString(string text, char delim) const;


    //==========================================================================================================================
    // Data
    //==========================================================================================================================
        std::vector<Vertex> 	_vertices;				///< Array of vertices used for rendering. This is the mesh of the object.
        std::vector<U32> 		_indices;				///< Rendering optimization. An array of indices used to help render the mesh without duplicated vertices.
        std::vector<F32> 		_uvList;				///< Array of UV pair values, used to render a texture on the mesh.
        GLuint 					_vao;					///< Vertex Array Object, used in OpenGL. See OGL documentation for details.
        GLuint 					_vbo[NUM_VBO];			///< Vertex Buffer Object, used in OpenGL. See OGL documentation for details.

    };//end Class
    typedef shared_ptr<Mesh> p_Mesh;
}//end namespace
