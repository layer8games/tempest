#pragma once

//===== Engine Includes =====
#include <Engine/Atom.h>
#include <Engine/Vector4.h>
#include <Engine/Quaternion.h>

//===== STL includes =====
#include <random>
#include <functional>
#include <ctime>


namespace TempestMath
{
//==========================================================================================================================
//Documentation
//=========================================================================================================================
///	Random number generator. It is based on the c++11 STL random, using the
///	mersene twist algorithm. 
///	Has an optional singleton. Unlike most singletons in the engine, Random is
///	allowed to create other instances. The singleton is there for convience only
    class Random
    {
    public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
///	Default constructor. Sets the _generator to the current time, to keep it random. 
        TEMPEST_API Random(void);

///	Default destructor. Doesn't have any function. 
        TEMPEST_API ~Random(void);

//==========================================================================================================================
//Singleton Option
//==========================================================================================================================
///	Basic Singleton pattern. Allows access to global copy. Not required for use. 				
        TEMPEST_API static shared_ptr<Random> Instance(void);
//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
///	Returns a 32 bit signed it between min and max.
///	\param min is the floor value. 
///	\param max is the ceiling value.
        TEMPEST_API S32 RandomInt(S32 min, S32 max);

///	Returns a 64 bit signed it between min and max.
///	\param min is the floor value. 
///	\param max is the ceiling value.
        TEMPEST_API S64 RandomLong(S64 min, S64 max);

///	Returns a random 32 bit floating point between min and max
///	\param min is the floor value. 
///	\param max is the ceiling value.
        TEMPEST_API F32 RandomFloat(F32 min, F32 max);

///	Returns a 64 bit floating point between min and max
///	\param min is the floor value. 
///	\param max is the ceiling value.
        TEMPEST_API F64 RandomDouble(F64 min, F64 max);

///	Returns a Vector4 with x, y and z (depending on flag) between min and max
///	\param min is the floor value. 
///	\param max is the ceiling value.
///	\param is2d determins if the z value should be set. false by default, it will be set to 0 unless true.
        TEMPEST_API Vector4 RandomVector4(real min, real max);

///	Returns a Quaternion with w,x,y and z between min and max
///	\param min is the floor value. 
///	\param max is the ceiling value.
        TEMPEST_API Quaternion RandomQuaternion(real min, real max);

    private:
        std::mt19937 	  		  _generator; ///< STL Mersenne twister engine instance.
        static shared_ptr<Random> _instance;  ///< Pointer to self used for singleton.
    };//end Class
}//end Namespace
