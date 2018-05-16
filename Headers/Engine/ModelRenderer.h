/*========================================================================
An abstraction for the Rendering and Batching code needed to render any
arbitrary 3D Model. 

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/WinProgram.h>
#include <Engine/Model.h>
#include <Engine/Camera.h>
#include <Engine/Matrix.h>
#include <Engine/Vector3.h>
#include <Engine/Color.h>
#include <Engine/Vertex.h>

namespace KM = KillerMath;

//=====OGL includes=====
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/wglext.h>

//=====STL Includes=====
#include <vector>

namespace KillerEngine
{
	class ModelRenderer
	{
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
	protected:
		ModelRenderer(void);

	public:
		~ModelRenderer(void);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		inline const GLuint GetShader(void)
		{
			return _shader;
		}

		void SetShader(GLuint shader);
//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
		static shared_ptr<ModelRenderer> Instance(void);

		inline void SetBackgroundColor(Color& c)
		{
			WinProgram::Instance()->SetBackgroundColor(c);
		}

		

		void AddToBatch(const Model& m);

		void Draw(void);

		void DrawNow(const Model& m);

	private:
		static shared_ptr<ModelRenderer> _instance;
		U32 							 _maxBatchSize;
		U32								 _currentBatchSize;
		std::vector<F32> 				 _vertices;
		const static U32				 _NUM_VOA = 1;
		GLuint							 _VOA[_NUM_VOA];
		GLuint							 _shader;
		
	};//end Class
}//end Namespace
