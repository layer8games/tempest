#version 430 core

layout (location = 0) in vec4 position;
//color not used
layout (location = 2) in vec2 texCoord;

uniform mat4 model_mat;
uniform mat4 view_mat;
uniform mat4 projection_mat;

out vec4 fs_texCoord;

void main(void)
{
	gl_Position = projection_mat * view_mat * model_mat * position;
	fs_texCoord = texCoord;
}