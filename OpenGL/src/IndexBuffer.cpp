#include "IndexBuffer.h"



IndexBuffer::IndexBuffer(const uint32_t* data, uint32_t count)
	: m_Count(count)
{
	ASSERT(sizeof(uint32_t) == sizeof(GLuint));

	// Index-Buffer
	const int buffersCount = 1;
	GL_CALL(glGenBuffers(buffersCount, &m_RendererID));
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(uint32_t), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
	const int buffersCount = 1;
	GL_CALL(glDeleteBuffers(buffersCount, &m_RendererID));
}

void IndexBuffer::Bind() const
{
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::UnBind() const
{
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));// 0 to unbind
}
