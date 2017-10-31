#include <Engine/SpriteBatch.h>

namespace KillerEngine
{
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
	SpriteBatch::SpriteBatch(void) : _maxBatchSize(0)
	{  }

	SpriteBatch::SpriteBatch(S32 size) : _maxBatchSize(size)
	{  }

	SpriteBatch::~SpriteBatch(void)
	{  }
}//end namespace