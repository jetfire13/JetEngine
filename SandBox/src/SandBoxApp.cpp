#include "JetEngine.h"


class ExampleLayer : public JetEngine::Layer {
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (JetEngine::Input::IsKeyPressed(JE_KEY_TAB))
			JE_TRACE("Tab key is pressed!");
	}

	void OnEvent(JetEngine::Event& event) override
	{
		if (event.GetEventType() == JetEngine::EventType::KeyPressed)
		{
			JetEngine::KeyPressedEvent& e = (JetEngine::KeyPressedEvent&)event;
			JE_TRACE("{0}", char(e.GetKeyCode()));
		}
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