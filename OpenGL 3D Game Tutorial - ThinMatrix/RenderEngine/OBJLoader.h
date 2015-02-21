#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <string>
#include <vector>
#include <glm\glm.hpp>
#include "Loader.h"
#include "../Models/RawModel.h"

class OBJLoader
{
public:
	static RawModel LoadObjModel(const std::string& fileName, Loader& loader);
private:
	static void ProcessVertices(char* vertexData, std::vector<int>& indices, std::vector<glm::vec2>& tempTextures,
		std::vector<glm::vec2>& textures, std::vector<glm::vec3>& tempNormals, std::vector<glm::vec3>& normals);
};

#endif // OBJLOADER_H