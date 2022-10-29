// https://docs.gl/

#include "Renderer/Renderer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/VertexBufferLayout.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"

#include "Tools/Colors.h"
#include "Tools/Timer.h"

static GLFWwindow* CreateOpenGLContext()
{
	/* Initialize the library */
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//should be called for glDebugMessageCallback
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);// Make the window's context current 
	glfwSwapInterval(false); // vsync
	GLenum state = glewInit();//glewInit should be called after a valid OpenGL rendering context has been created

	glDebugMessageCallback(OpenGLMessageCallback, nullptr);
	std::cout << glGetString(GL_VERSION) << std::endl;// GPU driver and OpenGL Information

	return window;
}

int main()
{
	GLFWwindow* window = CreateOpenGLContext();

	{
		//positions with texture coord 2 | 2
		// Each "Line" for X , Y 
		float positions[4 * 4] =
		{
			-0.5f , -0.5f, 0.0f, 0.0f,		// 0 bottom_left 
			 0.5f , -0.5f, 1.0f, 0.0f,		// 1 bottom_right
			 0.5f ,  0.5f, 1.0f, 1.0f,		// 2 top_right
			-0.5f ,  0.5f, 0.0f, 1.0f		// 3 top_left
		};

		
		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);

		VertexBuffer vertexBuffer(positions, 4 * 4 * sizeof(float));
		VertexArray vertexArray;
		vertexArray.AddBuffer(vertexBuffer, layout);

		uint32_t indices[6] =
		{
			0, 1, 2,
			2, 3, 0
		};
		IndexBuffer indexBuffer(indices, 6);
		indexBuffer.Bind();

		/**************************************************
		 *				3 * * * * * * * * * * * 2
		 *				*					*   *
		 *				* 			   *		*
		 *				*  		  *				*
		 * 				*  	  *					*
		 * 				*  *					*
		 * 				0 * * * * * * * * * * * 1
		 **************************************************/

		int increamnt = 0;
		Colors::RGBA color = Colors::RGBA(Colors::ColorsArray.at(0));

		// Shaders
		const char* textureUniform = "u_Texture";
		const char* colorUniform = "u_Color";

		Shader shader("res/shaders/Basic.shader");
		shader.Bind();
		shader.SetUniform4f(colorUniform, color.R, color.G, color.B, color.Alpha);

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
		Timer timer;
		timer.SetCallBackTimer(1.0f, changeColor);

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
					tm.Update();
			}
			
			
			renderer.Draw(vertexArray, indexBuffer, shader);
			renderer.Swap();
		}

	}


	// should be delete before glfwTerminate
	glfwTerminate();

	return 0;
}