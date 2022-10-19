#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class VertexArray;
class IndexBuffer;
class Shader;
struct GLFWwindow;

class Renderer
{
public:
	Renderer(GLFWwindow* window);

public:
	void Draw(const VertexArray& vb, const IndexBuffer& ib, const Shader& shader) const;
	void Clear() const;

	void Swap() const;

private:
	GLFWwindow* m_WindowHandle;
};






