#include "JetEngine.h"


class ExampleLayer : public JetEngine::Layer {
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		JE_INFO("ExampleLayer::Update");
	}

	void OnEvent(JetEngine::Event& event) override
	{
		JE_TRACE("{0}", event);
	}
};
class SandBox : public JetEngine::Application
{
public:
	SandBox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new JetEngine::ImGuiLayer());
	}

	~SandBox()
	{
			
	}
};

JetEngine::Application* JetEngine::CreateApplication()
{
	return new SandBox();
}