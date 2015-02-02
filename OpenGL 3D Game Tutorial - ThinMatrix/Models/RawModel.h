#ifndef RAWMODEL_H
#define RAWMODEL_H

#include <GL\glew.h>

class RawModel
{
public:
	RawModel(GLuint& vaoID, int& vertexCount);
	virtual ~RawModel();

	inline GLuint GetVaoID() { return m_vaoID; }
	inline int GetVertexCount() { return m_vertexCount; }
private:
	GLuint m_vaoID;
	int m_vertexCount;
};

#endif // RAWMODEL_H