#include "OBJLoader.h"
#include <stdio.h>
#include <time.h>

RawModel OBJLoader::LoadObjModel(const std::string& fileName, Loader& loader)
{
	clock_t startTime = clock();
	// Open the file as read only
	FILE* file;
	if (fopen_s(&file, ("../res/models/" + fileName + ".obj").c_str(), "r") != 0)
	{
		printf("Failed to open: %s\n", fileName);
	}

	// Storage variables
	std::vector<glm::vec2> textures, tempTextures;
	std::vector<glm::vec3> vertices, normals, tempNormals;
	std::vector<int> indices;

	char *type, *token, *stop = 0;
	double x, y, z;
	char line[256];
	while (fgets(line, 256, file) != NULL)
	{
		token = NULL;
		type = strtok_s(line, " ", &token);
		// V is vertex points
		if (type[0] == 'v' && type[1] == NULL)
		{
			x = strtod(token, &stop);
			token = stop + 1; // Move to the next value
			y = strtod(token, &stop);
			token = stop + 1; // Move to the next value
			z = strtod(token, &stop);
			// Store a new vertex
			vertices.push_back(glm::vec3(x, y, z));
		}
		// VT is vertex texture coordinates
		else if (type[0] == 'v' && type[1] == 't')
		{
			x = strtod(token, &stop);
			token = stop + 1; // Move to the next value
			y = 1 - strtod(token, &stop);
			// Store a new texture
			tempTextures.push_back(glm::vec2(x, y));
		}
		else if (type[0] == 'v' && type[1] == 'n')
		{
			x = strtod(token, &stop);
			token = stop + 1; // Move to the next value
			y = strtod(token, &stop);
			token = stop + 1; // Move to the next value
			z = strtod(token, &stop);
			// Store a new normal
			tempNormals.push_back(glm::vec3(x, y, z));
		}
		// F is the index list for faces
		else if (type[0] == 'f')
		{
			if (indices.size() == 0)
			{
				// Set the size of the array
				textures.resize(vertices.size());
				normals.resize(vertices.size());
			}
			// Process set of vertex data
			ProcessVertices(token, indices, tempTextures, textures, tempNormals, normals);
		}
	}
	fclose(file);

	printf("Load time: %dms\n", clock() - startTime);
	return loader.LoadToVAO(vertices, textures, normals, indices);
}


void OBJLoader::ProcessVertices(char* vertexData, std::vector<int>& indices, std::vector<glm::vec2>& tempTextures,
	std::vector<glm::vec2>& textures, std::vector<glm::vec3>& tempNormals, std::vector<glm::vec3>& normals)
{
	char *stop;
	int vertexPointer;
	for (unsigned int i = 0; i < 3; i++)
	{
		// Get and store index
		vertexPointer = strtol(vertexData, &stop, 10) - 1;
		indices.push_back(vertexPointer);
		vertexData = stop + 1; // Move to the next value
		// Get and store texture points
		textures[vertexPointer] = tempTextures[strtol(vertexData, &stop, 10) - 1];
		vertexData = stop + 1; // Move to the next value
		// Get and store normal points
		normals[vertexPointer] = tempNormals[strtol(vertexData, &stop, 10) - 1];
		vertexData = stop + 1; // Move to the next value
	}
}
