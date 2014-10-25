#pragma once

#include <GL/glew.h>
#include <string>
#include <glm.hpp>

class shader_program
{
public:
	shader_program();
	shader_program(const char* vertex_shader, const char* fragment_shader);
	~shader_program();

	int Use();
	void SetUniform(const char* uniformName, glm::mat4 mat);
private:
	GLint vertexCompileStatus, fragmentCompileStatus, linkStatus;
	std::string vertexCompileLog, fragmentCompileLog, linkLog;
	GLuint vertexShaderID, fragmentShaderID, programID;
};