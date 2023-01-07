#pragma once
#include "Core\Layer.h"

struct Quad
{
	glm::vec3 Position;
	Texture* Sprite;

	Quad(const glm::vec3& transform, Texture* texture)
		: Position(transform)
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

class ImGuiLayer : public Layer
{

public:
	ImGuiLayer();
	~ImGuiLayer();


public:
	virtual void OnStart(OpenGLWindow* window) override;
	virtual void SetupPlayerInput(PlayerInput* input) override;

	virtual void OnUpdate(const DeltaTime& deltaTime) override;

	virtual void OnDestroy() override;


private:
	std::vector<Quad> m_Quads;

	Texture m_TestTexture;
	Texture m_LogoTexture;
};


