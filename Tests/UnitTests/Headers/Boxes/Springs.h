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
#include <Engine/Particle.h>
#include <Engine/Vector4.h>
#include <Engine/Point.h>

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
		void v_InitLevel(U32 id, S32 w, S32 h, KE::Color& c);

		void v_Update(void);

	private:
		KE::Text			_levelTitle;
		KP::GravityForce    _gravity;
		KP::Particle 		_box1OtherEnd;
		KP::Particle 		_box1;
		KP::SpringForce     _box1Spring;
		KM::Point			_box2Anchor;
		KP::Particle 		_box2;
		KP::AnchoredSpring  _box2Spring;
		KP::Particle 		_box3OtherEnd;
		KP::Particle 		_box3;
		KP::SpringForce     _box3Spring;
		KP::Particle 		_box4;
		KP::BuoyantForce    _box4BuoyantForce;
	};
}