#ifndef RAWMODEL_H
#define RAWMODEL_H

#include <GL\glew.h>

class RawModel
{
public:
	RawModel(GLuint vaoID, int vertexCount);
	virtual ~RawModel();

	GLuint GetVaoID();
	int GetVertexCount();
private:
	GLuint m_vaoID;
	int m_vertexCount;
};

#endif // RAWMODEL_H