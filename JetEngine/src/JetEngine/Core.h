#pragma once

#ifdef JE_PLATFORM_WINDOWS
	#ifdef JE_BUILD_DLL
		#define JETENGINE_API __declspec(dllexport)
	#else 
		#define JETENGINE_API __declspec(dllimport)
	#endif
#else
	#error JetEngine only support Windows!
#endif

#ifdef JE_DEBUG
	#define JE_ENABLE_ASSERTS
#endif

#ifdef JE_ENABLE_ASSERTS
	#define JE_ASSERT(x, ...) { if(!(x)) { JE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define JE_CORE_ASSERT(x, ...) { if(!(x)) { JE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define JE_ASSERT(x, ...)
	#define JE_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define JE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)