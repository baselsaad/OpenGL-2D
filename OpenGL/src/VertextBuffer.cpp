#include "VertextBuffer.h"



VertexBuffer::VertexBuffer(const void* data, uint32_t size)
{
	// Vertex-Buffer
	const int buffersCount = 1;
	GL_CALL(glGenBuffers(buffersCount, &m_RendererID));
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	const int buffersCount = 1;
	GL_CALL(glDeleteBuffers(buffersCount, &m_RendererID));
}

void VertexBuffer::Bind() const
{
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::UnBind() const
{
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));// 0 to unbind
}
