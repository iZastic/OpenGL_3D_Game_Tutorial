#ifndef LOADER_H
#define LOADER_H

#include "RawModel.h"
#include <GL\glew.h>
#include <vector>

class Loader
{
public:
	Loader();
	virtual ~Loader();

	RawModel LoadToVAO(float positions[], int count);
	void UnbindVAO();
private:
	std::vector<GLuint> vaos;
	std::vector<GLuint> vbos;
	GLuint CreateVAO();
	void StoreDataInAttributeList(GLuint attribNumber, float data[], int count);
};

#endif // LOADER_H