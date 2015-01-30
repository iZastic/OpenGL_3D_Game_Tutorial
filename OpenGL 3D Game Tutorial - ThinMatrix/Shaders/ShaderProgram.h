#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <string>
#include <GL\glew.h>

class ShaderProgram
{
public:
	ShaderProgram(const std::string& fileName);
	virtual ~ShaderProgram();

	void Use();
	void UnUse();
private:
	GLuint m_programID;
	GLuint m_vertexShaderID;
	GLuint m_fragmentShaderID;

	GLuint LoadShader(const std::string& fileName, GLenum type);
protected:
	virtual void BindAttributes() = 0;
	void BindAttribute(int attribute, const std::string& variableName);
};

#endif // SHADERPROGRAM_H