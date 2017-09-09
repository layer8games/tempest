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
#include <Engine/ErrorManager.h>
#include <Engine/Vertex.h>
#include <Engine/Vector3.h>

namespace KM = KillerMath;

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

		void RenderModel(KM::Vector3& pos);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		GLuint GetShader(void)
		{
			return _shaderProgram;
		}

		bool HasShader(void)
		{
			if(_shaderProgram == 0)
				return false;
			
			else
				return true;
		}

	private:
		GLuint _shaderProgram;
		S32 _numVertices;
		std::vector<Vertex3D> _vertices;

		void InitShader(void);

		void InitShader(GLuint shader)
		{
			_shaderProgram = shader;
		}
		
	};//end Class
}//end Namespace
#endif