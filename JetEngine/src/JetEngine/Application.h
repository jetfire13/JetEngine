#pragma once

#include "Core.h"

#include "Window.h"
#include "JetEngine/LayerStack.h"
#include "JetEngine/Events/Event.h"
#include "JetEngine/Events/ApplicationEvent.h"



namespace JetEngine {

	class JETENGINE_API Application
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

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;
	};

	// To be defined in a client
	Application* CreateApplication();
}

