#include <Engine/Shader.h>
#include <iostream>

using namespace KillerEngine;
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Shader::Shader(void)
:
_spriteShader(0),
_modelShader(0),
_vertexPath(),
_tessellationPath(),
_geometryPath(),
_fragmentPath()
{  }

Shader::~Shader(void)
{
	glUseProgram(0);
	glDeleteProgram(_spriteShader);
	glDeleteProgram(_modelShader);
}

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
shared_ptr<Shader> Shader::_instance = NULL;

shared_ptr<Shader> Shader::Instance(void)
{
	if(_instance == NULL)
	{
		_instance = shared_ptr<Shader>(new Shader());
	}

	return _instance;
}

void Shader::InitSpriteShader(void)
{
	//=====Vertex Shaders=====
	//This is used when only colors, not textures are used to render
	//a pirmitive
	GLchar* vertexShaderSource[] = 
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
		"	gl_Position = projection_mat * position;										\n"
		//"	gl_Position = perspective_mat * modelView_mat * position;						\n"
		"	gs_color = color;																\n"
		//Because the geometry shader just applies the dimensions directly, the dimensions 
		//have to be transformed by the projection_matrix. Maybe this could be done better. 
		"	gs_dimensions = projection_mat * vec4(dimensions.x, dimensions.y, 0.0, 0.0);	\n"
		"	gs_bottomTop = bottomTop;														\n"
		"	gs_leftRight = leftRight; 														\n"
		"}																					\n"
	};

	//=====Geomtry Shader=====
	GLchar* geometryShaderSource[] =
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
	GLchar* fragmentShaderSource[] = 
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
	glShaderSource(vertexShaderProgram, 1, vertexShaderSource, NULL);
	glCompileShader(vertexShaderProgram);

	geometryShaderProgram = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(geometryShaderProgram, 1, geometryShaderSource, NULL);
	glCompileShader(geometryShaderProgram);

	fragmentShaderProgram = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderProgram, 1, fragmentShaderSource, NULL);
	glCompileShader(fragmentShaderProgram);

	//=====Link=====
	_spriteShader = glCreateProgram();
	glAttachShader(_spriteShader, vertexShaderProgram);
	glAttachShader(_spriteShader, geometryShaderProgram);
	glAttachShader(_spriteShader, fragmentShaderProgram);
	glLinkProgram(_spriteShader);

	GLint isLinked = 0;
	glGetProgramiv(_spriteShader, GL_LINK_STATUS, &isLinked);

	//=====Error Checking=====
	if(isLinked == GL_FALSE)
	{
		string errorMessage("Compile Error in Sprite Shader\n");
		GLint maxLength = 0;
		glGetProgramiv(_spriteShader, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(_spriteShader, maxLength, &maxLength, &infoLog[0]);

		for(auto i = infoLog.begin(); i != infoLog.end(); ++i)
		{
			errorMessage += *i ;
		}

		ErrorManager::Instance()->SetError(EC_OpenGL_Shader, errorMessage);

		//The program is useless now. So delete it.
		glDeleteProgram(_spriteShader);

	}

	//=====Clean up=====
	glDeleteShader(vertexShaderProgram);
	glDeleteShader(geometryShaderProgram);
	glDeleteShader(fragmentShaderProgram);
}


void Shader::InitModelShader(void)
{
	const GLchar* vertexShaderSource[] =
	{
		"#version 430 core															\n"

		"layout (location = 0) in vec4 position;									\n"
		"layout (location = 1) in vec4 color; 										\n"
		"uniform mat4 modelView_mat; 												\n"
		"uniform mat4 viewport_mat; 												\n"

		"uniform mat4 projection_mat;												\n"
		
		"out vec4 fs_color;															\n"

		"void main(void)															\n"
		"{ 																			\n"
		"	gl_Position = projection_mat * viewport_mat * modelView_mat * position;	\n"
		"	fs_color = color;														\n"
		"}																			\n"
	};

	const GLchar* fragmentShaderSource[] =
	{
		"#version 430 core															\n"

		"in vec4 fs_color;															\n"
		"out vec4 color;															\n"

		"void main(void)															\n"
		"{																			\n"
		"	color = fs_color;														\n"
		"}																			\n"
	};

	//===== compile shader =====
	GLuint vertexShaderProgram;
	GLuint fragmentShaderProgram;

	vertexShaderProgram = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderProgram, 1, vertexShaderSource, NULL);
	glCompileShader(vertexShaderProgram);

	fragmentShaderProgram = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderProgram, 1, fragmentShaderSource, NULL);
	glCompileShader(fragmentShaderProgram);

	//===== Link program =====
	_modelShader = glCreateProgram();
	glAttachShader(_modelShader, vertexShaderProgram);
	glAttachShader(_modelShader, fragmentShaderProgram);
	glLinkProgram(_modelShader);

	//===== Error checking =====
	GLint isLinked = 0; 
	glGetProgramiv(_modelShader, GL_LINK_STATUS, &isLinked);

	if(isLinked == GL_FALSE)
	{
		string errorMessage("Compile Error in Model\n");
		GLint maxLength = 0;
		glGetProgramiv(_modelShader, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(_modelShader, maxLength, &maxLength, &infoLog[0]);

		for(auto i = infoLog.begin(); i != infoLog.end(); ++i)
		{
			errorMessage += *i ;
		}

		ErrorManager::Instance()->SetError(EC_OpenGL_Shader, errorMessage);

		//The program is useless now. So delete it.
		glDeleteProgram(_modelShader);
	}

	//===== clean up =====
	glDeleteProgram(vertexShaderProgram);
	glDeleteProgram(fragmentShaderProgram);
}

GLuint Shader::CreateShader(void)
{

	if(_vertexPath == "")
	{
		ErrorManager::Instance()->SetError(EC_OpenGL_Shader, "Unable to create shader. No vertex shader path set.");
	}

	if(_fragmentPath == "")
	{
		ErrorManager::Instance()->SetError(EC_OpenGL_Shader, "Unable to create shader. No fragment shader path set.");
	}

	
	GLuint finalProgram = glCreateProgram();
	GLuint vertexProgram = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentProgram = glCreateShader(GL_FRAGMENT_SHADER);

/*
	std::ifstream file(_vertexPath.c_str());
	if(!file)
	{
		ErrorManager::Instance()->SetError(EC_OpenGL_Shader, "Unable to open file path to shader: " + _vertexPath);
	}

	std::stringstream vertexData;
	vertexData << file.rdbuf();

	file.close();
*/


	GLint shaderSize;
	const string vertexString = _GetFileString(_vertexPath);
	const char* vertexCode = vertexString.c_str();
	shaderSize = vertexString.size();

	glShaderSource(vertexProgram, 1, (const GLchar**)&vertexCode, (GLint*)&shaderSize);
	glCompileShader(vertexProgram);

	const string fragmentString = _GetFileString(_fragmentPath);
	const char* fragmentCode = fragmentString.c_str();
	shaderSize = fragmentString.size();

	glShaderSource(fragmentProgram, 1, (const GLchar**)&fragmentCode, (GLint*)&shaderSize);
	glCompileShader(fragmentProgram);

	glAttachShader(finalProgram, vertexProgram);
	glAttachShader(finalProgram, fragmentProgram);
	
	glLinkProgram(finalProgram);

	//===== Error checking =====
	GLint isLinked = 0; 
	glGetProgramiv(finalProgram, GL_LINK_STATUS, &isLinked);

	if(isLinked == GL_FALSE)
	{
		string errorMessage("Compile Error in shader\n");
		GLint maxLength = 0;
		glGetProgramiv(finalProgram, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(finalProgram, maxLength, &maxLength, &infoLog[0]);

		for(auto i = infoLog.begin(); i != infoLog.end(); ++i)
		{
			errorMessage += *i ;
		}

		ErrorManager::Instance()->SetError(EC_OpenGL_Shader, errorMessage);

		//The program is useless now. So delete it.
		glDeleteProgram(finalProgram);
	}

	//===== clean up =====
	glDeleteProgram(vertexProgram);
	glDeleteProgram(fragmentProgram);

	std::cout << "final program is set to: " << finalProgram << "\n";

	return finalProgram;
}

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
GLuint Shader::GetSpriteShader(void)
{
	if(_spriteShader == 0)
	{
		InitSpriteShader();
	}

	return _spriteShader;
}

GLuint Shader::GetModelShader(void)
{
	if(_modelShader == 0)
	{
		InitModelShader();
	}

	return _modelShader;
}

string Shader::_GetFileString(string path)
{
	std::ifstream file {};
	std::stringstream shaderData;

	file.open(path.c_str());

	if(!file.is_open())
	{
		ErrorManager::Instance()->SetError(EC_OpenGL_Shader, "Unable to open file path to shader: " + path);
	}

	shaderData << file.rdbuf();

	file.close();

	string returnVal = shaderData.str();

	return returnVal;
}