#include <Engine/Sprite.h>

namespace KillerEngine 
{
//==========================================================================================================================
//Static members
//==========================================================================================================================
	//GLuint Sprite::_shaderProgram = NULL;
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
	Sprite::Sprite(void) :  _bottomTop(0),
							_leftRight(0),
						    _textureID(0),
						    _shaderProgram(0)
	{
		_InitShader();
	}

	Sprite::~Sprite(void)
	{  }																	     

//==========================================================================================================================
//
//Operator overloads
//
//==========================================================================================================================
	Sprite& Sprite::operator=(Sprite& S)
	{
		_bottomTop = S.GetUVBottomTop();
		_leftRight = S. GetUVLeftRight();
		_textureID = S.GetTextureID();
		_characterData = S.GetCharData();
		_shaderProgram = S.GetShader();

		return *this;
	}

	Sprite& Sprite::operator=(std::shared_ptr<Sprite> S)
	{
		_bottomTop = S->GetUVBottomTop();
		_leftRight = S-> GetUVLeftRight();
		_textureID = S->GetTextureID();
		_characterData = S->GetCharData();
		_shaderProgram = S->GetShader();

		return *this;	
	}

//==========================================================================================================================
//
//Sprite Fucntions
//
//==========================================================================================================================
	void Sprite::SetTexture(U32 tID, const F32 top, const F32 bottom, const F32 right, const F32 left)
	{
		_textureID = tID;
		_bottomTop = KM::Vector2(bottom, top);
		_leftRight  = KM::Vector2(left, right);
	}

	void Sprite::Render(KM::Vector2& pos, F32 w, F32 h, Color& col)
	{
		if(_shaderProgram == 0)
		{
			ErrorManager::Instance()->SetError(EC_OpenGL_Shader, "Sprite: NO shader set when Render is called");
			return;
		}
		
		glUseProgram(_shaderProgram);
		//===== Camera will check that the current this shader is in use =====
		Camera::Instance()->SetOrthographic();
		Camera::Instance()->SetUp(_shaderProgram);
		
		glBindVertexArray(_vertexArrayObject[0]);

		GLuint 				 buffersLocal[5];
		glGenBuffers(NUM_BUFFERS, buffersLocal);

		std::vector<F32> vertices = { pos.GetX(), pos.GetY(), pos.GetZ(), pos.GetW() };
		std::vector<F32> colors = { col.GetRed(), col.GetGreen(), col.GetBlue(), col.GetAlpha() };
		std::vector<F32> dimensions = { w, h };

		glBindBuffer(GL_ARRAY_BUFFER, buffersLocal[0]);
		glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * vertices.size()), &vertices[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
		
		glBindBuffer(GL_ARRAY_BUFFER, buffersLocal[1]);
		glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * colors.size()), &colors[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);

		glBindBuffer(GL_ARRAY_BUFFER, buffersLocal[2]);
		glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * dimensions.size()), &dimensions[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);	
		

		if(_textureID > 0)
		{
			std::vector<F32> bottomTop = { _bottomTop.GetX(), _bottomTop.GetY() };
			std::vector<F32> leftRight = { _leftRight.GetX(), _leftRight.GetY() };

			TextureManager::Instance()->SetCurrentTextureID(_textureID);
			glEnable (GL_BLEND); 
			glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindBuffer(GL_ARRAY_BUFFER, buffersLocal[3]);
			glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * bottomTop.size()), &bottomTop[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	
			glBindBuffer(GL_ARRAY_BUFFER, buffersLocal[4]);
			glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * leftRight.size()), &leftRight[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(4);
			glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 0, NULL);
		}
		glDrawArrays(GL_POINTS, 0, 1);
	}

	void Sprite::Draw(int count)
	{
		glDrawArrays(GL_POINTS, 0, count);
	}

	void Sprite::_InitShader(void)
	{
		if(_shaderProgram != NULL) return;

		
		glGenVertexArrays(NUM_VOA, _vertexArrayObject);
		glBindVertexArray(_vertexArrayObject[0]);

		glGenBuffers(NUM_BUFFERS, _buffers);
		

		//=====Vertex Shaders=====
		//This is used when only colors, not textures are used to render
		//a pirmitive
		GLchar* _vertexShaderSource[] = 
		{
			"#version 430 core																	\n"
			
			"layout (location = 0) in vec4 position;											\n"
			"layout (location = 1) in vec4 color; 												\n"
			"layout (location = 2) in vec2 dimensions;											\n"
			"layout (location = 3) in vec2 bottomTop;											\n"
			"layout (location = 4) in vec2 leftRight; 											\n"

			"uniform mat4 projection_mat;														\n"
			"uniform mat4 translation_mat;														\n"
			//"uniform mat4 transform_mat;   														\n"
			
			"out vec4 gs_color;																	\n"
			"out vec4 gs_dimensions;															\n"
			"out vec2 gs_bottomTop;																\n"
			"out vec2 gs_leftRight;																\n"

			"void main(void) 																	\n"
			"{																					\n"
			"	gl_Position = projection_mat * translation_mat * position;						\n"
			//"	gl_Position = perspective_mat * modelView_mat * position;						\n"
			"	gs_color = color;																\n"
			"	gs_dimensions = projection_mat * vec4(dimensions.x, dimensions.y, 0.0, 0.0);	\n"
			"	gs_bottomTop = bottomTop;														\n"
			"	gs_leftRight = leftRight; 														\n"
			"}																					\n"
		};

		//=====Geomtry Shader=====
		GLchar* _geometryShaderSource[] =
		{
			"#version 430 core 																					\n"
			
			"layout(points) in; 																				\n"
			"layout(triangle_strip, max_vertices = 6) out;														\n"
			
			"in vec4 gs_color[]; 																				\n"
			"in vec4 gs_dimensions[]; 																			\n"
			"in vec2 gs_bottomTop[];																			\n"
			"in vec2 gs_leftRight[];																			\n"
			
			"out vec4 fs_color; 																				\n"
			"out vec2 fs_uvs; 																					\n"
			
			"void main()																						\n"
			"{																									\n"
			"	fs_color = gs_color[0]; 																		\n"
			//Right Bottom
			"	fs_uvs = vec2(gs_leftRight[0].y, gs_bottomTop[0].x);											\n"
			"	gl_Position = gl_in[0].gl_Position + vec4(-gs_dimensions[0].x, -gs_dimensions[0].y, 0, 0);		\n"
			" 	EmitVertex(); 																					\n"
			//Right Top
			"	fs_uvs = vec2(gs_leftRight[0].y, gs_bottomTop[0].y);											\n"
			"	gl_Position = gl_in[0].gl_Position + vec4(-gs_dimensions[0].x, gs_dimensions[0].y, 0.0, 0.0);	\n"
			"	EmitVertex(); 																					\n"
			//Left Bottom
			"	fs_uvs = vec2(gs_leftRight[0].x, gs_bottomTop[0].x);											\n"
			" 	gl_Position = gl_in[0].gl_Position + vec4(gs_dimensions[0].x, -gs_dimensions[0].y, 0.0, 0.0); 	\n"
			"	EmitVertex();				 																	\n"
			//Left Top
			"	fs_uvs = vec2(gs_leftRight[0].x, gs_bottomTop[0].y);											\n"
			"	gl_Position = gl_in[0].gl_Position + vec4(gs_dimensions[0].x, gs_dimensions[0].y, 0, 0); 		\n"
			"	EmitVertex(); 																					\n"
			
			"	EndPrimitive(); 																				\n"
			"}																									\n"
		};


		//=====Fragment Shaders=====
		//This is used when only colors, not textures are used to render
		//a pirmitive
		GLchar* _fragmentShaderSource[] = 
		{
			"#version 430 core																\n"
	
			"uniform sampler2D tex;															\n"

			"in vec4 fs_color;																\n"
			"in vec2 fs_uvs;"
			"out vec4 color;																\n"
			
			"void main(void) 																\n"
			"{																				\n"
			"	if(fs_uvs == vec2(0, 0)) { color = fs_color; }								\n"
			"	else { color = texture(tex, fs_uvs); } 										\n"
			"}																				\n"
		};


		//=====Compile Shaders=====
		GLuint vertexShaderProgram;
		GLuint geometryShaderProgram;
		GLuint fragmentShaderProgram;

		vertexShaderProgram = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShaderProgram, 1, _vertexShaderSource, NULL);
		glCompileShader(vertexShaderProgram);

		geometryShaderProgram = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometryShaderProgram, 1, _geometryShaderSource, NULL);
		glCompileShader(geometryShaderProgram);

		fragmentShaderProgram = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShaderProgram, 1, _fragmentShaderSource, NULL);
		glCompileShader(fragmentShaderProgram);

		//=====Link=====
		_shaderProgram = glCreateProgram();
		glAttachShader(_shaderProgram, vertexShaderProgram);
		glAttachShader(_shaderProgram, geometryShaderProgram);
		glAttachShader(_shaderProgram, fragmentShaderProgram);
		glLinkProgram(_shaderProgram);

		GLint isLinked = 0;
		glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &isLinked);

		//=====Error Checking=====
		if(isLinked == GL_FALSE)
		{
			string errorMessage("Compile Error in SqrSprite\n");
			GLint maxLength = 0;
			glGetProgramiv(_shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);

			//The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(_shaderProgram, maxLength, &maxLength, &infoLog[0]);

			for(auto i = infoLog.begin(); i != infoLog.end(); ++i)
			{
				errorMessage += *i ;
			}

			ErrorManager::Instance()->SetError(EC_OpenGL_Shader, errorMessage);

			//The program is useless now. So delete it.
			glDeleteProgram(_shaderProgram);

		}

		//=====Clean up=====
		glDeleteShader(vertexShaderProgram);
		glDeleteShader(geometryShaderProgram);
		glDeleteShader(fragmentShaderProgram);
	}

} //End namespace