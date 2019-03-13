#version 430 core

struct Material
{
	vec4 ambient;
	sampler2D diffuseMap;
	vec4 specular;
	float shininess;
};

struct PointLight
{
	vec4 position;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;

	float constant;
	float linear;
	float exponent;
};

in vec2 fs_texCoord;
in vec4 fs_normal;
in vec4 fs_position;

uniform vec4 view_position;
uniform PointLight light;
uniform Material material;

out vec4 frag_color;

void main()
{
	//Ambient
	vec4 ambient = light.ambient * material.ambient * vec4(texture(material.diffuseMap, fs_texCoord));

	//Diffuse
	vec4 normal = normalize(fs_normal);
	vec4 lightDirection = normalize(light.position - fs_position);
	float NDotL = max(dot(normal, lightDirection), 0.0f);
	vec4 diffuse = light.diffuse * NDotL * vec4(texture(material.diffuseMap, fs_texCoord));

	//Specular (Blinn-Phong)
	vec4 viewDirection = normalize(view_position - fs_position);
	vec4 halfDirection = normalize(lightDirection + viewDirection);
	float NDotH = max(dot(normal, halfDirection), 0.0f);
	vec4 specular = light.specular * material.specular * pow(NDotH, material.shininess);

	float d = length(light.position - fs_position);
	float attenuation = 1.0f / (light.constant + light.linear * d + light.exponent * (d * d));

	diffuse *= attenuation;
	specular *= attenuation;
	
	frag_color = (ambient + diffuse + specular);
	frag_color.w = 1.0f;
}