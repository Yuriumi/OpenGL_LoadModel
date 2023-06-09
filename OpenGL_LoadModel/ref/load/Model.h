#pragma once
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "../shader/Shader.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>


unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);
class Model
{
public:
	// Function
	Model(const char* path)
	{
		loadMode(path);
	}
	void Draw(Shader& shader);
private:
	// Mesh Data
	std::vector<Mesh> meshes;
	std::string directory;
	std::vector<Texture> textures_loaded;
	bool gammaCorrection;
	// Funciton
	void loadMode(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};

