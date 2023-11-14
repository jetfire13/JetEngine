#pragma once

#include "JetEngine.h"

class Sandbox2D : public JetEngine::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(JetEngine::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(JetEngine::Event& e) override;
private:
	JetEngine::OrthographicCameraController m_CameraController;
	
	// Temp
	JetEngine::Ref<JetEngine::VertexArray> m_SquareVA;
	JetEngine::Ref<JetEngine::Shader> m_FlatColorShader;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};