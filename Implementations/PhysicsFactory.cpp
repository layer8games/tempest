#include "stdafx.h"
#include <Engine/PhysicsFactory.h>
using namespace TempestPhysics;

PhysicsFactory::PhysicsFactory(void)
{  }

PhysicsFactory::~PhysicsFactory(void)
{  }

P_PhysicsFactory PhysicsFactory::_instance = nullptr;

P_PhysicsFactory PhysicsFactory::Instance(void)
{
    if(_instance == nullptr)
    {
        _instance = P_PhysicsFactory(new PhysicsFactory());
    }
    return _instance;
}