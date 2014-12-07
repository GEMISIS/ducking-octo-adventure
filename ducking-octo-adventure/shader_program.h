#pragma once

#include <GL/glew.h>
#include <string>
#include <glm.hpp>

enum class SHADER_ERRORS
{
	NONE = 0,
	UNKNOWN = -1,
	VERTEX_COMPILE_FAILURE = -2,
	FRAGMENT_COMPILE_FAILURE = -3,
	VERTEX_AND_FRAGMENT_COMPILE_FAILURE = -4,
	LINK_FAILURE = -5
};

class shader_program
{
public:
	shader_program();
	shader_program(const char* vertex_shader, const char* fragment_shader);
	~shader_program();

	SHADER_ERRORS Load(const char* vertex_shader, const char* fragment_shader);
	SHADER_ERRORS Use();

	void SetUniform(const char* uniformName, glm::mat4 mat);
private:
	GLint vertexCompileStatus, fragmentCompileStatus, linkStatus;
	std::string vertexCompileLog, fragmentCompileLog, linkLog;
	GLuint vertexShaderID, fragmentShaderID, programID;
};