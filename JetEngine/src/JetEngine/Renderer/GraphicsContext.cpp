#include "JEpch.h"
#include "JetEngine/Renderer/GraphicsContext.h"

#include "JetEngine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace JetEngine {

	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    JE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		JE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
