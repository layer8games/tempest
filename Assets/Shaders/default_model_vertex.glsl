#version 430 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texCoord;
layout (location = 3) in vec4 normal;

uniform mat4 mvp_transform;
uniform mat4 model_transform;

out vec2 fragment_texCoord;
out vec3 fragment_normal;
out vec3 fragment_position;

void main()
{
    fragment_texCoord = texCoord;
    
    fragment_normal = vec3(mvp_transform * normal);
    normalize(fragment_normal);
    
    fragment_position = vec3(model_transform * position);

    gl_Position = mvp_transform * position;
}