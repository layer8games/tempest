#include "stdafx.h"
#include <Engine/Contact.h>

using namespace TempestPhysics;
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Contact::Contact(void)
:
_contactPoint(),
_collissionNormal(),
_penetrationDepth(),
_collissionRestitution(),
_friction()
{  }

Contact::~Contact(void)
{  }