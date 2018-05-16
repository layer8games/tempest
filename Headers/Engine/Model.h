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

		Model(const Model& m);

		explicit Model(std::vector<Vertex3D> vertices);

		~Model(void);
//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
		void AddVertex(const Vertex3D& vert);

		void AddVertex(const KM::Vector3& pos, const Color& color);

		inline std::vector<Vertex3D> GetVertices(void) const
		{
			return _vertices;
		}

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
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
		S32 			 	  _numVertices;
		std::vector<Vertex3D> _vertices;
		KM::Vector3 		  _scale;
		GLuint				  _shaderProgram;
		
	};//end Class
}//end Namespace