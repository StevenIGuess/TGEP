#pragma once

#ifdef TGEP_PLATFORM_WINDOWS
    #ifdef TGEP_BUILD_DLL
        #define TGEP_API __declspec(dllexport)
    #else
        #define TGEP_API __declspec(dllimport)
    #endif
#endif 