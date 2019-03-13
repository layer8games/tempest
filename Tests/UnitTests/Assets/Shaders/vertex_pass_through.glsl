#version 430 core

layout (location = 0) in vec4 position; // in local space
layout (location = 1) in vec2 texCoord;

out vec2 fs_texCoord;

void main()
{
	gl_Position = position;
	fs_texCoord = texCoord;
}