/*========================================================================
Call Atom because it is the most basic include file. This is the file
to be included with all other files that are made. This contains the 
type definitions that will be the atomic variable types for the Killer1
Engine (as suggested by Jason Gregory in Game Engine Architecture 2nd 
Edition). It will also contain the basic header files that every other 
class or file will need. 

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#pragma once

//Includes. These will be the files that everything will need to have access to
//=====Killer1 Engine Includes=====

//=====Windows Includes=====
#include <Windows.h>

//=====OGL Includes=====
#include <GL/gl3w.h>



//=====STD Includes=====
#include <string>
#include <memory>
using std::shared_ptr;

//=====Global usings=====
//template<typename T>
//using shared_prt = std::shared_prt<T>;

//Signed Typedefs
typedef int8_t   S8;
typedef int16_t  S16;
typedef int32_t  S32;
typedef int64_t  S64;

//Unsigned Typedefs
typedef uint8_t  U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;

//Floating types
typedef float  F32;
typedef double F64;

//text type 
//typedef std::string string;
using std::string;

typedef float real;
#define DOUBLE_PRECISION
#define REAL_MAX FLT_MAX
#define real_sqrt sqrt	
#define real_abs fabsf
#define real_sin sin
#define real_cos cos
#define real_exp exp
#define real_pow pow
#define real_fmod fmod
#define real_epsilon DBL_EPSILON
const real R_PI = static_cast<real>(3.14159265358979);

//==========================================================================================================================
//Global Helper functions
//==========================================================================================================================
inline real RealSqr(real x)
{
 	return x * x;
}

inline F32 DegreeToRadian(F32 angle)
{
	return static_cast<F32>(angle * R_PI / 180.0f);
}