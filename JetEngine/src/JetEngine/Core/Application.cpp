#include "JEpch.h"

#include "Application.h"

#include "JetEngine/Renderer/Renderer.h"

#include "Input.h"

#include <GLFW/glfw3.h>






namespace JetEngine {

	Application* Application::s_Instance = nullptr;

	Application::Application()		
	{
		JE_PROFILE_FUNCTION();

		JE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = Window::Create();
		m_Window->SetEventCallback(JE_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();
	
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}


	Application::~Application()
	{
		JE_PROFILE_FUNCTION();

		Renderer::Shutdown();
	}

	void Application::PushLayer(Layer* layer)
	{
		JE_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		JE_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		JE_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(JE_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(JE_BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}	

	void Application::Run()
	{
		JE_PROFILE_FUNCTION();

		while (m_Running) 
		{
			JE_PROFILE_SCOPE("RunLoop");

			float time = (float)glfwGetTime(); // !TODO Platform::GetTime()
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				{
					JE_PROFILE_SCOPE("LayerStack Updates");
					
					for (Layer* layer : m_LayerStack)
							layer->OnUpdate(timestep);
				}

				m_ImGuiLayer->Begin();
				{
					JE_PROFILE_SCOPE("LayerStack OnImGuiRender");
					
					for (Layer* layer : m_LayerStack)
						layer->OnImGuiRender();		
				}
				m_ImGuiLayer->End();
			}

			

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		JE_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}
}