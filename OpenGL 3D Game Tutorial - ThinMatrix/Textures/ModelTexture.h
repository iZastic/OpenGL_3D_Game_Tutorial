#ifndef MODELTEXTURE_H
#define MODELTEXTURE_H

#include <GL\glew.h>

class ModelTexture
{
public:
	ModelTexture(GLuint id);
	virtual ~ModelTexture();

	GLuint GetTextureID();
private:
	GLuint m_textureID;
};

#endif // MODELTEXTURE_H