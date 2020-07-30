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

void Light::SetAmbientColor(const Color& color)
{
    _ambientColor = color;
    ShaderManager::Instance()->SetAllUnformsColorAsVec3("ambient_light_color", _ambientColor);
}

void Light::SetPosition(const TM::Vector3& pos)
{
    _position = pos;
    ShaderManager::Instance()->SetAllUniforms("directional_light_position", _position);
}

void Light::SetSpecularFactor(F32 factor)
{
    _specularFactor = factor;
    ShaderManager::Instance()->SetAllUniforms("specular_factor", _specularFactor);
}

void Light::SetSpecularShine(F32 shine)
{
    _specularShine = shine;
    ShaderManager::Instance()->SetAllUniforms("specular_shine", shine);
}