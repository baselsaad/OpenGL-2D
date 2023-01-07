#pragma once
class VertexArray;
class IndexBuffer;
class Texture;

class Renderer
{
public:
	Renderer() = default;
	Renderer(const Renderer&) = delete;

public:
	static void Init(const glm::vec2& viewport);
	static void ShutDown();

	static void DrawQuad(const glm::mat4& transform, const Texture* texture);
	static void DrawQuad(const glm::mat4& transform, const Colors::RGBA& color);
	static void DrawQuad(const glm::vec3& position,const glm::vec3& scale, const Texture* texture);
	static void DrawQuad(const glm::vec3& position,const glm::vec3& scale, const Colors::RGBA& color);

	static void ResetStats();
	static int GetDrawCalls();

	static void UpdateViewport(int width, int height);
	static const glm::vec2& GetViewport();
	static const glm::mat4& GetProjectionView();

private:
	static void Draw(const VertexArray& vb, const IndexBuffer& ib);
};






