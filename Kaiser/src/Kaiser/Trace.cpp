#include "stdafx.h"
#include "Trace.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Kaiser
{
	Logger Trace::s_CoreLogger;
	Logger Trace::s_ClientLogger;
}

void Kaiser::Trace::Init()
{
	spdlog::set_pattern("%^[%T] %n: %v%$");

	s_CoreLogger = spdlog::stdout_color_mt("Engine");
	s_CoreLogger->set_level(spdlog::level::trace);
	
	s_ClientLogger = spdlog::stdout_color_mt("APP");
	s_ClientLogger->set_level(spdlog::level::trace);

	KS_CORE_INFO("TraceLog: Initialized Successfully.");
	
}
