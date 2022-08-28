#pragma once

#define SET_LOG_COLOR_RED { printf("\033[0;31m"); }
#define SET_LOG_COLOR_BLUE { printf("\033[0;34m"); }
#define SET_LOG_COLOR_GREEN { printf("\033[0;32m"); }
#define RESET_LOG_COLOR { printf("\033[0m"); }

#define LOG(x, ...)   { SET_LOG_COLOR_GREEN printf(x, __VA_ARGS__); RESET_LOG_COLOR}
#define ERROR(x, ...) { SET_LOG_COLOR_RED printf(x, __VA_ARGS__); RESET_LOG_COLOR}
#define WARN(x, ...)  { SET_LOG_COLOR_BLUE printf(x, __VA_ARGS__); RESET_LOG_COLOR}

#define ASSERT_CORE(x, ...) { if (!(x)) {LOG_ERROR("%s%s\n", "TGEP::ASSERTION FAILED: ", __VA_ARGS__); throw std::runtime_error("Assertion failed"); } }
#define ASSERT(x, ...) { if (!(x)) { LOG_ERROR("%s%s\n", "ASSERTION FAILED: ", __VA_ARGS__); throw std::runtime_error("Assertion failed"); } }
