#version 430 core

in vec2 fs_texCoord;

out vec4 color;

uniform sampler2D text;
uniform vec4 text_color;

void main()
{
	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, fs_texCoord).r);
	color = vec4()
}