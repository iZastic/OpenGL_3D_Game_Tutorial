#include "OBJLoader.h"
#include <stdio.h>

RawModel OBJLoader::LoadObjModel(const std::string& fileName, Loader& loader)
{
	// Open the file as read only
	FILE* file;
	if (fopen_s(&file, ("../res/models/" + fileName + ".obj").c_str(), "r") != 0)
	{
		printf("Failed to open: %s\n", fileName);
	}

	// Storage variables
	std::vector<float> vertices, texturesArray, normalsArray;
	std::vector<glm::vec2> textures;
	std::vector<glm::vec3> normals;
	std::vector<int> indices;

	char *type, *token, *stop = 0;
	char line[256];
	while (fgets(line, 256, file) != NULL)
	{
		token = NULL;
		type = strtok_s(line, " ", &token);
		// V is vertex points
		if (type[0] == 'v' && type[1] == NULL)
		{
			// Store a new vertex
			vertices.push_back(strtof(token, &stop));
			token = stop + 1; // Move to the next value
			vertices.push_back(strtof(token, &stop));
			token = stop + 1; // Move to the next value
			vertices.push_back(strtof(token, &stop));
		}
		// VT is vertex texture coordinates
		else if (type[0] == 'v' && type[1] == 't')
		{
			double x = strtod(token, &stop);
			token = stop + 1; // Move to the next value
			double y = strtod(token, &stop);
			// Store a new texture
			textures.push_back(glm::vec2(x, y));
		}
		else if (type[0] == 'v' && type[1] == 'n')
		{
			double x = strtod(token, &stop);
			token = stop + 1; // Move to the next value
			double y = strtod(token, &stop);
			token = stop + 1; // Move to the next value
			double z = strtod(token, &stop);
			// Store a new normal
			normals.push_back(glm::vec3(x, y, z));
		}
		// F is the index list for faces
		else if (type[0] == 'f')
		{
			if (indices.size() == 0)
			{
				// Set the size of the array
				texturesArray.resize((vertices.size() / 3) * 2);
				normalsArray.resize(vertices.size());
			}
			// Process set of vertex data
			ProcessVertices(token, indices, textures, texturesArray, normals, normalsArray);
		}
	}
	fclose(file);

	return loader.LoadToVAO(vertices.data(), indices.data(), texturesArray.data(), vertices.size(), indices.size(), texturesArray.size());
}


void OBJLoader::ProcessVertices(char* vertexData, std::vector<int>& indices, std::vector<glm::vec2>& textures,
	std::vector<float>& texturesArray, std::vector<glm::vec3>& normals, std::vector<float>& normalsArray)
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
		glm::vec2 texture = textures[strtol(vertexData, &stop, 10) - 1];
		texturesArray[vertexPointer * 2] = texture.x;
		texturesArray[vertexPointer * 2 + 1] = 1 - texture.y;
		vertexData = stop + 1; // Move to the next value
		// Get and store normal points
		glm::vec3 normal = normals[strtol(vertexData, &stop, 10) - 1];
		normalsArray[vertexPointer * 3] = normal.x;
		normalsArray[vertexPointer * 3 + 1] = normal.y;
		normalsArray[vertexPointer * 3 + 2] = normal.z;
		vertexData = stop + 1; // Move to the next value
	}

}
