#pragma once

//===== Engine Includes =====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/Vector4.h>
#include <Engine/Quaternion.h>

//===== STL includes =====
#include <random>
#include <functional>
#include <ctime>


namespace TempestMath
{
    class Random
    {
    public:

        TEMPEST_API Random(void);

        TEMPEST_API ~Random(void);

        TEMPEST_API static shared_ptr<Random> Instance(void);

        TEMPEST_API S32 RandomInt(S32 min, S32 max);

        TEMPEST_API S64 RandomLong(S64 min, S64 max);

        TEMPEST_API F32 RandomFloat(F32 min, F32 max);

        TEMPEST_API F64 RandomDouble(F64 min, F64 max);

        TEMPEST_API Vector4 RandomVector4(real min, real max);

        TEMPEST_API Quaternion RandomQuaternion(real min, real max);

    private:
        std::mt19937 	  		  _generator;
        static shared_ptr<Random> _instance; 
    };//end Class
}//end Namespace
