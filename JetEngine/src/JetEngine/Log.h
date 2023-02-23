#pragma once

#include <memory.h>
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace JetEngine {

	class JETENGINE_API Log
	{
	public:
		static void Init();
		
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

		
		
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define JE_CORE_TRACE(...)  ::JetEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define JE_CORE_INFO(...)	::JetEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define JE_CORE_WARN(...)   ::JetEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define JE_CORE_ERROR(...)  ::JetEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define JE_CORE_FATAL(...)  ::JetEngine::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define JE_TRACE(...)  ::JetEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define JE_INFO(...)   ::JetEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define JE_WARN(...)   ::JetEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define JE_ERROR(...)  ::JetEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define JE_FATAL(...)  ::JetEngine::Log::GetClientLogger()->fatal(__VA_ARGS__)

