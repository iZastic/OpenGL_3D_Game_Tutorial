#include "Loader.h"

Loader::Loader()
{
	vaos.clear();
	vbos.clear();
}


Loader::~Loader()
{
	while (vbos.size() > 0)
	{
		glDeleteBuffers(1, &vbos.back());
		vbos.pop_back();
	}

	while (vaos.size() > 0)
	{
		glDeleteVertexArrays(1, &vaos.back());
		vaos.pop_back();
	}
}


RawModel Loader::LoadToVAO(float positions[], int count)
{
	// create a new VAO
	GLuint vaoID = CreateVAO();
	// Store the data in an attribute list
	StoreDataInAttributeList(0, positions, count);
	UnbindVAO();
	return RawModel(vaoID, count);
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
	vaos.push_back(vaoID);
	// Bind the VAO to use it
	glBindVertexArray(vaoID);
	return vaoID;
}


void Loader::StoreDataInAttributeList(GLuint attribNumber, float data[], int count)
{
	GLuint vboID;
	// Create a new buffer
	glGenBuffers(1, &vboID);
	// Store the buffer in the list
	vbos.push_back(vboID);
	// Bind the buffer to use it
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	// Store the data in the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(data) * count, data, GL_STATIC_DRAW);
	// Tell OpenGL how and where to store this VBO in the VAO
	glVertexAttribPointer(attribNumber, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
}