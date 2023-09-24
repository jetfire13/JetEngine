#include "JEpch.h"
#include "VertexArray.h"


#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace JetEngine {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		JE_CORE_ASSERT(false, "RenderereAPI::None is currently not supported"); return nullptr;
		case RendererAPI::API::OpenGL:	return new OpenGLVertexArray();
		}

		JE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}