#version 430 core

in vec2 fragment_texCoord;
in vec3 fragment_normal;
in vec3 fragment_position;

uniform sampler2D tex;
uniform vec3 ambient_light_color;
uniform vec4 color;
uniform vec3 directional_light_position;

out vec4 frag_color;

void main()
{
    // ambient
    float ambientFactor = 0.3;
    vec3 ambient = ambient_light_color * ambientFactor;
    
    // diffuse
    vec3 lightDirection = normalize(directional_light_position - fragment_position);
    float normal_dot_light = max(dot(fragment_normal, lightDirection), 0.0);
    vec3 diffuse = ambient_light_color * normal_dot_light;
    // diffuse = vec3(0.0);

    // specular
    vec3 specular = vec3(0.0);

    frag_color = vec4(ambient + diffuse + specular, 1.0);
}
