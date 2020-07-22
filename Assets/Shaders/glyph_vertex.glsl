#version 430 core

layout (location = 0) in vec2 position; // in local space
layout (location = 1) in vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 fs_texCoord;

void main()
{
    fs_texCoord = texCoord;

    gl_Position = projection * view * model * vec4(position, 0.0, 0.0);
}