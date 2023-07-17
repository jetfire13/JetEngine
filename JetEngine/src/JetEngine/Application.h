#pragma once

#include "Core.h"

#include "Window.h"
#include "JetEngine/LayerStack.h"
#include "JetEngine/Events/Event.h"
#include "JetEngine/Events/ApplicationEvent.h"

#include "JetEngine/ImGui/ImGuiLayer.h"

#include "JetEngine/Renderer/Shader.h"
#include "JetEngine/Renderer/Buffer.h"



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
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray;

		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	private:
		static Application* s_Instance;
	};

	// To be defined in a client
	Application* CreateApplication();
}

