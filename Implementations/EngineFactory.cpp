#include <Engine/EngineFactory.h>

using namespace Tempest;
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
EngineFactory::EngineFactory(void)
{  }

EngineFactory::~EngineFactory(void)
{  }

P_EngineFactory EngineFactory::_instance = nullptr;

P_EngineFactory EngineFactory::Instance(void)
{
	if(_instance == nullptr)
	{
		_instance = P_EngineFactory(new EngineFactory());
	}
	return _instance;
}