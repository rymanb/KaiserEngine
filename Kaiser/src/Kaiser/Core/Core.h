#pragma once

#include <memory>

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

#define KS_BIND_EVENT_FN(fn) std::bind(&##fn, this, std::placeholders::_1)

namespace Kaiser
{



	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
	
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
	

}
