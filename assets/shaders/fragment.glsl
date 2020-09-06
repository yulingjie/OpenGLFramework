#version 330 core
out vec4 FragColor;
in vec4 OutColor;
in vec3 Normal;
void main()
{
    FragColor = OutColor;
}
