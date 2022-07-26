#pragma once

#define DLLEXP __declspec(dllexport)
    
#define DLLIMP __declspec(dllimport)

#define ASSERT_CORE(x, ...) { if (!(x)) { printf("%s%s\n", "TGEP::ASSERTION FAILED: ", (std::string)__VA_ARGS__); throw std::runtime_error("Assertion failed"); } }
#define ASSERT(x, ...) { if (!(x)) { printf("%s%s\n", "ASSERTION FAILED: ", (std::string)__VA_ARGS__); throw std::runtime_error("Assertion failed"); } }

#define BIND_EVENT_FUNC(func) std::bind(&func, this, std::placeholders::_1)

#define BIT(x) (1 << x)
    
