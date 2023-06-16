#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"



typedef std::shared_ptr<spdlog::logger> Logger;

namespace Kaiser
{

	typedef std::shared_ptr<spdlog::logger> Logger;
	
	class Trace
	{
	public:
		static void Init();
		
		inline static Logger& GetCoreLogger() { return sCoreLogger; }
		inline static Logger& GetClientLogger() { return sClientLogger; }

	private:
		static Logger sCoreLogger; // static member variable
		static Logger sClientLogger;
	};
		
	
}

// core
#define KS_CORE_TRACE(...)	::Kaiser::Trace::GetCoreLogger()->trace(__VA_ARGS__)
#define KS_CORE_INFO(...)	::Kaiser::Trace::GetCoreLogger()->info(__VA_ARGS__)
#define KS_CORE_WARN(...)	::Kaiser::Trace::GetCoreLogger()->warn(__VA_ARGS__)
#define KS_CORE_ERROR(...)	::Kaiser::Trace::GetCoreLogger()->error(__VA_ARGS__)
#define KS_CORE_FATAL(...)	::Kaiser::Trace::GetCoreLogger()->critical(__VA_ARGS__)

// client
#define KS_TRACE(...)	::Kaiser::Trace::GetClientLogger()->trace(__VA_ARGS__)
#define KS_INFO(...)	::Kaiser::Trace::GetClientLogger()->info(__VA_ARGS__)
#define KS_WARN(...)	::Kaiser::Trace::GetClientLogger()->warn(__VA_ARGS__)
#define KS_ERROR(...)	::Kaiser::Trace::GetClientLogger()->error(__VA_ARGS__)
#define KS_FATAL(...)	::Kaiser::Trace::GetClientLogger()->critical(__VA_ARGS__)

