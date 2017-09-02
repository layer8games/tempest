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
#ifndef MODEL_H
#define MODEL_H

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Vertex.h>

//=====OpenGL Includes=====
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/wglext.h>

//=====STL Includes=====
#include <vector>

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

		Model(std::vector<Vertex3D> vertices);

		~Model(void);
//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
		void AddVertice(Vertex3D vert)
		{
			_vertices.push_back(vert);
		}

		std::vector<Vertex3D> GetVertices(void)
		{
			return _vertices;
		}

	private:
		static GLuint _shaderProgram;
		S32 _numVertices;
		std::vector<Vertex3D> _vertices;

		
	};//end Class
}//end Namespace
#endif