#include <Engine/SpriteBatch.h>

namespace KillerEngine
{
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
	SpriteBatch::SpriteBatch(void) : _maxBatchSize(0), _currentSize(0), _shaderProgram(0)
	{  }

	SpriteBatch::SpriteBatch(S32 size) : _maxBatchSize(size), _currentSize(0), _shaderProgram(0)
	{  }

	SpriteBatch::~SpriteBatch(void)
	{  }
//==========================================================================================================================
//
//Batch Functions
//
//==========================================================================================================================
	void SpriteBatch::AddToBatch(GameObject2D* gameObject)
	{
		
		if(_currentSize + 1 >= _maxBatchSize) 
		{ 
			DrawBatch(); 
		}

		Sprite sprite gameObject->GetSprite();

		if(_shaderProgram != sprite.GetShader())
		{
			_shaderProgram = sprite.GetShader();
		}

		KM::Vector2 pos = gameObject->GetPosition();
		Color col = gameObject->GetColor();

		_vertices.push_back(pos.GetX());
		_vertices.push_back(pos.GetY());
		_vertices.push_back(pos.GetZ());
		_vertices.push_back(pos.GetW());
		
		_colors.push_back(col.GetRed());
		_colors.push_back(col.GetGreen());
		_colors.push_back(col.GetBlue());
		_colors.push_back(col.GetAlpha());

		_dimensions.push_back(gameObject.GetWidth()/2);
		_dimensions.push_back(gameObject.GetHeight()/2);

		if(sprite.GetTextureID() > 0)
		{
			if(TextureManager::Instance()->GetCurrentTextureID() != sprite.GetTextureID())
			{
				DrawBatch();
				TextureManager::Instance()->SetCurrentTextureID(sprite.GetTextureID());
			}

			KM::Vector2 bottomTop = sprite.GetUVBottomTop();
			KM::Vector2 leftRight = sprite.GetUVLeftRight();

			_bottomTop.push_back(bottomTop.GetX());
			_bottomTop.push_back(bottomTop.GetY());
			_leftRight.push_back(leftRight.GetX());
			_leftRight.push_back(leftRight.GetY());
		}
		
		++_currentSize;
	}

	void SpriteBatch::DrawBatch(void)
	{
		glUseProgram(_shaderProgram);
		//===== Camera will check that the current this shader is in use =====
		Camera::Instance()->SetOrthographic();
		Camera::Instance()->SetUp(_shaderProgram);

		glBindVertexArray(_vertexArrayObject[0]);

		GLuint buffersLocal[5];
		glGenBuffers(NUM_BUFFERS, buffersLocal);

		glBindBuffer(GL_ARRAY_BUFFER, buffersLocal[0]);
		glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * _vertices.size()), &_vertices[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
		
		glBindBuffer(GL_ARRAY_BUFFER, buffersLocal[1]);
		glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * _colors.size()), &_colors[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);

		glBindBuffer(GL_ARRAY_BUFFER, buffersLocal[2]);
		glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * _dimensions.size()), &_dimensions[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);

		if(_bottomTop.size() > 0)
		{
			
			glEnable (GL_BLEND); 
			glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindBuffer(GL_ARRAY_BUFFER, buffersLocal[3]);
			glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * _bottomTop.size()), &_bottomTop[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	
			glBindBuffer(GL_ARRAY_BUFFER, buffersLocal[4]);
			glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * _leftRight.size()), &_leftRight[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(4);
			glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 0, NULL);
		}

		glDrawArrays(GL_POINTS, 0, _currentSize);
		//=====Reset All Containers and Counters=====
		_vertices.clear();
		_dimensions.clear();
		_colors.clear();
		_bottomTop.clear();
		_leftRight.clear();
		_currentSize = 0;
	}
}//end namespace