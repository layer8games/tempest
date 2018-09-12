/*========================================================================
Random number generator. It is based on the c++11 STL random, using the
mersene twist algorithm. 

Has an optional singleton. Unlike most singletons in the engine, Random is
allowed to create other instances. The singleton is there for convience only

RandomInt -> Returns a 32 bit signed it between min and max.

RandomLong -> Returns a 64 bit signed it between min and max. 

RandomFloat -> Returns a random 32 bit floating point between min and max

RandomDouble -> Returns a 64 bit floating point between min and max

RandomVector2 -> Returns a Vector2 with x and y between min and max

RandomVector3 -> Returns a Vector3 with x, y and z between min and max

RandomQuaternion -> Returns a Quaternion with x,y,z and w between min and max

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#pragma once

//===== Engine Includes =====
#include <Engine/Atom.h>
#include <Engine/Vector.h>
#include <Engine/Quaternion.h>

//===== STL includes =====
#include <random>
#include <functional>
#include <ctime>


namespace KillerMath
{
	class Random
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		Random(void);

		~Random(void);

//==========================================================================================================================
//Singleton Option
//==========================================================================================================================
		static shared_ptr<Random> Instance(void);
//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
		S32 RandomInt(S32 min, S32 max);

		S64 RandomLong(S64 min, S64 max);

		F32 RandomFloat(F32 min, F32 max);

		F64 RandomDouble(F64 min, F64 max);

		Vector RandomVector(F32 min, F32 max, bool is2d=false);

		Quaternion RandomQuaternion(F32 min, F32 max);

	private:
		std::mt19937 	  		  _generator;
		static shared_ptr<Random> _instance;
		
	};//end Class
}//end Namespace
