/*==========================================================================
The main Rendering framework for the Engine. A Singleton with a batch
system intregrated into it. It will be called from the Sprite class, or
from the main loop at the end of a frame, to make sure that everything
is drawn as it should be.

Add*

There is an Add function for Triangles, Squares and Hexagons. These are:
AddTri()
AddSqr()
AddHex()

These take the position of a cell, then create F32 Vecs, storing them in an std::vector, which is 
passed to OGL during the Draw().  

This is not free to use, and cannot be used without the express permission
of KillerWave. 

Written by Maxwell Miller
==========================================================================*/
#ifndef RENDERER_H
#define RENDERER_H

//=====Killer1 includes=====
#include <Engine/Atom.h>
#include <Engine/Sprite.h>
#include <Engine/WinProgram.h>
#include <Engine/TextureManager.h>
#include <Engine/Texture.hpp>
#include <Engine/ErrorManager.h>
#include <Engine/Camera.h>
#include <Engine/Matrix.h>
#include <Engine/Vector2.h>
#include <Engine/Color.h>
#include <Engine/Model.h>
#include <Engine/Vertex.h>

namespace KM = KillerMath;

//=====OGL includes=====
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/wglext.h>

//=====SOIL includes=====
#include <SOIL/SOIL.h>


//=====STL Includes=====
#include <vector>

namespace KillerEngine 
{

	//=====Foreward delcaration=====
	class Sprite;
	class Model;

	class Renderer 
	{
	public:
//==========================================================================================================================
//
//Destructor
//
//==========================================================================================================================
		~Renderer(void) {  };
		
//==========================================================================================================================
//
//Singleton Functions
//
//==========================================================================================================================
		static Renderer* Instance(void);

		void ShutDown(void)
		{
			delete _instance;
		}

//==========================================================================================================================
//
//Renderer Funtions
//
//==========================================================================================================================
		void SetBackgroundColor(Color& c) 
		{ 
			WinProgram::Instance()->SetBackgroundColor(c); 
		}

		void AddToBatch(const GLuint shader, KM::Vector2& pos, F32 w, F32 h, Color& c);

		void AddToBatch(const GLuint shader, KM::Vector2& pos, F32 w, F32 h, Color& c, U32 textureID);
		
		void AddToBatch(const GLuint shader, KM::Vector2& pos, F32 w, F32 h, Color& c, U32 textureID, KM::Vector2& origin, KM::Vector2& limit);

		void AddToBatch(std::vector<F32> v, std::vector<F32> c);

		void AddToBatch(Model& m);

		void AddTextureToBatch(std::vector<F32> v, std::vector<F32> uv);
		
		void Draw(void);

		//void Draw2(void);
		
	protected:
//==========================================================================================================================
//
//Constructor
//
//==========================================================================================================================
		Renderer(void);

	private:
		static Renderer* 	 _instance;
		U32 				 _maxBatchSize;
		U32 				 _currentBatchSize;
		std::vector<F32> 	 _vertices;
		std::vector<F32> 	 _colors;
		std::vector<F32> 	 _dimensions;
		std::vector<F32> 	 _bottomTop;
		std::vector<F32>     _leftRight;	
		GLuint				 _renderingProgramColor;
		
		const static U32	 NUM_VOA = 2;
		GLuint   			 _renderingProgramTexture;
		GLuint   			 _vertexArrayObject[NUM_VOA];
		
		GLuint 				 _currentShader;
		static const GLchar* _vertexShaderSourceColor[];
		static const GLchar* _vertexShaderSourceTexture[];
		static const GLchar* _fragmentShaderSourceColor[];
		static const GLchar* _fragmentShaderSourceTexture[];

	};

}//End namespace

#endif