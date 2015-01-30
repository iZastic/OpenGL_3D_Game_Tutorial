#include <iostream>
#include <fstream>
#include "ShaderProgram.h"


ShaderProgram::ShaderProgram(const std::string& fileName)
{
	// Load shaders from file
	m_vertexShaderID = LoadShader(fileName + ".vert", GL_VERTEX_SHADER);
	m_fragmentShaderID = LoadShader(fileName + ".frag", GL_FRAGMENT_SHADER);
	
	// Create shader program
	m_programID = glCreateProgram();
	// Attach the shaders to the program
	glAttachShader(m_programID, m_vertexShaderID);
	glAttachShader(m_programID, m_fragmentShaderID);
	// Link the program
	glLinkProgram(m_programID);
	glValidateProgram(m_programID);

	// Check validation status
	GLint status;
	glGetProgramiv(m_programID, GL_VALIDATE_STATUS, &status);
	if (status == GL_FALSE)
	{
		// Get info log length
		GLint infoLogLength;
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		// Get the info log
		GLchar* infoLog = new GLchar[infoLogLength];
		glGetProgramInfoLog(m_programID, infoLogLength, NULL, infoLog);
		std::cerr << "ERROR: could not validate program \n" << infoLog << std::endl;
		// Delete the array
		delete[] infoLog;
	}
}


ShaderProgram::~ShaderProgram()
{
	UnUse();
	glDetachShader(m_programID, m_vertexShaderID);
	glDetachShader(m_programID, m_fragmentShaderID);
	glDeleteShader(m_vertexShaderID);
	glDeleteShader(m_fragmentShaderID);
	glDeleteProgram(m_programID);
}


void ShaderProgram::Use()
{
	glUseProgram(m_programID);
}


void ShaderProgram::UnUse()
{
	glUseProgram(0);
}


GLuint ShaderProgram::LoadShader(const std::string& fileName, GLenum type)
{
	// Open the file
	std::ifstream file;
	file.open((fileName).c_str());

	// Create temp variables
	std::string source, line;

	if (file.is_open())
	{
		// Load file to string
		while (file.good())
		{
			getline(file, line);
			source.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	// Create shader ID
	GLuint shaderID = glCreateShader(type);

	// Prepare source for OpenGL
	const GLchar* sourceStrings[1];
	GLint sourceLengths[1];
	sourceStrings[0] = source.c_str();
	sourceLengths[0] = source.length();

	// Load source to OpenGL and compile
	glShaderSource(shaderID, 1, sourceStrings, sourceLengths);
	glCompileShader(shaderID);

	// Check compile status
	GLint status;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		// Get info log length
		GLint infoLogLength;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
		// Get the info log
		GLchar* infoLog = new GLchar[infoLogLength];
		glGetShaderInfoLog(shaderID, infoLogLength, NULL, infoLog);
		std::cerr << "ERROR: could not compile shader \n" << infoLog << std::endl;
		// Delete the array
		delete[] infoLog;
	}

	return shaderID;
}


void ShaderProgram::BindAttribute(int attribute, const std::string& variableName)
{
	glBindAttribLocation(m_programID, attribute, variableName.c_str());
}