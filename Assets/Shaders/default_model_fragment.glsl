
#version 430 core

in vec2 fragment_texCoord;
in vec3 fragment_normal;
in vec3 fragment_position;

uniform sampler2D tex;
uniform vec3 ambient_light_color;
uniform vec4 color;
uniform vec3 directional_light_position;
uniform vec3 camera_position;
uniform vec3 specular_factor;
uniform float specular_shine;

out vec4 out_color;

void main()
{
    // ambient
    float ambientFactor = 0.05;
    vec3 ambient = ambient_light_color * ambientFactor;
    
    // diffuse
    vec3 lightDirection = normalize(directional_light_position - fragment_position);
    float normal_dot_light = max(dot(fragment_normal, lightDirection), 0.0);
    vec3 diffuse = ambient_light_color * normal_dot_light;

    // specular (PHONG)
    vec3 viewDirection = normalize(camera_position - fragment_position);
    vec3 reflectionDirection = reflect(-lightDirection, fragment_normal);
    float reflection_dot_view = max(dot(reflectionDirection, viewDirection), 0.0);
    vec3 specular = ambient_light_color * specular_factor * pow(reflection_dot_view, specular_shine);

    out_color = vec4(ambient + diffuse + specular, 1.0);
}
