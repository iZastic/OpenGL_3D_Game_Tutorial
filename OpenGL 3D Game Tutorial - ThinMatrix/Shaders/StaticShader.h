#ifndef STATICSHADER_H
#define STATICSHADER_H

#include <string>
#include "ShaderProgram.h"

class StaticShader : public ShaderProgram
{
public:
	StaticShader(const std::string& fileName);
	virtual ~StaticShader();
private:
	const std::string SHADER_PATH;
protected:
	void BindAttributes();
};

#endif // STATICSHADER_H