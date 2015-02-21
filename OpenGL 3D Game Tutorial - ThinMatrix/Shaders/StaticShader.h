#ifndef STATICSHADER_H
#define STATICSHADER_H

#include <string>
#include "ShaderProgram.h"
#include "../Entities/Camera.h"
#include "../Entities/Light.h"

class StaticShader : public ShaderProgram
{
public:
	StaticShader(const std::string& fileName);
	virtual ~StaticShader();

	void LoadTransformMatrix(glm::mat4& matrix);
	void LoadProjectionMatrix(glm::mat4& matrix);
	void LoadViewMatrix(Camera& camera);
	void LoadLight(Light& light);
private:
	GLuint location_TransformMatrix;
	GLuint location_ProjectionMatrix;
	GLuint location_ViewMatrix;
	GLuint location_lightPosition;
	GLuint location_lightColor;
protected:
	void BindAttributes();
	void GetAllUniformLocations();
};

#endif // STATICSHADER_H