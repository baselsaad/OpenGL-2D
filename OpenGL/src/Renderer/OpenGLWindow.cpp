#include "pch.h"
#include "OpenGL-Core.h"
#include "Utilities\Debug.h"


OpenGLWindow::OpenGLWindow(const WindowData& data)
	: m_Width(data.Width)
	, m_Height(data.Height)
{
	int state = glfwInit();
	ASSERT(state == GLFW_TRUE, "GLFW cannot be initialized!");

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	m_Window = glfwCreateWindow(data.Width, data.Height, data.Title.c_str(), NULL, NULL);
	ASSERT(m_Window, "Window is null!");

	// Make the window's context current
	glfwMakeContextCurrent(m_Window);

	HandleErrorMessages();
	PrintGpuInformation();
	SetVsync(true);
}

OpenGLWindow::~OpenGLWindow()
{
	glfwTerminate();
}

void OpenGLWindow::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void OpenGLWindow::Swap()
{
	/* Swap front and back buffers */
	glfwSwapBuffers(m_Window);
}

void OpenGLWindow::PollEvents()
{
	/* Poll for and process events */
	glfwPollEvents();
}

void OpenGLWindow::SetupEventCallback()
{
	m_EventCallback = [this](Event& e) -> void { m_PlayerInput.OnEvent(e); };
	glfwSetWindowUserPointer(m_Window, &m_EventCallback);

	// Window Close 
	{
		auto callback = [](GLFWwindow* window)
		{
			auto& func = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);
			CloseWindowEvent e;
			func(e);
		};

		glfwSetWindowCloseCallback(m_Window, callback);
	}

	// Window Resize
	{
		auto callback = [](GLFWwindow* window, int width, int height)
		{
			auto& func = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);
			ResizeWindowEvent event(width, height);
			func(event);
		};

		glfwSetWindowSizeCallback(m_Window, callback);
	}

	// Mouse Buttons
	{
		auto callback = [](GLFWwindow* window, int button, int action, int mods)
		{
			auto& func = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);
			double outX, outY;
			glfwGetCursorPos(window, &outX, &outY);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button, outX, outY);
					func(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button, outX, outY);
					func(event);
					break;
				}
			}
		};

		glfwSetMouseButtonCallback(m_Window, callback);
	}

	// Mouse Move
	{
		auto callback = [](GLFWwindow* window, double x, double y)
		{
			auto& func = *(std::function<void(Event&)>*)glfwGetWindowUserPointer(window);

			MouseMoveEvent event((float)x, (float)y);
			func(event);
		};

		glfwSetCursorPosCallback(m_Window, callback);
	}
}

void OpenGLWindow::SetVsync(bool enable)
{
	m_Vsync = enable;
	glfwSwapInterval(enable);
}

void OpenGLWindow::UpdateWindowSize(int width, int height)
{
	m_Width = width;
	m_Height = height;
}

void OpenGLWindow::HandleErrorMessages()
{
	glfwSetErrorCallback(GLFWErrorCallback);
}

void OpenGLWindow::PrintGpuInformation()
{
	// GPU driver and OpenGL Information
	Debug::Info("------------OpenGL Info------------------------");
	Debug::Info(">> GPU: {}", glGetString(GL_RENDERER));
	Debug::Info(">> OpenGL-Version: {}", glGetString(GL_VERSION));
	Debug::Info(">> GLSL version: {}", glGetString(GL_SHADING_LANGUAGE_VERSION));
	Debug::Info("-----------------------------------------------");
}