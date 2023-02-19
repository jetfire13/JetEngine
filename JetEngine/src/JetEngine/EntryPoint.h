#pragma once

#ifdef JE_PLATFORM_WINDOWS
extern JetEngine::Application* JetEngine::CreateApplication();
int main(int argc, char** argv)
{
	auto app = JetEngine::CreateApplication();
	app->Run();
	delete app;
}
#endif