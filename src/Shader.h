#ifndef __SHADER_H__
#define __SHADER_H__
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	GLuint ID;

	Shader(const char* basePath);
	void compile(const char* vertexPath, const char* fragmentPath);
	void use();

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
private:
	std::string m_basePath;
};
#endif