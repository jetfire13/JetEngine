#pragma once

#include "Core.h"

#include "Window.h"
#include "JetEngine/LayerStack.h"
#include "JetEngine/Events/Event.h"
#include "JetEngine/Events/ApplicationEvent.h"

#include "JetEngine/ImGui/ImGuiLayer.h"

#include "JetEngine/Renderer/Shader.h"
#include "JetEngine/Renderer/Buffer.h"
#include "JetEngine/Renderer/VertexArray.h"


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

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVA;
	private:
		static Application* s_Instance;
	};

	// To be defined in a client
	Application* CreateApplication();
}

