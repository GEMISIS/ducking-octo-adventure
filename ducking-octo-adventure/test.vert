#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;

uniform mat4 perspectiveMatrix;
uniform mat4 viewMatrix;

void main()
{
	gl_Position.xyzw = perspectiveMatrix * viewMatrix * vec4(vertexPosition_modelspace, 1.0);
}