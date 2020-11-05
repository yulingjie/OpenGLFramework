#version 330 core
out vec4 FragColor;
in vec3 OutColor;
in vec3 Normal;
in vec3 WorldPos;

uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 objectColor;
void main()
{
    vec3 ambient = OutColor;
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - WorldPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff* lightColor;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - WorldPos);
   
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0),16);
    vec3 specular = specularStrength * spec * lightColor *step(0.0,dot(lightDir, norm));
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);

}
