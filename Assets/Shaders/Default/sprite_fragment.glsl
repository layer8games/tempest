#version 430 core

in vec2 fs_text_coord;

uniform sampler2D tex;
uniform vec4 sprite_color;

out vec4 color;

void main()
{
	vec4 sampled = texture(tex, fs_text_coord);
	color = sprite_color * sampled;
}