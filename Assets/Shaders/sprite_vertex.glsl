#version 430 core

layout (location = 0) in vec4 position; // in local space
layout (location = 1) in vec2 texCoord;
layout (location = 3) in vec4 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 fs_texCoord;
out vec4 fs_normal;
out vec4 fs_position;

void main()
{
	fs_normal = mat4(transpose(inverse(model))) * normal;
	fs_position = model * position;

	fs_texCoord = texCoord;
	gl_Position = projection * view * model * position;
}