#pragma once

#include "Core.h"

#include "Window.h"
#include "JetEngine/Core/LayerStack.h"
#include "JetEngine/Events/Event.h"
#include "JetEngine/Events/ApplicationEvent.h"

#include "JetEngine/Core/Timestep.h"

#include "JetEngine/ImGui/ImGuiLayer.h"




namespace JetEngine {

	class Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	// To be defined in a client
	Application* CreateApplication();
}

