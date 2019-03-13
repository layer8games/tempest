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
		"}