#pragma once

#define DLLEXP 
#define DLLIMP

#define TGEP_LOG // remove during production

#include <string>
#include <stdexcept>
#include <memory>

#ifdef TGEP_LOG
#define SET_LOG_COLOR_RED { printf("\033[0;31m"); }
#define SET_LOG_COLOR_BLUE { printf("\033[0;34m"); }
#define SET_LOG_COLOR_GREEN { printf("\033[0;32m"); }
#define RESET_LOG_COLOR { printf("\033[0m"); }

#define LOG(x, ...)   { SET_LOG_COLOR_GREEN printf(x, __VA_ARGS__); RESET_LOG_COLOR}
#define LOG_ERROR(x, ...) { SET_LOG_COLOR_RED printf(x, __VA_ARGS__); RESET_LOG_COLOR}
#define LOG_WARN(x, ...)  { SET_LOG_COLOR_BLUE printf(x, __VA_ARGS__); RESET_LOG_COLOR}

#define ASSERT_CORE(x, ...) { if (!(x)) {LOG_ERROR("%s%s\n", "TGEP::ASSERTION FAILED: ", __VA_ARGS__); throw std::runtime_error("Assertion failed"); } }
#define ASSERT(x, ...) { if (!(x)) { LOG_ERROR("%s%s\n", "ASSERTION FAILED: ", __VA_ARGS__); throw std::runtime_error("Assertion failed"); } }
#endif //TGEP_LOG

#ifndef TGEP_LOG //Make sure macros are defined
#define SET_LOG_COLOR_RED 
#define SET_LOG_COLOR_BLUE
#define SET_LOG_COLOR_GREEN
#define RESET_LOG_COLOR
#define LOG
#define ERROR
#define WARN 
#define ASSERT_CORE
#define ASSERT
#endif

#define BIND_EVENT_FUNC(func) std::bind(&func, this, std::placeholders::_1)

#define BIT(x) (1 << x)

namespace TGEP {

    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T>
    using Ref = std::shared_ptr<T>;

}

