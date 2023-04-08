#include <iostream>

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
bool DoTheImportThing(const std::string& pFile)
{
	// Create an instance of the Importer class
	Assimp::Importer importer;
	// And have it read the given file with some example postprocessing
	// Usually - if speed is not the most important aspect for you - you'll 
	// propably to request more postprocessing than we do in this example.
	const aiScene* scene = importer.ReadFile(pFile,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	// If the import failed, report it
	if (!scene)
	{
		std::cout << importer.GetErrorString() << std::endl;
		return false;
	}
	std::cout << "IMPORT SUCCESS" << std::endl;

	unsigned int meshNum(0);

	for (unsigned int i = 0; i < scene->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[i];
		meshNum += mesh->mNumVertices;
	}
	std::cout << meshNum << std::endl;

	return true;
}

int main()
{
	DoTheImportThing("D:/LearnOpenGL/Model/backpack/backpack.obj");
}