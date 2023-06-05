#include <Kaiser.h>

class Sandbox : public Kaiser::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}

	
};

Kaiser::Application* Kaiser::CreateApplication()
{
	return new Sandbox();
}