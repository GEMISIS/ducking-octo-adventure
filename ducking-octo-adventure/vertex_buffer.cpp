#include "vertex_buffer.h"

#define VERTEX_HASH_SCALAR 1000
#define STARTING_BUFFER_SIZE 1024

unsigned long buffer_size = STARTING_BUFFER_SIZE;
vertex_t** vertices = new vertex_t*[STARTING_BUFFER_SIZE];

unsigned long hashVertex(vertex_t vertex)
{
	unsigned long hash = 5381;
	hash = ((hash << 5) + hash) + unsigned long(vertex.x * VERTEX_HASH_SCALAR);
	hash = ((hash << 5) + hash) + unsigned long(vertex.y * VERTEX_HASH_SCALAR);
	hash = ((hash << 5) + hash) + unsigned long(vertex.z * VERTEX_HASH_SCALAR);
	return hash;
}

void resizeBuffer(unsigned long size)
{
	vertex_t** temp = new vertex_t*[size + 1];

	for (unsigned long i = 0; i < buffer_size; i += 1)
	{
		temp[i] = vertices[i];
	}

	free(vertices);
	vertices = temp;
	temp = NULL;

	buffer_size = size + 1;
}

void setVertex(vertex_t* vertex)
{
	unsigned long hash = hashVertex(*vertex);

	if (vertex == NULL)
	{
#ifdef _DEBUG
		std::cout << "Error: Vertex is NULL!";
#endif
		return;
	}

	if (hash < buffer_size)
	{
		if (vertices[hash] == NULL)
		{
			vertices[hash] = vertex;
		}
		else
		{
#ifdef _DEBUG
			std::cout << "Error: Vertex hash has collision!";
#endif
		}
	}
	else
	{
		resizeBuffer(hash);
		vertices[hash] = vertex;
	}
}

vertex_t* getVertex(vertex_t* vertex)
{
	if (vertex == NULL)
	{
		return NULL;
	}

	unsigned long hash = hashVertex(*vertex);

	if (hash < buffer_size)
	{
		if (vertices[hash] != NULL)
		{
			return vertices[hash];
		}
		else
		{
			vertices[hash] = vertex;
			return vertex;
		}
	}
	else
	{
		resizeBuffer(hash);
		vertices[hash] = vertex;
		return vertex;
	}
}

