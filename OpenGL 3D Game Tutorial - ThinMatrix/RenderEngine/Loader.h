#ifndef LOADER_H
#define LOADER_H

#include <vector>
#include <string>
#include <GL\glew.h>
#include <glm\glm.hpp>
#include "../Models/RawModel.h"

class Loader
{
public:
	Loader();
	virtual ~Loader();

	RawModel LoadToVAO(std::vector<glm::vec3> vertices, std::vector<glm::vec2> textures, std::vector<glm::vec3> normals, std::vector<int> indices);
	GLuint LoadTexture(const std::string& fileName, bool repeat = false);
	inline void UnbindVAO() { glBindVertexArray(0); }
private:
	std::vector<GLuint> m_vaos;
	std::vector<GLuint> m_vbos;
	std::vector<GLuint> m_textures;
	GLuint CreateVAO();
	void StoreDataInAttributeList(GLuint attribNumber, int attribSize, void* data, int dataSize);
	void BindIndicesBuffer(int* indices, int& count);
};

#endif // LOADER_H