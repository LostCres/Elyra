#pragma once
#include "Elyra.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Elyra {

    class ELYRA_API Log {
    public:
        static void Init();

        static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };

}

// Logging macros for convenience
#define EL_CORE_TRACE(...)     ::Elyra::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define EL_CORE_INFO(...)      ::Elyra::Log::GetCoreLogger()->info(__VA_ARGS__)
#define EL_CORE_WARN(...)      ::Elyra::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define EL_CORE_ERROR(...)     ::Elyra::Log::GetCoreLogger()->error(__VA_ARGS__)
#define EL_CORE_CRITICAL(...)  ::Elyra::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define EL_TRACE(...)          ::Elyra::Log::GetClientLogger()->trace(__VA_ARGS__)
#define EL_INFO(...)           ::Elyra::Log::GetClientLogger()->info(__VA_ARGS__)
#define EL_WARN(...)           ::Elyra::Log::GetClientLogger()->warn(__VA_ARGS__)
#define EL_ERROR(...)          ::Elyra::Log::GetClientLogger()->error(__VA_ARGS__)
#define EL_CRITICAL(...)       ::Elyra::Log::GetClientLogger()->critical(__VA_ARGS__)

#define EL_ASSERT(x, ...) \
    { if (!(x)) { EL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }

#define EL_TAGGED_CORE_INFO(tag, ...)    EL_CORE_INFO("[" tag "] " __VA_ARGS__)
#define EL_TAGGED_CLIENT_WARN(tag, ...)  EL_WARN("[" tag "] " __VA_ARGS__)
