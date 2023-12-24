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
	m_LogoTexture = JetEngine::Texture2D::Create("assets/textures/SomeLogo.png");
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
	JetEngine::Renderer2D::ResetStats();
	{
		JE_PROFILE_SCOPE("Renderer Prep");
		JetEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		JetEngine::RenderCommand::Clear();
	}

	{

		static float roration = 0.0f;
		roration += ts * 50.0f;

		JE_PROFILE_SCOPE("Renderer Draw");
		JetEngine::Renderer2D::BeginScene(m_CameraController.GetCamera());

		JetEngine::Renderer2D::DrawRotatedQuad({ 1.8f, 0.3f }, { 0.8f, 0.8f }, 45.0f, {0.3f, 0.2f, 0.8f, 1.0f});
		JetEngine::Renderer2D::DrawQuad({ 0.7f, -0.2f }, { 0.5f, 0.75f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		JetEngine::Renderer2D::DrawQuad({ -0.2f, 0.0f, 0.1f }, { 0.75f, 0.5f }, { 0.3f, 0.1f, 0.7f, 1.0f });

		JetEngine::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerpoardTexture, 5.0f, {0.2, 0.8, 0.5f, 1.0f});
		//JetEngine::Renderer2D::DrawQuad({ -0.5f, -0.5f, 0.0f }, { 1.0f, 1.0f }, m_LogoTexture, 1.0f, { 0.2, 0.8, 0.5f, 1.0f });
		JetEngine::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.1f }, { 2.5f, 2.5f }, roration, m_CheckerpoardTexture, 5.0f, { 0.5, 0.5, 0.0f, 1.0f });

		JetEngine::Renderer2D::EndScene();
		
		JetEngine::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.f, 0.4f, (y + 5.0f) / 10.f, 0.7f };
				JetEngine::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		JetEngine::Renderer2D::EndScene();
	
	}
}

void Sandbox2D::OnImGuiRender()
{
	JE_PROFILE_FUNCTION();
	ImGui::Begin("Settings");

	auto stats = JetEngine::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());


	ImGui::ColorEdit4("SquareColor", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(JetEngine::Event& e)
{
	m_CameraController.OnEvent(e);
}