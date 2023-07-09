#include "JEpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>

#include <glad/glad.h>

namespace JetEngine {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		JE_CORE_ASSERT(windowHandle, "Window Handle is null!!!!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		JE_CORE_ASSERT(status, "Failed to initialize Glad!");

		JE_CORE_INFO("OpenGL Info:");
		JE_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		JE_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		JE_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}