#include "shader_program.h"

#include <iostream>
#include <fstream>
#include <vector>

shader_program::shader_program()
{
	this->linkStatus = 0;
	this->vertexCompileStatus = 0;
	this->fragmentCompileStatus = 0;

	this->programID = 0;
	this->vertexShaderID = 0;
	this->fragmentShaderID = 0;
}

shader_program::shader_program(const char* vertex_shader, const char* fragment_shader)
{
	this->Load(vertex_shader, fragment_shader);
}

shader_program::~shader_program()
{
	if (this->programID > 0)
	{
		glDeleteProgram(this->programID);
	}
	if (this->vertexShaderID > 0)
	{
		glDeleteShader(this->vertexShaderID);
	}
	if (this->fragmentShaderID > 0)
	{
		glDeleteShader(this->fragmentShaderID);
	}
}

SHADER_ERRORS shader_program::Load(const char* vertex_shader, const char* fragment_shader)
{
	this->linkStatus = 0;
	this->vertexCompileStatus = 0;
	this->fragmentCompileStatus = 0;

	this->programID = 0;
	this->vertexShaderID = 0;
	this->fragmentShaderID = 0;

	int logLength = 0;
	std::vector<char> log;
	std::string vertexShaderCode, fragmentShaderCode;

	std::ifstream vertexShaderStream(vertex_shader, std::ios::in);
	if (vertexShaderStream.is_open())
	{
		// Iterates through the stream with characters, going through each character until it runs out of data in the buffer.
		vertexShaderCode = std::string((std::istreambuf_iterator<char>(vertexShaderStream)), std::istreambuf_iterator<char>());
		vertexShaderStream.close();

		this->vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

		const char* vertexShaderCodeArray = vertexShaderCode.c_str();
		glShaderSource(this->vertexShaderID, 1, &vertexShaderCodeArray, NULL);
		glCompileShader(this->vertexShaderID);

		glGetShaderiv(this->vertexShaderID, GL_COMPILE_STATUS, &this->vertexCompileStatus);
		glGetShaderiv(this->vertexShaderID, GL_INFO_LOG_LENGTH, &logLength);
		log = std::vector<char>(logLength);
		glGetShaderInfoLog(this->vertexShaderID, logLength, NULL, &log[0]);
		this->fragmentCompileLog = std::string(&log[0]);
		printf(&log[0]);
	}

	std::ifstream fragmentShaderStream(fragment_shader, std::ios::in);
	if (fragmentShaderStream.is_open())
	{
		// Iterates through the stream with characters, going through each character until it runs out of data in the buffer.
		fragmentShaderCode = std::string((std::istreambuf_iterator<char>(fragmentShaderStream)), std::istreambuf_iterator<char>());
		fragmentShaderStream.close();

		this->fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		const char* fragmentShaderCodeArray = fragmentShaderCode.c_str();
		glShaderSource(this->fragmentShaderID, 1, &fragmentShaderCodeArray, NULL);
		glCompileShader(this->fragmentShaderID);

		glGetShaderiv(this->fragmentShaderID, GL_COMPILE_STATUS, &this->fragmentCompileStatus);
		glGetShaderiv(this->fragmentShaderID, GL_INFO_LOG_LENGTH, &logLength);
		log = std::vector<char>(logLength);
		glGetShaderInfoLog(this->fragmentShaderID, logLength, NULL, &log[0]);
		this->fragmentCompileLog = std::string(&log[0]);
		printf(&log[0]);
	}

	if (this->vertexCompileStatus && this->fragmentCompileStatus)
	{
		this->programID = glCreateProgram();
		glAttachShader(this->programID, this->vertexShaderID);
		glAttachShader(this->programID, this->fragmentShaderID);
		glLinkProgram(this->programID);

		glGetProgramiv(this->programID, GL_LINK_STATUS, &this->linkStatus);
		glGetProgramiv(this->programID, GL_INFO_LOG_LENGTH, &logLength);
		log = std::vector<char>(logLength);
		glGetProgramInfoLog(this->programID, logLength, NULL, &log[0]);
		this->linkLog = std::string(&log[0]);

		glDeleteShader(this->vertexShaderID);
		glDeleteShader(this->fragmentShaderID);

		this->vertexShaderID = 0;
		this->fragmentShaderID = 0;
	}
	else if (!this->vertexCompileStatus && !this->fragmentCompileStatus)
	{
		return SHADER_ERRORS::VERTEX_AND_FRAGMENT_COMPILE_FAILURE;
	}
	else if (!this->vertexCompileStatus)
	{
		return SHADER_ERRORS::VERTEX_COMPILE_FAILURE;
	}
	else if (!this->fragmentCompileStatus)
	{
		return SHADER_ERRORS::FRAGMENT_COMPILE_FAILURE;
	}

	if (!this->linkStatus)
	{
		return SHADER_ERRORS::LINK_FAILURE;
	}
}

SHADER_ERRORS shader_program::Use()
{
	if (this->linkStatus)
	{
		glUseProgram(this->programID);
		return SHADER_ERRORS::NONE;
	}
	if (!this->linkStatus)
	{
		return SHADER_ERRORS::LINK_FAILURE;
	}
	else if (!this->fragmentCompileStatus)
	{
		return SHADER_ERRORS::FRAGMENT_COMPILE_FAILURE;
	}
	else if (!this->vertexCompileStatus)
	{
		return SHADER_ERRORS::VERTEX_COMPILE_FAILURE;
	}
	return SHADER_ERRORS::UNKNOWN;
}

void shader_program::SetUniform(const char* uniformName, glm::mat4 mat)
{
	glUniformMatrix4fv(glGetUniformLocation(this->programID, uniformName), 1, GL_FALSE, &mat[0][0]);
}