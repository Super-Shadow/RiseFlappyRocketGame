#pragma once

#include <memory>

#ifdef RS_PLATFORM_WINDOWS
#if RS_DYNAMIC_LINK
	#ifdef RS_BUILD_DLL
		#define RISE_API __declspec(dllexport)
	#else
		#define RISE_API __declspec(dllimport)
	#endif
#else
	#define RISE_API
#endif
#else
	#error Rise only supports Windows!
#endif

#ifdef RS_DEBUG
	#define RS_ENABLE_ASSERTS
#endif

#ifdef RS_ENABLE_ASSERTS
	#define RS_ASSERT(x, ...) { if(!(x)) { RS_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define RS_CORE_ASSERT(x, ...) { if(!(x)) { RS_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define RS_ASSERT(x, ...)
	#define RS_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << (x))

#define RS_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Rise
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T>
	using Ref = std::shared_ptr<T>;
}
