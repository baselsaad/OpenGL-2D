#include "VertexArray.h"

#include "Debug.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"


VertexArray::VertexArray()
{
	GL_CALL(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
	GL_CALL(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();

	const auto& elements = layout.GetElements();
	uint32_t offset = 0;

	for (uint32_t i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];

		//should be called for glVertexAttribPointer
		GL_CALL(glEnableVertexAttribArray(i));

		//tell OpenGL how to read vertexBuffer
		//(index, size_of_values_per_vertex, type, if_values_are_normlized, offset_between_vertecis, offset_of_attribute)
		GL_CALL(glVertexAttribPointer(i, element.Count, element.Type, element.normlized, layout.GetStride(), (const void*)offset));
		offset += element.Count * VertexBufferElement::GetSizeOfType(element.Type);
	}
}

void VertexArray::Bind() const
{
	GL_CALL(glBindVertexArray(m_RendererID));
}

void VertexArray::UnBind() const
{
	GL_CALL(glBindVertexArray(0));
}
