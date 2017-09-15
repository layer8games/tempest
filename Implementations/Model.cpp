#include <Engine/Model.h>

namespace KillerEngine
{
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
	Model::Model(void) : _shaderProgram(0), _numVertices(0), _vertices()
	{
		_InitShader();
	}

	Model::Model(std::vector<Vertex3D> vertices) : _shaderProgram(0), _numVertices(0), _vertices(vertices)
	{
		_InitShader();
	}

	Model::~Model(void)
	{  }

//==========================================================================================================================
//
//Model Functions
//
//==========================================================================================================================
	void Model::Render(KM::Vector3& pos)
	{	
		if(_shaderProgram == 0)
		{
			ErrorManager::Instance()->SetError(EC_OpenGL_Shader, "Model: NO shader initialized when render was attempted");
			return;
		}

		//Renderer::Instance()->AddToBatch(*this);
	}

	void Model::_InitShader(void)
	{
		const GLchar* vertexShaderSource[] =
		{
			"#version 430 core															\n"

			"layout (location = 0) in vec4 vertice; 									\n"
			"layout (location = 1) in vec4 color;										\n"

			"uniform mat4 projection_mat;												\n"
			"uniform mat4 translation_mat;												\n"

			"out vec4 fs_color;															\n"

			"void main(void)															\n"
			"{ 																			\n"
			"	gl_Position =  vertice;				\n"
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
		_shaderProgram = glCreateProgram();
		glAttachShader(_shaderProgram, vertexShaderProgram);
		glAttachShader(_shaderProgram, fragmentShaderProgram);
		glLinkProgram(_shaderProgram);

		//===== Error checking =====
		GLint isLinked = 0; 
		glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &isLinked);

		if(isLinked == GL_FALSE)
		{
			string errorMessage("Compile Error in Model\n");
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

		//===== clean up =====
		glDeleteProgram(vertexShaderProgram);
		glDeleteProgram(fragmentShaderProgram);
	}

}//end namespace