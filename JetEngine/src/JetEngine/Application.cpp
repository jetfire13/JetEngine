#include "Application.h"

#include "JetEngine/Events/ApplicationEvent.h"
#include "JetEngine/Log.h"


namespace JetEngine {

	Application::Application()
	{
	}


	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		JE_TRACE(e);

		while (true);
	}
}