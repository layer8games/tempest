#version 430 core

uniform vec4 lightColor;

out vec4 frag_color;


void main()
{
	frag_color = lightColor;
}