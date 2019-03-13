#version 430 core

in vec2 fs_texCoord;

out vec4 frag_color;

uniform sampler2D tex;
//uniform sampler2D tex1;
//uniform sampler2D tex2;

void main()
{
	//frag_color = mix(texture(tex1, fs_texCoord), texture(tex2, fs_texCoord), 0.8);
	frag_color = texture(tex, fs_texCoord);
}