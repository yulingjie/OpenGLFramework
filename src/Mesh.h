#ifndef  __MESH_H__
#define __MESH_H__
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include<assimp/mesh.h>
#include<assimp/scene.h>
struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};
struct Texture {
	unsigned int id;
	std::string type;
};

class Mesh {
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	Mesh() {}
	Mesh(const std::vector<Vertex>& vertices,
		const std::vector<unsigned int>& indices,
		const  std::vector<Texture>& textures);
public:
	//static std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	static Mesh processMesh(aiMesh* mesh, const aiScene* scene);
private:
	
};
#endif // ! __MESH_H__
