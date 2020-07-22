#version 430 core

in vec2 fs_texCoord;

uniform sampler2D tex;
uniform vec4 ambient;
uniform vec4 color;

out vec4 frag_color;

void main()
{
    vec3 scatteredLight = vec3(ambient);
    vec3 rgb = min(color.rgb * scatteredLight, vec3(1.0));
    frag_color = vec4(rgb, color.a);
}
