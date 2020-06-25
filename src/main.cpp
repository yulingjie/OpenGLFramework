#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Shader.h"
#include "config.h"
#include <vector>
#include <glm/ext.hpp>
#include "Mesh.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void processInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Framework", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	std::string basePath = ".";

#ifdef USE_CURRENT_PATH
	basePath = CURRENT_PATH;
#endif
	// load model
	const std::string cube_path = basePath + "/assets/objs/cube.obj";
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(cube_path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "load mesh error" << importer.GetErrorString() << std::endl;
		return -1;
	}
	//std::vector<Mesh> meshes;
	
	Mesh cube = Mesh::processMesh(scene->mMeshes[0], scene);
	


	
	
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * cube.vertices.size(),&cube.vertices[0], GL_STATIC_DRAW);

	GLuint IndexVBO;
	glGenBuffers(1, &IndexVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * cube.indices.size(), &cube.indices[0], GL_STATIC_DRAW);
	
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);

	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
	
	Shader ourShader(basePath.c_str());
	ourShader.compile("/assets/shaders/vertex.glsl", "/assets/shaders/fragment.glsl");
	
	glm::mat4 view = glm::lookAt(glm::vec3(5.f, 5.f, 5.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
	glm::mat4 proj = glm::perspective(glm::radians(45.f), 800.f / 600.f, 0.1f, 100.0f);
	ourShader.use();


	ourShader.setMat4("projection", proj);
	glm::vec3 cubePosition = glm::vec3(0.0f, 0.0f, -10.0f);
	glm::mat4 model = glm::mat4(1.0f);
	//model = glm::translate(model, cubePosition);
	ourShader.setMat4("model", model);
	ourShader.setMat4("view",view);
	ourShader.setVec3("objectColor", glm::vec3(0.4, 0.4, 0.4));
	ourShader.setVec3("lightColor", glm::vec3(1, 1, 1));

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		// rendering commands
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glDrawElements(GL_TRIANGLES,cube.indices.size(), GL_UNSIGNED_INT, (const void*)(0));
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

