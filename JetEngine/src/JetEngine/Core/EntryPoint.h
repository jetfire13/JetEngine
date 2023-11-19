#pragma once

#ifdef JE_PLATFORM_WINDOWS
	extern JetEngine::Application* JetEngine::CreateApplication();
	int main(int argc, char** argv)
	{
		JetEngine::Log::Init();
		JE_CORE_WARN("Initialized Log!");
		int a = 5;
		JE_INFO("Hello! var = {0}", a);

		auto app = JetEngine::CreateApplication();
		app->Run();
		delete app;
	}
#endif