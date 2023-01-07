#pragma once
#include "OpenGL-Core.h"
#include "Utilities\DeltaTime.h"
#include "Renderer\Defaults.h"
#include "ImGuiLayer.h"

static bool s_Running = false;

class Application
{
public:
	Application()
		: m_Window(nullptr)
		, m_Layer(nullptr)
	{
		WindowData data;
		data.Width = Defaults::WINDOW_WIDTH;
		data.Height = Defaults::WINDOW_HEIGHT;
		data.Title = "Chess";

		m_Window = new OpenGLWindow(data);
		m_Window->SetVsync(true);

		Renderer::Init({ data.Width,data.Height });

		Debug::Info("Width {}, Height {}", data.Width, data.Height);
	}

	~Application()
	{
		delete m_Window;
		delete m_Layer;
		Renderer::ShutDown();
	}

	void OnStart()
	{
		s_Running = true;
		m_Window->SetupEventCallback();

		m_Window->GetPlayerInput()->BindActionEvent(EventType::CloseWindow, this, &Application::OnClose);
		m_Window->GetPlayerInput()->BindActionEvent(EventType::ResizeWindow, this, &Application::OnResizeWindow);

		m_Layer = new ImGuiLayer();
		m_Layer->OnStart(m_Window);
		m_Layer->SetupPlayerInput(m_Window->GetPlayerInput());
	}


	void Run()
	{
		OnStart();

		while (s_Running)
		{
			m_DeltaTime.Update();
			Renderer::ResetStats();

			m_Window->Clear();
			m_Window->PollEvents();
			{
				m_Layer->OnUpdate(m_DeltaTime);
			}
			m_Window->Swap();
		}

		OnDestroy();
	}


	void OnDestroy()
	{
		m_Layer->OnDestroy();
	}

	void OnClose(CloseWindowEvent& event)
	{
		s_Running = false;
	}

	void OnResizeWindow(ResizeWindowEvent& event)
	{
		Renderer::UpdateViewport(event.GetWidth(), event.GetHeight());
		m_Window->UpdateWindowSize(event.GetWidth(), event.GetHeight());
	}

private:
	DeltaTime m_DeltaTime;

	OpenGLWindow* m_Window;
	Layer* m_Layer;
};

