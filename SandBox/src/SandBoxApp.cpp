#include "JetEngine.h"

class SandBox : public JetEngine::Application
{
public:
	SandBox()
	{

	}

	~SandBox()
	{
			
	}
};

JetEngine::Application* JetEngine::CreateApplication()
{
	return new SandBox();
}