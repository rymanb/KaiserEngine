#pragma once

#include "Kaiser/Core/CrashDump.h"


#ifdef KS_PLATFORM_WINDOWS

extern Kaiser::Application* Kaiser::CreateApplication();

int main(int argc, char** argv)
{
	__try
	{
		Kaiser::Trace::Init();
		Kaiser::CrashDump::Init();


		auto app = Kaiser::CreateApplication();
		app->Run();
		delete app;
	}
	__except (Kaiser::CrashDump::WriteDump(GetExceptionInformation()))
	{


	}
}

#endif