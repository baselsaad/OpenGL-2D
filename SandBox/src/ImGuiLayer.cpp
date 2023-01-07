#include "pch.h"
#include "OpenGL-Core.h"
#include "ImGuiLayer.h"

#include "imgui\Include\imgui.h"
#include "imgui\Include\imgui_impl_glfw_gl3.h"

ImGuiLayer::ImGuiLayer()
	: m_TestTexture("res/textures/test.png")
	, m_LogoTexture("res/textures/Logo.png")
{
}

ImGuiLayer::~ImGuiLayer()
{
}

void ImGuiLayer::OnStart(OpenGLWindow* window)
{
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(*window, true);
	ImGui::StyleColorsDark();
}

void ImGuiLayer::SetupPlayerInput(PlayerInput* input)
{
}

static int textureNumber = 1;

void ImGuiLayer::OnUpdate(const DeltaTime& deltaTime)
{
	// Render
	ImGui_ImplGlfwGL3_NewFrame();
	{

		ImGui::SliderInt("Which Texture? ", &textureNumber, 1, 2);

		if (ImGui::Button("Add Sprite"))
		{
			Texture* selectedTexture = textureNumber == 1 ? &m_TestTexture : &m_LogoTexture;
			m_Quads.emplace_back(glm::vec3(1.0f), selectedTexture);
		}

		for (int i = 0; i < m_Quads.size(); i++)
		{
			const Quad& quad = m_Quads[i];

			Renderer::DrawQuad(quad.Position, glm::vec3(100.0f), quad.Sprite);

			std::string labelName = "Sprite-" + std::to_string(i + 1);
			ImGui::SliderFloat3(labelName.c_str(), &m_Quads[i].Position.x, 0.0f, Renderer::GetViewport().x);
		}

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Text("Draw Calls %llu", Renderer::GetDrawCalls());

		ImGui::Render();
	}
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::OnDestroy()
{
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
}
