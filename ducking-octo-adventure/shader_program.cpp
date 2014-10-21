#include "shader_program.h"

#include <iostream>
#include <fstream>
#include <vector>

shader_program::shader_program()
{
	this->linkStatus = 0;
	this->vertexCompileStatus = 0;
	this->fragmentCompileStatus = 0;

	this->programID = -1;
	this->vertexShaderID = -1;
	this->fragmentShaderID = -1;
}

shader_program::shader_program(const char* vertex_shader, const char* fragment_shader)
{
	this->linkStatus = 0;
	this->vertexCompileStatus = 0;
	this->fragmentCompileStatus = 0;

	this->programID = -1;
	this->vertexShaderID = -1;
	this->fragmentShaderID = -1;

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

		this->vertexShaderID = -1;
		this->fragmentShaderID = -1;
	}
}

shader_program::~shader_program()
{
	if (this->programID > -1)
	{
		glDeleteProgram(this->programID);
	}
	if (this->vertexShaderID > -1)
	{
		glDeleteShader(this->vertexShaderID);
	}
	if (this->fragmentShaderID > -1)
	{
		glDeleteShader(this->fragmentShaderID);
	}
}

int shader_program::Use()
{
	if (this->linkStatus)
	{
		glUseProgram(this->programID);
		return 1;
	}
	return 0;
}