/*========================================================================
Demo map to test out the physics functionality of spring-like behaviors
created in the KillerPhysics namespace of the Killer engine

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Level.h>
#include <Engine/FontManager.h>
#include <Engine/Text.h>
#include <Engine/LevelManager.h>
#include <Engine/SpringForce.h>
#include <Engine/AnchoredSpring.h>
#include <Engine/BuoyantForce.h>
#include <Engine/GravityForce.h>
#include <Engine/RigidBody2D.h>
#include <Engine/Vector4.h>
#include <Engine/Point.h>


#include <Boxes/DataBases.h>

namespace KE = KillerEngine;
namespace KP = KillerPhysics;
namespace KM = KillerMath;

namespace Boxes
{
	class Springs : public KE::Level
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================		
		Springs();
		
		~Springs();

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
		void v_Init(void);

		void v_Update(void);

	private:
		KE::Text			_levelTitle;
		KP::GravityForce    _gravity;
		KP::RigidBody2D 		_box1OtherEnd;
		KP::RigidBody2D 		_box1;
		KP::SpringForce     _box1Spring;
		KM::Point			_box2Anchor;
		KP::RigidBody2D 		_box2;
		KP::AnchoredSpring  _box2Spring;
		KP::RigidBody2D 		_box3OtherEnd;
		KP::RigidBody2D 		_box3;
		KP::SpringForce     _box3Spring;
		KP::RigidBody2D 		_box4;
		KP::BuoyantForce    _box4BuoyantForce;
	};
}