#pragma once

#include <GL/glew.h>
#include <string>

class shader_program
{
public:
	shader_program();
	shader_program(const char* vertex_shader, const char* fragment_shader);
	~shader_program();

	int Use();
private:
	GLint vertexCompileStatus, fragmentCompileStatus, linkStatus;
	std::string vertexCompileLog, fragmentCompileLog, linkLog;
	GLuint vertexShaderID, fragmentShaderID, programID;
};