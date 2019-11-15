#pragma once

#ifdef TEMPEST_EXPORTS
#define TEMPEST_API __declspec(dllexport)
#else
#define TEMPEST_API __declspec(dllimport)
#endif