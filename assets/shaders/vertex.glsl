#version 330 core

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};
uniform Material material;
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;


uniform vec3 objectColor;
uniform vec3 lightColor;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 OutColor;
out vec3 Normal;
void main()
{
	float ambientStrength = 0.2;
	vec3 ambient = ambientStrength * lightColor;
	vec3 result = ambient * objectColor;
	OutColor = vec4(result,1.0);
	gl_Position = projection * view * model *  vec4(aPos, 1.0);
	Normal = aNormal;
}