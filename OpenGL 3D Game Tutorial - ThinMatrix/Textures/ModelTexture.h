#ifndef MODELTEXTURE_H
#define MODELTEXTURE_H

#include <GL\glew.h>

class ModelTexture
{
public:
	ModelTexture(GLuint id, float shine, float shineDamper)
		{ ModelTexture(id, false, false, shine, shineDamper); }
	ModelTexture(GLuint id, bool hasTransparency = false, bool useUpNormal = false, float shine = 0, float shineDamper = 1)
		: m_textureID(id), m_hasTransparency(hasTransparency), m_useUpNormal(useUpNormal),
		m_shine(shine), m_shineDamper(shineDamper){}

	inline GLuint GetTextureID() { return m_textureID; }
	inline float GetShineDamper() { return m_shineDamper; }
	inline void SetShineDamper(float s) { m_shineDamper = s; }
	inline float GetShine() { return m_shine; }
	inline void SetShine(float s) { m_shine = s; }
	inline bool GetHasTransparency() { return m_hasTransparency; }
	inline bool GetUseUpNormal() { return m_useUpNormal; }
private:
	GLuint m_textureID;
	bool m_hasTransparency;
	bool m_useUpNormal;
	float m_shineDamper;
	float m_shine;
};

#endif // MODELTEXTURE_H