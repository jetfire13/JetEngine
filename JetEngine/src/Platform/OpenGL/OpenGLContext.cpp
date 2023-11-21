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
		JE_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		JE_CORE_ASSERT(status, "Failed to initialize Glad!");

		JE_CORE_INFO("OpenGL Info:");
		JE_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		JE_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		JE_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));

	#ifdef JE_ENABLE_ASSERTS
			int versionMajor;
			int versionMinor;
			glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
			glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

			JE_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "JetEngine requires at least OpenGL version 4.5!");
	#endif
	}

	void OpenGLContext::SwapBuffers()
	{
		JE_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}

}