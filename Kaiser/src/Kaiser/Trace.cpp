#include "stdafx.h"
#include "Trace.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Kaiser
{
	Logger Trace::sCoreLogger;
	Logger Trace::sClientLogger;
}

void Kaiser::Trace::Init()
{
	spdlog::set_pattern("%^[%T] %n: %v%$");

	sCoreLogger = spdlog::stdout_color_mt("Engine");
	sCoreLogger->set_level(spdlog::level::trace);
	
	sClientLogger = spdlog::stdout_color_mt("APP");
	sClientLogger->set_level(spdlog::level::trace);

	KS_CORE_INFO("TraceLog: Initialized Successfully.");
	
}
