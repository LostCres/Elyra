#include "Elyrapch.hpp"
#include "Log.hpp"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Elyra {

    std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
    std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

    void Log::Init() {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        if (s_ClientLogger)
            return; // Already initialized

        s_CoreLogger = spdlog::stdout_color_mt("ELYRA");
        s_CoreLogger->set_level(spdlog::level::info);

        s_ClientLogger = spdlog::stdout_color_mt("SANDBOX");
        s_ClientLogger->set_level(spdlog::level::trace);
    }

}
