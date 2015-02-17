#include "OBJLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>

RawModel OBJLoader::LoadObjModel(const std::string& fileName, Loader& loader)
{
	// Open the file
	std::ifstream file;
	file.open("../res/models/" + fileName + ".obj");

	std::vector<float> verticesArray, texturesArray, normalsArray;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> textures;
	std::vector<glm::vec3> normals;
	std::vector<int> indices;

	if (file.is_open())
	{
		// Temporary read variable
		std::string line;
		std::vector<std::string> lineArray;
		// Load file and get a line
		while (std::getline(file, line))
		{
			// Split the string
			lineArray = SplitString(line, ' ');
			// V is vertex points
			if (lineArray[0] == "v")
			{
				// Store a new vertex (stod converts string to double)
				glm::vec3 vertex(std::stod(lineArray[1]), std::stod(lineArray[2]), std::stod(lineArray[3]));
				vertices.push_back(vertex);
			}
			// VT is vertex texture coordinates
			else if (lineArray[0] == "vt")
			{
				glm::vec2 uv(std::stod(lineArray[1]), std::stod(lineArray[2]));
				textures.push_back(uv);
			}
			else if (lineArray[0] == "vn")
			{
				// Store a new vertex (stod converts string to double)
				glm::vec3 vertex(std::stod(lineArray[1]), std::stod(lineArray[2]), std::stod(lineArray[3]));
				normals.push_back(vertex);
			}
			// F is the faces (indices)
			else if (lineArray[0] == "f")
			{
				if (verticesArray.size() == 0)
				{
					// Set the size of the array
					texturesArray.resize(vertices.size() * 2);
					normalsArray.resize(vertices.size() * 3);
				}
				// Process set of vertex data
				ProcessVertices(lineArray, indices, textures, texturesArray, normals, normalsArray);
			}
		}
		file.close();
	}
	else
	{
		std::cerr << "Unable to load model: " << fileName << std::endl;
	}

	for (glm::vec3 vertex : vertices)
	{
		verticesArray.push_back(vertex.x);
		verticesArray.push_back(vertex.y);
		verticesArray.push_back(vertex.z);
	}

	return loader.LoadToVAO(verticesArray.data(), indices.data(), texturesArray.data(), verticesArray.size(), indices.size(), texturesArray.size());
}


// This method is used to split strings
std::vector<std::string> OBJLoader::SplitString(const std::string& string, char delim)
{
	// This is a temporary vector
	std::vector<std::string> stringVector;
	// Create a stream from the string
	std::stringstream ss(string);
	std::string item;
	// Go through each word in the string
	while (std::getline(ss, item, delim))
		stringVector.push_back(item);

	return stringVector;
}


void OBJLoader::ProcessVertices(std::vector<std::string>& vertexDataArray, std::vector<int>& indices, std::vector<glm::vec2>& textures,
	std::vector<float>& texturesArray, std::vector<glm::vec3>& normals, std::vector<float>& normalsArray)
{
	for (unsigned int i = 1; i < 4; i++)
	{
		// Get vertex data from array
		std::vector<std::string> vertexData;
		vertexData = SplitString(vertexDataArray[i], '/');
		// Get and store index
		int vertexPointer = std::stoi(vertexData[0]) - 1;
		indices.push_back(vertexPointer);
		// Get and store texture points
		glm::vec2 texture = textures.at(std::stoi(vertexData[1]) - 1);
		texturesArray[vertexPointer * 2] = texture.x;
		texturesArray[vertexPointer * 2 + 1] = 1 - texture.y;
		// Get and store normal points
		glm::vec3 normal = normals.at(std::stoi(vertexData[2]) - 1);
		normalsArray.at(vertexPointer * 3) = normal.x;
		normalsArray.at(vertexPointer * 3 + 1) = normal.y;
		normalsArray.at(vertexPointer * 3 + 2) = normal.z;
	}

}
