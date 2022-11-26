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
	bool HasTexture;

	Quad(const glm::vec3& transform, Texture* texture)
	{
		Transform = transform;

		if (texture == nullptr)
		{
			Sprite = nullptr;
			HasTexture = false;
		}
		else
		{
			Sprite = texture;
			HasTexture = true;
		}
	}

	bool BindTexture()
	{
		if (!HasTexture)
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

	inline int GetDrawCalls() const { return m_Quads.size(); }

private:
	GLFWwindow* m_WindowHandle;
	std::vector<Quad> m_Quads;
};






