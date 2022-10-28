#include "Renderer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"


Renderer::Renderer(GLFWwindow* window)
{
	m_WindowHandle = window;
}

void Renderer::Draw(const VertexArray& vb, const IndexBuffer& ib, const Shader& shader) const
{
	// because we generate and bind the buffer outside the loop, OpenGL knows which buffer should be drawn
	vb.Bind();
	ib.Bind();
	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Swap() const
{
	/* Swap front and back buffers */
	glfwSwapBuffers(m_WindowHandle);

	/* Poll for and process events */
	glfwPollEvents();
}

