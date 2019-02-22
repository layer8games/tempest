/*
  This is filler code, likely to never get used. The Game Physics book
  is very light on the details of what is meant to go into something like
  this. This is a very vague idea to me because of this. I have ordered
  a book that will shed some light on this topic, and when it comes, the
  final version of this code will be writen. 
 */
#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Vector4.h>

namespace KM = KillerMath;

namespace KillerPhysics
{
	class Contact
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		Contact(void);

		~Contact(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
	private:
		KM::Vector4 _contactPoint;
		KM::Vector4 _collissionNormal;
		real 	   _penetrationDepth;
		real 	   _collissionRestitution;
		real 	   _friction;
		
	};//end Class
}//end Namespace
