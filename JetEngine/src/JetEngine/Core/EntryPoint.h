#pragma once

#ifdef JE_PLATFORM_WINDOWS
	extern JetEngine::Application* JetEngine::CreateApplication();
	int main(int argc, char** argv)
	{
		JetEngine::Log::Init();

		JE_PROFILE_BEGIN_SESSION("Startup", "JetEngineProfile-Startup.json");
		auto app = JetEngine::CreateApplication();
		JE_PROFILE_END_SESSION();

		JE_PROFILE_BEGIN_SESSION("Startup", "JetEngineProfile-Runtime.json");
		app->Run();
		JE_PROFILE_END_SESSION();

		JE_PROFILE_BEGIN_SESSION("Startup", "JetEngineProfile-Shutdown.json");
		delete app;
		JE_PROFILE_END_SESSION();
	}
#elif defined (JE_PLATFORM_LINUX)
	extern JetEngine::Application* JetEngine::CreateApplication();
	int main(int argc, char** argv)
	{
		JetEngine::Log::Init();

		JE_PROFILE_BEGIN_SESSION("Startup", "JetEngineProfile-Startup.json");
		auto app = JetEngine::CreateApplication();
		JE_PROFILE_END_SESSION();

		JE_PROFILE_BEGIN_SESSION("Startup", "JetEngineProfile-Runtime.json");
		app->Run();
		JE_PROFILE_END_SESSION();

		JE_PROFILE_BEGIN_SESSION("Startup", "JetEngineProfile-Shutdown.json");
		delete app;
		JE_PROFILE_END_SESSION();
	}
#endif