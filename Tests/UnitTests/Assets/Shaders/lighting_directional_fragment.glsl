#version 430 core

struct Material
{
	vec3 ambient;
	sampler2D diffuseMap;
	vec3 specular;
	float shininess;
};

struct DirecitonalLight
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec2 fs_texCoord;
in vec4 fs_normal;
in vec4 fs_position;

uniform vec3 view_position;
uniform DirecitonalLight light;
uniform Material material;
uniform bool has_texture = false;

out vec4 frag_color;

void main()
{
	//Ambient
	vec3 ambient = light.ambient * material.ambient;

	vec3 fsNormal = vec3(fs_normal.x, fs_normal.y, fs_normal.z);
	vec3 fsPosition = vec3(fs_position.x, fs_normal.y, fs_normal.z);

	//Diffuse
	vec3 normal = normalize(fsNormal);
	vec3 lightDirection = normalize(-light.direction);
	float NDotL = max(dot(normal, lightDirection), 0.0f);
	vec3 diffuse = light.diffuse * NDotL * vec3(texture(material.diffuseMap, fs_texCoord));

	//Specular (Blinn-Phong)
	vec3 viewDirection = normalize(view_position - fsPosition);
	vec3 halfDirection = normalize(lightDirection + viewDirection);
	float NDotH = max(dot(normal, halfDirection), 0.0f);
	vec3 specular = light.specular * material.specular * pow(NDotH, material.shininess);
	
	frag_color = vec4(ambient + diffuse + specular, 1.0f);
}