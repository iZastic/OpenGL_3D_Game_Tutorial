#include "RawModel.h"


RawModel::RawModel(GLuint& vaoID, int& vertexCount)
	: m_vaoID(vaoID), m_vertexCount(vertexCount)
{
}


RawModel::~RawModel()
{
}


GLuint RawModel::GetVaoID()
{
	return m_vaoID;
}


int RawModel::GetVertexCount()
{
	return m_vertexCount;
}