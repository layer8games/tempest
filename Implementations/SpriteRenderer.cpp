#include <Engine/SpriteRenderer.h>
#include <iostream>

using namespace KillerEngine;

//=======================================================================================================
//
//Constructor
//
//=======================================================================================================
SpriteRenderer::SpriteRenderer(void)
: 
_maxBatchSize(1000), 
_currentBatchSize(0),
_vertices(0),
_colors(0),
_dimensions(0),
_bottomTop(0),
_leftRight(0),
_renderingProgramColor(0),
_renderingProgramTexture(0),
_shader(0),
_shaderSetCount(0),
_drawCount(0)
{ 
	glGenVertexArrays(NUM_VOA, _vertexArrayObject);
	glBindVertexArray(_vertexArrayObject[0]);
}

SpriteRenderer::~SpriteRenderer(void)
{  }
//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
void SpriteRenderer::SetShader(GLuint shader)
{
	++_shaderSetCount;
	//std::cout << "Set Shader called " << _shaderSetCount << " times\r";

	Draw();
	_shader = shader;

	glUseProgram(_shader);

	Camera::Instance()->SetOrthographic();
	Camera::Instance()->SetUp(shader);
}
//==========================================================================================================================
//
//Private SpriteRenderer Functions
//
//==========================================================================================================================
//==========================================================================================================================
//
//Singleton Functions
//
//==========================================================================================================================
//=======================================================================================================
//Instance
//=======================================================================================================
shared_ptr<SpriteRenderer> SpriteRenderer::_instance{NULL};

shared_ptr<SpriteRenderer> SpriteRenderer::Instance(void) 
{
	if(_instance == NULL) 
	{ 
		_instance = shared_ptr<SpriteRenderer>(new SpriteRenderer()); 
	}
	return _instance;
}

//=======================================================================================================
//ShutDown
//=======================================================================================================
/*void SpriteRenderer::ShutDown(void) {
	delete _instance;
	glDeleteVertexArrays(1, &_vertexArrayObject);
	glDeleteProgram(_renderingProgram);
	glDeleteVertexArrays(1, &_vertexArrayObject);
}*/


//=======================================================================================================
//AddToBatch
//=======================================================================================================

void SpriteRenderer::AddToBatch(const KM::Vector2& pos, F32 w, F32 h, const Color& c)
{

	if(_currentBatchSize + 1 >= _maxBatchSize) 
	{ 
		Draw(); 
	}

	_vertices.push_back(pos.GetX());
	_vertices.push_back(pos.GetY());
	_vertices.push_back(pos.GetZ());
	_vertices.push_back(pos.GetW());
	
	_dimensions.push_back(w/2);
	_dimensions.push_back(h/2);

	_colors.push_back(c.GetRed());
	_colors.push_back(c.GetGreen());
	_colors.push_back(c.GetBlue());
	_colors.push_back(c.GetAlpha());
	
	++_currentBatchSize;
}

void SpriteRenderer::AddToBatch(const KM::Vector2& pos, F32 w, F32 h, const Color& c, U32 textureID)
{
	if(textureID != 0 && textureID != TextureManager::Instance()->GetCurrentTextureID())
	{
		Draw();
		TextureManager::Instance()->SetCurrentTextureID(textureID);
	}

	_bottomTop.push_back(0.0f);
	_bottomTop.push_back(0.0f);
	_leftRight.push_back(1.0f);
	_leftRight.push_back(1.0f);
	AddToBatch(pos, w, h, c);
}

void SpriteRenderer::AddToBatch(const KM::Vector2& pos, F32 w, F32 h, const Color& c, U32 textureID, 
							 const KM::Vector2& verticalLimit, const KM::Vector2& horizontalLimit)
{
	if(textureID != 0 && TextureManager::Instance()->GetCurrentTextureID() != textureID)
	{
		Draw();
		TextureManager::Instance()->SetCurrentTextureID(textureID);
	}
	
	_bottomTop.push_back(verticalLimit.GetX());
	_bottomTop.push_back(verticalLimit.GetY());
	_leftRight.push_back(horizontalLimit.GetX());
	_leftRight.push_back(horizontalLimit.GetY());
	AddToBatch(pos, w, h, c);
}

/*	
//==========================================================================================================================
//Soon to be removed. Keeping now for historical reasons
//==========================================================================================================================
void SpriteRenderer::AddToBatch(Model& m)
{
	

	std::vector<Vertex3D> modelVertices = m.GetVertices();

	for(auto i = modelVertices.begin(); i != modelVertices.end(); ++i)
	{
		_vertices.push_back((*i).position.GetX());
		_vertices.push_back((*i).position.GetY());
		_vertices.push_back((*i).position.GetZ());
		_vertices.push_back((*i).position.GetW());

		_colors.push_back((*i).color.GetRed());
		_colors.push_back((*i).color.GetGreen());
		_colors.push_back((*i).color.GetBlue());
		_colors.push_back((*i).color.GetAlpha());

		++_currentBatchSize;
	}
}
*/
//=======================================================================================================
//Draw
//=======================================================================================================

void SpriteRenderer::Draw(void)
{
	if(_currentBatchSize == 0) return;

	glBindVertexArray(_vertexArrayObject[0]);

	GLuint buffers[5];
	glGenBuffers(5, buffers);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * _vertices.size()), &_vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	
	glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * _colors.size()), &_colors[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);

	if(_dimensions.size() > 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
		glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * _dimensions.size()), &_dimensions[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);	
	}

	if(_bottomTop.size() > 0)
	{
		
		glEnable(GL_BLEND); 
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindBuffer(GL_ARRAY_BUFFER, buffers[3]);
		glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * _bottomTop.size()), &_bottomTop[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, NULL);

		glBindBuffer(GL_ARRAY_BUFFER, buffers[4]);
		glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * _leftRight.size()), &_leftRight[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	}
	
	glDrawArrays(GL_POINTS, 0, _currentBatchSize);

	//=====Reset All Containers and Counters=====
	_vertices.clear();
	_dimensions.clear();
	_colors.clear();
	_bottomTop.clear();
	_leftRight.clear();
	_currentBatchSize = 0;

	++_drawCount;

	std::cout << "Draw count: " << _drawCount << "\r";
}

/*
void SpriteRenderer::Draw(void)
{
	if(_currentBatchSize == 0) return;

	GLuint buffers[2];
	glGenBuffers(2, buffers);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * _vertices.size()), &_vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	
	glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * _colors.size()), &_colors[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	
	glDrawArrays(GL_TRIANGLES, 0, _currentBatchSize);

	//=====Reset All Containers and Counters=====
	_vertices.clear();
	_colors.clear();
	_currentBatchSize = 0;
}
*/
/*
void SpriteRenderer::Draw(void)
{
	static const GLfloat g_vertex_buffer_data[] = {
	    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
	    -1.0f,-1.0f, 1.0f,
	    -1.0f, 1.0f, 1.0f, // triangle 1 : end
	    1.0f, 1.0f,-1.0f, // triangle 2 : begin
	    -1.0f,-1.0f,-1.0f,
	    -1.0f, 1.0f,-1.0f, // triangle 2 : end
	    1.0f,-1.0f, 1.0f,
	    -1.0f,-1.0f,-1.0f,
	    1.0f,-1.0f,-1.0f,
	    1.0f, 1.0f,-1.0f,
	    1.0f,-1.0f,-1.0f,
	    -1.0f,-1.0f,-1.0f,
	    -1.0f,-1.0f,-1.0f,
	    -1.0f, 1.0f, 1.0f,
	    -1.0f, 1.0f,-1.0f,
	    1.0f,-1.0f, 1.0f,
	    -1.0f,-1.0f, 1.0f,
	    -1.0f,-1.0f,-1.0f,
	    -1.0f, 1.0f, 1.0f,
	    -1.0f,-1.0f, 1.0f,
	    1.0f,-1.0f, 1.0f,
	    1.0f, 1.0f, 1.0f,
	    1.0f,-1.0f,-1.0f,
	    1.0f, 1.0f,-1.0f,
	    1.0f,-1.0f,-1.0f,
	    1.0f, 1.0f, 1.0f,
	    1.0f,-1.0f, 1.0f,
	    1.0f, 1.0f, 1.0f,
	    1.0f, 1.0f,-1.0f,
	    -1.0f, 1.0f,-1.0f,
	    1.0f, 1.0f, 1.0f,
	    -1.0f, 1.0f,-1.0f,
	    -1.0f, 1.0f, 1.0f,
	    1.0f, 1.0f, 1.0f,
	    -1.0f, 1.0f, 1.0f,
	    1.0f,-1.0f, 1.0f
	};

glDrawArrays(GL_TRIANGLES, 0, 12*3);

static const GLfloat g_color_buffer_data[] = {
	    0.583f,  0.771f,  0.014f,
	    0.609f,  0.115f,  0.436f,
	    0.327f,  0.483f,  0.844f,
	    0.822f,  0.569f,  0.201f,
	    0.435f,  0.602f,  0.223f,
	    0.310f,  0.747f,  0.185f,
	    0.597f,  0.770f,  0.761f,
	    0.559f,  0.436f,  0.730f,
	    0.359f,  0.583f,  0.152f,
	    0.483f,  0.596f,  0.789f,
	    0.559f,  0.861f,  0.639f,
	    0.195f,  0.548f,  0.859f,
	    0.014f,  0.184f,  0.576f,
	    0.771f,  0.328f,  0.970f,
	    0.406f,  0.615f,  0.116f,
	    0.676f,  0.977f,  0.133f,
	    0.971f,  0.572f,  0.833f,
	    0.140f,  0.616f,  0.489f,
	    0.997f,  0.513f,  0.064f,
	    0.945f,  0.719f,  0.592f,
	    0.543f,  0.021f,  0.978f,
	    0.279f,  0.317f,  0.505f,
	    0.167f,  0.620f,  0.077f,
	    0.347f,  0.857f,  0.137f,
	    0.055f,  0.953f,  0.042f,
	    0.714f,  0.505f,  0.345f,
	    0.783f,  0.290f,  0.734f,
	    0.722f,  0.645f,  0.174f,
	    0.302f,  0.455f,  0.848f,
	    0.225f,  0.587f,  0.040f,
	    0.517f,  0.713f,  0.338f,
	    0.053f,  0.959f,  0.120f,
	    0.393f,  0.621f,  0.362f,
	    0.673f,  0.211f,  0.457f,
	    0.820f,  0.883f,  0.371f,
	    0.982f,  0.099f,  0.879f
	};

	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);


	// 2nd attribute buffer : colors
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glVertexAttribPointer(
	    1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
	    3,                                // size
	    GL_FLOAT,                         // type
	    GL_FALSE,                         // normalized?
	    0,                                // stride
	    (void*)0                          // array buffer offset
	);


}
*/