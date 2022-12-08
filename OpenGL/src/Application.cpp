// https://docs.gl/

#include "OpenGL.h"
#include "Renderer/Renderer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/VertexBufferLayout.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"

#include "Tools/Colors.h"
#include "Tools/Timer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui\imgui.h"
#include "imgui\imgui_impl_glfw_gl3.h"


static Timer::Lambda ChangeColor(Shader& shader, const char* colorUniform)
{
	int increamnt = 0;
	Colors::RGBA color = Colors::RGBA(Colors::ColorsArray.at(0));

	// colorUniform should be copied because its get out of scope 
	Timer::Lambda changeColor = [&color, &increamnt, &shader, colorUniform]()
	{
		increamnt++;
		if (increamnt >= Colors::ColorsArray.size())
		{
			increamnt = 0;
		}

		color = Colors::ColorsArray.at(increamnt);

		shader.Bind();
		shader.SetUniform4f(colorUniform, color.R, color.G, color.B, color.Alpha);
	};

	return changeColor;
}

int main()
{
	GLFWwindow* window = CreateOpenGLContext();

	{
		//ImGui
		ImGui::CreateContext();
		ImGui_ImplGlfwGL3_Init(window, true);
		ImGui::StyleColorsDark();

		// VertexBuffer
		VertexBuffer vertexBuffer(Defaults::positions, Defaults::PositionsSize * sizeof(float));
		
		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);

		// VertexArray
		VertexArray vertexArray;
		vertexArray.AddBuffer(vertexBuffer, layout);

		//IndexBuffer
		IndexBuffer indexBuffer(Defaults::indices, Defaults::IndicesSize);

		// Shaders
		Shader shader("res/shaders/Basic.shader");

		int textureNumber = 1;
		Texture testTexture("res/textures/test.png");
		Texture logoTexture("res/textures/Logo.png");

		Renderer renderer(window);

		// Timers 
		Timer timer;
		//timer.SetCallBackTimer(1.0f, ChangeColor(shader, colorUniform));

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			renderer.Clear();

			// Update TimersCallback
			{
				for (auto& tm : timer.CallbacksVec)
				{
					tm.Update();
				}
			}

			// Render
			ImGui_ImplGlfwGL3_NewFrame();
			{
				ImGui::SliderInt("Which Texture? ", &textureNumber, 1, 2);

				if (ImGui::Button("Add Sprite"))
				{
					Texture* selectedTexture = textureNumber == 1 ? &testTexture : &logoTexture;
					renderer.AddNewQuad(selectedTexture);
				}

				//Basic Way to render multiaple objects (TODO: Batch rendering)
				renderer.OnUpdate(vertexArray, indexBuffer, shader);

				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
				ImGui::Text("Draw Calls %llu", renderer.GetDrawCalls());

				ImGui::Render();
			}
			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

			renderer.Swap();
		}

	}

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	// should be delete before glfwTerminate
	glfwTerminate();

	return 0;
}