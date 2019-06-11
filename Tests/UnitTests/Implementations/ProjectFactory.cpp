#include <Boxes/ProjectFactory.h>

using namespace Boxes;
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
ProjectFactory::ProjectFactory(void)
{  }

ProjectFactory::~ProjectFactory(void)
{  }

p_ProjectFactory ProjectFactory::_instance = nullptr;

p_ProjectFactory ProjectFactory::Instance(void)
{
	if(_instance == nullptr)
	{
		_instance = p_ProjectFactory(new ProjectFactory());
	}

	return _instance;
}