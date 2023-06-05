#pragma once


#ifdef KS_PLATFORM_WINDOWS

extern Kaiser::Application* Kaiser::CreateApplication();

int main(int argc, char** argv)
{
	Kaiser::Trace::Init();
	KS_CORE_WARN("Initialized Log!");
	KS_INFO("Initialized Log!");
	
	auto app = Kaiser::CreateApplication();
	app->Run();
	delete app;
}

#endif