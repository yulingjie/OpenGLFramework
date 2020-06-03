#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#include "config.h"
#include "tiny_obj_loader.h"

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

	tinyobj::ObjReader reader;
	tinyobj::ObjReaderConfig config;
	config.vertex_color = false;
	config.triangulate = false;
	if (!reader.ParseFromFile(basePath + "/assets/objs/cube.obj", config))
	{
		std::cout << "Error!! ParseFromFile Failed!!" << std::endl;
	}

	tinyobj::attrib_t attrib = reader.GetAttrib();
	const std::vector<tinyobj::shape_t> shapes = reader.GetShapes();
	tinyobj::shape_t cube = shapes[0];
	
	std::vector<int> indices;
	for (int i = 0; i < cube.mesh.indices.size(); ++i)
	{
		indices.push_back(cube.mesh.indices[i].vertex_index);
	}

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tinyobj::real_t) * (attrib.vertices.size()), attrib.vertices.data(), GL_STATIC_DRAW);
	
	GLuint IndexVBO;
	glGenBuffers(1, &IndexVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), indices.data(), GL_STATIC_DRAW);
	
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(tinyobj::real_t), (void*)0);
	glEnableVertexAttribArray(0);

//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
	
	Shader ourShader(basePath.c_str());
	ourShader.compile("/assets/shaders/vertex.glsl", "/assets/shaders/fragment.glsl");
	

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		// rendering commands
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ourShader.use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(),GL_UNSIGNED_INT,(void*)0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

