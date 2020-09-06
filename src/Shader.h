#ifndef __SHADER_H__
#define __SHADER_H__
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>

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
	void setMat4(const std::string& name,const glm::mat4& mat4) const;
	void setVec3(const std::string& name,const glm::vec3& value) const;
private:
	std::string m_basePath;
};
#endif
