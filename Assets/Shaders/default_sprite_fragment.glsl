#version 430 core

in vec2 fs_texCoord;

uniform sampler2D tex;
uniform bool has_texture;
uniform vec4 color;

out vec4 frag_color;

void main()
{
    if(has_texture) 
    {
        vec4 texColor = color * texture(tex, fs_texCoord);
        if(texColor.a < 0.01)
        {
            discard;
        }
        frag_color = texColor;
    }
    else
    {
        if(color.a < 0.01)
        {
            discard;
        }
        frag_color = color;
    }
}