#pragma once
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Texture.h"
#include "Shader.h"
#include "glm/vec3.hpp"

class VertexArray;
class IndexBuffer;
class Shader;
struct GLFWwindow;

static const glm::vec3 DEFAULT_TRANSFORM(200, 200, 0);

struct Quad
{
	glm::vec3 Transform;
	Texture* Sprite;

	Quad(const glm::vec3& transform, Texture* texture)
		: Transform(transform)
		, Sprite(texture)
	{
	}

	bool BindTexture()
	{
		if (Sprite == nullptr)
			return false;

		Sprite->Bind(0);
		Sprite->EnableBlending();
		return true;
	}

};

class Renderer
{
public:
	Renderer(GLFWwindow* window);

public:
	void Draw(const VertexArray& vb, const IndexBuffer& ib) const;
	void OnUpdate(const VertexArray& vb, const IndexBuffer& ib, Shader& shader, const char* projUniform);

	void Clear() const;
	void Swap() const;

	void AddNewQuad(Texture* texture);

	inline size_t GetDrawCalls() const { return m_Quads.size(); }
private:
	GLFWwindow* m_WindowHandle;
	std::vector<Quad> m_Quads;
};






