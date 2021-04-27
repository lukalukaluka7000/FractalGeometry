#pragma once
#include <gl\glew.h>
#include <string>
class GLSLProgram
{
public:
	GLSLProgram();
	~GLSLProgram();

	void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
	void addAttribute(std::string attributeName);
	void linkShaders();


	void use();
	void unuse();
	GLuint getUniformLocation(const std::string uniformName);
private:
	void compileShadersFromSource(const char* vertexSource, const char* fragmentSource);
	void compileShader(const char* source, const std::string& name, GLuint id);

	GLushort _programId, _vertexShaderId, _fragmentShaderId, _numAttributes;
};

