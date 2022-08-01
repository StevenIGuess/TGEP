#pragma once

#define DLLEXP 
    
#define DLLIMP

#include <string>
#include <stdexcept>

#define ASSERT_CORE(x, ...) { if (!(x)) { printf("%s%s\n", "TGEP::ASSERTION FAILED: ", __VA_ARGS__); throw std::runtime_error("Assertion failed"); } }
#define ASSERT(x, ...) { if (!(x)) { printf("%s%s\n", "ASSERTION FAILED: ", __VA_ARGS__); throw std::runtime_error("Assertion failed"); } }

#define BIND_EVENT_FUNC(func) std::bind(&func, this, std::placeholders::_1)

#define BIT(x) (1 << x)
    
