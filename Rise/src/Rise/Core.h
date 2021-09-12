#pragma once

#ifdef RS_PLATFORM_WINDOWS
#ifdef RS_BUILD_DLL
#define RISE_API __declspec(dllexport)
#else
#define RISE_API __declspec(dllimport)
#endif
#else
#error Rise only supports Windows!
#endif
