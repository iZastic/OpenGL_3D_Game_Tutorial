#ifndef STATICSHADER_H
#define STATICSHADER_H

#include <string>
#include "ShaderProgram.h"

class StaticShader : public ShaderProgram
{
public:
	StaticShader(const std::string& fileName);
	virtual ~StaticShader();

	void LoadTransformMatrix(glm::mat4 matrix);
private:
	GLuint location_TransformMatrix;
protected:
	void BindAttributes();
	void GetAllUniformLocations();
};

#endif // STATICSHADER_H