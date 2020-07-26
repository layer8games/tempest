#include "stdafx.h"
#include <Engine/Light.h>

using namespace Tempest;

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Light::Light(void)
    :
    _ambientColor(1.0f),
    _position(0.0f),
    _specularFactor(0.5f),
    _specularShine(100.0f)
{  }

Light::~Light(void)
{  }