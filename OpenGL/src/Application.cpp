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
	Timer::Lambda changeColor = [&color, &increamnt, &shader, &colorUniform]()
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
		// VertextBuffer
		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);

		VertexBuffer vertexBuffer(Defaults::positions, Defaults::PositionsSize * sizeof(float));
		VertexArray vertexArray;
		vertexArray.AddBuffer(vertexBuffer, layout);

		//IndexBuffer
		IndexBuffer indexBuffer(Defaults::indices, Defaults::IndicesSize);
		indexBuffer.Bind();

		// Shaders
		const char* textureUniform = "u_Texture";
		const char* colorUniform = "u_Color";
		const char* projUniform = "u_MVP";

		// 4:3 Aspect ratio
		// 2.0 * 2 = 4
		// 1.5 * 2 = 3
		glm::mat4 proj = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100.0f, 0.0f, 0.0f));


		Shader shader("res/shaders/Basic.shader");
		shader.Bind();

		ImGui::CreateContext();
		ImGui_ImplGlfwGL3_Init(window, true);
		ImGui::StyleColorsDark();

		glm::vec3 translation(200, 200, 0);

		// Timers 
		Timer timer;
		timer.SetCallBackTimer(1.0f, ChangeColor(shader, colorUniform));

		// Texture
		Texture texture("res/textures/logo.png");
		texture.Bind(0);
		texture.EnableBlending();
		shader.SetUniform1i(textureUniform, 0); // to slot 0, if texture.Bind(2) => SetUniform1i("u_Texture", 2);

		Renderer renderer(window);

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
			

			// Imgui render
			{
				ImGui_ImplGlfwGL3_NewFrame();

				glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
				glm::mat4 mvp = proj * view * model;
				shader.SetUniformMat4f(projUniform, mvp);

				ImGui::SliderFloat3("Translation", &translation.x, 0.0f, 960.0f);
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

				renderer.Draw(vertexArray, indexBuffer, shader);

				ImGui::Render();
				ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
			}

			
			renderer.Swap();
		}

	}

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	// should be delete before glfwTerminate
	glfwTerminate();

	return 0;
}