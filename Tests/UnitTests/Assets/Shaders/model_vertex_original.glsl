#version 430 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

uniform mat4 model_mat;
uniform mat4 view_mat;
uniform mat4 projection_mat;

out vec4 fs_color;

void main(void)
{
	gl_Position = position;
	fs_color = color;
}