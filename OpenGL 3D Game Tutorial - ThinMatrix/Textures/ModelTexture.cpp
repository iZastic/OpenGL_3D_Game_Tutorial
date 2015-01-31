#include "ModelTexture.h"


ModelTexture::ModelTexture(GLuint id)
	: m_textureID(id)
{
}


ModelTexture::~ModelTexture()
{
}



GLuint ModelTexture::GetTextureID()
{
	return m_textureID;
}