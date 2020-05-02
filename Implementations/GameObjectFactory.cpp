#include "stdafx.h"
#include <Engine/GameObjectFactory.h>

using namespace Tempest;

GameObjectFactory::GameObjectFactory(void)
{  }

GameObjectFactory::~GameObjectFactory(void)
{  }

P_GameObjectFactory GameObjectFactory::_instance = nullptr;

P_GameObjectFactory GameObjectFactory::Instance(void)
{
    if(_instance == nullptr)
    {
        _instance = P_GameObjectFactory(new GameObjectFactory());
    }
    return _instance;
}