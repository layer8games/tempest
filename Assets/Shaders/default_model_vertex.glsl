#version 430 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texCoord;

uniform mat4 world_transform;
uniform mat4 view;
uniform mat4 projection;

out vec2 fs_texCoord;

void main()
{
    gl_Position = projection * view * world_transform * position;
    fs_texCoord = texCoord;
}