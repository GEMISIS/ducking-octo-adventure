#include "vertex_buffer.h"

#define VERTEX_BUFFER_SCALE 2
#define VERTEX_HASH_SCALAR 1000
#define STARTING_BUFFER_SIZE 1024

unsigned long buffer_size = STARTING_BUFFER_SIZE;
vertex_t** vertices = NULL;

signed int currentIndex = 0;

void zeroBuffer(unsigned long start, unsigned long end)
{
	for (unsigned long i = start; i < end && i < buffer_size; i += 1)
	{
		vertices[i] = NULL;
	}
}

unsigned long hashVertex(vertex_t vertex)
{
	unsigned long hash = 5381;
	hash = ((hash << 5) + hash) + unsigned long(vertex.x * VERTEX_HASH_SCALAR);
	hash = ((hash << 5) + hash) + unsigned long(vertex.y * VERTEX_HASH_SCALAR);
	hash = ((hash << 5) + hash) + unsigned long(vertex.z * VERTEX_HASH_SCALAR);
	return hash;
}

void setupVertexBuffer()
{
	setupVertexBuffer(STARTING_BUFFER_SIZE);
}

void setupVertexBuffer(unsigned long bufferSize)
{
	buffer_size = bufferSize;
	vertices = new vertex_t*[buffer_size];
	zeroBuffer(0, buffer_size);
}

void resizeBuffer(unsigned long size)
{
	vertex_t** temp = new vertex_t*[size * VERTEX_BUFFER_SCALE];

	for (unsigned long i = 0; i < buffer_size; i += 1)
	{
		temp[i] = vertices[i];
	}

	delete temp;
	vertices = temp;
	temp = NULL;

	zeroBuffer(buffer_size, size * VERTEX_BUFFER_SCALE);
	buffer_size = size * VERTEX_BUFFER_SCALE;
}

signed int addVertex(vertex_t* vertex)
{
	unsigned long hash = hashVertex(*vertex);

	if (vertex == NULL)
	{
#ifdef _DEBUG
		std::cout << "Error: Vertex is NULL!";
#endif
		return -1;
	}

	if (hash < buffer_size)
	{
		if (vertices[hash] == NULL)
		{
			vertex->index = currentIndex;
			vertices[hash] = vertex;
			currentIndex += 1;
			return currentIndex - 1;
		}
		else
		{
			//TODO: Handle Collisions
			return -1;
#ifdef _DEBUG
			std::cout << "Error: Vertex hash has collision!";
#endif
		}
	}
	else
	{
		resizeBuffer(hash);

		vertex->index = currentIndex;
		vertices[hash] = vertex;
		currentIndex += 1;
		return currentIndex - 1;
	}
}

signed int getVertexIndex(vertex_t* vertex)
{
	if (vertex == NULL)
	{
		return -1;
	}

	unsigned long hash = hashVertex(*vertex);

	if (hash < buffer_size)
	{
		if (vertices[hash] != NULL)
		{
			return vertices[hash]->index;
		}
		else
		{
			return -1;
		}
	}
	else
	{
		return -1;
	}
}

void destroyVertexBuffer()
{
	delete vertices;
}
