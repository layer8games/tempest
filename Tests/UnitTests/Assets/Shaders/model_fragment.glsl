#version 430 core

in vec4 fs_texCoord;
out vec4 color;

uniform sampler2D tex;

void main(void)
{
	color = texture(tex, fs_texCoord);
}