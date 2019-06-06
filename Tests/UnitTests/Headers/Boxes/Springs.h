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
		void v_Init(void) final;

		void v_Update(void) final;

	private:
		KE::Text			_levelTitle;
		shared_ptr<KP::GravityForce>    _gravity;
		shared_ptr<KP::Particle> 		_box1OtherEnd;
		shared_ptr<KP::Particle> 		_box1;
		shared_ptr<KP::SpringForce>     _box1Spring;
		shared_ptr<KM::Point>			_box2Anchor;
		shared_ptr<KP::Particle> 		_box2;
		shared_ptr<KP::AnchoredSpring>  _box2Spring;
		shared_ptr<KP::Particle> 		_box3OtherEnd;
		shared_ptr<KP::Particle> 		_box3;
		shared_ptr<KP::SpringForce>     _box3Spring;
		shared_ptr<KP::Particle> 		_box4;
		shared_ptr<KP::BuoyantForce>    _box4BuoyantForce;
	};
}