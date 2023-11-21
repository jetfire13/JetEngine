#include "Sandbox2D.h"
#include "imgui/imgui.h" 

#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include <chrono>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{

}

void Sandbox2D::OnAttach()
{
	m_CheckerpoardTexture = JetEngine::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(JetEngine::Timestep ts)
{
	JE_PROFILE_FUNCTION();
	// Update
	m_CameraController.OnUpdate(ts);
	
	// Render
	{
		JE_PROFILE_SCOPE("Renderer Prep");
		JetEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		JetEngine::RenderCommand::Clear();
	}

	{
		JE_PROFILE_SCOPE("Renderer Draw");
		JetEngine::Renderer2D::BeginScene(m_CameraController.GetCamera());

		JetEngine::Renderer2D::DrawQuad({ -0.8f, 0.3f }, 45.0f, { 0.8f, 0.8f }, { 0.3f, 0.2f, 0.8f, 1.0f });
		JetEngine::Renderer2D::DrawQuad({ 0.7f, -0.2f }, 0.0f, { 0.5f, 0.75f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		JetEngine::Renderer2D::DrawQuad({ 0.1f, 0.0f, -0.1f }, 0.0f, { 10.5f, 10.5f }, m_CheckerpoardTexture);

		JetEngine::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	JE_PROFILE_FUNCTION();
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("SquareColor", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(JetEngine::Event& e)
{
	m_CameraController.OnEvent(e);
}