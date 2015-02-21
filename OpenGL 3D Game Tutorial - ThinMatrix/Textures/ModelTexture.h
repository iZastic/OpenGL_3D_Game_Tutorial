#ifndef MODELTEXTURE_H
#define MODELTEXTURE_H

#include <GL\glew.h>

class ModelTexture
{
public:
	ModelTexture(GLuint id) : m_textureID(id) {}

	inline GLuint GetTextureID() { return m_textureID; }
	inline float GetShineDamper() { return m_shineDamper; }
	inline void SetShineDamper(float s) { m_shineDamper = s; }
	inline float GetShine() { return m_shine; }
	inline void SetShine(float s) { m_shine = s; }
private:
	GLuint m_textureID;
	float m_shineDamper = 1;
	float m_shine = 0;
};

#endif // MODELTEXTURE_H