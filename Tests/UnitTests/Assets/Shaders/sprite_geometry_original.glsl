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
		"}