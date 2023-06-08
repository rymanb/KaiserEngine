#pragma once

//#ifdef KS_PLATFORM_WINDOWS
//	#ifdef KS_BUILD_DLL
//		#define KAISER_API __declspec(dllexport)
//	#else
//		#define KAISER_API __declspec(dllimport)
//	#endif
//
//#endif

#ifdef KS_ENABLE_ASSERTS
	#define KS_ASSERT(x, ..) { if(!(x)) { KS_Error("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define KS_CORE_ASSERT(x, ..) { if(!(x)) { KS_CORE_Error("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define KS_ASSERT(x, ...)
	#define KS_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)