#pragma once

#ifdef _WIN32
    #ifdef ELYRA_BUILD_DLL
        #define ELYRA_API __declspec(dllexport)
    #else
        #define ELYRA_API __declspec(dllimport)
    #endif
#else
    #define ELYRA_API
#endif