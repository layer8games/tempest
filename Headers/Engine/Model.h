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
#include <Engine/Renderer.h>
#include <Engine/Vertex.h>
#include <Engine/Vector3.h>
#include <Engine/Camera.h>
#include <Engine/Matrix.h>

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
		void AddVertice(Vertex3D& vert)
		{
			_vertices.push_back(vert);
			++_numVertices;
		}

		void AddColor(Color& col)
		{
			_colors.push_back(col);
		}

		std::vector<Vertex3D> GetVertices(void)
		{
			return _vertices;
		}

		void Render(KM::Vector3& pos);

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
	
		S32 _numVertices;
		std::vector<Vertex3D> _vertices;
		std::vector<Color> _colors;

		const static U32 NUM_VOA = 1; 
		const static U32 NUM_BUFFERS = 2;
		GLuint 			 _vertexArrayObject[NUM_VOA];
		GLuint 			 _buffers[2];

		GLuint _shaderProgram;

		void _InitShader(void);

		void _InitShader(GLuint shader)
		{
			_shaderProgram = shader;
		}
		
	};//end Class
}//end Namespace
#endif