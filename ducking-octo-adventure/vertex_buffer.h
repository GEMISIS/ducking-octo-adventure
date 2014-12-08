#pragma once

#include <vector>

#ifdef _DEBUG
#include <iostream>
#endif

typedef struct
{
	unsigned int bufferID;
	float x, y, z;
}vertex_t;

void setupVertexBuffer();
void setupVertexBuffer(unsigned long bufferSize);
void setVertex(vertex_t* vertex);
vertex_t* getVertex(vertex_t* vertex);
void destroyVertexBuffer();
