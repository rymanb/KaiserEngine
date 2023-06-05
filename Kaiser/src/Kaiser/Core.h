#pragma once

#ifdef KS_PLATFORM_WINDOWS
	#ifdef KS_BUILD_DLL
		#define KAISER_API __declspec(dllexport)
	#else
		#define KAISER_API __declspec(dllimport)
	#endif

#endif