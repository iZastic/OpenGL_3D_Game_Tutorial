#include "Loader.h"
#include <iostream>
#include <cassert>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Loader::Loader()
{
	// Initialize the storage arrays
	m_vaos.clear();
	m_vbos.clear();
	m_textures.clear();
}


Loader::~Loader()
{
	// Loop through all the storage arrays and delete OpenGL variables

	while (m_vbos.size() > 0)
	{
		glDeleteBuffers(1, &m_vbos.back());
		m_vbos.pop_back();
	}

	while (m_vaos.size() > 0)
	{
		glDeleteVertexArrays(1, &m_vaos.back());
		m_vaos.pop_back();
	}

	while (m_textures.size() > 0)
	{
		glDeleteTextures(1, &m_textures.back());
		m_textures.pop_back();
	}
}


RawModel Loader::LoadToVAO(float vertices[], int indices[], float texCoords[], int vertCount, int indCount, int texCount)
{
	// create a new VAO
	GLuint vaoID = CreateVAO();
	BindIndicesBuffer(indices, indCount);
	// Store the data in attribute lists
	StoreDataInAttributeList(0, 3, vertices, vertCount);
	StoreDataInAttributeList(1, 2, texCoords, texCount);
	UnbindVAO();
	return RawModel(vaoID, vertCount);
}


GLuint Loader::LoadTexture(const std::string& fileName)
{
	GLuint texture;
	int width, height, numComponents;
	// Load image data
	stbi_uc* imageData = stbi_load(("../res/textures/" + fileName + ".png").c_str(), &width, &height, &numComponents, 4);

	if (imageData == NULL)
		std::cerr << "ERROR: texture loading failed for " << fileName << std::endl;

	// Generate and bind a OpenGL texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// How OpenGL will fill an area that's to big or to small
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Store the OpenGL texture data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	// Store the buffer in the list
	m_textures.push_back(texture);

	// Unload image data
	stbi_image_free(imageData);

	return texture;
}


void Loader::UnbindVAO()
{
	glBindVertexArray(0);
}


GLuint Loader::CreateVAO()
{
	GLuint vaoID;
	// Create a new VAO
	glGenVertexArrays(1, &vaoID);
	// Store the vao in the list
	m_vaos.push_back(vaoID);
	// Bind the VAO to use it
	glBindVertexArray(vaoID);
	return vaoID;
}


void Loader::StoreDataInAttributeList(GLuint attribNumber, int size, float data[], int& count)
{
	GLuint vboID;
	// Create a new buffer
	glGenBuffers(1, &vboID);
	// Store the buffer in the list
	m_vbos.push_back(vboID);
	// Bind the buffer to use it
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	// Store the data in the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(data) * count, data, GL_STATIC_DRAW);
	// Tell OpenGL how and where to store this VBO in the VAO
	glVertexAttribPointer(attribNumber, size, GL_FLOAT, GL_FALSE, 0, nullptr);
}


void Loader::BindIndicesBuffer(int indices[], int& count)
{
	GLuint vboID;
	// Generate a buffer and bind it for use
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
	// Store the indices in the buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * count, indices, GL_STATIC_DRAW);
}