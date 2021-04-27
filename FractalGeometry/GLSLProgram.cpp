#include "GLSLProgram.h"
#include <GL\glew.h>
#include <SDL\SDL.h>
#include <iostream>
#include <fstream>
#include <vector>


GLSLProgram::GLSLProgram() : _numAttributes(0),  _vertexShaderId(0), _fragmentShaderId(0), _programId(0)
{
}

GLSLProgram::~GLSLProgram()
{
}
void GLSLProgram::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
{
	std::string vertSource, fragSource;

	IOManager::readFileToBuffer(vertexShaderFilePath, vertSource);
	IOManager::readFileToBuffer(fragmentShaderFilePath, fragSource);

	compileShadersFromSource(vertSource.c_str(), fragSource.c_str());
}
void GLSLProgram::addAttribute(std::string attributeName)
{
	glBindAttribLocation(_programId, _numAttributes++, attributeName.c_str());
}
void GLSLProgram::linkShaders()
{
	glAttachShader(_programId, _vertexShaderId);
	glAttachShader(_programId, _fragmentShaderId);

	glLinkProgram(_programId);

	GLint isLinked = 0;
	glGetProgramiv(_programId, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(_programId, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);

		glGetProgramInfoLog(_programId, maxLength, &maxLength, &errorLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(_programId);
		// Don't leak shaders either.
		glDeleteShader(_vertexShaderId);
		glDeleteShader(_fragmentShaderId);

		// Use the infoLog as you see fit.

		// In this simple program, we'll just leave
		std::printf("%s\n", &(errorLog[0]));
		std::cout << "Shader failed to link" << std::endl;

		return;
	}
	// Always detach shaders after a successful link.
	glDetachShader(_programId, _vertexShaderId);
	glDetachShader(_programId, _fragmentShaderId);

	glDeleteShader(_vertexShaderId);
	glDeleteShader(_fragmentShaderId);
}
void GLSLProgram::compileShadersFromSource(const char* vertexSource, const char* fragmentSource)
{
	_programId = glCreateProgram();

	_vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	if (_vertexShaderId == 0) {
		std::cout << "Vertex Shader failed to be created!" << std::endl;
		exit(69);
	}
	_fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	if (_fragmentShaderId == 0) {
		std::cout << "Fragment Shader failed to be created!" << std::endl;
		exit(69);
	}
	compileShader(vertexSource, "Vertex File", _vertexShaderId);
	compileShader(fragmentSource, "Fragment File", _fragmentShaderId);
}
void GLSLProgram::compileShader(const char* source, const std::string& name, GLuint id)
{
	std::ifstream File(source);
	std::string fileContents = "";
	std::string line;
	while (std::getline(File, line)) {
		fileContents += line + "\n";
	}
	File.close();
	const char* contentsPtr = fileContents.c_str();
	glShaderSource(id, 1, &contentsPtr, nullptr);
	glCompileShader(id);

	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.
		glDeleteShader(id); // Don't leak the shader.

		std::printf("%s\n", &errorLog[0]);

		std::cout << "Shader " + name + " failed to compile" << std::endl;
	}
}
void GLSLProgram::use() {
	glUseProgram(_programId);
	for (int i = 0; i < _numAttributes; i++) {
		glEnableVertexAttribArray(i);
	}
}
void GLSLProgram::unuse() {
	glUseProgram(0);
	for (int i = 0; i <= _numAttributes; i++) {
		glDisableVertexAttribArray(i);
	}
}
GLuint GLSLProgram::getUniformLocation(const std::string uniformName)
{
	GLuint location = glGetUniformLocation(_programId, uniformName.c_str());
	if (location == GL_INVALID_INDEX) {
		SDL_Quit();
		exit(69);
	}
	return location;
}
