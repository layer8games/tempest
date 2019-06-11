#include <Engine/KillerFactory.h>

using namespace KillerEngine;
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
KillerFactory::KillerFactory(void)
{  }

KillerFactory::~KillerFactory(void)
{  }

P_KillerFactory KillerFactory::_instance = nullptr;

P_KillerFactory KillerFactory::Instance(void)
{
	if(_instance == nullptr)
	{
		_instance = P_KillerFactory(new KillerFactory());
	}
	return _instance;
}