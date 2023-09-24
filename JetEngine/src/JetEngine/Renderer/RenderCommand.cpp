#include "JEpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace JetEngine {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}