#include <Engine/Random.h>

using namespace KillerMath;

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Random::Random(void) 
: 
_generator(std::time(0))
{  }

Random::~Random(void)
{  }

//==========================================================================================================================
//Singleton optional
//==========================================================================================================================
shared_ptr<Random> Random::_instance = nullptr;

shared_ptr<Random> Random::Instance(void)
{
	if(_instance == nullptr)
	{
		_instance = shared_ptr<Random>(new Random());
	}

	return _instance;
}

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================

S32 Random::RandomInt(S32 min, S32 max)
{
	std::uniform_int_distribution<int> dist(min, max);
	return dist(_generator);
}

S64 Random::RandomLong(S64 min, S64 max)
{
	std::uniform_int_distribution<S64> dist(min, max);
	return dist(_generator);	
}

F32 Random::RandomFloat(F32 min, F32 max)
{
	std::uniform_real_distribution<F32> dist(min, max);
	return dist(_generator);
}

F64 Random::RandomDouble(F64 min, F64 max)
{
	std::uniform_real_distribution<F64> dist(min, max);
	return dist(_generator);
}

Vector2 Random::RandomVector2(F32 min, F32 max)
{
	std::uniform_real_distribution<F32> xVal(min, max);
	std::uniform_real_distribution<F32> yVal(min, max);
	return Vector2(xVal(_generator), yVal(_generator));
}

Vector3 Random::RandomVector3(F32 min, F32 max)
{
	std::uniform_real_distribution<F32> xVal(min, max);
	std::uniform_real_distribution<F32> yVal(min, max);
	std::uniform_real_distribution<F32> zVal(min, max);	
	return Vector3(xVal(_generator), yVal(_generator), zVal(_generator));
}

Quaternion Random::RandomQuaternion(F32 min, F32 max)
{
	std::uniform_real_distribution<F32> xVal(min, max);
	std::uniform_real_distribution<F32> yVal(min, max);
	std::uniform_real_distribution<F32> zVal(min, max);
	std::uniform_real_distribution<F32> wVal(min, max);
	return Quaternion(xVal(_generator), yVal(_generator), zVal(_generator), wVal(_generator));
}