/*========================================================================
A batch system for GameObject2D sprite based rendering. The ideas is that each 
map can have its own batch, or mulitple batches, and the batch wil controler
when a draw comman happens based on parameters that can be set within the 
class itself. 

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#ifndef SPRITE_BATCH_DEP_H
#define SPRITE_BATCH_DEP_H

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Sprite.h>
#include <Engine/Color.h>
#include <Engine/TextureManager.h>
#include <Engine/GameObject2D.h>

//=====STL includes=====
#include <vector>

namespace KillerEngine
{
	class SpriteBatch
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		SpriteBatch(void);

		explicit SpriteBatch(S32 size);

		~SpriteBatch(void);
//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
		void SetMaxBatchSize(S32 s)
		{
			_maxBatchSize = s;
		}

		S32 GetMaxBatchSize(void)
		{
			return _maxBatchSize;
		}


		S32 GetCurrentBatchSize(void)
		{
			return _currentSize;
		}

		void AddToBatch(Sprite);

		void DrawBatch(void);

	private:
		S32 _maxBatchSize;
		S32 _currentSize;
		std::vector<F32> 	 _vertices;
		std::vector<F32> 	 _colors;
		std::vector<F32> 	 _dimensions;
		std::vector<F32> 	 _bottomTop;
		std::vector<F32>     _leftRight;
		GLuint _shaderProgram;
		
	};//end Class
}//end Namespace
#endif