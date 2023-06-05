#pragma once

#include "Core.h"

namespace Kaiser
{
	class KAISER_API Application
	{
	public:
		Application();
		virtual ~Application();


		void Run();
	};

	// client defined function
	Application* CreateApplication();
}

