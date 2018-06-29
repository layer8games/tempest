#version 430 core

uniform sampler2D tex;

in vec4 fs_color;
in vec2 fs_uvs;
out vec4 color;

void main(void)
{
	if(fs_uvs == vec2(0, 0))
	{ 
		color = fs_color; 
	}
	else 
	{ 
		color = texture(tex, fs_uvs); 
	}
}