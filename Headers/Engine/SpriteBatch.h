/*========================================================================
A batch system for GameObject2D sprite based rendering. The ideas is that each 
map can have its own batch, or mulitple batches, and the batch wil controler
when a draw comman happens based on parameters that can be set within the 
class itself. 

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#ifndef SPRITE_BATCH_H
#define SPRITE_BATCH_H

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Sprite.h>

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

		void AddToBatch(void)
		{
			++_currentSize;
			if(_currentSize >= _maxBatchSize)
			{
				DrawBatch();
			}
		}

		void DrawBatch(void)
		{
			Sprite::Draw(_currentSize);
			_currentSize = 0;
		}

	private:
		S32 _maxBatchSize;
		S32 _currentSize;
		
	};//end Class
}//end Namespace
#endif