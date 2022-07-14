#pragma once 

#include "pch.h"

#include "Core.h"

namespace TGEP 
{
    class DLLEXP Log
    {
    public:
        static void Init();
        
        inline static std::shared_ptr<spdlog::logger> &GetCoreLogger() {return s_CoreLogger;}
        inline static std::shared_ptr<spdlog::logger> &GetClientLogger() {return s_ClientLogger;}
    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}

//log macros
#ifdef _ENGINE_LOG_MACROS_
#define LOG_CORE_ERROR(...) ::TGEP::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LOG_CORE_WARN(...) ::TGEP::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LOG_CORE_INFO(...) ::TGEP::Log::GetCoreLogger()->info(__VA_ARGS__)
#endif
