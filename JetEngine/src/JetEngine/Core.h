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

#define BIT(x) (1 << x)
