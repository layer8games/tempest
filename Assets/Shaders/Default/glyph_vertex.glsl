#version 430 core

layout (location = 0) in vec4 position; // in local space
layout (location = 1) in vec2 texCoord;

uniform vec4 text_offset;
uniform mat4 projection;

out vec2 fs_texCoord;

void main()
{
	fs_texCoord = texCoord;
	//vec4 newPos = vec4(position.x + text_offset.x, position.y, position.z, position.w);
	gl_Position = vec4(position.x + text_offset.x, position.y, position.z, position.w);
}