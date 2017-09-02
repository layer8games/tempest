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

#ifndef ATOM_H
#define ATOM_H

//Includes. These will be the files that everything will need to have access to
//=====Killer1 Engine Includes=====

//=====Windows Includes=====
#include <windows.h>

//=====OGL Includes=====
#include <GL/gl3w.h>



//=====STD Includes=====
#include <string>
#include <memory>

//=====Global usings=====
//template<typename T>
//using shared_prt = std::shared_prt<T>;

//Signed Typedefs
typedef signed __int8   S8;
typedef signed __int16  S16;
typedef signed __int32  S32;
typedef signed __int64  S64;

//Unsigned Typedefs
typedef unsigned __int8  U8;
typedef unsigned __int16 U16;
typedef unsigned __int32 U32;
typedef unsigned __int64 U64;

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
#define R_PI 3.14159265358979


#endif