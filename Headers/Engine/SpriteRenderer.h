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
#pragma once

//=====Killer1 includes=====
#include <Engine/Atom.h>
#include <Engine/Sprite.h>
#include <Engine/WinProgram.h>
#include <Engine/TextureManager.h>
#include <Engine/Texture.h>
#include <Engine/ErrorManager.h>
#include <Engine/Camera.h>
#include <Engine/Matrix.h>
#include <Engine/Vector2.h>
#include <Engine/Color.h>

namespace KM = KillerMath;

//=====SOIL includes=====
#include <SOIL/SOIL.h>


//=====STL Includes=====
#include <vector>

namespace KillerEngine 
{

	//=====Foreward delcaration=====
	class Sprite;

	class SpriteRenderer 
	{
	public:
//==========================================================================================================================
//
//Destructor
//
//==========================================================================================================================
		~SpriteRenderer(void);
		
//==========================================================================================================================
//
//Singleton Functions
//
//==========================================================================================================================
		static shared_ptr<SpriteRenderer> Instance(void);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		void SetBatchSize(U32 size)
		{
			_maxBatchSize = size;
		}

		inline const GLuint GetShader(void)
		{
			return _shader;
		}

		void SetShader(GLuint shader);

//==========================================================================================================================
//
//SpriteRenderer Funtions
//
//==========================================================================================================================
		void SetBackgroundColor(Color& c) 
		{ 
			WinProgram::Instance()->SetBackgroundColor(c); 
		}

		void AddToBatch(const KM::Vector2& pos, F32 w, F32 h, const Color& c);

		void AddToBatch(const KM::Vector2& pos, F32 w, F32 h, const Color& c, U32 textureID);
		
		void AddToBatch(const KM::Vector2& pos, F32 w, F32 h, const Color& c, U32 textureID, 
						const KM::Vector2& verticalLimit, const KM::Vector2& horizontalLimit);

		void AddToBatch(std::vector<F32> v, std::vector<F32> c);

		//void AddToBatch(Model& m);

		void AddTextureToBatch(std::vector<F32> v, std::vector<F32> uv);
		
		void Draw(void);

		//void Draw2(void);
		
	protected:
//==========================================================================================================================
//
//Constructor
//
//==========================================================================================================================
		SpriteRenderer(void);

	private:
		static shared_ptr<SpriteRenderer>  _instance;
		
		U32 				 _maxBatchSize;
		U32 				 _currentBatchSize;
		std::vector<F32> 	 _vertices;
		std::vector<F32> 	 _colors;
		std::vector<F32> 	 _dimensions;
		std::vector<F32> 	 _bottomTop;
		std::vector<F32>     _leftRight;	
		GLuint				 _renderingProgramColor;
		
		const static U32	 NUM_VOA = 1;
		GLuint   			 _renderingProgramTexture;
		GLuint   			 _vertexArrayObject[NUM_VOA];
		GLuint 				 _shader;
		U32 				 _shaderSetCount;
		U32 				 _drawCount;

	};

}//End namespace