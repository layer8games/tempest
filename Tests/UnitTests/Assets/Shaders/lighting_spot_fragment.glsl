#version 430 core

struct Material
{
	vec4 ambient;
	sampler2D diffuseMap;
	vec4 specular;
	float shininess;
};

struct SpotLight
{
	vec4 position;
	vec4 direction;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;

	float constant;
	float linear;
	float exponent;

	float cosInnerCone;
	float cosOuterCone;
	bool on;
};

in vec2 fs_texCoord;
in vec4 fs_normal;
in vec4 fs_position;

uniform vec4 view_position;
uniform SpotLight light;
uniform Material material;

vec4 calcSpotlight();

out vec4 frag_color;

void main()
{
	//Ambient
	vec4 ambient = light.ambient * material.ambient * vec4(texture(material.diffuseMap, fs_texCoord));

	vec4 spotColor = vec4(0.0f);

	if(light.on)
		spotColor = calcSpotlight();
	
	frag_color = (ambient + diffuse + specular);
	frag_color.w = 1.0f;
}

vec4 calcSpotlight()
{
	vec4 lightDirection = normalize(light.position - fs_position);
	vec4 spotDirection = normalize(light.direction);

	float cosDirection = dot(-lightDirection, spotDirection);
	float spotIntensity = smoothstep(light.cosOuterCone, light.cosInnerCone, cosDirection);

	//Diffuse
	vec4 normal = normalize(fs_normal);
	float NDotL = max(dot(normal, lightDirection), 0.0f);
	vec4 diffuse = light.diffuse * NDotL * vec4(texture(material.diffuseMap, fs_texCoord));

	//Specular (Blinn-Phong)
	vec4 viewDirection = normalize(view_position - fs_position);
	vec4 halfDirection = normalize(lightDirection + viewDirection);
	float NDotH = max(dot(normal, halfDirection), 0.0f);
	vec4 specular = light.specular * material.specular * pow(NDotH, material.shininess);

	float d = length(light.position - fs_position);
	float attenuation = 1.0f / (light.constant + light.linear * d + light.exponent * (d * d));

	diffuse *= attenuation * spotIntensity;
	specular *= attenuation * spotIntensity;

	return (diffuse + specular);
}