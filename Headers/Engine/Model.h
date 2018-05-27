/*========================================================================
Representation of a 3D model. 

Has:
-Vertices
-Shader(s)

Uses:
Most of these will be stored in a GameObject with values
passed when needed  
-Position
-Orientation
-Scale
-Color
-Texture

Behaviors: 
-Render
-ImportModel

This is not free to use, and cannot be used without the express permission
of Layer8 Games.

Written by Maxwell Miller
========================================================================*/
#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/Vertex.h>
#include <Engine/Vector3.h>
#include <Engine/Camera.h>
#include <Engine/Matrix.h>
#include <Engine/Shader.h>

namespace KM = KillerMath;

#include <Extern/rapidxml.hpp>

//=====OpenGL Includes=====
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/wglext.h>

//=====STL Includes=====
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm> 

namespace KillerEngine
{
	class Model
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		Model(void);

		Model(const Model& m);

		Model(std::vector<Vertex3D> vertices, std::vector<U16> indices);

		~Model(void);
//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
		void LoadModel(string filepath);

		void AddIndex(U16 index);

		void AddIndex(std::vector<U16> indices);

		inline void SetIndex(std::vector<U16> indices)
		{
			_indices = indices;
			_numVertices = _indices.size();
		}

		void ClearIndices(void);

		void AddVertex(const Vertex3D& vert);

		void AddVertex(const KM::Vector3& pos, const Color& color);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		inline std::vector<Vertex3D> GetVertices(void) const
		{
			return _vertices;
		}

		inline std::vector<U16> GetIndices(void) const
		{
			return _indices;
		}

		inline const KM::Vector3& GetScale(void) const
		{
			return _scale;
		}

		inline void SetScale(KM::Vector3& s)
		{
			_scale = s; 
		}

		inline void SetShader(GLuint shader)
		{
			_shaderProgram = shader;
		}

		inline GLuint GetShader(void) const
		{
			return _shaderProgram;
		}

		inline S32 VertexCount(void) const
		{
			return _numVertices;
		}

	private:
		
		std::vector<U16> _SplitU16(string text, char delim) const;
		std::vector<F32> _SplitF32(string text, char delim) const;

		S32 			 	  _numVertices;
		std::vector<Vertex3D> _vertices;
		std::vector<U16> 	  _indices;
		KM::Vector3 		  _scale;
		GLuint				  _shaderProgram;
		
	};//end Class
}//end Namespace