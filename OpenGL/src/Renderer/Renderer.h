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

static constexpr glm::vec3 DEFAULT_TRANSFORM(200, 200, 0);

struct Quad
{
	glm::vec3 Transform;
	Texture Sprite;

	Quad(const glm::vec3& transform, const char* spritePath)
		: Transform(transform)
		, Sprite(Texture(spritePath))
	{
	}

	Quad(const glm::vec3& transform)
		: Quad(transform, DEFAULT_SPRITE)
	{
	}

	void BindTexture(Shader& shader)
	{
		Sprite.Bind();
		Sprite.EnableBlending();
		shader.SetUniform1i("u_Texture",0);
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
	void AddNewQuad(Shader& shader);

	inline int GetDrawCalls() const { return m_Quads.size(); }

private:
	GLFWwindow* m_WindowHandle;
	std::vector<Quad> m_Quads;
};






