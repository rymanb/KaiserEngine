#pragma once

#ifdef KS_PLATFORM_WINDOWS

extern Kaiser::Application* Kaiser::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Kaiser::CreateApplication();
	app->Run();
	delete app;
}

#endif