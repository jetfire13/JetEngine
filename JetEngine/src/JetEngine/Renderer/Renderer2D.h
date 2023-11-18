#pragma once

#include "OrthographicCamera.h"

namespace JetEngine {

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown(); 

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		// Privitives
		static void DrawQuad(const glm::vec2& position, float rotation, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, float rotation, const glm::vec2& size, const glm::vec4& color);
	};
}