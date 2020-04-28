#pragma once

#ifdef TEMPEST_EXPORTS
#define TEMPEST_API __declspec(dllexport)
#else
#define TEMPEST_API __declspec(dllimport)
#endif

#include "stdafx.h"

//=====OGL includes=====
#define GLEW_STATIC




typedef int8_t   S8;
typedef int16_t  S16;
typedef int32_t  S32;
typedef int64_t  S64;
typedef uint8_t  U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;
typedef float  F32;
typedef double F64;

typedef float real;

#define REAL_MAX FLT_MAX
#define real_sqrt sqrtf	
#define real_abs fabsf
#define real_sin sinf
#define real_cos cosf
#define real_tan tanf
#define real_atan atanf
#define real_atan2 atan2f
#define real_exp expf
#define real_pow powf
#define real_fmod fmod4
#define real_epsilon DBL_EPSILON
const real R_PI = static_cast<real>(3.14159265358979);

//==========================================================================================================================
//Global Helper functions
//==========================================================================================================================
/*!
    Returns the value squared.
    \param x is the value.
*/
inline real REAL_SQR(real x)
{
    return x * x;
}

/*!
    Converts an angle to a radian.
    \param angle is the value to convert.
*/
inline real RADIAN(real angle)
{
    return static_cast<real>(angle * R_PI / 180.0f);
}

/*!
    Converts a radian to an angle. 
    \param radian is the value to convert. 
*/
inline real DEGREE(real radian)
{
    return static_cast<real>(radian * 180.0f / R_PI);
}

/*!
    Clamps a value to a set min and max. 
    \param val is the value to clamp. 
    \param min is the floor.
    \param max is the ceiling.
*/
inline real REAL_CLAMP(real val, real min, real max)
{
    if(val < min)
    {
        return min;
    }
    else if(val > max)
    {
        return max;
    }
    else
    {
        return val;
    }
}