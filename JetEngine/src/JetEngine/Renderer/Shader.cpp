#include "JEpch.h"
#include "Shader.h"


#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace JetEngine {

	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		JE_CORE_ASSERT(false, "RenderereAPI::None is currently not supported"); return nullptr;
		case RendererAPI::API::OpenGL:		return  std::make_shared<OpenGLShader>(filepath);
		}

		JE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		JE_CORE_ASSERT(false, "RenderereAPI::None is currently not supported"); return nullptr;
		case RendererAPI::API::OpenGL:		return  std::make_shared<OpenGLShader>(vertexSrc, fragmentSrc);
		}

		JE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}