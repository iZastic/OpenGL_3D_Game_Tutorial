#ifndef STATICSHADER_H
#define STATICSHADER_H

#include <string>
#include "ShaderProgram.h"
#include "../Entities/Camera.h"
#include "../Entities/Light.h"

class BasicShader : public ShaderProgram
{
public:
	BasicShader(const std::string& fileName);
	virtual ~BasicShader();

	void LoadTransformMatrix(glm::mat4& matrix);
	void LoadProjectionMatrix(glm::mat4& matrix);
	void LoadViewMatrix(Camera& camera);
	void LoadLight(Light& light, float ambientLight);
	void LoadShineVariables(float shineDamper, float shine);
private:
	GLuint location_TransformMatrix;
	GLuint location_ProjectionMatrix;
	GLuint location_ViewMatrix;
	GLuint location_lightPosition;
	GLuint location_lightColor;
	GLuint location_ambientLight;
	GLuint location_shineDamper;
	GLuint location_shine;
protected:
	void BindAttributes();
	void GetAllUniformLocations();
};

#endif // STATICSHADER_H