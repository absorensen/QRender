#version 330 core
struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};

struct Light {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

out vec4 FragColor;

uniform Material material;
uniform Light light;
uniform vec3 objectColor;
uniform float time;
//uniform vec3 lightColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;

void main()
{
	vec3 ambient = light.ambient * vec3(texture(material.specular, TexCoords));

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(LightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse =  light.diffuse * diff * vec3(texture(material.specular, TexCoords));

	vec3 viewDir = normalize(-FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * (spec * vec3(texture(material.specular, TexCoords)));

	// emission
	vec3 emission = vec3(0.0f);
	if(texture(material.specular, TexCoords).r == 0.0)
	{
		emission = texture(material.emission, TexCoords).rgb;

		emission = texture(material.emission, TexCoords + vec2(0.0, time)).rgb;
		emission = emission * (sin(time) * 0.5 + 0.5) * 2.0;
	}

    FragColor = vec4(ambient + diffuse + specular + emission, 1.0);
}