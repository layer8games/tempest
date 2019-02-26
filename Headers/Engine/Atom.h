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

//=====OGL includes=====
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>



//=====STD Includes=====
#include <string>
#include <memory>
using std::shared_ptr;

/*!
	@file Atom.h
	Called Atom because it is the most basic include file. This is the file to be included with all other 
	files that are made. This contains the type definitions that will be the atomic variable types for the 
	KillerEngine (as suggested by Jason Gregory in Game Engine Architecture 2nd Edition). It will also 
	contain the basic header files that every other class or file will need. 
*/

//=====Global usings=====
//template<typename T>
//using shared_prt = std::shared_prt<T>;



//===== Signed typedefs =====

/// Signed, 8 bit integer.
typedef int8_t   S8;

/// Signed, 16 bit integer
typedef int16_t  S16;

/// Signed, 32 bit integer.
typedef int32_t  S32;

///Signed, 64 bit integer.
typedef int64_t  S64;

//===== Unsighed typedefs =====

/// Unsigned, 8 bit integer.
typedef uint8_t  U8;

/// Unsigned, 16 bit integer.
typedef uint16_t U16;

/// Unsigned, 32 bit integer.
typedef uint32_t U32;

/// Unsigned, 64 bit integer.
typedef uint64_t U64;

//===== Floating point typedefs =====

/// 32 bit float point number.
typedef float  F32;

/// 64 bit float point number.
typedef double F64;

/// Using string directly, for convience. 
using std::string;

/// A configurable real number. Currently set to be 32 bits, could be set to 64 bits. 
typedef float real;
//#define DOUBLE_PRECISION

/// Defined as FLT_MAX
#define REAL_MAX FLT_MAX

/// Alias for the sqrt function.
#define real_sqrt sqrt	

/// Alias for the fabsf function.
#define real_abs fabsf

/// Alias for the sin function.
#define real_sin sin

// Alias for the cos funtion.
#define real_cos cos

/// Alias for the tan function. 
#define real_tan tan

/// Alias for the exp function.
#define real_exp exp

/// Alias for the pow function. 
#define real_pow pow

/// Alias for fmod4 function.
#define real_fmod fmod4

// Defined as DBL_EPSILON.
#define real_epsilon DBL_EPSILON

/// Defined as 3.14159265358979.
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
inline F32 RADIAN(F32 angle)
{
	return static_cast<F32>(angle * R_PI / 180.0f);
}

/*!
	Converts a radian to an angle. 
	\param radian is the value to convert. 
*/
inline F32 DEGREE(F32 radian)
{
	return static_cast<F32>(radian * 180.0f / R_PI);
}

/*!
	Clamps a value to a set min and max. 
	\param val is the value to clamp. 
	\param min is the floor.
	\param max is the ceiling.
*/
inline F32 FLOAT_CLAMP(F32 val, F32 min, F32 max)
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

/*!
	Alias set up to allow a refernce to each element of a Vector, Matrix, Quaternion and any
	other type of object that uses an x, y, z and w value. 
*/
enum 
{
	x = 0,
	y = 1,
	z = 2,
	w = 3
};