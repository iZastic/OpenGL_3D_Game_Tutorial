#ifndef STATICSHADER_H
#define STATICSHADER_H

#include <string>
#include "ShaderProgram.h"
#include "../Entities/Camera.h"

class StaticShader : public ShaderProgram
{
public:
	StaticShader(const std::string& fileName);
	virtual ~StaticShader();

	void LoadTransformMatrix(glm::mat4& matrix);
	void LoadProjectionMatrix(glm::mat4& matrix);
	void LoadViewMatrix(Camera& camera);
private:
	GLuint location_TransformMatrix;
	GLuint location_ProjectionMatrix;
	GLuint location_ViewMatrix;
protected:
	void BindAttributes();
	void GetAllUniformLocations();
};

#endif // STATICSHADER_H