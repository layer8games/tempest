"#version 430 core																\n"

		"uniform sampler2D tex;															\n"

		"in vec4 fs_color;																\n"
		"in vec2 fs_uvs;"
		"out vec4 color;																\n"
		
		"void main(void) 																\n"
		"{																				\n"
		"	if(fs_uvs == vec2(0, 0)) { color = fs_color; }								\n"
		"	else { color = texture(tex, fs_uvs); } 										\n"
		"}	